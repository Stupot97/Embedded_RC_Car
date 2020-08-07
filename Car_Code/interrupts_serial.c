#include "macros.h"
#include "functions.h"
#include "msp430.h"
#include <string.h>

// global variables
volatile unsigned int usb_rx_ring_wrUCA0;
volatile unsigned int usb_rx_ring_wrUCA3;
volatile unsigned int Receive_Flag;
volatile unsigned int Sent_Flag;
volatile unsigned int Wifi_Up;
volatile unsigned int Wifi_Up_Temp;
volatile unsigned int Wifi_Up_Temp2;
volatile unsigned int Wifi_Up_Temp3;
volatile unsigned int Wifi_Up_Temp4;
volatile unsigned int Wifi_Up_Temp5;
volatile unsigned int Wifi_Up_Temp6;
volatile unsigned int IP_Received;
volatile unsigned int IP_Received_Temp;
volatile unsigned int Command_Flag;
volatile unsigned int IOT_Direction;
volatile unsigned int Exiting;
volatile unsigned int Input_Received;
char IP_Addr1[ARRAY11]="          ";
char IP_Addr2[ARRAY11]="          ";
unsigned int IP_End;
extern volatile char USB_Char_Rx0[SMALL_RING_SIZE];
extern volatile char USB_Char_Rx3[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_rUCA3;
extern volatile unsigned int usb_rx_ring_rUCA0;
extern char display_line[ARRAY4][ARRAY11];
extern unsigned int Menu_Level;
extern volatile unsigned int Navigating;
extern volatile unsigned int Navigate_Speed;

//------------------------------------------------------------------------------
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
 unsigned int temp;
 switch(__even_in_range(UCA0IV,UCA0IVMAX)){
 case NOVECTOR: // Vector 0 - no interrupt
 break;
 case RECEIVEVECTOR: // Vector 2 - RXIFG
 temp = usb_rx_ring_wrUCA0;
 USB_Char_Rx0[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
 out_character3(USB_Char_Rx0[temp]); //echo
 if (++usb_rx_ring_wrUCA0 >= (SMALL_RING_SIZE)){
 usb_rx_ring_wrUCA0 = BEGINNING; // Circular buffer back to beginning
 }
 break;
 case TRANSMIT: 
 break;
 default: break;
 }
}
//------------------------------------------------------------------------------

#pragma vector=USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
 unsigned int temp;
 char* IP_Index_ptr;
 char temp_array[SMALL_RING_SIZE];
  unsigned int i;
  unsigned int IP_Index;

 switch(__even_in_range(UCA3IV,UCA3IVMAX)){
 case NOVECTOR: // Vector 0 - no interrupt
 break;
 case RECEIVEVECTOR: // Vector 2 – RXIFG
// code for Receive
 temp = usb_rx_ring_wrUCA3;
 USB_Char_Rx3[temp] = UCA3RXBUF; // RX -> USB_Char_Rx character
 out_character0(USB_Char_Rx3[temp]); //echo
 if (++usb_rx_ring_wrUCA3 >= (SMALL_RING_SIZE)){
 usb_rx_ring_wrUCA3 = BEGINNING; // Circular buffer back to beginning
 }
 if(Wifi_Up_Temp6&&(USB_Char_Rx3[temp]=='i')){
  Wifi_Up=TRUE;
 }
 if(Wifi_Up_Temp5&&(USB_Char_Rx3[temp]=='F')){
  Wifi_Up_Temp6=TRUE;
 }
 if(Wifi_Up_Temp4&&(USB_Char_Rx3[temp]=='i')){
  Wifi_Up_Temp5=TRUE;
 }
 if(Wifi_Up_Temp3&&(USB_Char_Rx3[temp]=='W')){
  Wifi_Up_Temp4=TRUE;
 }
 if(Wifi_Up_Temp2&&(USB_Char_Rx3[temp]==':')){
  Wifi_Up_Temp3=TRUE;
 }
 if(Wifi_Up_Temp&&(USB_Char_Rx3[temp]=='4')){
  Wifi_Up_Temp2=TRUE;
 }
 if(USB_Char_Rx3[temp]=='2'){
 Wifi_Up_Temp=TRUE;
 }
 if(Receive_Flag){
 if(Command_Flag){
   switch(USB_Char_Rx3[temp]){
    case 'F':
      Init_Timer_A2();
      wheels_off();
      IOT_Direction=GO_FORWARD;
      Command_Flag=FALSE;
      break;
    case 'B':
      Init_Timer_A2();
      wheels_off();
      IOT_Direction=GO_REVERSE;
      Command_Flag=FALSE;
      break;
    case 'L':
      Init_Timer_A2();
      wheels_off();
      IOT_Direction=GO_LEFT;
      Command_Flag=FALSE;
      break;
    case 'R':
      Init_Timer_A2();
      wheels_off();
      IOT_Direction=GO_RIGHT;
      Command_Flag=FALSE;
      break;
    case 'S':
      IOT_Direction=DEFAULT;
      wheels_off();
      Command_Flag=FALSE;
     break;
    case 'X': //slow speed
       Navigate_Speed=DUTY_CYCLE_38;
       Menu_Level=NAVIGATION_MENU;
       wheels_off();
       Command_Flag=FALSE;
       strcpy(display_line[ARRAY0],"NAVIGATING");
     break;
     case 'Y': //medium speed
       Navigate_Speed=DUTY_CYCLE_50;
       Menu_Level=NAVIGATION_MENU;
       wheels_off();
       Command_Flag=FALSE;
       strcpy(display_line[ARRAY0],"NAVIGATING");
     break;
     case 'Z': //fast speed
       Navigate_Speed=DUTY_CYCLE_56;  //63
       Menu_Level=NAVIGATION_MENU;
       wheels_off();
       Command_Flag=FALSE;
       strcpy(display_line[ARRAY0],"NAVIGATING");
     break;
    case 'E':
       Init_Timer_A2();
       wheels_off();
       IOT_Direction=GO_FORWARD;
       Navigating=FALSE;
       Exiting=TRUE;
       Menu_Level=RECEIVE_MENU;
       Command_Flag=FALSE;
       strcpy(display_line[ARRAY0],"EXITING   ");
     break;
   }
 }
 if((USB_Char_Rx3[temp]=='/')&&(!Command_Flag)){
     Command_Flag=TRUE;
     Input_Received=TRUE;
 }
 else
   Command_Flag=FALSE;
 }
 if(USB_Char_Rx3[temp]=='\r'){
   if(Wifi_Up){
     UCA3IE &= ~UCRXIE; //disable interrupt
     IP_End=temp;
     for(i=RESET_STATE;i<SMALL_RING_SIZE;++i){
        temp_array[i]=USB_Char_Rx3[i];
     }
     IP_Index_ptr = strstr(temp_array, "Up:");//get IP Address
     IP_Index=IP_Index_ptr-temp_array+ARRAY3;
     i=RESET_STATE;
       while((temp_array[IP_Index]>='.')&&(temp_array[IP_Index]<='9')){
         if(i>=ARRAY10){
          IP_Addr2[i-ARRAY10]=temp_array[IP_Index];
         }
         if(i<ARRAY10){
           IP_Addr1[i]=temp_array[IP_Index];
         }
             ++i;
         IP_Index=(IP_Index+ONE)%SMALL_RING_SIZE;
       }
       Wifi_Up=FALSE;
       Wifi_Up_Temp=FALSE;
       Wifi_Up_Temp2=FALSE;
       Wifi_Up_Temp3=FALSE;
       Wifi_Up_Temp4=FALSE;
       Wifi_Up_Temp5=FALSE;
       Wifi_Up_Temp6=FALSE;
       UCA3IE |= UCRXIE; //enable interrupt 
      IP_Received=TRUE;
    }
 }
 break;
 default: break;
}
}
