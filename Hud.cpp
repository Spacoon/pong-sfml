#include "Hud.h"

void Hud::updatePlayerScoreCounter(Player& obj)
{
	obj.points += 1;
	pointsCountdown_string = std::to_string(obj.points);
	text.setString(pointsCountdown_string);
}

Hud::Hud()
{
	fontPath += fontFile;
	if (font.loadFromFile(fontPath))
	{
		text.setFont(font);
		text.setCharacterSize(40);
	}
}

Hud::~Hud()
{
}
