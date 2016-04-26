/************************************************************************
 * Arduino Code for 1241 LED strip using NeoPixel Libary from Adafruit
 * https://learn.adafruit.com/adafruit-neopixel-uberguide/overview
 * To Download the Libary go to sketch/include libary/manage libaries/ and search for neopixel and you can download it
 * 
 * Year: 2016
 * Author: James Taylor
 * 
 * WARNING BEFORE STARTING MAKE SURE THERE IS A 1000uF CAPACITOR CONNECTED TO THE POWER SUPPLY GOING TO THE LED STRIP
 * OTHERWISE YOU COULD DAMAGE THE STRIP. ALSO MAKE SURE THERE IS A 300Î© TO 500Î© RESISTOR CONNECTED BETWEEN THE ARDUINO
 * AND THE LED STRIP DIN PORT
 * 
 * Ways to output to LED
 * 1)
 *      strip.setPixelColor(n, red, green, blue);
 *      n = led number in strip, 0 is first LED, Last led will be n-1 ex.. 60 leds in strip last led will be 59
 *      red = pixel color, 0 is off and 255 is max 
 *      green = pixel color, 0 is off and 255 is max
 *      blue = pixel color, 0 is off and 255 is max
 * 2)
 *      strip.setPixelColor(n, color);
 *      in order to do this one you first need to declare the color
 *      ex.. 
 *      uint32_t magenta = strip.Color(255,0,255);
 *      strip.setPixelColor(10, magenta);
 *      this will set the 10th pixel to magenta
 *      
 * setPixelColor does not update right away in order to upadate you need to call
 *      strip.show();
 * 
 * if you want to change the brightnees of the leds you can use
 *      strip.setBrightness(x);
 *      x = a value between 0 (off) and 255 (max)
 *      needs to be updated with strip.show();
 *      recomended that you use this in the setup loop, not intended for constant use
 *      
 * for loop structure
 * ex.. will turn the leds to red starting with the first led all the way to the last one
 *      for(uint16_t i = 0; i<strip.numPixels(); i++)
 *      {
 *        strip.setPixelColor(i, 255,0,0);
 *      }
 *      strip.show();
 *      delay(50);
 *      
 */

/*
 * Included libaries
 */
#include <Adafruit_NeoPixel.h>

/*
 * Global Variables
 */
#define PIN 9 // Left Strip
#define PIN2 10 // Center Strip
#define PIN3 11 // Right Strip
#define LED 18 // Number of Leds in strip
const int rioInput = 2; // First Input from roboRio
const int rioInput1 = 3; // Secound Input from roboRio
boolean team = false; // to know what team you are on

/*
 * Initialization 
 * 
 * NEO_GRB type of flag
 * NEO_KHZ800 800 KHz bitstream for WS2812 LEDS
 */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(LED, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(LED, PIN3, NEO_GRB + NEO_KHZ800);

/*
 * Color Declerations
 */
uint32_t blue = strip.Color(0,192,255);

/*
 * Setup loop will run once
 */
void setup() {
  //make the rioInputs Inputs
  pinMode(rioInput, INPUT);
  pinMode(rioInput1, INPUT);
  //Start the strip 
  strip.begin();
  strip.setBrightness(150);
  strip2.begin();
  strip2.setBrightness(150);
  strip3.begin();
  strip3.setBrightness(150);
  strip.show();
  strip2.show();
  strip3.show();
}

/*
 * Main loop runs constantly 
 */
void loop() {

  //When input from rio is 1,1
  if (digitalRead(rioInput) == HIGH && digitalRead(rioInput1) == HIGH) 
  {
    pattern1();
  }
  //When input from rio is 0,1
  else if (digitalRead(rioInput) == LOW && digitalRead(rioInput1) == HIGH)
  {
    team = true;
    pattern2();
  }
  //When input from rio is 1,0
  else if (digitalRead(rioInput) == HIGH && digitalRead(rioInput1) == LOW)
  {
    team = false;
    pattern3();
  }
  //When input from rio is 0,0 and default off
  else
  {
     uint16_t i, j;
  
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      for(i=0; i<strip.numPixels(); i++) {
        if(digitalRead(rioInput) == HIGH || digitalRead(rioInput1) == HIGH)
        break;
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) - j) & 255));
        strip2.setPixelColor(i, Wheel(((i * 256 / strip2.numPixels()) - j) & 255));
        strip3.setPixelColor(i, Wheel(((i * 256 / strip3.numPixels()) -  j) & 255));
      }
      if(digitalRead(rioInput) == HIGH || digitalRead(rioInput1) == HIGH)
        break;
      strip.show();
      strip2.show();
      strip3.show();
      delay(5);
  }
  }
}

