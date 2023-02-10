#include <Arduino.h>
#include <Clocks.h>


void setupGCLK(void){
// enable the Gen Clock 4
  REG_GCLK_GENCTRL3  =  GCLK_SOURCE_OSC16M | //  GCLK_SOURCE_GCLKGEN1 | GCLK_SOURCE_DPLL1 //GCLK_SOURCE_XOSC0 | //   GCLK_SOURCE_OSC16M | //   GCLK_SOURCE_DFLL48M | // GCLK_SOURCE_GCLKGEN1 | GCLK_SOURCE_DFLL48M
                        GCLK_GENCTRL_GENEN |
                        GCLK_GENCTRL_IDC   |
                        GCLK_GENCTRL_OE |
                        (0x08 << 16);         // 959 KHz
  // write syncronized
  while (GCLK->SYNCBUSY.bit.GENCTRL3);
}
