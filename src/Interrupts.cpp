#include <Arduino.h>
#include <Interrupts.h>
#include <Clocks.h>


// ****************************
// Encoder interrupt configuration
void SetupInterrupt_Encoder(){

    // ****************************
  // Encoder interrupt PIN configuration
  // PA22 as input and set for external interrupts
  PORT->Group[PORTA].DIRCLR.reg = PORT_PA21;  // Direction == INPUT
  PORT->Group[PORTA].PINCFG[PIN_PA21].reg |= PORT_PINCFG_PMUXEN;
  PORT->Group[PORTA].PMUX[PIN_PA21/2].bit.PMUXO |= 0X00; // EIC

  setupGCLK();
  // Interrupt needs for clock the enables it
  MCLK->APBAMASK.reg |= MCLK_APBAMASK_EIC;
  // *************************
  // Setup GCLK channel 3 for supply EIC clock (0x04)
  GCLK->PCHCTRL[4].bit.GEN = 0x03;     // Uses GCLK channel 3
  GCLK->PCHCTRL[4].bit.CHEN = 0x01;    // Peripheral Channel Enabled

  // *************************
  // EIC dis-able write SYNC required
  EIC->CTRLA.bit.ENABLE = 0x0;
  while(EIC->SYNCBUSY.bit.ENABLE);

  // Enable both edge interrupt sense, no sync reuired
  EIC->CONFIG[0].reg = EIC_CONFIG_SENSE5_FALL;//  EIC_CONFIG_SENSE3_BOTH;

  // Enabel Event output for external interrupt 5  on PA21
  EIC->EVCTRL.bit.EXTINTEO |= (1 << 5);

  // Disable interrupt for extint channel 5 on PA21
  EIC->INTENCLR.reg = (1 << 5);
  //EIC->INTENSET.reg = (1 << 3);

  // Interrupt shall be async channel 5 on PA21
  EIC->ASYNCH.reg  = (1 << 5); //  |= (1 << 0x03);

  // Enable GCLK EIC no write SYNC required
  EIC->CTRLA.bit.CKSEL &= ~(1<<EIC_CTRLA_CKSEL_Pos);  
  
  
  // EIC enable write SYNC required
  EIC->CTRLA.reg = EIC_CTRLA_ENABLE;
  while(EIC->SYNCBUSY.bit.ENABLE);
  
  // *************************
  // Enable interrupt for extint channel 5 on PA21
  EIC->INTENSET.reg |= (1 << 0x05);
  NVIC_EnableIRQ(EIC_5_IRQn);
} // void EncIntConfig(){
