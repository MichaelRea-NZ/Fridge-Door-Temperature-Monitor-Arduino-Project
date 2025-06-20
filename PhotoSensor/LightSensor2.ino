int lightReading = A0;
int lightValue;
bool writeChanged = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(lightReading, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightValue = analogRead(lightReading);
  
  if(lightValue > 200 && !writeChanged){   
    Serial.println("Open ");
    //writeChange();
    writeChanged = true;
  }
  else if(lightValue < 200 && writeChanged){
    Serial.println("Closed ");
    //writeChange();
    writeChanged = false;
  }
}

void writeChange(){
  Serial.println(lightValue);
  Serial.println();
}
