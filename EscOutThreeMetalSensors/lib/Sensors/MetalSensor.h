#ifndef MetalSensor_h
#define MetalSensor_h

#include "Arduino.h"

class MetalSensor
{
public:
	MetalSensor(uint8_t pin, uint16_t debounce_ms = 100);
	void begin();
	bool read();
	bool toggled();
	bool pressed();
	bool released();
	bool has_changed();

	const static bool PRESSED = LOW;
	const static bool RELEASED = HIGH;

private:
	uint8_t _pin;
	uint16_t _delay;
	bool _state;
	uint32_t _ignore_until;
	bool _has_changed;
};

#endif