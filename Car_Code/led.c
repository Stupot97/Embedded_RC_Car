#include "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns off both LEDs
  P1OUT &= ~RED_LED;
  P1OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}

void LEDs_ON(void){
  P1OUT |= RED_LED;
  P1OUT |= GRN_LED;
}