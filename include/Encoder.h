#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

#ifndef __ENCODERH__
#define __ENCODERH__

#define SS_SWITCH   24
#define SS_NEOPIX   6

#define SEESAW_ADDR 0x36

static int iPaolo=0;

static Adafruit_seesaw ss;
static seesaw_NeoPixel sspixel = seesaw_NeoPixel(1, SS_NEOPIX, NEO_GRB + NEO_KHZ800);

void Setup_Encoder(void);

#endif 