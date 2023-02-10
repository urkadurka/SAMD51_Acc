#include <Prop_SPI.h>
#include <wiring_private.h>
#include <ICM.h>

void BeginTransaction(SPIClass locSPI, uint8_t ui8CS){
  locSPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
  digitalWrite(ui8CS,LOW);
}

void EndTransaction(SPIClass locSPI, uint8_t ui8CS){
  digitalWrite(ui8CS,HIGH);
  locSPI.endTransaction();
}

void SPI_CS(uint8_t ui18CS, uint8_t ui8Level ){
  switch (ui8Level){
    case HIGH :
      digitalWrite(ui18CS, HIGH);
      break;
    case LOW :
      digitalWrite(ui18CS, LOW);
      break;
  }
  // cambia qualcosa
}




void setupMySPI(void){
  //uint16_t ui16Receive, ui16Transmit = 0x80, ui16Res=0;
  uint16_t ui16Res=0;
  //uint8_t ui8Prefix, ui8Data, ui8Receive, ui8Low, ui8High;
  uint8_t ui8Low, ui8High;
  MySPI.begin();
  pinPeripheral(10, PIO_SERCOM);  // MISO
  pinPeripheral(12, PIO_SERCOM);  // MOSI
  pinPeripheral(13, PIO_SERCOM);  // SCK

  pinMode(ICM_CS,OUTPUT);
  digitalWrite(ICM_CS,HIGH);

  PORT->Group[0].PMUX[10].bit.PMUXE = 0x03;
  PORT->Group[0].PINCFG[10].bit.PULLEN = 0x01;

  ui8Low = ICM_DeviceReset(MySPI, ICM_CS);

  //ui8Low = ICM_WhoAmI(MySPI, ICM_CS);
  //Serial.printf("Who Am I %d\t ", ui8Low);

  //BeginTransaction(ICM_CS); //SPI_CS(ICM_CS,HIGH);
  // while(1){
  //   // **************
  //   // Read AccZ HIGH Byte
  //   //BeginTransaction(ICM_CS); //SPI_CS(ICM_CS,HIGH);

  //   ////ui8High = ICM_ReadREG(MySPI, 0x31, ICM_CS);
  //   ////ui8Low = ICM_ReadREG(MySPI, 0x32, ICM_CS);



  //   SPI_CS(ICM_CS,LOW);
  //   ui8High =SPI3.transfer((0x31 | 0x80));
  //   ui8High =SPI3.transfer((0xFF));
  //   //SPI_CS(ICM_CS,HIGH);
  //   //EndTransaction(ICM_CS); //SPI_CS(ICM_CS,LOW);

  //   //BeginTransaction(ICM_CS); //SPI_CS(ICM_CS,HIGH);
  //   //SPI_CS(ICM_CS,LOW);
  //   ui8Low =SPI3.transfer((0x32 | 0x80));
  //   ui8Low =SPI3.transfer((0xFF));
  //   SPI_CS(ICM_CS,HIGH);
  //   //EndTransaction(ICM_CS); //SPI_CS(ICM_CS,LOW);
  //   */

  //   ////ui16Res = ui8High;
  //   ////ui16Res <<= 8;
  //   ////ui16Res |= ui8Low;

  //   ui16Res = getAccAxis(MySPI, zAxis);
    
  //   Serial.printf("High %d\t Low %d\tAcc Z  %d\n ", ui8High, ui8Low, ui16Res);
    
  //   delay(100); 
  //}
}