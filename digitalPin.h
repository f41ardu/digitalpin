/*
   Devlopment Branch
*/
// http://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Klassen

#ifndef digitalPin_H
#define digitalPin_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"  // for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif
//#include <inttypes.h>

class digitalPin
{
  public:                             // Public 
    digitalPin();                   // Default-Constructor
    digitalPin(uint8_t);             // Constructor with parameter - paramater number of pin used internal
    digitalPin(unsigned int,  uint8_t ); // Button constructor time in ms, pin 
    digitalPin(uint8_t, unsigned int, unsigned int);
    ~digitalPin();                     // Class Destruktor
    // Funktionen
    uint8_t init(uint8_t);           // Init PIN 
    void on();                        // PIN on 
    void off();                       // PIN off
    void blink(int);        // PIN on / off intervall in ms
    void fade(uint8_t);             // Voltage to PIN (0 .. 255) -> 0 .. 5 volt
    void timechange(int, int);        // Set ON/OFF time in ms
    void toggle();                    // Toggle PIN  ON/OFF, OFF/ON)
    void flash();                     // Flash PIN (OnTime, OffTime)
    bool tread();                     // Read Button state (debounced)
    bool read();                      // read status
    void write(bool);                 // write status

    // Operator Overload
    digitalPin& operator=(bool);
    digitalPin& operator&&(digitalPin&);
    digitalPin& operator||(digitalPin&);
    digitalPin& operator!(void);
    operator bool();

  private:                            // privat
    bool _status;
    uint8_t _pin;
    unsigned int _previousMillis, _currentMillis, _intervalMillis, _OnTime, _OffTime;

    class digitalPin *next;
    static digitalPin* first;
};

#endif // digitalPin


