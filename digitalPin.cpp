/*
  Devlopment Branch
*/
// http://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Klassen

#include "digitalPin.h"

digitalPin *digitalPin::first;

digitalPin::digitalPin(): // Constructor
  _pin(0), _status(0)
{
  //leerer Constructor;
}
digitalPin::digitalPin(uint8_t a): // Constructor mit Initialisierung
  _pin(a)
{
  init(_pin);
}
digitalPin::digitalPin(unsigned int intervall, uint8_t a): // Constructor mit Initialisierung
  _pin(a), _intervalMillis(intervall)
{
  init(_pin);
  _previousMillis = millis();
}
digitalPin::digitalPin(uint8_t pin, unsigned int OnTime, unsigned int OffTime): // Contructor
  _pin(pin), _OnTime(OnTime), _OffTime(OffTime)
{
  init(_pin);
  _previousMillis = millis();
  off();
}
digitalPin::~digitalPin() // Destructor
{
}
uint8_t digitalPin::init(uint8_t pin) // PIN intialsieren
{
  _pin = pin;                   // speichert den LED Pin in der privaten Variable _led
  next = first;
  first = this;
  pinMode(_pin, OUTPUT);
  return 1;
}
void digitalPin::on() // LED ein
{
  _status = HIGH;
  digitalWrite(_pin, HIGH); //set the pin HIGH and thus turn LED on
}

void digitalPin::off() // LED aus
{
  _status = LOW;
  digitalWrite(_pin, LOW); //set the pin HIGH and thus turn LED off
}

void digitalPin::blink(int intervall) // LED intervall ms blinken lassen
{
  // check to see if it's time to change the state of the LED
  if ((_currentMillis - _previousMillis >= intervall / 2))
  {
    toggle();  // Turn it off
    _previousMillis = _currentMillis;  // Remember the time
  }
  else if ((_currentMillis - _previousMillis >= intervall / 2))
  {
    toggle();  // turn it on
    _previousMillis = _currentMillis;   // Remember the time
  }
  _currentMillis = millis();
}

void digitalPin::fade(uint8_t value) // LED Helligkeit setzen
{
  analogWrite(_pin, value);
}

void digitalPin::toggle()
{
  _status ? off() : on();
}

void digitalPin::timechange(int OnTime, int OffTime) //
{
  _OnTime = OnTime;
  _OffTime = OffTime;
}

void digitalPin::flash() {
  // check to see if it's time to change the state of the LED
  if ((_currentMillis - _previousMillis >= _OnTime))
  {
    toggle();  // Turn it off
    _previousMillis = _currentMillis;  // Remember the time
  }
  else if ((_currentMillis - _previousMillis >= _OffTime))
  {
    toggle();  // turn it on
    _previousMillis = _currentMillis;   // Remember the time
  }
  _currentMillis = millis();
}

bool digitalPin::tread()
{
  bool newState = digitalRead(_pin);
  if (_status != newState ) {
    if (millis() - _previousMillis >= _intervalMillis) {
      _previousMillis = millis();
      _status = newState;
    }
  }
  return _status;
}

void digitalPin::write(bool val) {
  _status = val;
  digitalWrite(_pin, _status);
}
bool  digitalPin::read() {
  return (_status);
}
// An operator aequivalent for =
digitalPin& digitalPin::operator=(bool value) {
  write(value);
  return *this;
}
// An operator aequivalent for && -> logical and
digitalPin& digitalPin::operator&&(digitalPin& obj) {
  write(_status && obj.read());
  return *this;
}
// An operator aequivalent for || -> (logical or)
digitalPin& digitalPin::operator||(digitalPin& obj) {
  write(_status || obj.read());
  return *this;
}
// An operator aequivalent for ! -> (logical not)
digitalPin& digitalPin::operator!(void) {
  write(!_status);
  return *this;
}
//An operator aequivalent for read()
digitalPin::operator bool() {
  return read();
}
