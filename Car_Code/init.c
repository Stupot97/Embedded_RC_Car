#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"

extern char display_line[ARRAY4][ARRAY11];
extern char *display[ARRAY4];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=ARRAY0;i<ARRAY11;i++){
    display_line[ARRAY0][i] = RESET_STATE;
    display_line[ARRAY1][i] = RESET_STATE;
    display_line[ARRAY2][i] = RESET_STATE;
    display_line[ARRAY3][i] = RESET_STATE;
  }
  display_line[ARRAY0][ARRAY10] = RESET_STATE;
  display_line[ARRAY1][ARRAY10] = RESET_STATE;
  display_line[ARRAY2][ARRAY10] = RESET_STATE;
  display_line[ARRAY3][ARRAY10] = RESET_STATE;

  display[ARRAY0] = &display_line[ARRAY0][ARRAY0];
  display[ARRAY1] = &display_line[ARRAY1][ARRAY0];
  display[ARRAY2] = &display_line[ARRAY2][ARRAY0];
  display[ARRAY3] = &display_line[ARRAY3][ARRAY0];
  update_display = FALSE;
  update_display_count = FALSE;

// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}