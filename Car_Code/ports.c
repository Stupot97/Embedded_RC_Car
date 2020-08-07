//This file initializes all the ports

#include "macros.h"
#include "msp430.h"
#include "functions.h"


void Init_Ports(void){ 
Init_Port1();
Init_Port2();
Init_Port3();
Init_Port4();
Init_Port5();
Init_Port6();
Init_Port7();
Init_Port8();
Init_PortJ();
}  

void Init_Port1(void){
//Configure Port 1
P1SEL0 = RESET_STATE; // GP I/O
P1SEL1 = RESET_STATE; // GP I/O
P1DIR = OUT_DIR; // Set P1 direction to input
P1OUT = RESET_STATE;
// P1_0
P1SEL0 &= ~RED_LED; // RED_LED as GP I/O
P1SEL1 &= ~RED_LED; // RED_LED as GP I/O
P1OUT |= RED_LED; // Set Red LED On
P1DIR |= RED_LED; // Set Red LED direction to output
// P1_1
P1SEL0 &= ~GRN_LED; // GRN_LED as GP I/O
P1SEL1 &= ~GRN_LED; // GRN_LED as GP I/O
P1OUT |= GRN_LED; // Set Green LED On
P1DIR |= GRN_LED; // Set Green LED direction to output
// P1_2
P1SEL0 |= V_THUMB; // ADC input for Thumbwheel
P1SEL1 |= V_THUMB; // ADC input for Thumbwheel
// P1_3
P1SEL0 &= ~TEST_PROBE; // TEST_PROBE as GP I/O
P1SEL1 &= ~TEST_PROBE; // TEST_PROBE as GP I/O
P1OUT &= ~TEST_PROBE; // Set TEST_PROBE Off
P1DIR |= TEST_PROBE; // Set TEST_PROBE direction to output
// P1_4
P1SEL0 |= V_DETECT_R; // ADC input for Right Detector
P1SEL1 |= V_DETECT_R; // ADC input for Right Detector
// P1_5
P1SEL0 |= V_DETECT_L; // ADC input for Left Detector
P1SEL1 |= V_DETECT_L; // ADC input for Left Detector
// P1_6
P1SEL0 &= ~SD_UCB0SIMO; // USCI_B1 MOSI pin
P1SEL1 |= SD_UCB0SIMO; // USCI_B1 MOSI pin
// P1_7
P1SEL0 &= ~SD_UCB0SOMI; // USCI_B1 MISO pin
P1SEL1 |= SD_UCB0SOMI; // USCI_B1 MISO pin
}

void Init_Port2(void){
//Configure Port 2
P2SEL0 = RESET_STATE; // GP I/O
P2SEL1 = RESET_STATE; // GP I/O
//P2_0
P2SEL0 &= ~BCLUART_TXD; // BCLUART_TXD Pin
P2SEL1 |= BCLUART_TXD; // BCLUART_TXD Pin
//P2_1
P2SEL0 &= ~BCLUART_RXD; // BCLUART_RXD Pin
P2SEL1 |= BCLUART_RXD; // BCLUART_RXD Pin
//P2_2
P2SEL0 &= ~SD_SPICLK; // SD_SPIClK Pin
P2SEL1 |= SD_SPICLK; // SD_SPIClK Pin
//P2_3
P2SEL0 &= ~P2_3; // GP I/O
P2SEL1 &= ~P2_3; // GP I/O
P2DIR  &= ~P2_3; // Input
P2OUT  &= ~P2_3; // Output low
//P2_4
P2SEL0 &= ~P2_4; // GP I/O
P2SEL1 &= ~P2_4; // GP I/O
P2DIR  &= ~P2_4; // Input
P2OUT  &= ~P2_4; // Output low
//P2_5
P2SEL0 &= ~UCA1TXD ; // UCA1_TXD Pin
P2SEL1 |= UCA1TXD ; // UCA1_TXD Pin
//P2_6
P2SEL0 &= ~UCA1RXD ; // UCA1_RXD Pin
P2SEL1 |= UCA1RXD ; // UCA1_RXD Pin
//P2_7
P2SEL0 &= ~P2_7; // GP I/O
P2SEL1 &= ~P2_7; // GP I/O
P2DIR  &= ~P2_7; // Input
P2OUT  &= ~P2_7; // Output low
}

