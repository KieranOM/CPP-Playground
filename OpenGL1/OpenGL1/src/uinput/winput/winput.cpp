#include "winput.h"
#include <Windows.h>
#include <cmath>

void WInput::update(long long deltaTime) {
	// Calculate the rate of interpolation
	float interpolationRate = ((float)deltaTime) / interpolate;
	// Determine direction from Windows keypresses (X axis)
	float rawInput = (float)(((GetKeyState('D') & 0x8000) ? 1 : 0) - ((GetKeyState('A') & 0x8000) ? 1 : 0));

	// If there's no direction (or input cancelled out), begin returning the joystick to the original position
	if (rawInput == 0) {
		if (xInput < 0) {
			xInput = clampf(xInput + interpolationRate, -1.0f, 0.0f);
		}
		else {
			xInput = clampf(xInput - interpolationRate, 0.0f, 1.0f);
		}
	}
	// Otherwise, move joystick based on X input
	else {
		xInput = clampf(xInput + rawInput * interpolationRate, -1.0f, 1.0f);
	}

	// Determine direction again (Y axis)
	rawInput = (float)(((GetKeyState('W') & 0x8000) ? 1 : 0) - ((GetKeyState('S') & 0x8000) ? 1 : 0));

	// If there's no direction, begin returning the joystick to the original position
	if (rawInput == 0) {
		if (yInput < 0) {
			yInput = clampf(yInput + interpolationRate, -1.0f, 0.0f);
		}
		else {
			yInput = clampf(yInput - interpolationRate, 0.0f, 1.0f);
		}
	}
	// Otherwise, move joystick based on Y input
	else {
		yInput = clampf(yInput + rawInput * interpolationRate, -1.0f, 1.0f);
	}

	// Calculate distance
	float dist = sqrtf(powf(xInput, 2) + powf(yInput, 2));

	// Normalise the XY input vector
	if (dist > 1) {
		xInput /= dist;
		yInput /= dist;
	}
}