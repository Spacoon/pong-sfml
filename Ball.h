#pragma once

#define _USE_MATH_DEFINES

#include <random>
#include "SFML\Graphics.hpp"

class Ball
{
private:

	////variables////

	float ballSpeed_x;
	float ballSpeed_y;
	static const int ballPoints = 16;

	std::random_device rd;

public:

	////variables////

	sf::CircleShape shape;
	float ballRadius = 10.f;
	float ballAngle;
	const float initialBallSpeed = 300.f;
	float ballSpeed;
	float ballBounceCounter = 1.f;
	float ballSpeedMultiplier = 1.f;
	float ballAngleModifier;

	////functions////

	void moveShape(float dt);
	void setRandomAngle();

	Ball();
	~Ball();
};

