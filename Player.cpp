#include "Player.h"

void Player::GetMovementInput(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown, float dt)
{
	if (sf::Keyboard::isKeyPressed(keyUp))
		shape.move(0.f, -playerSpeed * dt);
	if (sf::Keyboard::isKeyPressed(keyDown))
		shape.move(0.f, playerSpeed * dt);
}

Player::Player()
{
	shape.setSize(sf::Vector2f(playerSize_x, playerSize_y));
	shape.setFillColor(sf::Color::White);
}

Player::~Player()
{
}