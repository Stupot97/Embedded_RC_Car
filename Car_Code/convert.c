#include "macros.h"
#include "msp430.h"
#include "functions.h"

char string[ARRAY11];
char string2[ARRAY11];
int tens_places[ARRAY4];

void convert(int L_detect, int R_detect, int thumb){
  tens_places[ARRAY0]=L_detect%TENS;
  tens_places[ARRAY1]=(L_detect%HUNDREDS-tens_places[ARRAY0])/TENS;
  tens_places[ARRAY2]=(L_detect%THOUSANDS-tens_places[ARRAY0]-tens_places[ARRAY1]*TENS)/HUNDREDS;
  tens_places[ARRAY3]=(L_detect%TENTHOUSANDS-tens_places[ARRAY0]-tens_places[ARRAY1]*TENS-tens_places[ARRAY2]*HUNDREDS)/THOUSANDS;
     
  string[ARRAY0]=tens_places[ARRAY3]+CHAR_INCREMENT;
  string[ARRAY1]=tens_places[ARRAY2]+CHAR_INCREMENT;
  string[ARRAY2]=tens_places[ARRAY1]+CHAR_INCREMENT;
  string[ARRAY3]=tens_places[ARRAY0]+CHAR_INCREMENT;
  
  tens_places[ARRAY0]=R_detect%TENS;
  tens_places[ARRAY1]=(R_detect%HUNDREDS-tens_places[ARRAY0])/TENS;
  tens_places[ARRAY2]=(R_detect%THOUSANDS-tens_places[ARRAY0]-tens_places[ARRAY1]*TENS)/HUNDREDS;
  tens_places[ARRAY3]=(R_detect%TENTHOUSANDS-tens_places[ARRAY0]-tens_places[ARRAY1]*TENS-tens_places[ARRAY2]*HUNDREDS)/THOUSANDS;
  
  string[ARRAY4]=' ';
  string[ARRAY5]=tens_places[ARRAY3]+CHAR_INCREMENT;
  string[ARRAY6]=tens_places[ARRAY2]+CHAR_INCREMENT;
  string[ARRAY7]=tens_places[ARRAY1]+CHAR_INCREMENT;
  string[ARRAY8]=tens_places[ARRAY0]+CHAR_INCREMENT;
  string[ARRAY9]=' ';
  
  tens_places[ARRAY0]=thumb%TENS;
  tens_places[ARRAY1]=(thumb%HUNDREDS-tens_places[ARRAY0])/TENS;
  tens_places[ARRAY2]=(thumb%THOUSANDS-tens_places[ARRAY0]-tens_places[ARRAY1]*TENS)/HUNDREDS;
  tens_places[ARRAY3]=(thumb%TENTHOUSANDS-tens_places[ARRAY0]-tens_places[ARRAY1]*TENS-tens_places[ARRAY2]*HUNDREDS)/THOUSANDS;
  
  string2[ARRAY0]=' ';
  string2[ARRAY1]=' ';
  string2[ARRAY2]=' ';
  string2[ARRAY3]=tens_places[ARRAY3]+CHAR_INCREMENT;
  string2[ARRAY4]=tens_places[ARRAY2]+CHAR_INCREMENT;
  string2[ARRAY5]=tens_places[ARRAY1]+CHAR_INCREMENT;
  string2[ARRAY6]=tens_places[ARRAY0]+CHAR_INCREMENT;
  string2[ARRAY7]=' ';
  string2[ARRAY8]=' ';
  string2[ARRAY9]=' ';
}