void Init_Port3(void){
//------------------------------------------------------------------------------
P3DIR = OUT_DIR; // Set P3 direction to output
P3OUT = RESET_STATE; // P3 set Low

P3SEL0 &= ~IOT_RESET; // Set to GP I/O
P3SEL1 &= ~IOT_RESET; // Set to GP I/O
P3OUT &= ~IOT_RESET; // Set out value Low [active]
P3DIR |= IOT_RESET; // Set direction to output

P3SEL0 &= ~IOT_STA_MINIAP; // Set to GP I/O
P3SEL1 &= ~IOT_STA_MINIAP; // Set to GP I/O
P3OUT |= IOT_STA_MINIAP; // Set out value no Mini AP
P3DIR |= IOT_STA_MINIAP; // Set direction to output

P3SEL0 &= ~IOT_LINK; // Set to GP I/O
P3SEL1 &= ~IOT_LINK; // Set to GP I/O
//P3OUT |= IOT_LINK;
P3DIR &= ~IOT_LINK; // Set direction to input
  P3IES &= ~IOT_LINK; // lo/hi edge interrupt 
  P3IFG &= ~IOT_LINK; // Clear all IOT link interrupt flags 
  P3IE |= IOT_LINK; // IOT Link interrupt enabled


P3SEL0 &= ~IOT_WAKEUP; // Set to GP I/O
P3SEL1 &= ~IOT_WAKEUP; // Set to GP I/O
P3OUT &= ~IOT_WAKEUP; // Set out value Low [off]
P3DIR |= IOT_WAKEUP; // Set direction to output

P3SEL0 |= L_REVERSE; // Set to PWM
P3SEL1 &= ~L_REVERSE; // Set to PWM
//P3OUT &= ~L_REVERSE; // Set out value Low [off]
P3DIR |= L_REVERSE; // Set direction to output
P3SEL0 |= L_FORWARD; // Set to PWM
P3SEL1 &= ~L_FORWARD; // Set to PWM
//P3OUT &= ~L_FORWARD; // Set out value Low [off]
P3DIR |= L_FORWARD; // Set direction to output
P3SEL0 |= R_REVERSE; // Set to PWM
P3SEL1 &= ~R_REVERSE; // Set to PWM
//P3OUT &= ~R_REVERSE; // Set out value Low [off]
P3DIR |= R_REVERSE; // Set direction to output
P3SEL0 |= R_FORWARD; // Set to PWM
P3SEL1 &= ~R_FORWARD; // Set to PWM
//P3OUT &= ~R_FORWARD; // Set out value Low [off]
P3DIR |= R_FORWARD; // Set direction to output


  
//------------------------------------------------------------------------------
}

void Init_Port4(void){
//Configure Port 4. Every pin is GP I/O
  P4SEL0=RESET_STATE; //GP I/O
  P4SEL1=RESET_STATE; //GP I/O
//P4_O
  P4SEL0 &= ~SD_CS; //GP I/O
  P4SEL1 &= ~SD_CS; //GP I/O
  P4OUT &= ~SD_CS; //Input 
  P4DIR &= ~SD_CS; //Output Low
//P4_1
  P4SEL0 &= ~J4_31; //GP I/O
  P4SEL1 &= ~J4_31; //GP I/O
  P4OUT &= ~J4_31; // Input
  P4DIR &= ~J4_31; // Output Low
//P4_2
  P4SEL0 &= ~J4_32; //GP I/O
  P4SEL1 &= ~J4_32; //GP I/O
  P4OUT &= ~J4_32; // Input
  P4DIR &= ~J4_32; // Output Low
//P4_3
  P4SEL0 &= ~J4_33; //GP I/O
  P4SEL1 &= ~J4_33; //GP I/O
  P4OUT &= ~J4_33; // Input
  P4DIR &= ~J4_33; // Output Low
//P4_4
  P4SEL0 &= ~UCB1_CS_LCD; //GP I/O
  P4SEL1 &= ~UCB1_CS_LCD; //GP I/O
  P4OUT |= UCB1_CS_LCD; // Output High 
  P4DIR |= UCB1_CS_LCD; // Direction High
//P4_5
  P4SEL0 &= ~P4_4; //GP I/O
  P4SEL1 &= ~P4_4; //GP I/O
  P4OUT &= ~P4_4; // Input
  P4DIR &= ~P4_4; // Output Low
//P4_6
  P4SEL0 &= ~P4_5; //GP I/O
  P4SEL1 &= ~P4_5; //GP I/O
  P4OUT &= ~P4_5; // Input
  P4DIR &= ~P4_5; // Output Low
//P4_7
  P4SEL0 &= ~J3_29; //GP I/O
  P4SEL1 &= ~J3_29; //GP I/O
  P4OUT &= ~J3_29; // Input
  P4DIR &= ~J3_29; // Output Low
}

