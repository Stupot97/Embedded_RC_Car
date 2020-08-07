#include "macros.h"
#include "msp430.h"
#include "functions.h"

volatile char USB_Char_Rx0 [SMALL_RING_SIZE];
char USB_Char_Tx0 [SMALL_RING_SIZE];
char *usb_rx_ring_wr0;
char *usb_rx_ring_rd0;

volatile char USB_Char_Rx3 [SMALL_RING_SIZE];
char USB_Char_Tx3 [SMALL_RING_SIZE];
char *usb_rx_ring_wr3;
char *usb_rx_ring_rd3;

extern char Received_Array[SMALL_RING_SIZE];
extern volatile unsigned int usb_rx_ring_wrUCA3;
extern volatile unsigned int usb_rx_ring_rUCA3;
extern volatile unsigned int usb_rx_ring_wrUCA0;
extern volatile unsigned int usb_rx_ring_rUCA0;

void Init_Serial_UCA0(int Baud_Rate){
 int i;
 for(i=RESET_STATE; i<SMALL_RING_SIZE; i++){
 USB_Char_Rx0[i] = RESET_STATE; // USB Rx Buffer
 }
 usb_rx_ring_wr0 = BEGINNING;
 usb_rx_ring_rd0 = BEGINNING;

 
 // Configure UART 0
 UCA0CTLW0 = RESET_STATE; // Use word register
 UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA0CTLW0 |= UCSWRST; // Set Software reset enable
//***** Continued on next slide
 // ***** Continuation from previous slide
// 115,200 Baud Rate
// 1. Calculate N = fBRCLK / Baudrate
// N = SMCLK / 115,200 => 8,000,000 / 115,200 = 69.4444
// if N > 16 continue with step 3, otherwise with step 2
// 2. OS16 = 0, UCBRx = INT(N)
// continue with step 4
// 3. OS16 = 1,
// UCx = INT(N/16),
// = INT(N/16) = 69.4444/16 => 4
// UCFx = INT([(N/16) – INT(N/16)] × 16)
//= ([69.4444/16-INT(69.4444/16)]*16)
//= (0.340275)*16
//= 0.340275*16 = 5.444
// 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
// Decimal of SMCLK / 8,000,000 / 115,200 = 69.4444 => 0.444 yields 0x55 [Table]
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// TX error (%) RX error (%)
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 115200 1 4 5.444 0x49 -0.08 0.04 -0.10 0.14
if(Baud_Rate==BAUD_RATE_115200){
  UCA0BRW = BAUD_RATE_115200_BRW; // 9,600 Baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA0MCTLW = BAUD_RATE_115200_MCTLW;
 }
 if(Baud_Rate==BAUD_RATE_460800){
   UCA0BRW = BAUD_RATE_460800_BRW; // 9,600 Baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA0MCTLW = BAUD_RATE_460800_MCTLW;
 }
 UCA0CTLW0 &= ~UCSWRST; // Release from reset
 UCA0IE |= UCRXIE; // Enable RX interrupt
}

void Init_Serial_UCA3(int Baud_Rate){
 int i;
 for(i=RESET_STATE; i<SMALL_RING_SIZE; i++){
 USB_Char_Rx3[i] = RESET_STATE; // USB Rx Buffer
 }
 usb_rx_ring_wr3 = BEGINNING;
 usb_rx_ring_rd3 = BEGINNING;

 // Configure UART 0
 UCA3CTLW0 = RESET_STATE; // Use word register
 UCA3CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
 UCA3CTLW0 |= UCSWRST; // Set Software reset enable
//***** Continued on next slide
 // ***** Continuation from previous slide
// 9,600 Baud Rate
// 1. Calculate N = fBRCLK / Baudrate
// N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
// if N > 16 continue with step 3, otherwise with step 2
// 2. OS16 = 0, UCBRx = INT(N)
// continue with step 4
// 3. OS16 = 1,
// UCx = INT(N/16),
// = INT(N/16) = 833.333/16 => 52
// UCFx = INT([(N/16) – INT(N/16)] × 16)
//= ([833.333/16-INT(833.333/16)]*16)
//= (52.08333333-52)*16
//= 0.083*16 = 1
// 4. UCSx is found by looking,600 = 833.3333333 => 0.333 yields 0x49 [Table]
// 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
// TX error (%) RX error (%) up the fractional part of N (= N-INT(N)) in table Table 18-4
// Decimal of SMCLK / 8,000,000 / 9
// BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
// 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
 if(Baud_Rate==BAUD_RATE_115200){
  UCA3BRW = BAUD_RATE_115200_BRW; // 9,600 Baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA3MCTLW = BAUD_RATE_115200_MCTLW;
 }
 if(Baud_Rate==BAUD_RATE_460800){
   UCA3BRW = BAUD_RATE_460800_BRW; // 9,600 Baud
// UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
// UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
 UCA3MCTLW = BAUD_RATE_460800_MCTLW;
 }
 UCA3CTLW0 &= ~UCSWRST; // Release from reset
 UCA3IE |= UCRXIE; // Enable RX interrupt
}

