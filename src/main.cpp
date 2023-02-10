#include <Arduino.h>
#include <main.h>
#include <Prop_SPI.h>
#include <ICM.h>
#include <Encoder.h>
#include <Interrupts.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_ICM20X.h>
//#include <Adafruit_ICM20948.h>

void EIC_5_Handler()
{
  //uint8_t ui8_e4;
  //ui8_e4++;
  u_int32_t ui32ResetFlag = (1<<0x05);;

  REG_EIC_INTFLAG |= ui32ResetFlag;
  // REG_EIC_INTENCLR 
  if (bNewEncPosition==false) {
    i32EncPosition = ss.getEncoderPosition();
    ui8EncSwitchValue = ss.digitalRead(SS_SWITCH);
    bNewEncPosition = true;
  }
  else {
    int32_t i32Dummy = ss.getEncoderPosition();
  }

  //EIC->INTFLAG[3]  .reg = ui32ResetFlag;
  //PORT->Group[PORTA].OUTTGL.reg |= PORT_PA23;  
}

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

  SetupInterrupt_Encoder();


}


void loop() {
  // put your main code here, to run repeatedly:
  
  ui8Generic = ICM_WhoAmI(MySPI, ICM_CS);
  ui16Generic = getAccAxis(MySPI, zAxis);
  Serial.printf("WhoIAm=%d\t Counter %d\t Acc Z  %d\t\n ",ui8Generic, ui8GenericCounter++, ui16Generic);
  if (ui8GenericCounter>100) ui8GenericCounter =0;

  if (bNewEncPosition){
    Serial.printf("\t\t\t New Enc Pos %d\t EndSwitch %d\n",bNewEncPosition, ui8EncSwitchValue);
    bNewEncPosition = false;
  }

  delay(200);


}