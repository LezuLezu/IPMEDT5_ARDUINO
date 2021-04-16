#include <Servo.h>

Servo myServo;
int servoPin = 9;
bool windowOpen = false;

int sensorPin = A0;  
int sensorValue = 890;    //change here the value for the monoxide measurement
const int BUZZER = 2;
const int LEDGREEN = 5;
const int LEDYELLOW = 3;
const int LEDRED = 4;

int data = 0;
char object = ' ';

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDYELLOW, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  while(Serial.available() > 0){
    data = Serial.read();
    
    switch(data){
    case 'b':
      object = 'b';
      break;   
//    case '1': 
//      if(object == 'b'){            //switch voor meerder actuatoren
//        digitalWrite(LEDYELLOW, HIGH);
//        analogWrite(BUZZER, 30);
//      }
//      break;
    case '0':
      if(object == 'b'){
        analogWrite(BUZZER, 0);
      }
      break;
    }
  }

  myServo.detach();

  Serial.println(sensorValue);
  delay(1000);

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
  
  //IF CO TO HIGH THAN BUZZER MAKES ALARMING SOUND
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
