
#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

unsigned int counter;
unsigned volatile int counter2;
unsigned int counter3;
volatile unsigned int Reset_Count;
volatile unsigned int Exiting_Count;
volatile extern unsigned int IOT_Reset;
extern unsigned int Menu_Count;
extern unsigned int Menu_Level;
extern unsigned int Baud_Select;
extern unsigned int Display_State;
extern unsigned int Receive_State;
extern int ADC_Right_Detector; 
extern int ADC_Left_Detector; 
extern int ADC_Thumb;
extern char string[ARRAY11]; 
extern char string2[ARRAY11]; 
extern char Command[ARRAY11];
char Time_String[ARRAY11]="TIME:0000s";
extern unsigned int Movement_Count;
extern unsigned int Left_Flag;
extern unsigned int Right_Flag;
extern char display_line[ARRAY4][ARRAY11]; 
extern volatile unsigned char update_display; 
extern volatile unsigned char display_changed;
extern volatile unsigned int IOT_Direction;
extern char Received_Array[SMALL_RING_SIZE];
extern char Ping[ARRAY25];
extern char IP_Addr1[ARRAY11];
extern char IP_Addr2[ARRAY11];
extern volatile unsigned int IP_Received;
extern volatile unsigned int Exiting;
extern volatile unsigned int Input_Received;


//display timer
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){//T0 interrupt every 50 ms
//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
//----------------------------------------------------------------------------
++counter;

if(Input_Received && (counter%FullSec==RESET_STATE)){//timer on display 
  if(Time_String[ARRAY8]!='9'){
    ++Time_String[ARRAY8];
  }
  else{
    Time_String[ARRAY8]='0';
    if(Time_String[ARRAY7]!='9'){
      ++Time_String[ARRAY7];
    }
    else{
      Time_String[ARRAY7]='0';
      if(Time_String[ARRAY6]!='9'){
        ++Time_String[ARRAY6];
      }
      else{
        Time_String[ARRAY6]='0';
        if(Time_String[ARRAY5]!='9'){
          ++Time_String[ARRAY5];
        }
        else
          Time_String[ARRAY5]='9';
      }
    }
  }
}
if(!Input_Received){
  Time_String[ARRAY5]=Time_String[ARRAY6]=Time_String[ARRAY7]=Time_String[ARRAY8]='0';
}

if(counter%FifthSec==RESET_STATE){//every 200 ms
      convert(ADC_Left_Detector,ADC_Right_Detector,ADC_Thumb);
      switch(Menu_Level){
       case START_MENU:
        if((ADC_Thumb%ITEM3)<=ITEM1){
            Menu_Count=SEL1;
          }
        if(((ADC_Thumb%ITEM3)>ITEM1)&&((ADC_Thumb%ITEM3)<=ITEM2)){
            Menu_Count=SEL2;
          }
         if(((ADC_Thumb%ITEM3)>ITEM2)){
            Menu_Count=SEL3;
          }
        switch(Menu_Count){ 
          case LINE: 
            strcpy(display_line[ARRAY0], ">LINE     ");
            strcpy(display_line[ARRAY1], " IOT      ");
            strcpy(display_line[ARRAY2], " BRIGHT   ");
            break; 
          case BAUDMODE:
            strcpy(display_line[ARRAY0], " LINE     ");
            strcpy(display_line[ARRAY1], ">IOT      ");
            strcpy(display_line[ARRAY2], " BRIGHT   ");
            break;
          case LIGHTMODE:
            strcpy(display_line[ARRAY0], " LINE     ");
            strcpy(display_line[ARRAY1], " IOT      ");
            strcpy(display_line[ARRAY2], ">BRIGHT   ");
          break;
        }
        if(IP_Received){
          strcpy(display_line[ARRAY3], " CONNECTED");
        }
        else
          strcpy(display_line[ARRAY3], "          ");
        break;
      case RECEIVE_MENU:
        if(!Input_Received){
          strcpy(display_line[ARRAY0]," WAITING  ");
          strcpy(display_line[ARRAY1]," FOR INPUT");
        }
        else{
          strcpy(display_line[ARRAY1],Time_String);
        }
        strcpy(display_line[ARRAY2], IP_Addr1);
        strcpy(display_line[ARRAY3], IP_Addr2);
        break;
      case BACKLIGHT_MENU:
         strcpy(display_line[ARRAY0]," USE KNOB ");
         strcpy(display_line[ARRAY1],"  ADJUST  ");
         strcpy(display_line[ARRAY2],"<<      >>");
         strcpy(display_line[ARRAY3],"BRIGHT DIM");
        break;
      case LINE_MENU:
        if((ADC_Thumb%ITEM2)<=ITEM1){
            Menu_Count=SEL1;
          }
        if(((ADC_Thumb%ITEM2)>ITEM1)&&((ADC_Thumb%ITEM2)<=ITEM2)){
            Menu_Count=SEL2;
          }
         LEFT_FORWARD_SPEED=WHEEL_OFF;
         RIGHT_FORWARD_SPEED=WHEEL_OFF;
        switch(Menu_Count){ 
          case CALMODE: 
            strcpy(display_line[ARRAY0], ">CAL MODE "); 
            strcpy(display_line[ARRAY1], " NAV MODE ");   
          break;
          case NAVMODE: 
            strcpy(display_line[ARRAY0], " CAL MODE "); 
            strcpy(display_line[ARRAY1], ">NAV MODE ");  
          break;
        }
        strcpy(display_line[ARRAY2], "          ");
        strcpy(display_line[ARRAY3], "          "); 
        break;
        case CALIBRATION_MENU:
        switch(Menu_Count){
        case WHITE_SURFACE:
        P8OUT|=IR_LED;
        strcpy(display_line[ARRAY0], "   WHITE  "); 
        strcpy(display_line[ARRAY1], "  SURFACE "); 
        strcpy(display_line[ARRAY2], "LED: ON   ");
        strcpy(display_line[ARRAY3], string); 
        break;
         case BLACK_LINE: 
          strcpy(display_line[ARRAY0], "   BLACK  "); 
          strcpy(display_line[ARRAY1], "   LINE   "); 
          strcpy(display_line[ARRAY2], "LED: ON   ");
          strcpy(display_line[ARRAY3], string); 
          break; 
        }
        break;
      case NAVIGATION_MENU:
        if(!Input_Received){
          strcpy(display_line[ARRAY0], "NAVIGATING"); 
          strcpy(display_line[ARRAY1], "          ");
          strcpy(display_line[ARRAY2], "          ");
          strcpy(display_line[ARRAY3], "          ");
        }
        break;
      }
      update_string(display_line[ARRAY0], ARRAY0);
      update_string(display_line[ARRAY1], ARRAY1);
      update_string(display_line[ARRAY2], ARRAY2);
      update_string(display_line[ARRAY3], ARRAY3);
    update_display=TRUE; display_changed=TRUE; Display_Process();
}
  
TA0CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
//----------------------------------------------------------------------------
}

