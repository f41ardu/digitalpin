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
  public:                             // öffentlich
    digitalPin();                   // der Default-Konstruktor
    digitalPin(uint8_t);             // Konstruktor mit Parameter
    digitalPin(unsigned int,  uint8_t ); // Button Debounce
    digitalPin(uint8_t, unsigned int, unsigned int);
    //   digitalPin(const LED& a);     // Copy-Konstruktor wird nicht benötigt
    ~digitalPin();                     // Class Destruktor
    // Funktionen
    uint8_t init(uint8_t);           // einen PIN initialisieresn
    void on();                        // einen PIN einschalten
    void off();                       // einen PIN ausschalten
    void blink(int);        // PIN ein und auschalten (intervall)
    void fade(uint8_t);             // eine Spannung (0 .. 5Volt/255) am PIN ausgeben
    void timechange(int, int);
    void toggle();                    // PIN Zustand umschalten (ON/OFF, OFF/ON)
    void flash();                     // PIN ein und auschalten (OnTime, OffTime)
    bool tread();                     // PIN Button lesen
    bool read();                      // PIN status lesen
    void write(bool);

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


