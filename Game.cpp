#include "Game.h"

void Game::initVar()
{
	window = nullptr;
	settings.antialiasingLevel = 6;
	
	//sounds

	soundBufferPlayer1Collide.loadFromFile("sounds\\ballplayer1collide.wav");
	soundBufferPlayer2Collide.loadFromFile("sounds\\ballplayer2collide.wav");
	soundBufferWallCollide.loadFromFile("sounds\\ballwallcollide.wav");

	soundPlayer1Collide.setBuffer(soundBufferPlayer1Collide);
	soundPlayer2Collide.setBuffer(soundBufferPlayer2Collide);
	soundWallCollide.setBuffer(soundBufferWallCollide);
}

void Game::initWindow()
{
	window = new sf::RenderWindow(windowResolution, windowTitle, sf::Style::Close | sf::Style::Titlebar, settings);
	window->setFramerateLimit(FPSlimit);
	icon.loadFromFile("icon\\pongicon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initShapes()
{
	//players
	
	player1.shape.setPosition(50.f, static_cast<float> (window->getSize().y / 2) - static_cast<float> (player1.shape.getSize().y / 2));
	player2.shape.setPosition(window->getSize().x - 50.f - player2.shape.getSize().x, static_cast<float> (window->getSize().y / 2) - static_cast<float> (player1.shape.getSize().y / 2));

	//ball

	ball.shape.setPosition(static_cast<float>(window->getSize().x / 2) - ball.shape.getRadius(), static_cast<float>(window->getSize().y / 2) - ball.shape.getRadius());
}

void Game::drawShapes()
{
	//shapes
	
	window->draw(ball.shape);
	window->draw(player1.shape);
	window->draw(player2.shape);

	//players score counters

	if (startGame)
	{
		window->draw(player1ScoreCounter.text);
		window->draw(player2ScoreCounter.text);
	}

	//main menu buttons

	if (!startGame)
	{
		window->draw(startGameButton.text);
		window->draw(mainMenuTitleText.text);
		window->draw(mainMenuDescriptionPlayer1Text.text);
		window->draw(mainMenuDescriptionPlayer2Text.text);
		window->draw(mainMenuDescriptionEscText.text);
	}

	//FPS counter

	if (enableFPScounter)
		window->draw(FPScounterText.text);
}

void Game::getInput()
{
	////exiting the game////

	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		//close window
		case sf::Event::Closed:
			window->close();
			break;

		//ESC key
		case sf::Event::KeyPressed:
			if (event.key.code == exitKey)
				window->close();
			break;

		//start game button
		case sf::Event::MouseButtonPressed:
			if (!startGame && startGameButton.isEnabled && startGameButton.text.getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y) && event.mouseButton.button == sf::Mouse::Left)
				startGame = true;
			break;
		case sf::Event::MouseMoved:
			if (!startGame && startGameButton.isEnabled && startGameButton.text.getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
				startGameButton.text.setFillColor(sf::Color(200, 200, 200));
			else
				startGameButton.text.setFillColor(sf::Color::White);
			break;

		default:
			break;
		}
	}

	////game objects movement////

	if (startGame)
	{
		player1.GetMovementInput(player1upKey, player1downKey, deltaTime);
		player2.GetMovementInput(player2upKey, player2downKey, deltaTime);
		ball.moveShape(deltaTime);
	}
	
}

