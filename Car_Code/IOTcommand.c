#include "macros.h"
#include "functions.h"
#include "msp430.h"
#include <string.h>

char IOT_Buffer[SMALL_RING_SIZE];//IOT Buffer
unsigned int IOT_Read;//IOT read pointer
unsigned int IOT_Write;//IOT write pointer
char Command[ARRAY11]="          ";
extern unsigned int First_Time2;
extern char display_line[ARRAY4][ARRAY11]; 
extern volatile unsigned int Command_Flag;
extern volatile unsigned int Command_Index;
extern volatile char Command_Buff[SMALL_RING_SIZE];

void process_command(void){
  if(Command_Flag){//if command was sent
    while(Command_Buff[Command_Index]!='\r'){
    if(++Command_Index>=SMALL_RING_SIZE){
      Command_Index=BEGINNING;
    }
    switch(Command_Buff[Command_Index]){
      case 'F':
        if(++Command_Index>=SMALL_RING_SIZE){
          Command_Index=BEGINNING;
        }
        if(Command_Buff[Command_Index]=='4'){//if F4
          strcpy(display_line[ARRAY2], "FORWARD 4S");
          First_Time2=TRUE;
          while(!forward(FourFullSec)){
          
          }
        }
      break;
      case 'B':
        if(++Command_Index>=SMALL_RING_SIZE){
          Command_Index=BEGINNING;
        }
        if(Command_Buff[Command_Index]=='1'){//if B1
        strcpy(display_line[ARRAY2], "REVERSE 1S");
        First_Time2=TRUE;
          while(!reverse(FullSec)){
          
          }
        }
      break; 
      case 'R':
        if(++Command_Index>=SMALL_RING_SIZE){
          Command_Index=BEGINNING;
        }
        if(Command_Buff[Command_Index]=='9'){//if R9
          if(++Command_Index>=SMALL_RING_SIZE){
            Command_Index=BEGINNING;
          }
          if(Command_Buff[Command_Index]=='0'){//if R90
            strcpy(display_line[ARRAY2], "RIGHT TURN");
            First_Time2=TRUE;
            while(!clockwise(HalfSec)){
          
            }
          }
        }
      break;
      case 'L':
        if(++Command_Index>=SMALL_RING_SIZE){
          Command_Index=BEGINNING;
        }
        if(Command_Buff[Command_Index]=='4'){//if L4
          if(++Command_Index>=SMALL_RING_SIZE){
            Command_Index=BEGINNING;
          }
          if(Command_Buff[Command_Index]=='5'){//if L45
            strcpy(display_line[ARRAY2], "LEFT TURN ");
            First_Time2=TRUE;
            while(!counterclockwise(HalfSec)){
          
            }
          }
        }
      break;
    }
    }
  }
  }
