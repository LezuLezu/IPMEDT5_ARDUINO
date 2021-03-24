//Source Dust code https://create.arduino.cc/projecthub/infoelectorials/project-010-arduino-grove-dust-sensor-ppd42ns-project-ab5f5e

int pin = 8;
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
}

void loop() {
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
}
