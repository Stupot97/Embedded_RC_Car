#include "macros.h"
#include "msp430.h"
#include "functions.h"

extern int ADC_Right_Detector; 
extern int ADC_Left_Detector;
extern unsigned int counter;
extern unsigned int counter3;
extern unsigned int White;
extern unsigned int Black;
unsigned int First_Time;
unsigned int First_Time2;
unsigned int Counter_Snapshot;
unsigned int Turned;
unsigned int Left_Flag;
unsigned int Right_Flag;
unsigned int Time_Count;
unsigned int Movement_Count;
volatile unsigned int Navigate_Speed=DUTY_CYCLE_38;

void navigate(void){
     switch(Movement_Count){
        case STATE1: //intercepting
          if(!First_Time){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
            Counter_Snapshot=counter;
          }
          LEFT_FORWARD_SPEED=WHEEL_PERIOD;
          RIGHT_FORWARD_SPEED=Navigate_Speed;
            if((ADC_Left_Detector<=White)&&(ADC_Right_Detector<=White)){//if on white surface, start looking for black
              ++Movement_Count;
              Time_Count=FALSE;
            } 
          First_Time2=TRUE;
          break; 
        case STATE2: //look for black
          if((ADC_Left_Detector>=Black)&&(ADC_Right_Detector>=Black)){//if on black surface, wait
              ++Movement_Count;
              Time_Count=FALSE;
            }
          break;
        case STATE3: //waiting
          if(Wait(HalfSec)){
            First_Time2=TRUE;
            ++Movement_Count;
          }
          break;
        case STATE4: //turning
          if(First_Time2){//if waiting is done
            LEFT_REVERSE_SPEED=DUTY_CYCLE_50; 
            RIGHT_FORWARD_SPEED=DUTY_CYCLE_50;
            if((ADC_Left_Detector>=Black)&&(ADC_Right_Detector>=Black)){
              wheels_off();
              Counter_Snapshot=counter;
              ++Movement_Count;
            }
            First_Time=TRUE;
          }
          break;
     case STATE5: //navigate
                   if((ADC_Right_Detector>=Black)&&(ADC_Left_Detector>=Black)){//if both on track
                   if(LEFT_REVERSE_SPEED || RIGHT_REVERSE_SPEED){
                      Init_Timer_A2();
                      LEFT_REVERSE_SPEED=WHEEL_OFF;
                      RIGHT_REVERSE_SPEED=WHEEL_OFF;
                   }
                   if(counter3==TRUE){
                    LEFT_FORWARD_SPEED=DUTY_CYCLE_50; //changed both
                    RIGHT_FORWARD_SPEED=DUTY_CYCLE_50; //changed from 38
                   }
                   Left_Flag=FALSE;
                   Right_Flag=FALSE;
            }
            else if((ADC_Right_Detector>=Black)&&(ADC_Left_Detector<=Black)){ //if left
                     if(LEFT_REVERSE_SPEED || RIGHT_FORWARD_SPEED){
                      Init_Timer_A2();
                      LEFT_REVERSE_SPEED=WHEEL_OFF;
                      RIGHT_FORWARD_SPEED=WHEEL_OFF;
                     }
                     if(counter3==TRUE){
                      LEFT_FORWARD_SPEED=DUTY_CYCLE_50; //changed from 38
                      RIGHT_REVERSE_SPEED=DUTY_CYCLE_50; //changed
                     }
                     Left_Flag=TRUE;
                     Right_Flag=FALSE;
            }
            else if((ADC_Right_Detector<=Black)&&(ADC_Left_Detector>=Black)){ //if right
                  if(LEFT_FORWARD_SPEED || RIGHT_REVERSE_SPEED){
                      Init_Timer_A2();
                      LEFT_FORWARD_SPEED=WHEEL_OFF;
                      RIGHT_REVERSE_SPEED=WHEEL_OFF;
                     }
                     if(counter3==TRUE){
                      LEFT_REVERSE_SPEED=DUTY_CYCLE_50; //changed
                      RIGHT_FORWARD_SPEED=DUTY_CYCLE_50; //changed from 38
                     }
                  Left_Flag=FALSE;
                  Right_Flag=TRUE;
            }
       break;
     } 
}