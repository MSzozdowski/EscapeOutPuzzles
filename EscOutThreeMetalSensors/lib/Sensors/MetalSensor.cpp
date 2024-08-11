#include <Arduino.h>
#include "MetalSensor.h"

MetalSensor::MetalSensor(uint8_t pin, uint16_t debounce_ms)
	: _pin(pin), _delay(debounce_ms), _state(HIGH), _ignore_until(0), _has_changed(false)
{
}

void MetalSensor::begin()
{
	pinMode(_pin, INPUT_PULLUP);
}

//
// public methods
//

bool MetalSensor::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > millis())
	{
		// ignore any changes during this period
	}

	// pin has changed
	else if (digitalRead(_pin) != _state)
	{
		_ignore_until = millis() + _delay;
		_state = !_state;
		_has_changed = true;
	}

	return _state;
}

// has the MetalSensor been toggled from on -> off, or vice versa
bool MetalSensor::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a MetalSensor has changed after calling the read() function
bool MetalSensor::has_changed()
{
	if (_has_changed)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the MetalSensor gone from off -> on
bool MetalSensor::pressed()
{
	return (read() == PRESSED && has_changed());
}

// has the MetalSensor gone from on -> off
bool MetalSensor::released()
{
	return (read() == RELEASED && has_changed());
}