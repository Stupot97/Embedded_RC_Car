#include "macros.h"
#include "msp430.h"
#include "functions.h"
#include <string.h>

int debounce_B1;
int debounce_B2;

volatile int B_Pressed;
unsigned int Menu_Change;
int B1_pressed;
int B2_pressed;

extern unsigned int Receive_State;
extern unsigned int Movement_Count;
extern unsigned int Display_State;
extern unsigned int Menu_Count;
extern unsigned int Menu_Level;
extern char display_line[ARRAY4][ARRAY11];
extern int ADC_Right_Detector; 
extern int ADC_Left_Detector;
extern unsigned int First_Time;
extern unsigned int First_Time2;
extern volatile unsigned int Receive_Flag;
extern volatile unsigned int Reset_Count;
extern volatile unsigned int Receive_Flag;

unsigned int White=DEFAULT_WHITE;
unsigned int Black=DEFAULT_BLACK;
volatile unsigned int IOT_Reset;
volatile unsigned int Backlight_Setting;
extern volatile unsigned int IP_Received;
extern volatile unsigned int Navigating;
extern volatile unsigned int Input_Received;

#pragma vector=PORT5_VECTOR
__interrupt void BUTTON_interrupt(void){//interrupt for button press
// BUTTON 1
if (P5IFG & BUTTON1) {//if button 1 pressed
  if(B1_pressed){
    if(debounce_B1){
       Init_Timer_A1();
       TA0CCTL0 &= ~CCIE; // CCR0 disable interrupt
       TA0CCR0 = TA0CCR0_INTERVAL;
       if(Menu_Level==CALIBRATION_MENU){
         switch(Menu_Count){
         case SEL1:
           White=(ADC_Left_Detector>=ADC_Right_Detector)?(ADC_Left_Detector):(ADC_Right_Detector);
           break;
         case SEL2:
            Black=(ADC_Left_Detector>=ADC_Right_Detector)?(ADC_Left_Detector):(ADC_Right_Detector);
            break;
         }
       ++Menu_Count;
        if(Menu_Count>SEL2){
          P8OUT&=~IR_LED;
          Menu_Level=LINE_MENU;
        }
        Menu_Change=TRUE;
       }
       if((Menu_Level==LINE_MENU)&&(!Menu_Change)){
         if(Menu_Count==SEL1){
          Menu_Level=CALIBRATION_MENU;
         }
         if(Menu_Count==SEL2){
            P8OUT|=IR_LED;
            Menu_Level=NAVIGATION_MENU;
            Movement_Count=STATE1;
         }
        Menu_Change=TRUE;
       }
       if((Menu_Level==START_MENU)&&(!Menu_Change)){
         if(Menu_Count==SEL1){
          Menu_Level=LINE_MENU;
         }
         if((Menu_Count==SEL2)&&(IP_Received)){
          Menu_Level=RECEIVE_MENU;
          Receive_Flag=TRUE;
         }
         if(Menu_Count==SEL3){
          Menu_Level=BACKLIGHT_MENU;
         }
          Menu_Change=TRUE;
       }
       if((Menu_Level==BACKLIGHT_MENU)&&(!Menu_Change)){
          Backlight_Setting=BACKLIGHT_ON;
          Menu_Change=TRUE;
       }
       if((Menu_Level==RECEIVE_MENU)&&(!Menu_Change)){
          Menu_Change=TRUE;
       }
       P5IFG &= ~BUTTON1; // Clear all P5.5 interrupt flags
       P5IE  &= ~BUTTON1; // P5.5 interrupt disabled
       debounce_B1=FALSE;
       B1_pressed=FALSE;
       Menu_Change=FALSE;
      }
    }
  else{
    B1_pressed=TRUE;
    debounce_B1=TRUE;
  }

  B_Pressed=BUTTON1;
  }
  
// BUTTON 2
if (P5IFG & BUTTON2){//if button 2 pressed
   if(B2_pressed){
    if(debounce_B2){
       Init_Timer_A1();
       TA0CCTL0 &= ~CCIE; // CCR0 disable interrupt
       TA0CCR0 = TA0CCR0_INTERVAL;
       if((Menu_Level==LINE_MENU)||(Menu_Level==RECEIVE_MENU)||(Menu_Level==BACKLIGHT_MENU)){
         if(Menu_Level==BACKLIGHT_MENU){
            BACKLIGHT_ON=Backlight_Setting;
         }
         Menu_Level=START_MENU;
       }
       if(Menu_Level==NAVIGATION_MENU){
       wheels_off();
       Menu_Level=LINE_MENU;
       Movement_Count=STATE1;
       Receive_Flag=FALSE;
       Init_LEDs();
       }
       P8OUT &= ~IR_LED; //Turn LED OFF 
       P5IFG &= ~BUTTON2; // Clear all P5.5 interrupt flags
       P5IE  &= ~BUTTON2; // P5.5 interrupt disabled
       debounce_B2=FALSE;
       B2_pressed=FALSE;
      }
    }
  else{
    B2_pressed=TRUE;
    debounce_B2=TRUE;
  }
B_Pressed=BUTTON2;
Menu_Change=FALSE;
}
}

//interrupt for disconnecting IOT link
#pragma vector=PORT3_VECTOR
__interrupt void LINK_interrupt(void){
  if ((P3IFG & IOT_LINK)){ //if board loses connection
    if(!Navigating){
      wheels_off();
    }
    P3OUT &= ~IOT_RESET;
    IOT_Reset=TRUE;
    TA3CCTL0 |= CCIE; //disable timer
    P3IFG &=~IOT_LINK;
    P3IE &=~IOT_LINK;
    Reset_Count=RESET_STATE;
  }
}
