//This file contains all the macros to be used in main and the port initialization file

#define ALWAYS                  (1)
#define ONE                     (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x02) // GREEN LED 1
#define TIME1                 (0x19) //0.25 seconds
#define TIME2                   (0x32) //0.50 seconds
#define TIME3                    (0x4B)    //0.75 seconds
#define TIME4                   (0x64)     //1 second
#define TIME5                    (0x7D)    //1.25 seconds
#define FALSE                     (0x0)
#define TRUE                      (0x1)
#define ARRAY0                  (0x0)
#define ARRAY1                  (0x1)
#define ARRAY2                  (0x2)
#define ARRAY3                  (0x3)
#define ARRAY4                  (0x4)
#define ARRAY5                  (0x5)
#define ARRAY6                  (0x6)
#define ARRAY7                  (0x7)
#define ARRAY8                  (0x8)
#define ARRAY9                  (0x9)
#define ARRAY10                 (0xA)
#define ARRAY11                 (0xB)
#define ARRAY14                 (0x0E)
#define ARRAY15                 (0x0F)
#define ARRAY16                 (0x10)
#define ARRAY18                 (0x12)
#define ARRAY23                 (0x17)
#define ARRAY24                 (0x18)
#define ARRAY25                 (0x19)
#define ARRAY35                 (0x23)
#define ARRAY36                 (0x24)
#define ARRAY37                 (0x25)
#define ARRAY63                 (0x3F)
#define LARGEST_NUM             (0xFFFF)

//Clocks Macros
#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK                  (0x01) // Any incorrect password locks registers

// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)


// Port 1 Pins
#define RED_LED (0x01) // RED LED – P1_0_LED1
#define GRN_LED (0x02) // GREEN LED – P1_1_LED2
#define V_THUMB (0x04) // ADC for Thumb Wheel
#define TEST_PROBE (0x08) // GP I/O Pin to use to check code operation
#define V_DETECT_R (0x10) // ADC for Right Detector
#define V_DETECT_L (0x20) // ADC for Left Detector
#define SD_UCB0SIMO (0x40) // SPI mode - slave in/master out for SD Card
#define SD_UCB0SOMI (0x80) // SPI mode - slave out/master in for SD Card

// Port 2 Pins
#define BCLUART_TXD (0x01) //BCLUART Data Out
#define BCLUART_RXD (0x02) //BCLUART Data In
#define SD_SPICLK (0x04) //SD SPICLK
#define P2_3 (0x08) //P2_3
#define P2_4 (0x10) //P2_4
#define UCA1TXD (0x20) //UCAI Data Out
#define UCA1RXD (0x40) //UCAI Data In
#define P2_7 (0x80) //P2_7


// Port 3 Pins
#define IOT_RESET (0x01) // RESET
#define IOT_STA_MINIAP (0x02) // IOT_STA_MINIAP
#define IOT_LINK (0x04) // IOT_LINK
#define IOT_WAKEUP (0x08) // IOT_WAKEUP
#define L_REVERSE (0x10) // Left Reverse
#define L_FORWARD (0x20) // Left Forward
#define R_REVERSE (0x40) // Right Reverse
#define R_FORWARD (0x80) // Right Forward
#define OUT_DIR (0xFF)//Output Direction for Port 3

// Port 4 Pins
#define SD_CS (0x01) //SD Chip Select
#define J4_31 (0x02) //J4_31 GP I/O
#define J4_32 (0x04) //J4_32 GP I/O
#define J4_33 (0x08) //J4_33 GP I/O
#define UCB1_CS_LCD (0x10) //UCB LCD Chip Select
#define P4_4 (0x20) //BP Header I/O
#define P4_5 (0x40) //P4_5
#define J3_29 (0x80) //J3_29 GP I/O


// Port 5 Pins
#define SPI_UCB1SIMO (0x01) // UCB1SIMO
#define SPI_UCB1SOMI (0x02) // UCB1SOMI
#define SPI_UCB1CLK (0x04) // SPI mode - clock output—UCB1CLK
#define RESET_LCD (0x08) // LCD Reset
#define P5_4_UNUSED (0x10) // UNUSED
#define BUTTON2 (0x20) // Button 2
#define BUTTON1 (0x40) // Button 1
#define LCD_BACKLITE (0x80) // LCD Backlite

// Port 6 Pins
#define UCA3TXD (0x01) //UCA3 Data Out
#define UCA3RXD (0x02) //UCA3 Data In
#define J1_5 (0x04) //BP Header GP I/O
#define MAG_INT (0x08) //MAG_INT GP I/O
#define P6_4 (0x10) //P6_4 I/O
#define P6_5 (0x20) //P6_5 I/O
#define P6_6 (0x40) //P6_6 I/O
#define P6_7 (0x80) //P6_7 I/O

// Port 7 Pins
#define I2CSDA (0x01) //BP I2CSDA
#define I2CSCL (0x02) //BP I2CSCL
#define SD_DETECT (0x04) //SD Card Detector
#define J4_36 (0x08) //Timer Capture J4_36
#define P7_4 (0x10) //P7_4
#define P7_5 (0x20) //P7_5
#define P7_6 (0x40) //P7_6
#define P7_7 (0x80) //P7_7

