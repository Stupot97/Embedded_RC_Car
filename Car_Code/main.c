//------------------------------------------------------------------------------ 
// 
// Description: This file contains the Main Routine - "While" Operating System 
// 
// 
// Stuart D'Amico 
// Jan 31, 2018 
// Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2) 
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------ 
#include "msp430.h" 
#include "functions.h" 
#include <string.h> 
#include "macros.h" 

// Global Variables 
 
extern volatile unsigned char display_changed; 
extern int ADC_Right_Detector; 
extern int ADC_Left_Detector; 
extern int ADC_Thumb;
extern volatile int B_Pressed; 
extern unsigned int counter; 
volatile extern unsigned int counter2;
extern unsigned int counter3;
extern unsigned int Baud_Select;
extern volatile char USB_Char_Rx0[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx3[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wrUCA3;
extern volatile unsigned int Receive_Flag;
extern volatile unsigned int Sent_Flag;
volatile unsigned int usb_rx_ring_rUCA0;
volatile unsigned int usb_rx_ring_rUCA3;
unsigned int Counter_Snapshot2;
unsigned int Menu_Count;
unsigned int Menu_Level;
unsigned int Display_State;
unsigned int Receive_State;
volatile unsigned int Navigating;
char Received_Array[SMALL_RING_SIZE];

void main(void){ 
  //------------------------------------------------------------------------------ 
  // Main Program 
  // This is the main routine for the program. Execution of code starts here. 
  // The operating system is Back Ground Fore Ground. 
  // 
  //------------------------------------------------------------------------------ 
  Init_Ports(); // Initialize Ports  
  // Disable the GPIO power-on default high-impedance mode to activate 
  // previously configured port settings
  Init_Clocks(); // Initialize Clock System 
  Init_Conditions(); // Initialize Variables and Initial Conditions
  Init_ADC(); //Initialize ADC
  Init_Timers(); // Initialize Timers
  Init_LCD(); // Initialize LCD
  Init_Serial_UCA0(BAUD_RATE_115200); //Initialize Serial Ports
  Init_Serial_UCA3(BAUD_RATE_115200);
  Init_LEDs();
  //------------------------------------------------------------------------------ // Begining of the "While" Operating System 
  //------------------------------------------------------------------------------ 
  while(ALWAYS){ // Can the Operating system run
      switch(Menu_Level){
        case BACKLIGHT_MENU:
           BACKLIGHT_ON=ADC_Thumb;
           break;
        case NAVIGATION_MENU:
          P8OUT|=IR_LED;
          Navigating=TRUE;
          navigate();
          break;
      }
      if(Menu_Level!=NAVIGATION_MENU){
        Navigating=FALSE;
      }
  } 
} //------------------------------------------------------------------------------