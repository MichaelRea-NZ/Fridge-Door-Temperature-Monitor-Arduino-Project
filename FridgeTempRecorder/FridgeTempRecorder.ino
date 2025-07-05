#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS3231 rtc;
File fridgeFile;
int lightReading = A0;
int lightValue;
bool doorChanged = false;
String doorState;
String hourStr;
String minuteStr;
String secondStr;
float temp;
String fridgeTemp;
String formattedTime;
String info;

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(lightReading, INPUT);
  Serial.begin(9600);
// The below while loop is only ment to run while the USB is connected. If the USB is not connected the loop can cause faulty output.
// while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
//Serial.print is only used for testing so they are commented out while the board is running on battery. 
//  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
//    Serial.println("initialization failed!");
   while (1);
  }
//  Serial.println("initialization done.");  

   if (! rtc.begin()) {    
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {   
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
}

void loop() {
  // nothing happens after setup
  lightValue = analogRead(lightReading);
  DateTime now = rtc.now();   
  hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC); 
  minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
  secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);
  temp = rtc.getTemperature();
  fridgeTemp = String(temp);  
  formattedTime  =  hourStr + ":" + minuteStr + ":" + secondStr ;

  if(lightValue > 200 && !doorChanged){   
    fridgeFile = SD.open("fridge.csv", FILE_WRITE);
    doorState = "Open ";
    info = formattedTime + ",  " + fridgeTemp + ", ";
    //info = doorState + ", " + lightValue;
    //Serial.print(info);    
    if (fridgeFile) {
      fridgeFile.print(info);     
    }
    doorChanged = true;
  }
  else if(lightValue < 200 && doorChanged){    
    doorState = " Closed ";
    //info = doorState + ", " + lightValue;
    info = formattedTime + ",  " + fridgeTemp;
    //Serial.println(info);   
   if (fridgeFile) {
      fridgeFile.println(info);
      fridgeFile.close();
    }
    doorChanged = false;
  }
}