/*
 * Pattern 1 Shooting 
 */
 void pattern1(){
  if(team == true){
    for(int y = 0; y<strip.numPixels(); y++){
    //turn off leds
      strip.setPixelColor(y, 0, 0, 255);
      strip2.setPixelColor(y, 0, 0, 255);
      strip3.setPixelColor(y, 0, 0, 255);
  }
    strip.show();
    strip2.show();
    strip3.show();
    delay(10);
  uint16_t i, x, d;
  for(i = 0; i<5; i++){
      //turn on leds
      strip.setPixelColor(i-1, 255, 50, 0);
      strip2.setPixelColor(i+2, 255, 50, 0);
      strip3.setPixelColor(i-1, 255, 50, 0);
    }
    strip.show();
    strip2.show();
    strip3.show();
    delay(100);
  for(x = 0; x<strip.numPixels(); x++){
    //turn on leds
      strip.setPixelColor(i-1+x, 255, 50, 0);
      strip2.setPixelColor(i+2+x, 255, 50, 0);
      strip3.setPixelColor(i-1+x, 255, 50, 0);
    strip.show();
    strip2.show();
    strip3.show();
      //turn on leds
      strip.setPixelColor(x, 0, 0, 255);
      strip2.setPixelColor(x+3, 0, 0, 255);
      strip3.setPixelColor(x, 0, 0, 255);
   if(x==0)
   {
    strip2.setPixelColor(2,0,0,255);
   }
    
    strip.show();
    strip2.show();
    strip3.show();
    delayMicroseconds(140000);
  }
  }
  else if (team == false){
    for(int y = 0; y<strip.numPixels(); y++){
    //turn off leds
      strip.setPixelColor(y, 255, 0, 0);
      strip2.setPixelColor(y, 255, 0, 0);
      strip3.setPixelColor(y, 255, 0, 0);
  }
    strip.show();
    strip2.show();
    strip3.show();
    delay(10);
  uint16_t i, x, d;
  for(i = 0; i<5; i++){
      //turn on leds
      strip.setPixelColor(i-1, 0, 0, 255);
      strip2.setPixelColor(i+2, 0, 0, 255);
      strip3.setPixelColor(i-1, 0, 0, 255);
    }
    strip.show();
    strip2.show();
    strip3.show();
    delay(100);
  for(x = 0; x<strip.numPixels(); x++){
    //turn on leds
      strip.setPixelColor(i-1+x, 0, 0, 255);
      strip2.setPixelColor(i+2+x, 0, 0, 255);
      strip3.setPixelColor(i-1+x, 0, 0, 255);
    strip.show();
    strip2.show();
    strip3.show();
      //turn on leds
      strip.setPixelColor(x, 255, 0, 0);
      strip2.setPixelColor(x+3, 255, 0, 0);
      strip3.setPixelColor(x, 255, 0, 0);
   if(x==0)
   {
    strip2.setPixelColor(2, 255, 0, 0);
   }
    
    strip.show();
    strip2.show();
    strip3.show();
    delayMicroseconds(140000);
  }
  }
  
  delay(500);
 }

/*
 * Pattern 2 Blue
 */
void pattern2(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 255);
    strip2.setPixelColor(i, 0, 0, 255);
    strip3.setPixelColor(i, 0, 0, 255);
  }
  strip.show();
  strip2.show();
  strip3.show();
  delay(10);
}

/*
 * pattern3 Red
 */
void pattern3() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 0, 0);
    strip2.setPixelColor(i, 255, 0, 0);
    strip3.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
  strip2.show();
  strip3.show();
  delay(10);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
