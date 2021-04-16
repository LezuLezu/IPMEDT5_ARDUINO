#include "Wire.h"
#include "SFE_BMP180.h"
#include <Servo.h>

SFE_BMP180 bmp180;
Servo myservo;
Servo myservo2;

int pos = 0;    //posititie van de motor
bool window_open = false;   //status van het raam (of hij open of dicht is)
bool heating_on = false;    //status van de verwarming (of hij aan of uit staat)

String incoming = "";   //data die van de pi wordt gestuurd naar de arduino

void setup() {
  Serial.begin(9600);
  bool success = bmp180.begin();

  //connecten met de motoren
  myservo.attach(9);
  myservo2.attach(10);

}

void loop() {
  String incoming = "";
  char status;
  double T, P;
  bool success = false;

  //meten luchtdruk
  status = bmp180.startTemperature();

  if (status != 0) {
    delay(1000);
    status = bmp180.getTemperature(T);

    if(status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) {
          Serial.print("P");
          Serial.println(P);  //printen van bijvoorbeeld P1035
        }
      }
    }
  }

  //lezen van serial
  while(Serial.available() > 0) {
    const int incoming_byte = Serial.read() - '0';  //incoming byte omzetten naar int om mee te werken
    Serial.print("S");
    Serial.println(incoming_byte);

    //het getallen die binnenkomen achter elkaar plakken in een string
    switch(incoming_byte) {
    case 0:
      incoming = incoming + '0';
      break;
    case 1:
      incoming = incoming + '1';
      break;
    case 2:
      incoming = incoming + '2';
      break;
    case 3:
      incoming = incoming + '3';
      break;
    case 4:
      incoming = incoming + '4';
      break;
    case 5:
      incoming = incoming + '5';
      break;
    case 6:
      incoming = incoming + '6';
      break;
    case 7:
      incoming = incoming + '7';
      break;
    case 8:
      incoming = incoming + '8';
      break;
    case 9:
      incoming = incoming + '9';
      break;
    }
  }

  int gewenste_luchtdruk = incoming.toInt();  //String met binnengekomen getallen omzetten naar int
  if(gewenste_luchtdruk != 0){
    Serial.print("G");
    Serial.println(gewenste_luchtdruk);

    //het raam open of dicht doen en de verwarming aan of uit doen 
    //op basis van de gewenste luchtdruk die is gegeven
    if(P <= gewenste_luchtdruk && window_open == false) {
      open();
      window_open = true;
      Serial.print("W");
      Serial.println("open");
      Serial.print("H");
      Serial.println("off");
      delay(1000); 
    } else if(P > gewenste_luchtdruk && window_open == true) {
      close();
      window_open = false;
      Serial.print("W");
      Serial.println("closed");
      Serial.print("H");
      Serial.println("on");
      delay(1000);
    }
  }

  //status van het raam en de verwarming printen als het veranderd
  if(window_open == true) {
      Serial.print("W");
      Serial.println("open");
      Serial.print("H");
      Serial.println("off");
  } else if(window_open == false) {
      Serial.print("W");
      Serial.println("closed");
      Serial.print("H");
      Serial.println("on");
  }

  Serial.flush(); //serial refreshen zodat er geen bytes meer in de wacht staan
}

//functie om motoren te laten draaien om raam open te zetten en verwarming uit
void open() {
  myservo.write(180);
  delay(400);
  myservo.write(90);

  myservo2.write(180);
  delay(1000);
  myservo2.write(90);
}

//functie om motoren te laten draaien om raam dicht te trekken en verwarming aan te zetten
void close() {
    myservo.write(0);
    delay(400);
    myservo.write(90);

    myservo2.write(0);
    delay(1000);
    myservo2.write(90);
}
