#include "macros.h"
#include "msp430.h"
#include "functions.h"


extern unsigned int Counter_Snapshot;
extern unsigned int Counter_Snapshot2;
extern unsigned int counter;
extern unsigned int counter3;
extern unsigned int Time_Count;
extern unsigned int First_Time;
extern unsigned int First_Time2;
unsigned extern volatile int counter2;

void Init_Timers(void){//initialize timers 
Init_Timer_A0();
Init_Timer_A1();
Init_Timer_A2();
Init_Timer_A3();
Init_Timer_A4();
Init_Timer_B0();
}     

void Init_Timer_A0(void) {//initialize T0 
  TA0CTL = TASSEL__SMCLK; // SMCLK source
  TA0CTL |= TACLR; // Resets TA0R, clock divider, count direction
  TA0CTL |= MC__CONTINOUS; // Continuous up
  TA0CTL |= ID__2; // Divide clock by 2
  TA0EX0 = TAIDEX_7; // Divide clock by an additional 8
  TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
  TA0CCTL0 |= CCIE; // CCR0 enable interrupt
  TA0CTL &= ~TAIE; // Disable Overflow Interrupt
  TA0CTL &= ~TAIFG; // Clear Overflow Interrupt flag
}

//debounce timer
void Init_Timer_A1(void) {//initialize T1
  TA1CTL = TASSEL__SMCLK; // SMCLK source
  TA1CTL |= TACLR; // Resets TA0R, clock divider, count direction
  TA1CTL |= MC__CONTINOUS; // Continuous up
  TA1CTL |= ID__2; // Divide clock by 2
  TA1EX0 = TAIDEX_7; // Divide clock by an additional 8
  TA1CCR0 = TA0CCR0_INTERVAL; // CCR0
  TA1CCTL0 |= CCIE; // CCR0 enable interrupt
  TA1CTL &= ~TAIE; // Disable Overflow Interrupt
  TA1CTL &= ~TAIFG; // Clear Overflow Interrupt flag
  counter2=RESET_STATE;
}

//movement timer
void Init_Timer_A2(void) {//initialize T2
  TA2CTL = TASSEL__SMCLK; // SMCLK source
  TA2CTL |= TACLR; // Resets TA0R, clock divider, count direction
  TA2CTL |= MC__CONTINOUS; // Continuous up
  TA2CTL |= ID__2; // Divide clock by 2
  TA2EX0 = TAIDEX_7; // Divide clock by an additional 8
  TA2CCR0 = TA0CCR0_INTERVAL; // CCR0
  TA2CCTL0 |= CCIE; // CCR0 enable interrupt
  TA2CTL &= ~TAIE; // Disable Overflow Interrupt
  TA2CTL &= ~TAIFG; // Clear Overflow Interrupt flag
  counter3=RESET_STATE;
}

//ping timer
void Init_Timer_A3(void) {//initialize T3
  TA3CTL = TASSEL__SMCLK; // SMCLK source
  TA3CTL |= TACLR; // Resets TA0R, clock divider, count direction
  TA3CTL |= MC__CONTINOUS; // Continuous up
  TA3CTL |= ID__2; // Divide clock by 2
  TA3EX0 = TAIDEX_7; // Divide clock by an additional 8
  TA3CCR0 = TA0CCR0_INTERVAL; // CCR0
  TA3CCTL0 |= CCIE; // CCR0 enable interrupt
  TA3CTL &= ~TAIE; // Disable Overflow Interrupt
  TA3CTL &= ~TAIFG; // Clear Overflow Interrupt flag
}


//pwm timer for backlight
void Init_Timer_A4(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TA4.1 BACKLIGHT
//------------------------------------------------------------------------------
TA4CTL = TASSEL__SMCLK; // SMCLK
TA4CTL |= MC__UP; // Up Mode
TA4CTL |= TACLR; // Clear TAR
TA4CCR0 = WHEEL_PERIOD; // PWM Period
TA4CCTL1 = OUTMOD_7; // CCR1 reset/set
BACKLIGHT_ON = BACKLIGHT_OFF; // P5.6 Backlight PWM duty cycle
//------------------------------------------------------------------------------
}

//pwm timer for motors
void Init_Timer_B0(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB0.3 P3.4 L_REVERSE TB0.1 P3.6 R_REVERSE
// TB0.4 P3.5 L_FORWARD TB0.2 P3.7 R_FORWARD
//------------------------------------------------------------------------------
TB0CTL = TBSSEL__SMCLK; // SMCLK
TB0CTL |= MC__UP; // Up Mode
TB0CTL |= TBCLR; // Clear TAR
TB0CCR0 = WHEEL_PERIOD; // PWM Period
TB0CCTL3 = OUTMOD_7; // CCR1 reset/set
LEFT_REVERSE_SPEED = WHEEL_OFF; // P3.4 Left Reverse PWM duty cycle
TB0CCTL4 = OUTMOD_7; // CCR2 reset/set
LEFT_FORWARD_SPEED = WHEEL_OFF; // P3.5 Left Forward PWM duty cycle
TB0CCTL5 = OUTMOD_7; // CCR1 reset/set
RIGHT_REVERSE_SPEED = WHEEL_OFF; // P3.6 Right Reverse PWM duty cycle
TB0CCTL6 = OUTMOD_7; // CCR2 reset/set
RIGHT_FORWARD_SPEED = WHEEL_OFF; // P3.7 Right Forward PWM duty cycle
//------------------------------------------------------------------------------
}

void Reset_Timer_A2(void){//turns off interrupt and resets
 TA2CTL = TASSEL__SMCLK; // SMCLK source
  TA2CTL |= TACLR; // Resets TA0R, clock divider, count direction
  TA2CTL |= MC__CONTINOUS; // Continuous up
  TA2CTL |= ID__2; // Divide clock by 2
  TA2EX0 = TAIDEX_7; // Divide clock by an additional 8
  TA2CCR0 = TA0CCR0_INTERVAL; // CCR0
  TA2CCTL0 &= ~CCIE; // CCR0 enable interrupt
  TA2CTL &= ~TAIE; // Disable Overflow Interrupt
  TA2CTL &= ~TAIFG; // Clear Overflow Interrupt flag
}

int Wait(int Time){
  if(First_Time2){
    Counter_Snapshot2=counter;
    First_Time2=FALSE;
  }
   LEFT_FORWARD_SPEED=WHEEL_OFF;
   RIGHT_FORWARD_SPEED=WHEEL_OFF;
   LEFT_REVERSE_SPEED=WHEEL_OFF;
   RIGHT_REVERSE_SPEED=WHEEL_OFF;
  if(counter==(Counter_Snapshot2+Time)){
    return TRUE;
   }
  else
    return FALSE;
}
