#pragma once

#include "wled.h"

/*
 * Usermod for 3D printed 7 segment digital clock
 *
 */

class UsermodDigitalClock : public Usermod {
  private:

  // Private class members. You can declare variables and functions only accessible to your usermod here
    bool enabled = false;
    bool initDone = false;
    unsigned long lastTime = 0;

     // string that are used multiple time (this will save some flash memory)
    static const char _name[];
    static const char _enabled[];

/*
 * Digital clock defines and global
 */

    const int NUM_DIGITS            = 4 ;    // Number of connected Digits 
    const int NUM_PIXEL_PER_SEGMENT = 3 ;    // Number of LEDs in each Segment
    const int NUM_PIXEL_PER_DOTS    = 2 ;    // Number of pixel per dots

    const int NUM_DOTS              =  (NUM_DIGITS/2) - 1; //Number of "dots" between digits: 1 for 4 digits, 2 for 6 digits
    //Total number of LEDs:
    //const int NUM_LEDS           (NUM_PIXEL_PER_SEGMENT*7)*NUM_DIGITS + NUM_PIXEL_PER_DOTS ;

    //Digits array
    byte digitsMatrix[12] = {
      //abcdefg
      0b1111110,     // 0
      0b1000010,     // 1
      0b0110111,     // 2
      0b1100111,     // 3
      0b1001011,     // 4
      0b1101101,     // 5
      0b1111101,     // 6
      0b1000110,     // 7
      0b1111111,     // 8
      0b1101111,     // 9
      0b0111100,     // C
      0b0011100,     // F
    };

/*
 * Support for the 7-Segment style digital clock
 */
void writeDigit(int index, int val) {
  byte digit = digitsMatrix[val];
  int margin;
  //Choose margin for dots pixel
  if (index == 0 || index == 1 ) margin = 0;
  if (index == 2 || index == 3 ) margin = 1;
  if (index == 4 || index == 5 ) margin = 2;
  //Bit vector indexing
  for (int i = 6; i >= 0; i--) {
    int offset = (index * (NUM_PIXEL_PER_SEGMENT * 7)) + (i * NUM_PIXEL_PER_SEGMENT) + (margin * NUM_PIXEL_PER_DOTS);
    //Pixel in a digit indexing
    for (int j = offset; j < offset + NUM_PIXEL_PER_SEGMENT; j++) {
      if ((digit & 0x01) == 0) {
        strip.setPixelColor(j, 0x000000);
      }
    }
    digit = digit >> 1;
  }
}

void blinkDots(void) {
  int dot;
  for (int i = 0; i < NUM_PIXEL_PER_DOTS; i++) {
    // 2 digits before first dots pixel
    dot = 2 * (NUM_PIXEL_PER_SEGMENT * 7) + i;
    if(second(localTime) % 2 == 0) strip.setPixelColor(dot, 0x000000);
  }
}

/**
     * Enable/Disable the usermod
     */
    inline void enable(bool enable) { enabled = enable; }

    /**
     * Get usermod enabled/disabled state
     */
    inline bool isEnabled() { return enabled; }

void _overlayDigitalClock()
{
  byte hr = hour(localTime);

  if (useAMPM && !countdownMode)
  {
    if (hr>12) hr-=12;
    else if (hr == 0) hr +=12;
  }
  writeDigit(3, hr / 10);
  writeDigit(2, hr % 10);
  writeDigit(1, minute(localTime) / 10);
  writeDigit(0, minute(localTime) % 10);
  blinkDots();
}



  public:
    UsermodDigitalClock() {

    }
    void setup() {

    }

    void loop() {
      if (!toki.isTick()) return;
      strip.trigger();
    }

    void handleOverlayDraw() {
        _overlayDigitalClock();
    }

    uint16_t getId()
    {
        return USERMOD_ID_DIGITAL_CLOCK;
    }
};

// add more strings here to reduce flash memory usage
const char UsermodDigitalClock::_name[]    PROGMEM = "UsermodDigitalClock";
const char UsermodDigitalClock::_enabled[] PROGMEM = "enabled";