# Фларариум с подключением к Алисе через wqtt.ru

- FLORARIUM-IoT-MGS-THI50.ino - скетч для работы с сервисом wqtt.ru
- MGS-THI50_test.ino - скетч для проверки компонентов
- MGS-THI50EN_auto_I2Caddr.ino - пример скетча c автоматическим определением I2C адреса
- Adafruit_MCP9808_Library-master.zip - библиотека для работы в Arduino IDE
- Adafruit_MCP9808_Library-master.zip - библиотека для работы в Arduino IDE
- Adafruit_MCP9808_Library-master.zip - библиотека для работы в Arduino IDE
- PubSubClient.rar - библиотека для работы в Arduino IDE
  

# Компаненты:

|№|Компоненет |Кол-во|
| ----------- | -----------|-----------|
|1|Контроллер «ЙоТик 32А»|1 шт.|
|2|Датчик температуры и влажности почвы цифровой с I2C MGS-THI50 |1 шт|
|3|Плата расширения RJ-9 MGB-I2C63 |1 шт|
|4|Провода RJ-9 ИЛИ Провода "Мама -> Папа" |1 шт ИЛИ 4 шт (соответствено)|
|5|Конструкция для флорариума|1 шт|

# Инструкция по програмированию:

В разработке
- 1 Зарегистрируетесь на [wqtt.ru](https://dash.wqtt.ru/account/)

 <img src="https://i.imgur.com/6l6TWX0.jpg">

 - 2 Зайдите в раздел Брокер 

<img src="https://imgur.com/38u80Wz.jpg">

- 3 В начале кода укажите данные из брокера

> [!WARNING]
> Не забуте поменять порт в прошивке на ваш

```
const char* mqtt_server = "xx.wqtt.ru"; //Адрес
const int mqtt_port = 1234; //порт (у вас скорее другой)
const char* mqtt_user = "****"; //Пользователь
const char* mqtt_password = "****"; //Пароль
```
<img src="https://imgur.com/GCz0EJS.jpg">

- 4 Загрузите прошивку на плату
- 5 Проверьте во вкладке *WebSocket клиент* наличие топиков *humidity* и *temperature*
