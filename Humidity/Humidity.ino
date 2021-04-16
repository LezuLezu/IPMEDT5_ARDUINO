#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include <dht11.h>
#define DHT11PIN 2
dht11 DHT11;


hd44780_I2Cexp lcd;

const int LCD_COLS = 16;
const int LCD_ROWS = 2;
int verstuur = 29;
//eens per minuut op het moment (doel, 10 minuten, voor weergave tijdens presentatie op 1 minuut laten staan. anders is het niet te laten zien)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  lcd.begin(LCD_COLS, LCD_ROWS);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lees = DHT11.read(DHT11PIN);
  int hum = DHT11.humidity;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: " + String(hum) + "%");

  //leeghalen van tweede lijn op LCD display om status weer te geven uit IF statement
  lcd.setCursor(0, 1);
  lcd.print ("                ");
  lcd.setCursor(0, 1);

  //weergave van status per verschillende hoogten in luchtvochtigheid
  if(hum >= 60){
    lcd.print("It's too high!");
    
  } else if(hum >= 55 && hum < 60){
    lcd.print("It's high");

  } else if(hum >= 45 && hum < 55){
    lcd.print("It's normal");
    
  } else if(hum >= 40 && hum < 45){
    lcd.print("It's low");

  } else if(hum < 40){
    lcd.print("It's too low!");
  }
  
  verstuur += 1;

  //eens per minuut nu verzenden van informatie naar de database
  if(verstuur == 30){
    Serial.println(hum);
    verstuur = 0;
  }
  delay(2000);

}
