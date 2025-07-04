
#include "RTClib.h"

RTC_DS3231 rtc;


void setup () {
  Serial.begin(9600);

  if (! rtc.begin()) {    
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {   
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
}

void loop () {
  // Get the current time from the RTC
  DateTime now = rtc.now();  
 
  String hourStr = (now.hour() < 10 ? "0" : "") + String(now.hour(), DEC); 
  String minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
  String secondStr = (now.second() < 10 ? "0" : "") + String(now.second(), DEC);
  float temp = rtc.getTemperature();
  String fridgeTemp;
  fridgeTemp = String(temp);  
  String formattedTime =  hourStr + ":" + minuteStr + ":" + secondStr + ",  " + fridgeTemp;

  Serial.println(formattedTime);

 
  delay(3000);
}
