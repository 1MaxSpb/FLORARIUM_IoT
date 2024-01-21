#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <MCP3221.h>
#include <Adafruit_MCP9808.h>
/////////////////// SETTINGS /////////////////////////////

// Wi-Fi
const char* ssid = "********";
const char* password = "********";

// MQTT
const char* mqtt_server = "xx.wqtt.ru";
const int mqtt_port = 1234;
const char* mqtt_user = "****";
const char* mqtt_password = "****";

// SENSOR
const int sending_period = 5;
const bool retain_flag = false;
const char* temperature_topic = "temperature";
const char* humidity_topic = "humidity";
MCP3221 mcp3221_5(0x49); // Адрес может отличаться(также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

int a = 2248; // масштабирование значений
int b = 1165;
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

/////////////////////////////////////////////////////////


WiFiClient espClient;
PubSubClient client(espClient);

uint32_t tmr1;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32-" + WiFi.macAddress();
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password) ) {
      Serial.println("connected");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void sendData() {
  tempsensor.wake();
  float t1 = tempsensor.readTempC();
  float h1 = mcp3221_5.getData();
  h1 = map(h1, a, b, 0, 100);
  Serial.println(h1);
  Serial.println(t1);

  client.publish(temperature_topic, String(t1).c_str(), retain_flag);
  client.publish(humidity_topic, String(h1).c_str(), retain_flag);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mcp3221_5.setAlpha(DEFAULT_ALPHA);
  mcp3221_5.setNumSamples(DEFAULT_NUM_SAMPLES);
  mcp3221_5.setSmoothing(ROLLING_AVG);
  
  if (!tempsensor.begin(0x18))
  {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  tempsensor.setResolution(3);


  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - tmr1 >= (sending_period * 1000)) {
    tmr1 = millis();
    sendData();
  }
}