
#include "DHT.h"

#define DHTPIN 2 //de pin die gebruikt word voor de temperatuur sensor
const int LEDROOD = 8; //de pin die gebruikt word voor de led
const int LEDGROEN = 9; //de pin die gebruikt word voor de led

#define DHTTYPE DHT11 

//initaliseerd de sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  //set up van de verschillende pins
  pinMode(LEDROOD, OUTPUT);
  pinMode(LEDGROEN, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //een paar seconde wachten tussen metingen
  delay(2000);
  //de temperatuur lezen in celsius
  float c = dht.readTemperature();

  //geef een error als er geen temperatuur gelezen kan worden
  if (isnan(c)) {
    Serial.println("Er kan geen temperatuur gemeten worden!");
    return;
  }

  //print de temperatuur naar de console
  Serial.println(c);

  //als het te koud is brand er een rood lampje
  if(c <= 17){
     digitalWrite(LEDGROEN, LOW); 
     digitalWrite(LEDROOD, HIGH); 
  }
  //als de temperatuur goed is brand er een groen lampje
  if(c >= 18 && c <= 21){
     digitalWrite(LEDGROEN, HIGH); 
     digitalWrite(LEDROOD, LOW); 
  }
  //als het te warm is brand er een rood lampje
  if(c >= 21){
     digitalWrite(LEDGROEN, LOW); 
     digitalWrite(LEDROOD, HIGH); 
  }
}
