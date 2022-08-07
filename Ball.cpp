#include "Ball.h"

void Ball::moveShape(float dt)
{
	ballSpeed_x = sinf(ballAngle) * ballSpeed;
	ballSpeed_y = -cosf(ballAngle) * ballSpeed;

	shape.move(ballSpeed_x * dt, ballSpeed_y * dt);
}

void Ball::setRandomAngle()
{
	ballSpeed = initialBallSpeed;
	ballSpeedMultiplier = 1.f;
	ballBounceCounter = 1.f;

	std::uniform_int_distribution <int> distri(0, 1);
	std::default_random_engine engi(rd());
	int leftorRight = distri(engi);

	if (leftorRight)
	{
		std::uniform_real_distribution <float> distrf(M_PI / 6.f, M_PI - M_PI / 6.f);
		std::default_random_engine eng(rd());
		this->ballAngle = distrf(eng);
	}
	else
	{
		std::uniform_real_distribution <float> distrf((7.f / 6.f) * M_PI, (11.f / 6.f) * M_PI);
		std::default_random_engine eng(rd());
		this->ballAngle = distrf(eng);
	}
}

Ball::Ball()
{
	//initializing ball
	ballSpeed = initialBallSpeed;
	shape.setRadius(ballRadius);
	shape.setPointCount(ballPoints);
	shape.setFillColor(sf::Color::White);

	ballSpeed_x = 0.f;
	ballSpeed_y = 0.f;
	ballAngle = 0.f;
	ballAngleModifier = 0.f;
	
	//random ball angle
	
	setRandomAngle();
	
}

Ball::~Ball()
{
}