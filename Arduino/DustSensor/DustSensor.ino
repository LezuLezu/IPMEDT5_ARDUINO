//Source Dust code https://create.arduino.cc/projecthub/infoelectorials/project-010-arduino-grove-dust-sensor-ppd42ns-project-ab5f5e

//Pin layout
//Sensor
int pin = 8; 

//Led's
const int LED_GREEN = 2;
const int LED_YELLOW = 3;
const int LED_RED = 4;

// switch case variables
int data = 0;
char object = ' ';

//Variables decleration for sensor
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000; //Orignal sample time: 2000

unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0; 

float m3 = 0.0283168466; //To calculate cubicmetre

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  starttime = millis(); 

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
//  Loop code for measurements
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms) //if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  
    concentration = (1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62)* m3; 
    String measurement = (String(concentration) + " \t ug/m^3");  //micro gram per kubic metre
    Serial.println(measurement);
    lowpulseoccupancy = 0;
    starttime = millis();
  }

//  Loop code for LED indications
  while (Serial.available() > 0){
    data = Serial.read();
  }
  switch(data){
    case 'g':
      // When input is for green, fine levels of dust
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
      break;
    case 'y':
      // When input is for yellow, moderate levels of dust
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, HIGH);
      digitalWrite(LED_RED, LOW);
      break;
    case 'r':
      // When input is for red, high levels of dust
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, HIGH);  
      break;
    default:
//    Default states
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);


        
  }  
}
