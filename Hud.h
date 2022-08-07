#pragma once

#include <string>
#include "Player.h"

class Hud
{
private:

	std::string fontPath = "fonts\\";
	sf::Font font;
	std::string pointsCountdown_string;
	
public:

	void updatePlayerScoreCounter(Player& obj);
	std::string fontFile = "arial.ttf";
	sf::Text text;


	Hud();
	~Hud();
};