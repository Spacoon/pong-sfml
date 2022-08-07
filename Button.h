#pragma once

#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Hud.h"

class Button : public Hud
{
private:

public:

	bool isEnabled = true;

	Button();
	~Button();
};

