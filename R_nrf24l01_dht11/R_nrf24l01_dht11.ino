#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h> 

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
RF24 radio(9, 10);
struct MyData {
  byte h; 
  byte t;
};
MyData data;
void setup()
{
  Serial.begin(9600); 
  radio.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();
  //lcd.println("Receiver ");
}
void recvData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));
    }
}
void loop()
{
  recvData();
  Serial.print("Humidity: ");
  Serial.print(data.h);
  lcd.setCursor(0,0);
  lcd.print("Humidity:"); 
  lcd.print(data.h);
  lcd.print("%");
  lcd.setCursor(0,1);
  Serial.print("Temperature: ");
  Serial.print(data.t);
  lcd.print("Temperature:");
  lcd.print(data.t);
  lcd.print(" C");  
  //Serial.print("\n");
}