//debounce timer

#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void){//T1 interrupt every 50ms
//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
//----------------------------------------------------------------------------
++counter2;
if(counter2==HalfSec){
    TA1CCTL0 &= ~CCIE; // CCR1 disable interrupt
    P5IFG &= ~BUTTON1; // Clear all P5.5 interrupt flags
    P5IE  |= BUTTON1; // P5.5 interrupt enabled
    
    P5IFG &= ~BUTTON2; // Clear all P5.6 interrupt flags
    P5IE |= BUTTON2; // P5.6 interrupt enabled
    
    TA0CCTL0 |= CCIE; // CCR0 enable T0 interrupt
}
  
TA1CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
//----------------------------------------------------------------------------
}


//movement timer

#pragma vector = TIMER2_A0_VECTOR
__interrupt void Timer2_A0_ISR(void){//T2 interrupt every 50ms
//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
//----------------------------------------------------------------------------
counter3=TRUE;
TA2CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0

switch(IOT_Direction){
  case GO_FORWARD:
    forward();
    if(!Exiting){
      strcpy(display_line[ARRAY0], "FORWARDS  ");
      Reset_Timer_A2();
    }
    else{
      ++Exiting_Count;
      if(Exiting_Count==FourFullSec){
        Reset_Timer_A2();
        Exiting_Count=RESET_STATE;
        wheels_off();
        strcpy(display_line[ARRAY0], "DONE      ");
      }
    }
  break;
  case GO_REVERSE:
     strcpy(display_line[ARRAY0], "REVERSE   ");
     reverse();
     Reset_Timer_A2();
  break;
  case GO_LEFT:
    strcpy(display_line[ARRAY0], "LEFT      ");
    left();
    Reset_Timer_A2();
  break;
  case GO_RIGHT:
    strcpy(display_line[ARRAY0], "RIGHT     ");
    right();
    Reset_Timer_A2();
  break;
}

//----------------------------------------------------------------------------
}


//reset IOT timer
#pragma vector = TIMER3_A0_VECTOR
__interrupt void Timer3_A0_ISR(void){//T3 interrupt every 50ms
//------------------------------------------------------------------------------
// TimerA3 0 Interrupt handler
//----------------------------------------------------------------------------
++Reset_Count;
TA3CCR0 += TA0CCR0_INTERVAL; // Add Offset to TACCR0
if(IOT_Reset==TRUE){
  P3OUT|=IOT_RESET;
  IOT_Reset=FALSE;
}

if(Reset_Count==ThreeFullSec){
  TA3CCTL0 &= ~CCIE; //disable timer
  P3IFG &= ~IOT_LINK;
  P3IE |=IOT_LINK; //enable interrupt
  out_string3("AT+S.PING=152.14.99.201\r"); //ping server
  out_string3("AT+S.SOCKD=32000\r"); //establish socket connection
}
  
//----------------------------------------------------------------------------
}