//Port 8 Pins
#define IR_LED (0x01) //IR LED
#define OPT_INT (0x02) //OPT INT
#define TMP_INT (0x04) //TMP INT
#define INT2 (0x08) //INT2

//Port J Pins
#define PJ_0 (0x01) //PJ_0
#define PJ_1 (0x02) //PJ_1
#define PJ_2 (0x04) //PJ_2
#define PJ_3 (0x08) //PJ_3
#define LFXIN (0x10) // LFXIN
#define LFXOUT (0x20) // LFXOUT
#define HFXIN (0x40) // HFXIN
#define HFXOUT (0x80) // HFXOUT

//Timer
#define TA0CCR0_INTERVAL (25000)  //timer interval of 50 msec
#define TwentiethSec (0x01) //50ms
#define FifthSec (0x04) 
#define QuarterSec (0x05)
#define HalfSec (0x0A)
#define FullSec (0x14)
#define TwoFullSec (0x28)
#define ThreeFullSec (0x3C)
#define FourFullSec (0x50)
#define ThreeSec (0x0F)
#define FiveSec (0x64)
#define TwentySec (0x190)
#define ThirtySec (0x258)

//ADC
#define DEFAULT_BLACK (3300)
#define DEFAULT_WHITE (1900)
#define TENS (0xA)
#define HUNDREDS (0x64)
#define THOUSANDS (0x03E8)
#define TENTHOUSANDS (0x2710)
#define CHAR_INCREMENT (0x30)

//MENU
#define MENU_SEL (0x3E)
#define ITEM1 (0x200)
#define ITEM2 (0x400)
#define ITEM3 (0x600)
#define ITEM4 (0x800)
#define ITEM5 (0xA00)
#define ITEM6 (0xC00)
#define ITEM7 (0xE00)
#define ITEM8 (0x1000)
#define LINE (0x00)
#define BAUDMODE (0x01)
#define LIGHTMODE (0x02)
#define CALMODE (0x00)
#define NAVMODE (0x01)
#define BAUD_RATE1 (0x00)
#define BAUD_RATE2 (0x01)
#define RECEIVE (0x02)
#define WHITE_SURFACE (0x00)
#define BLACK_LINE (0x01)
#define START_MENU (0x00)
#define DIRECTION_MENU (0x01)
#define LINE_MENU (0x02)
#define CALIBRATION_MENU (0x03)
#define NAVIGATION_MENU (0x04)
#define BAUD_MENU (0x05)
#define DISPLAY_MENU (0x06)
#define RECEIVE_MENU (0x07)
#define BACKLIGHT_MENU (0x08)
#define SEL1 (0x00)
#define SEL2 (0x01)
#define SEL3 (0x02)
#define SEL4 (0x03)
#define SEL5 (0x04)
#define STATE1 (0x00)
#define STATE2 (0x01)
#define STATE3 (0x02)
#define STATE4 (0x03)
#define STATE5 (0x04)
#define STATE6 (0x05)

//PWM
#define WHEEL_PERIOD (40000)
#define WHEEL_OFF (0x00)
#define LEFT_REVERSE_SPEED (TB0CCR3)
#define LEFT_FORWARD_SPEED (TB0CCR4)
#define RIGHT_REVERSE_SPEED (TB0CCR5)
#define RIGHT_FORWARD_SPEED (TB0CCR6)
#define BACKLIGHT_PERIOD (4095)
#define BACKLIGHT_OFF (0x00)
#define BACKLIGHT_ON (TA4CCR1)
#define DUTY_CYCLE_10 (4000) //10% duty cycle
#define DUTY_CYCLE_15 (6000) //15% duty cycle
#define DUTY_CYCLE_25 (10000) //25% duty cycle
#define DUTY_CYCLE_38 (15000) //37.5% duty cycle
#define DUTY_CYCLE_50 (20000) //50% duty cycle
#define DUTY_CYCLE_56 (23200) //58% duty cycle
#define DUTY_CYCLE_63 (25000) //62.5% duty cycle
#define DUTY_CYCLE_88 (35000) //87.5% duty cycle

//serial
#define BEGINNING (0)
#define SMALL_RING_SIZE (64)
#define BAUD_RATE_115200 (115)
#define BAUD_RATE_115200_BRW (4)
#define BAUD_RATE_115200_MCTLW (0x5551)
#define BAUD_RATE_460800 (460)
#define BAUD_RATE_460800_BRW (1)
#define BAUD_RATE_460800_MCTLW (0x4A11)

//interrupt vectors
#define NOVECTOR (0)
#define RECEIVEVECTOR (2)
#define TRANSMIT (4)
#define UCA0IVMAX (0x08)
#define UCA3IVMAX (0x08)

//IOT command directions
#define DEFAULT    (0x00)
#define GO_FORWARD (0x01)
#define GO_REVERSE (0x02)
#define GO_LEFT    (0x03)
#define GO_RIGHT   (0x04)