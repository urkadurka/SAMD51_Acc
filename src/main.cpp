#include <Arduino.h>
#include <main.h>
#include <Prop_SPI.h>
#include <ICM.h>
#include <Encoder.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_ICM20X.h>
//#include <Adafruit_ICM20948.h>


void setup() {
  // put your setup code here, to run once:

  // ****************************
  // Open Serial Port
  Serial.begin(115200);
  int iCnt=0;
  while(iCnt<5){
    Serial.printf("Starting %d\n",iCnt);
    delay(1000);
    iCnt++;
  }
  
  setupMySPI(); // 2^ SPI Channel for ADA ICM20948

  Setup_Encoder();


}


void loop() {
  // put your main code here, to run repeatedly:
  
  ui8Generic = ICM_WhoAmI(MySPI, ICM_CS);
  ui16Generic = getAccAxis(MySPI, zAxis);
  Serial.printf("WhoIAm=%d\t Counter %d\t Acc Z  %d\n ",ui8Generic, ui8GenericCounter++, ui16Generic);
  if (ui8GenericCounter>100) ui8GenericCounter =0;
  delay(200);


}