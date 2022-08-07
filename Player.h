#pragma once

#include "SFML\Graphics.hpp"

class Player
{
private:
	////variables////

	float playerSize_x = 18.f;
	float playerSize_y = 120.f;

public:
	////variables////

	sf::RectangleShape shape;
	float playerSpeed = 450.f;
	int points = 0;

	////functions////

	void GetMovementInput(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown, float dt);
	
	Player();
	~Player();
};