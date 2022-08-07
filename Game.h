#pragma once
#define _USE_MATH_DEFINES

#include "SFML/Audio.hpp"
#include "Hud.h"
#include "Ball.h"
#include "Player.h"
#include "Button.h"
#include <cmath>
#include <ctime>

class Game
{
private:

	////shapes////

	Player player1;
	Player player2;
	Ball ball;

	////HUD////

	Hud player1ScoreCounter;
	Hud player2ScoreCounter;
	Hud FPScounterText;

	////main menu////

	Button startGameButton;
	Hud mainMenuTitleText;
	Hud mainMenuDescriptionPlayer1Text;
	Hud mainMenuDescriptionPlayer2Text;
	Hud mainMenuDescriptionEscText;
	
	////functions////

	void initVar();
	void initWindow();
	void initShapes();
	void initMainMenu();
	void initHud();
	void drawShapes();
	void getInput();
	void checkBoundaries();
	void calculateDeltaTime();
	void lookForLoser();
	
	////system variables////

	sf::RenderWindow* window;
	sf::VideoMode windowResolution = sf::VideoMode(1920, 1080);
	sf::Image icon;
	const std::string windowTitle = "Pong game";
	const int FPSlimit = 144;
	sf::Event event;
	sf::ContextSettings settings;
	sf::Clock clock;
	float deltaTime;
	sf::SoundBuffer soundBufferPlayer1Collide;
	sf::SoundBuffer soundBufferPlayer2Collide;
	sf::SoundBuffer soundBufferWallCollide;
	sf::Sound soundPlayer1Collide;
	sf::Sound soundPlayer2Collide;
	sf::Sound soundWallCollide;
	sf::Mouse mouse;
	int FPScounter;
	bool enableFPScounter = true;
	bool startGame;

	////keycodes////

	const sf::Keyboard::Key player1upKey = sf::Keyboard::W;
	const sf::Keyboard::Key player1downKey = sf::Keyboard::S;
	const sf::Keyboard::Key player2upKey = sf::Keyboard::Up;
	const sf::Keyboard::Key player2downKey = sf::Keyboard::Down;
	const sf::Keyboard::Key exitKey = sf::Keyboard::Escape;
	
public:

	////system functions////

	const bool isRunning() const;
	void update();
	void render();

	Game();
	~Game();
};