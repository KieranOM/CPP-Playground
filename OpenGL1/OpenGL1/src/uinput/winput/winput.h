#pragma once
#include "../uinput.h"

class WInput : public UInput {

public:
	void UInput::update(long long deltaTime) override;
};