#include <FastLED.h>

#define ROWS 360 // 36 leds * 10 boxes
#define COLS 9
#define RATE 3 // 3 seems like the ideal value, slowdown if glitches appear at the end of the strips but watchout for dropping FPS

//set teensy at 144 mhz

CRGB leds[COLS][ROWS];//holds the values of the leds for fastled output

int indexcount;//counter for serial, resets on incoming byte 255, then counts which led the serial is receiving

unsigned long lastOutputTime = 0;
unsigned long timeSinceLastOutput = 0;

void setup() {
  lastOutputTime = 0;
  Serial.begin(2500000);// baud rate 2500000

  //setup led outputs, port numbers and order tested, from the pcb schematic
  FastLED.addLeds<APA102, 5, 6, BGR, DATA_RATE_MHZ(RATE)>(leds[2], ROWS);
  FastLED.addLeds<APA102, 7, 8, BGR, DATA_RATE_MHZ(RATE)>(leds[1], ROWS);
  FastLED.addLeds<APA102, 25, 26, BGR, DATA_RATE_MHZ(RATE)>(leds[0], ROWS);
  FastLED.addLeds<APA102, 27, 28, BGR, DATA_RATE_MHZ(RATE)>(leds[5], ROWS);
  FastLED.addLeds<APA102, 29, 30, BGR, DATA_RATE_MHZ(RATE)>(leds[4], ROWS);
  FastLED.addLeds<APA102, 31, 32, BGR, DATA_RATE_MHZ(RATE)>(leds[3], ROWS);
  FastLED.addLeds<APA102, 0, 1, BGR, DATA_RATE_MHZ(RATE)>(leds[8], ROWS);
  FastLED.addLeds<APA102, 3, 4, BGR, DATA_RATE_MHZ(RATE)>(leds[7], ROWS);
  FastLED.addLeds<APA102, 19, 18, BGR, DATA_RATE_MHZ(RATE)>(leds[6], ROWS);
}

void loop() {

  //the following sets a single led's value and the counter
  if (Serial.available()) {
    while (Serial.available() > 0) {
      int incomingByte = Serial.read();//read single byte
      if (incomingByte == 255)//reset byte is 255, resets the counter for setting led values
      {
        indexcount = 0;//reset counter
      }
      else //not start byte, so value byte. value between 0 and 254 correspond to led brightness
      {
        int value = incomingByte;
        if (indexcount < ROWS * COLS)//check if counter hasn't glitched
        {
          int x = indexcount % COLS;
          int y = indexcount / COLS; //get strip output index [0 -> 9] from counter
          //set led values
          leds[x][y].red = value;
          leds[x][y].green = value;
          leds[x][y].blue = value;
        }
        indexcount++;// increment counter to next led
      }
    }
    
      FastLED.show();//send led data to strips

      //Serial watchdog
      
      timeSinceLastOutput = millis() - lastOutputTime;
      Serial.write(255);
      Serial.write(timeSinceLastOutput & 11111111);

      lastOutputTime = millis();//update time for output counter
    
  }


/*
  //fastled output
  if (millis() - lastOutputTime   > 15)//check if it's been 15 milliseconds since last output (don't want to output too fast)
  {
    //Serial.println(millis() - lastOutputTime);//uncomment for debugging: print framerate (frame duriation, should print 15)
    FastLED.show();//send led data to strips

    //Serial watchdog
    timeSinceLastOutput = constrain(millis() - lastOutputTime, 0, 254);
    Serial.write(255);
    Serial.write(char(timeSinceLastOutput));

    lastOutputTime = millis();//update time for output counter
  }
*/

}

