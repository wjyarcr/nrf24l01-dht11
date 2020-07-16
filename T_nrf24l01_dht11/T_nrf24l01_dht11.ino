#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
#define DHTPIN 2
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal_I2C.h> // library i2c
LiquidCrystal_I2C lcd(0x27,16,2);
RF24 radio(9, 10); //  CN and CSN  pins of nrf
struct MyData {
  byte h;
  byte t;
};
MyData data;
void setup()
{
   lcd.init();                       // initialize the lcd
 lcd.init();
 lcd.backlight(); 
  Serial.begin(9600); 
  dht.begin();
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
}
void loop()
{
  data.h = dht.readHumidity();
  data.t = dht.readTemperature();
  if (isnan(data.h) || isnan(data.t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
   lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(data.h);
   lcd.setCursor(0,1);
  lcd.print("Temperature: ");
  lcd.print(data.t);
  radio.write(&data, sizeof(MyData));
}

 
