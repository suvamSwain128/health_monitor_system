#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

char auth[] = "4X3sM0gYDQmB6ZuAuo_zhvMK8jmdc_4F";

char ssid[] = "ZONG MBB-E8231-6E63";
char pass[] = "janikhan1";

SimpleTimer timer;

String myString;
char rdata; // received characters

String firstVal, secondVal,thirdVal; // sensors 

void myTimerEvent()
{
  Blynk.virtualWrite(V1, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,sensorvalue1); 
}

void loop()
{
   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {

String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2);
 


firstVal = l;
secondVal = m;
thirdVal = n;

  myString = "";
// end new code
    }
  }

}

void sensorvalue1()
{
  Blynk.virtualWrite(V3, firstVal);
  Blynk.virtualWrite(V4, secondVal);
}


String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index 
