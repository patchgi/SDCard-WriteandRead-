#include <SD.h>
const int chipSelect=4;
File dataFile;
int count,saveCount,loadCount;

void setup(){

  Serial.begin(9600);
  Serial.print(F("Initializing..."));
  pinMode(SS,OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));

    while(1);
  }
  
  Serial.println(F("ok."));
}



void loop(){
  
  int data=0;
  if(Serial.available()>0){
    data=Serial.read();

    if(data=='s'){
      SD.remove("datalog1.txt");
      Serial.println("delite");
      Serial.println("start");
      saveCount=0;
      count=1;
    }

    if(data=='t'){
      count=0;
    }

    if(data=='p'){
      count=2;
    }

  }

 
  if(count==1){
     dataFile=SD.open("datalog1.txt",FILE_WRITE);
    if(dataFile){
      int value=analogRead(0)/4;
      dataFile.println(value);
      saveCount++;
      dataFile.close();
      Serial.println(value);
    }

  }

 if(count==2){
   while(saveCount>=loadCount){
    dataFile = SD.open("datalog1.txt");
    if (dataFile) {

      byte buffer[64];
      while (dataFile.available()) {
        int length = dataFile.available();
        if(length > 64){
          length = 64;
        }
        dataFile.read(buffer, length);
        Serial.write(buffer, length);
      }
       loadCount++;
      dataFile.close();
    }
   }
  }  
  
  delay(100);

}







