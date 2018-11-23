#include "uinput.h"

float UInput::getInputX() {
	return xInput;
}

float UInput::getInputY() {
	return yInput;
}

float UInput::clampf(float value, float min, float max) {
	return value < min ? min : value > max ? max : value;
}