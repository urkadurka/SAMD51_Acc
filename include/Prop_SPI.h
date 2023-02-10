#include <Arduino.h>
#include <SPI.h>

#ifndef __PROPSPI__
#define __PROPSPI__

  // For SPI mode, we need a CS pin
  #define ICM_CS 9
  // For software-SPI mode we need SCK/MOSI/MISO pins
  #define ICM_SCK 25
  #define ICM_MISO 23
  #define ICM_MOSI 24

  static SPIClass MySPI(&sercom3, 10, 13, 12, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_2);

  void BeginTransaction(SPIClass locSPI, uint8_t ui8CS);
  void EndTransaction(SPIClass locSPI, uint8_t ui8CS);
  void SPI_CS(uint8_t ui18CS, uint8_t ui8Level );
  void setupMySPI(void);


#endif