void Init_Port5(void){
//--------------------------------------------------------------------
// Configure PORT 5
// SPI_UCB1SIMO (0x01) // UCB1SIMO
// SPI_UCB1SOMI (0x02) // UCB1SOMI
// SPI_UCB1CLK (0x04) // SPI mode - clock output—UCB1CLK
// RESET_LCD (0x08) // LCD Reset
// BUTTON2 (0x20) // Button 2
// BUTTON1 (0x40) // Button 1
// LCD_BACKLITE (0x80) // LCD Backlight
P5SEL0 = RESET_STATE; // GP I/O
P5SEL1 = RESET_STATE; // GP I/O
P5DIR  = RESET_STATE; 
//P5_0
P5SEL0 |= SPI_UCB1SIMO; // USCI_B1 SIMO pin
P5SEL1 &= ~SPI_UCB1SIMO; // USCI_B1 SIMO pin
//P5_1
P5SEL0 |= SPI_UCB1SOMI; // USCI_B1 SOMI pin
P5SEL1 &= ~SPI_UCB1SOMI; // USCI_B1 SOMI pin
//P5_2
P5SEL0 |= SPI_UCB1CLK; // USCI_B1 SCLK pin
P5SEL1 &= ~SPI_UCB1CLK; // USCI_B1 SCLK pin
//P5_3
P5SEL0 &= ~RESET_LCD; // Set GP I/O for RESET_LCD
P5SEL1 &= ~RESET_LCD; // Set GP I/O for RESET_LCD
P5OUT |= RESET_LCD; // Set RESET_LCD Off [High]
P5DIR |= RESET_LCD; // Set RESET_LCD direction to output
//P5_4
P5SEL0 &= ~P5_4_UNUSED; // Set GP I/O for P5_4_UNUSED
P5SEL1 &= ~P5_4_UNUSED; // Set GP I/O for P5_4_UNUSED
P5DIR &= ~P5_4_UNUSED; // Set RESET_LCD direction to input
//P5_5
P5SEL0 &= ~BUTTON2; // Set GP I/O for BUTTON2
P5SEL1 &= ~BUTTON2; // Set GP I/O for BUTTON2
P5OUT |= BUTTON2; // Configure pullup resistor
P5DIR &= ~BUTTON2; // Direction = input
P5REN |= BUTTON2; // Enable pullup resistor
P5IES |= BUTTON2; // BUTTON2 Hi/Lo edge interrupt
P5IFG &= ~BUTTON2; // IFG BUTTON2 cleared
P5IE |= BUTTON2; // BUTTON2 interrupt enabled

//P5_6
P5SEL0 &= ~BUTTON1; // BUTTON1 set as I/0
P5SEL1 &= ~BUTTON1; // BUTTON1 set as I/0
P5DIR &= ~BUTTON1; // BUTTON1 Direction = input
P5OUT |= BUTTON1; // Configure pull-up resistor BUTTON1
P5REN |= BUTTON1; // Enable pull-up resistor BUTTON1
P5IES |= BUTTON1; // BUTTON1 Hi/Lo edge interrupt
P5IFG &= ~BUTTON1; // IFG BUTTON1 cleared
P5IE |= BUTTON1; // BUTTON1 interrupt Enabled

//P5_7
P5SEL0 &= ~LCD_BACKLITE; // Set PWM for LCD_BACKLITE
P5SEL1 |= LCD_BACKLITE; // Set PWM for LCD_BACKLITE
//P5OUT &= ~LCD_BACKLITE; // Set LCD_BACKLITE Off [Low]                           
P5DIR |= LCD_BACKLITE; // Set LCD_BACKLITE direction to output 


//P5 interrupts
  PM5CTL0 &= ~LOCKLPM5; 
  P5IES |= BUTTON2; // P4.0 Hi/Lo edge interrupt 
  P5IFG &= ~BUTTON2; // Clear all P5.6 interrupt flags 
  P5IE |= BUTTON2; // P5.6 interrupt enabled 
  P5IES |= BUTTON1; // P4.0 Hi/Lo edge interrupt 
  P5IFG &= ~BUTTON1; // Clear all P5.5 interrupt flags 
  P5IE |= BUTTON1; // P5.5 interrupt enabled 
//--------------------------------------------------------------------
}

