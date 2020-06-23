#include <Arduino.h>
#include "display.h"
#include "LedControl.h"

//if arduino has no memory left put "static" in front of int
// numbers several letters and all on example
int one[8]              = {B00000000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00000000};
int two[8]              = {B01111110, B01100000, B01100000, B01111110, B00000110, B00000110, B01111110, B00000000};
int three[8]            = {B01111110, B01111110, B01100000, B01111110, B01111110, B01100000, B01111110, B01111110};
int four[8]             = {B01100110, B01100110, B01100110, B01100110, B01111110, B00000110, B00000110, B00000110};
int five[8]             = {B01111110, B01111110, B01100000, B01100000, B01111110, B00000110, B00000110, B01111110};
int six[8]              = {B01111110, B01111110, B01100000, B01111110, B01100110, B01100110, B01111110, B00000000};
int seven[8]            = {B01111110, B01111110, B00000110, B00001100, B00011000, B00110000, B01100000, B11000000};
int eight[8]            = {B01111110, B01111110, B01100110, B01100110, B01111110, B01100110, B01100110, B01111110};
int nine[8]             = {B01111110, B01100110, B01100110, B01100110, B01111110, B00000110, B01100110, B01111110};
int zero[8]             = {B01111110, B01111110, B01100110, B01100110, B01100110, B01100110, B01111110, B01111110};
int letterL[8]          = {B00000110, B00000110, B00000110, B00000110, B00000110, B00000110, B01111110, B01111110};
int letterR[8]          = {B00111110, B01111110, B01100110, B00111110, B00111110, B01100110, B01100110, B01100110};
int letterT[8]          = {B01111110, B01111110, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000};
int allOn[8]            = {B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111};
int arrowBottomRight[8] = {B00000001, B00000010, B00000100, B00001000, B00010000, B10100000, B11000000, B11100000};
int music[8]            = {B01000000, B01000000, B01000000, B01010000, B01111000, B01111100, B00111000, B00010000};

LedControl lc = LedControl(12,11,10,1);

void clearMatrix(){
    lc.clearDisplay(0);
}

void initialiseLED(){
    lc.shutdown(0,false);
    lc.setIntensity(0,1);
    lc.clearDisplay(0); 
}

void printToMatrix(int number){
    lc.clearDisplay(0);
    if(number == 1){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, one[c]);
        }
      } else if(number == 2){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, two[c]);
        }
      } else if(number == 3){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, three[c]);
        }
      } else if(number == 4){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, four[c]);
        }
      } else if(number == 5){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, five[c]);
        }
      } else if(number == 6){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, six[c]);
        }
      } else if(number == 7){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, seven[c]);
        }
      } else if(number == 8){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, eight[c]);
        }
      } else if(number == 9){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, nine[c]);
        }
      } else if(number == 0){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, zero[c]);
        }
      } else if(number == 'l'){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, letterL[c]);
        }
      } else if(number == 'r'){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, letterR[c]);
        }
      } else if(number == 't'){
        for(int c = 0; c < 8; c++){
          lc.setColumn(0, c, letterT[c]);
        }
      } else if(number == ' '){
        // for(int c = 0; c < 8; c++){
        //   lc.setColumn(0, c, allOn[c]);
        printArray(allOn);
      } else if (number == '-'){
        printArray(arrowBottomRight);
      } else if (number == 'm'){
        printArray(music);
      }
      

}

void printArray(int* array){
  for(int c = 0; c < 8; c++){
    lc.setColumn(0, c, array[c]);
  }
}

void printDot(int row, int col){
  lc.setLed(0, row, col, 1);
}
