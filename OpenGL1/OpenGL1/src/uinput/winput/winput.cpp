#include "winput.h"
#include <Windows.h>
#include <cmath>

void WInput::update(long long deltaTime) {
	float interpolationRate = ((float) deltaTime) / interpolate;
	float rawInput = (float) (((GetKeyState('D') & 0x8000) ? 1 : 0) - ((GetKeyState('A') & 0x8000) ? 1 : 0));

	if (rawInput == 0) {
		if (xInput < 0) {
			xInput = clampf(xInput + interpolationRate, -1.0f, 0.0f);
		}
		else {
			xInput = clampf(xInput - interpolationRate, 0.0f, 1.0f);
		}
	}
	else {
		xInput = clampf(xInput + rawInput * interpolationRate, -1.0f, 1.0f);
	}

	rawInput = (float)(((GetKeyState('W') & 0x8000) ? 1 : 0) - ((GetKeyState('S') & 0x8000) ? 1 : 0));

	if (rawInput == 0) {
		if (yInput < 0) {
			yInput = clampf(yInput + interpolationRate, -1.0f, 0.0f);
		}
		else {
			yInput = clampf(yInput - interpolationRate, 0.0f, 1.0f);
		}
	}
	else {
		yInput = clampf(yInput + rawInput * interpolationRate, -1.0f, 1.0f);
	}

	// Calculate distance
	float dist = sqrtf(powf(xInput, 2) + powf(yInput, 2));

	if (dist > 1) {
		xInput /= dist;
		yInput /= dist;
	}
}