void out_character3(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA3IFG & UCTXIFG)); // USCI_A3 TX buffer ready?
 UCA3TXBUF = character;
//------------------------------------------------------------------------------
}

void out_character0(char character){
//------------------------------------------------------------------------------
// The while loop will stall as long as the Flag is not set [port is busy]
 while (!(UCA0IFG & UCTXIFG)); // USCI_A3 TX buffer ready?
 UCA0TXBUF = character;
//------------------------------------------------------------------------------
}

void out_string0(char* s){
  while(*s){
    out_character0(*s);
    s++;
  }
}

void out_string3(char* s){
  while(*s){
    out_character3(*s);
    s++;
  }
}

void read_char3(char volatile* s){
  unsigned int temp_read=usb_rx_ring_rUCA3;
  unsigned int temp_write=usb_rx_ring_wrUCA3;
  int index=RESET_STATE;
  char next_char;
  while(temp_read!=temp_write){
     while((*(s+usb_rx_ring_rUCA3)=='\0')||(*(s+usb_rx_ring_rUCA3)=='\n')||(*(s+usb_rx_ring_rUCA3)=='\r')){//if null or line feed
        usb_rx_ring_rUCA3=(ONE+usb_rx_ring_rUCA3)%SMALL_RING_SIZE;
        //usb_rx_ring_wrUCA3=(ONE+usb_rx_ring_wrUCA3)%SMALL_RING_SIZE;
     }
     if(usb_rx_ring_rUCA3==temp_write)
       break;
        Received_Array[index]=*(usb_rx_ring_rUCA3+s);
     if (++usb_rx_ring_rUCA3 >= (SMALL_RING_SIZE)){
       usb_rx_ring_rUCA3 = BEGINNING; // Circular buffer back to beginning
     }
     temp_read=usb_rx_ring_rUCA3;
     if (++usb_rx_ring_rUCA3 >= (SMALL_RING_SIZE)){//get next character
       next_char=*s; 
     }
     else
       next_char=*(s+usb_rx_ring_rUCA3);
     if(usb_rx_ring_rUCA3==BEGINNING)
       usb_rx_ring_rUCA3=SMALL_RING_SIZE-ONE;
     else
       --usb_rx_ring_rUCA3;
     temp_write=usb_rx_ring_wrUCA3;
     if((index>=(SMALL_RING_SIZE-ONE))&&(next_char=='\r')){
     index=(SMALL_RING_SIZE-ONE);
     }
     else
       ++index;
  }
}

void read_char0(char volatile* s){
  unsigned int temp_read=usb_rx_ring_rUCA0;
  unsigned int temp_write=usb_rx_ring_wrUCA0;
  int index=RESET_STATE;
  char next_char;
  while(temp_read!=temp_write){
     while((*(s+usb_rx_ring_rUCA0)=='\0')||(*(s+usb_rx_ring_rUCA0)=='\n')||(*(s+usb_rx_ring_rUCA0)=='\r')){//if null or line feed
        usb_rx_ring_rUCA0=(ONE+usb_rx_ring_rUCA0)%SMALL_RING_SIZE;
     }
     if(usb_rx_ring_rUCA0==temp_write)
       break;
        Received_Array[index]=*(usb_rx_ring_rUCA0+s);
     if (++usb_rx_ring_rUCA0 >= (SMALL_RING_SIZE)){
       usb_rx_ring_rUCA0 = BEGINNING; // Circular buffer back to beginning
     }
     temp_read=usb_rx_ring_rUCA0;
     if (++usb_rx_ring_rUCA0 >= (SMALL_RING_SIZE)){//get next character
       next_char=*s; 
     }
     else
       next_char=*(s+usb_rx_ring_rUCA0);
     if(usb_rx_ring_rUCA0==BEGINNING)
       usb_rx_ring_rUCA0=SMALL_RING_SIZE-ONE;
     else
       --usb_rx_ring_rUCA0;
     temp_write=usb_rx_ring_wrUCA0;
     if((index>=(SMALL_RING_SIZE-ONE))&&(next_char=='\r')){
     index=(SMALL_RING_SIZE-ONE);
     }
     else
       ++index;
  }
}