void Game::checkBoundaries()
{

	////players collision with window boundaries////

	//player1

	if (player1.shape.getPosition().y < 0.f)	//upper bound
		player1.shape.setPosition(player1.shape.getPosition().x, 0.f);

	if (player1.shape.getPosition().y + player1.shape.getSize().y > window->getSize().y)	//lower bound
		player1.shape.setPosition(player1.shape.getPosition().x, window->getSize().y - player1.shape.getSize().y);
	

	//player2

	if (player2.shape.getPosition().y < 0.f)	//upper bound
		player2.shape.setPosition(player2.shape.getPosition().x, 0.f);

	if (player2.shape.getPosition().y + player2.shape.getSize().y > window->getSize().y)	//lower bound
		player2.shape.setPosition(player2.shape.getPosition().x, window->getSize().y - player2.shape.getSize().y);

	//ball collision with upper and lower bound

	if (ball.shape.getPosition().y <= 0 || ball.shape.getPosition().y + 2 * ball.shape.getRadius() >= window->getSize().y)
	{
		ball.ballAngle += static_cast<float> (M_PI) - 2 * ball.ballAngle;

		soundWallCollide.play();
	}
	
	////players collision with ball////

	//player1 collision

	if (ball.shape.getPosition().y + 1.5f * ball.shape.getRadius() >= player1.shape.getPosition().y &&
		ball.shape.getPosition().y + ball.shape.getRadius() / 2 <= player1.shape.getPosition().y + player1.shape.getSize().y && 
		ball.shape.getPosition().x <= player1.shape.getPosition().x + player1.shape.getSize().x && 
		ball.shape.getPosition().x >= player1.shape.getPosition().x)
	{
		ball.ballBounceCounter += 1.f;
		ball.ballSpeedMultiplier = log10f(ball.ballBounceCounter) + 1.f;
		ball.ballSpeed = ball.initialBallSpeed * ball.ballSpeedMultiplier;

		soundPlayer1Collide.play();

		if (ball.shape.getPosition().y + ball.shape.getRadius() <= player1.shape.getPosition().y + player1.shape.getSize().y / 2)	//upper half of the player
		{
			ball.ballAngleModifier = (M_PI / 3) * (1 - (ball.shape.getPosition().y + ball.shape.getRadius() - player1.shape.getPosition().y) / (player1.shape.getSize().y / 2));
			ball.ballAngle = M_PI_2 - ball.ballAngleModifier;
		}
		else if (ball.shape.getPosition().y + ball.shape.getRadius() > player1.shape.getPosition().y + player1.shape.getSize().y / 2)	//lower half od the player
		{
			ball.ballAngleModifier = (M_PI / 3) * (1 - (player1.shape.getPosition().y + player1.shape.getSize().y - (ball.shape.getPosition().y + ball.shape.getRadius())) / (player1.shape.getSize().y / 2));
			ball.ballAngle = M_PI_2 + ball.ballAngleModifier;
		}
	}

	//player2 collision

	if (ball.shape.getPosition().y + 1.5f * ball.shape.getRadius() >= player2.shape.getPosition().y && 
		ball.shape.getPosition().y + ball.shape.getRadius() / 2 <= player2.shape.getPosition().y + player2.shape.getSize().y && 
		ball.shape.getPosition().x + 2 * ball.shape.getRadius() >= player2.shape.getPosition().x && 
		ball.shape.getPosition().x + 2 * ball.shape.getRadius() <= player2.shape.getPosition().x + player2.shape.getSize().x)
	{
		ball.ballBounceCounter += 1.f;
		ball.ballSpeedMultiplier = log10f(ball.ballBounceCounter) + 1.f;
		ball.ballSpeed = ball.initialBallSpeed * ball.ballSpeedMultiplier;

		soundPlayer2Collide.play();

		if (ball.shape.getPosition().y + ball.shape.getRadius() <= player2.shape.getPosition().y + player2.shape.getSize().y / 2)	//upper half of the player
		{
			ball.ballAngleModifier = (M_PI / 3) * (1 - (ball.shape.getPosition().y + ball.shape.getRadius() - player2.shape.getPosition().y) / (player2.shape.getSize().y / 2));
			ball.ballAngle = -M_PI_2 + ball.ballAngleModifier;
		}
		else if (ball.shape.getPosition().y + ball.shape.getRadius() > player2.shape.getPosition().y + player2.shape.getSize().y / 2)//lower half od the player
		{
			ball.ballAngleModifier = (M_PI / 3) * (1 - (player2.shape.getPosition().y + player2.shape.getSize().y - (ball.shape.getPosition().y + ball.shape.getRadius())) / (player2.shape.getSize().y / 2));
			ball.ballAngle = -M_PI_2 - ball.ballAngleModifier;
		}
	}
}