void Init_Port6(void){
//Configure Port 6
P6SEL0 = RESET_STATE; // GP I/O
P6SEL1 = RESET_STATE; // GP I/O
//P6_0
P6SEL0 |= UCA3TXD; // UCA3TXD Function
P6SEL1 &= ~UCA3TXD; // UCA3TXD Function
//P6_1
P6SEL0 |= UCA3RXD; // UCA3RXD Function
P6SEL1 &= ~UCA3RXD; // UCA3RXD Function
//P6_2
P6SEL0 &= ~J1_5; // GP I/O
P6SEL1 &= ~J1_5; // GP I/O
P6OUT &= ~J1_5; // Input
P6DIR &= ~J1_5; // Output Low
//P6_3
P6SEL0 &= ~MAG_INT; // GP I/O
P6SEL1 &= ~MAG_INT; // GP I/O
P6OUT &= ~MAG_INT; // Input
P6DIR &= ~MAG_INT; // Output Low
//P6_4
P6SEL0 &= ~P6_4; // GP I/O
P6SEL1 &= ~P6_4; // GP I/O
P6OUT &= ~P6_4; // Input
P6DIR &= ~P6_4; // Output Low
//P6_5
P6SEL0 &= ~P6_5; // GP I/O
P6SEL1 &= ~P6_5; // GP I/O
P6OUT &= ~P6_5; // Input
P6DIR &= ~P6_5; // Output Low
//P6_6
P6SEL0 &= ~P6_6; // GP I/O
P6SEL1 &= ~P6_6; // GP I/O
P6OUT &= ~P6_6; // Input
P6DIR &= ~P6_6; // Output Low
//P6_7
P6SEL0 &= ~P6_7; // GP I/O
P6SEL1 &= ~P6_7; // GP I/O
P6OUT &= ~P6_7; // Input
P6DIR &= ~P6_7; // Output Low
}

void Init_Port7(void){
//Configure Port 7
  P7SEL0=RESET_STATE; //Reset SEL0
  P7SEL1=RESET_STATE; //Reset SEL1
  //P7_0
  P7SEL0 |= I2CSDA; //BP I2CSDA
  P7SEL1 &= ~I2CSDA; //BP I2CSDA
  //P7_1
  P7SEL0 |= I2CSCL; //BP I2CSCL
  P7SEL1 &= ~I2CSDA; //BP I2CSCL
   //P7_2
  P7SEL0 |= SD_DETECT; //SD DETECT
  P7SEL1 &= ~SD_DETECT; //SD_DETECT
   //P7_3
  P7SEL0 |= J4_36; //J4_36
  P7SEL1 &= ~J4_36; //J4_36
   //P7_4
  P7SEL0 &= ~P7_4; //GP I/O
  P7SEL1 &= ~P7_4; //GP I/O
  P7OUT &= ~P7_4; //Input
  P7DIR &= ~P7_4; //Output Low
  //P7_5
  P7SEL0 &= ~P7_5; //GP I/O
  P7SEL1 &= ~P7_5; //GP I/O
  P7OUT &= ~P7_5; //Input
  P7DIR &= ~P7_5; //Output Low
  //P7_6
  P7SEL0 &= ~P7_6; //GP I/O
  P7SEL1 &= ~P7_6; //GP I/O
  P7OUT &= ~P7_6; //Input
  P7DIR &= ~P7_6; //Output Low
  //P7_7
  P7SEL0 &= ~P7_7; //GP I/O
  P7SEL1 &= ~P7_7; //GP I/O
  P7OUT &= ~P7_7; //Input
  P7DIR &= ~P7_7; //Output Low
}

void Init_Port8(void){
//Configure Port 8
  P8SEL0=RESET_STATE; //RESET SEL0
  P8SEL1=RESET_STATE; //RESET SEL1
  //P8_0
  P8SEL0 &= ~IR_LED; //GP I/O       
  P8SEL1 &= ~IR_LED; //GP I/O
  P8OUT &= ~IR_LED; //Input
  P8DIR |= IR_LED; //Output High
  //P8_1
  P8SEL0 &= ~OPT_INT; //GP I/O       
  P8SEL1 &= ~OPT_INT; //GP I/O
  P8OUT &= ~OPT_INT; //Input
  P8DIR &= ~OPT_INT; //Output Low
  //P8_2
  P8SEL0 &= ~TMP_INT; //GP I/O       
  P8SEL1 &= ~TMP_INT; //GP I/O
  P8OUT &= ~TMP_INT; //Input
  P8DIR &= ~TMP_INT; //Output Low
  //P8_3
  P8SEL0 &= ~INT2; //GP I/O       
  P8SEL1 &= ~INT2; //GP I/O
  P8OUT &= ~INT2; //Input
  P8DIR &= ~INT2; //Output Low
}

void Init_PortJ(void){
//------------------------------------------------------------------------------
//Configure Port J
  PJSEL0 = RESET_STATE;               // For XT1
  PJSEL1 = RESET_STATE;               // For XT1
  PJDIR = RESET_STATE;                // Set PJ direction to input
  PJOUT = RESET_STATE;                // PJ set Low

  PJSEL0 |= LFXIN;             // For XT1
  PJSEL1 &= ~LFXIN;            // For XT1

  PJSEL0 |= LFXOUT;            // For XT1
  PJSEL1 &= ~LFXOUT;           // For XT1

  PJSEL0 &= ~HFXIN;            // For XT1
  PJSEL1 &= ~HFXIN;            // For XT1

  PJSEL0 &= ~HFXOUT;           // For XT1
  PJSEL1 &= ~HFXOUT;           // For XT1
//------------------------------------------------------------------------------
}