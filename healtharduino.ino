#define USE_ARDUINO_INTERRUPTS true  
#include <PulseSensorPlayground.h>     
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
SoftwareSerial nodemcu(2,3);



const int PulseWire = 0;       
const int LED13 = 13;         
int Threshold = 550;          
                               
PulseSensorPlayground pulseSensor;  



// for ds18b20 temperature sensor

#define ONE_WIRE_BUS 4 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 float Celcius=0;
 float Fahrenheit=0;

String cdata; // complete data
int sdata1 = 0; 
int sdata2 = 0;

char buff[10];
String tempc; 
String tempf;
void setup() {   

  Serial.begin(9600);          
  nodemcu.begin(9600);
  
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);      
  pulseSensor.setThreshold(Threshold);   

   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  
  }
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  
                                              
if (pulseSensor.sawStartOfBeat()) {           
Serial.println(myBPM); 
}
delay(20);
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Fahrenheit=sensors.toFahrenheit(Celcius);

//TEMPERATURE SENSOR 

 tempc = dtostrf(Celcius, 3, 2, buff);
  tempf = dtostrf(Fahrenheit, 3, 2, buff);

   cdata = cdata + tempc+","+tempf +","+myBPM; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   blue.println("Patient Monitoring."); 
   blue.println(cdata);
delay(20);
   cdata = "";   
}
