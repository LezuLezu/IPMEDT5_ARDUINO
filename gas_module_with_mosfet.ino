#include <Servo.h>

Servo myServo;
int servoPin = 9;
bool windowOpen = false;

int sensorPin = A0;  
int sensorValue = 0;
const int BUZZER = 2;
const int LEDGREEN = 5;
const int LEDYELLOW = 3;
const int LEDRED = 4;

int data = 0;
char object = ' ';

void setup() {
  myServo.attach(servoPin);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDYELLOW, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);  
}
  
void loop() { 
//  while(Serial.available() > 0){
//    data = Serial.read();
//    
//    switch(data){
//    case 'b':
//      object = 'b';
//      break;   
////    case '1':
////      if(object == 'b'){            //switch voor meerder actuatoren
////        digitalWrite(LEDYELLOW, HIGH);
////        analogWrite(BUZZER, 30);
////      }
////      break;
//    case '0':
//      if(object == 'b'){          //TO STOP THE BUZZER ONLINE BUT WASN'T NECESSARY
//        analogWrite(BUZZER, 0);
//      }
//      break;
//    }
//  }

  myServo.detach();
  
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(60000);           
 // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);
 // we need to read the sensor at 5V, but must not let it heat up. So hurry!  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay (50); //don't know how long to wait without heating up too much. Getting an analog read apparently takes 100uSec  
 
  sensorValue = analogRead(sensorPin);  
  Serial.println(sensorValue);

  //  GOOD VALUE
  if(sensorValue < 200){
    digitalWrite(LEDGREEN, HIGH);
  }
  else{
    digitalWrite(LEDGREEN, LOW);
  }
  

  //IF CO TO HIGH THAN LED YELLOW ON WINDOW OPEN
  if(sensorValue >= 200 && sensorValue < 800){
    digitalWrite(LEDYELLOW, HIGH);
    myServo.attach(servoPin);

    if(windowOpen == false){
      windowOpen = true;
      myServo.write(80); 
      delay(2100);        //WINDOW OPEN
    } 
    myServo.detach(); 
  }

  else{
    digitalWrite(LEDYELLOW, LOW);
  }

  //IF CO TO HIGH THAN BUZZER MAKES ALARMING SOUND AND WINDOW OPEN
  if(sensorValue >= 800){
    digitalWrite(LEDRED, HIGH);
    analogWrite(BUZZER, 30);
    myServo.attach(servoPin);
    
    if(windowOpen == false){
      windowOpen = true;
      myServo.write(80); 
      delay(2100);        //WINDOW OPEN
    }
    
    myServo.detach(); 
  }
  
  else{
    digitalWrite(LEDRED, LOW);
    analogWrite(BUZZER, 0);
  }
} 
 
