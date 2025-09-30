#pragma once
#include <SFML/Graphics.hpp>
#include "AIActor_Guard.h"

#include "../AI_Framework/framework.h"
#include "AIConstructor_BT.h"


class GameController
{
public:
	GameController();
	~GameController();

	enum TerrainType { Ground, StartZone, EndZone, Alarm };

	//Intialisation
	void Init();
	void LoadGraphicsAssests();
	void CreateGround(bool alarm);
	void SetMapSprites();
	void SetupGuards();
	void SetupPlayer();

	//Events and Game Loop
	void Update(float dt);
	void HandleKeyPress(const sf::Event::KeyPressed* _keyPress);
	void HandleMousePress(const sf::Event::MouseButtonPressed* _mousePress);

	// Rendering
	void DisplayUI(sf::RenderWindow& window);
	void Render(sf::RenderWindow& window);

	// Game Status

	void StartGame();
	void CheckGameOver();
	void CheckGuardAlarm();
	void ResetGame();
	bool gameRunning;

private:

	// constants
	static const int mapWidth = 20;
	static const int mapHeight = 15;

	static const int playerStartX = 0;
	static const int playerStartY = 7;

	const int alarmGuardCount = 2;
	const int startGuardCount = 2;

	const float playerSpeed = 6.f;

	const int playerCount = 1;
	const float mapSectionXY = 64.0f;

	// Actors
	sf::Vector2f player;
	std::vector<AIActor_Guard*> guards;

	// Status
	bool alarmRaised;

	// Environment Checks
	void CheckGuardLOS();
	void CheckGuardHearing();

	void TriggerAlarmGuards();

	// Rendering

	void DrawMap(sf::RenderWindow& window);
	void DrawGuards(sf::RenderWindow& window);
	void DrawPlayer(sf::RenderWindow& window);
	void DisplayUIText(sf::RenderWindow& window, std::string _text, float _yPos);

	// AI Initialisation
	void InitAI();
	AIConstructor_BT btAIConstructor;

	// Graphics
	sf::Font font;

	sf::Texture textureGround;
	sf::Texture textureStartZone;
	sf::Texture textureEndZone;
	sf::Texture textureAlarm;
	sf::Texture textureGuard;
	sf::Texture texturePlayer;

	TerrainType terrain[mapWidth][mapHeight];

	std::vector< sf::Sprite > mapArea;

	std::vector<sf::Sprite> guardChars;
	std::vector<sf::Sprite> playerChar;

	//Global Access
	AIRandom_Global* _random;
	AIMath_Global* _math;

};

