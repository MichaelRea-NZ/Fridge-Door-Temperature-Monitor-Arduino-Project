#include <SPI.h>
#include <SD.h>


File fridgeFile;

int lightReading = A0;
int lightValue;
bool doorChanged = false;
String doorState;

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(lightReading, INPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");  
}

void loop() {
  // nothing happens after setup
  lightValue = analogRead(lightReading);

  if(lightValue > 200 && !doorChanged){   
    fridgeFile = SD.open("test.txt", FILE_WRITE);
    doorState = "Open ";
    String info = doorState + ", " + lightValue + ", ";
    Serial.print(info);    
    if (fridgeFile) {
      fridgeFile.print(info);     
    }
    doorChanged = true;
  }
  else if(lightValue < 200 && doorChanged){    
    doorState = "Closed ";
    String info = doorState + ", " + lightValue;
    Serial.println(info);   
   if (fridgeFile) {
      fridgeFile.println(info);
      fridgeFile.close();
    }
    doorChanged = false;
  }
}

