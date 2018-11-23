#pragma once

class UInput {

protected:
	// Measured in ms to go from 0 to 1.
	static const int interpolate = 200;
	float xInput, yInput;
	float clampf(float value, float min, float max);

public:
	float getInputX();
	float getInputY();
	virtual void update(long long deltaTime) = 0;

};