void Game::initMainMenu()
{
	//buttons

	startGameButton.text.setString("Start game");
	startGameButton.text.setPosition(static_cast <float> (window->getSize().x) / 2 - startGameButton.text.getGlobalBounds().width / 2, 0.4f * window->getSize().y);

	//text

	mainMenuTitleText.text.setString("Controls:");
	mainMenuTitleText.text.setStyle(sf::Text::Style::Bold);
	mainMenuTitleText.text.setPosition(static_cast <float> (window->getSize().x) / 2 - mainMenuTitleText.text.getGlobalBounds().width / 2, 0.6f * window->getSize().y);

	mainMenuDescriptionPlayer1Text.text.setString("W\nS");
	mainMenuDescriptionPlayer1Text.text.setCharacterSize(24);
	mainMenuDescriptionPlayer1Text.text.setPosition(mainMenuTitleText.text.getPosition().x, 0.67f * window->getSize().y);

	mainMenuDescriptionPlayer2Text.text.setString("Up\nDown");
	mainMenuDescriptionPlayer2Text.text.setCharacterSize(24);
	mainMenuDescriptionPlayer2Text.text.setPosition(mainMenuTitleText.text.getPosition().x + mainMenuTitleText.text.getGlobalBounds().width - mainMenuDescriptionPlayer2Text.text.getGlobalBounds().width, 0.67f * window->getSize().y);


	mainMenuDescriptionEscText.text.setString("ESC - quit the game");
	mainMenuDescriptionEscText.text.setCharacterSize(24);
	mainMenuDescriptionEscText.text.setPosition(mainMenuTitleText.text.getPosition().x + mainMenuTitleText.text.getGlobalBounds().width / 2.f - mainMenuDescriptionEscText.text.getGlobalBounds().width / 2.f,
												0.74f * window->getSize().y);
}

void Game::calculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
	if (enableFPScounter)
	{
		FPScounter = static_cast<int> (1.f / deltaTime);
		FPScounterText.text.setString(std::to_string(FPScounter));
	}
}

void Game::lookForLoser()
{
	if (ball.shape.getPosition().x + ball.shape.getRadius() <= player1.shape.getPosition().x - 10.f)
	{
		player1ScoreCounter.updatePlayerScoreCounter(player1);
		ball.setRandomAngle();
		ball.shape.setPosition(static_cast<float>(window->getSize().y / 2) - ball.shape.getRadius(), static_cast<float>(window->getSize().y / 2) - ball.shape.getRadius());

		player1.shape.setPosition(50.f, static_cast<float> (window->getSize().y / 2) - static_cast<float> (player1.shape.getSize().y / 2));
		player2.shape.setPosition(window->getSize().x - 50.f - player2.shape.getSize().x, static_cast<float> (window->getSize().y / 2) - static_cast<float> (player1.shape.getSize().y / 2));
	}

	if (ball.shape.getPosition().x + ball.shape.getRadius() >= player2.shape.getPosition().x + player1.shape.getSize().x + 10.f)
	{
		player2ScoreCounter.updatePlayerScoreCounter(player2);
		ball.setRandomAngle();
		ball.shape.setPosition(static_cast<float>(window->getSize().x / 2) - ball.shape.getRadius(), static_cast<float>(window->getSize().y / 2) - ball.shape.getRadius());

		player1.shape.setPosition(50.f, static_cast<float> (window->getSize().y / 2) - static_cast<float> (player1.shape.getSize().y / 2));
		player2.shape.setPosition(window->getSize().x - 50.f - player2.shape.getSize().x, static_cast<float> (window->getSize().y / 2) - static_cast<float> (player1.shape.getSize().y / 2));
	}
}

void Game::initHud()
{
	player1ScoreCounter.text.setStyle(sf::Text::Style::Bold);
	player2ScoreCounter.text.setStyle(sf::Text::Style::Bold);

	player1ScoreCounter.text.setString("0");
	player2ScoreCounter.text.setString("0");

	player1ScoreCounter.text.setPosition(static_cast <float> (window->getSize().x) / 3, 0.1f * window->getSize().y);
	player2ScoreCounter.text.setPosition(static_cast <float> (window->getSize().x) * 2 / 3 - player2ScoreCounter.text.getGlobalBounds().width, 0.1f * window->getSize().y);

	FPScounterText.text.setPosition(0.f, 0.f);
	FPScounterText.text.setFillColor(sf::Color::Green);
	FPScounterText.text.setCharacterSize(20);
}

const bool Game::isRunning() const
{
	return window->isOpen();
}

void Game::update()
{
	getInput();
	checkBoundaries();
	calculateDeltaTime();
	lookForLoser();
}

void Game::render()
{
	window->clear();
	drawShapes();
	window->display();
}

Game::Game()
{
	initVar();
	initWindow();
	initMainMenu();
	initHud();
	initShapes();
}

Game::~Game()
{
	delete window;
}