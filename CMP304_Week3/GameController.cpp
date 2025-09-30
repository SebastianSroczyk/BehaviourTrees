#include "GameController.h"


#include <iostream>
#include <sstream>
#include <string>
#include "BT_ReasonerNode.h"
using namespace std;


GameController::GameController()
{
    gameRunning = false;
    alarmRaised = false;


    // obtain Math and Random singletons
    _random = AIRandom_Global::getInstance();
    _math = AIMath_Global::getInstance();
}

GameController::~GameController()
{


}


// ** Intialisation **

/*
* Init should be called prior to starting to game
*/
void GameController::Init()
{


    //initialise the graphics 
    LoadGraphicsAssests();
    CreateGround(true);
    SetMapSprites();

    //initialise the game environment
    InitAI();


    // initialise the player and guards
    guards.clear();
    guardChars.clear();
    SetupGuards();
    SetupPlayer();
}

/*
* InitAI initalises the AIConstructor. Must be called before game starts. 
*/
void GameController::InitAI()
{
    //DefineAI will initialise all of the Actions, Considerations and Options used by the AI
    btAIConstructor.Init();
    btAIConstructor.DefineAI();
}


void GameController::SetMapSprites()
{
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            if (terrain[x][y] == TerrainType::Ground)
            {
                mapArea.push_back(sf::Sprite(textureGround));
            }
            else if (terrain[x][y] == TerrainType::EndZone)
            {
                mapArea.push_back(sf::Sprite(textureEndZone));
            }
            else if (terrain[x][y] == TerrainType::StartZone)
            {
                mapArea.push_back(sf::Sprite(textureStartZone));
            }
            else if (terrain[x][y] == TerrainType::Alarm)
            {
                mapArea.push_back(sf::Sprite(textureAlarm));
            }

        }
    }
}



/*
LoadGraphicsAssests will load the graphics assets from file erady for use
*/
void GameController::LoadGraphicsAssests()
{
    bool load = textureGround.loadFromFile("Assets/Ground.png");
    load = textureStartZone.loadFromFile("Assets/StartZone.png");
    load = textureEndZone.loadFromFile("Assets/EndZone.png");
    load = textureAlarm.loadFromFile("Assets/Alarm.png");
    load = textureGuard.loadFromFile("Assets/Guard.png");
    load = texturePlayer.loadFromFile("Assets/Player.png");


    font.openFromFile("Assets/DefaultAriel.ttf");

}


void GameController::SetupPlayer()
{

    // set the starting position of the player
    player.x = _math->ConvertGridPosToSreenPos(playerStartX);
    player.y = _math->ConvertGridPosToSreenPos(playerStartY);

    for (int i = 0; i < playerCount; i++)
    {
        sf::Sprite _s(texturePlayer);
        _s.setOrigin(sf::Vector2f(32, 32));
        playerChar.push_back(_s);
    }

}


/*
* SetupGuards will create the guards present at the start of the game and assign their AI Brain
*/
void GameController::SetupGuards()
{
    for (int i = 0; i < startGuardCount; i++)
    {

        sf::Sprite _s(textureGuard);
        _s.setOrigin(sf::Vector2f(128, 32));
        guardChars.push_back(_s);

        AIActor_Guard* _g = new AIActor_Guard();
        std::string _name = "Guard_";
        _name.append(std::to_string(i));
        _g->Init(_name, btAIConstructor);

        //starting Blackboard values
        _g->AddBBValue("Energy", 20);
        _g->AddBBValueInt("CanSeePlayer", 0);
        _g->AddBBValueInt("CanHearPlayer", 0);
        _g->AddBBValueInt("ReachedDesintation", 0);
        _g->AddBBValueInt("HasRaisedAlarm", 0);
        _g->AddBBValueInt("IsRaisingAlarm", 0);
        _g->AddBBValueInt("IsHealing", 0);

        _g->SetPatrolBounds(mapWidth, mapHeight);

        // spawn the guards in alternating top and bottom positions of the right side of the map
        int _ySpawn = ((i % 2) * (mapHeight - 1)) + 1;
        _g->Spawn(_math->ConvertGridPosToSreenPos(mapWidth - 2), _math->ConvertGridPosToSreenPos(_ySpawn));
        _g->isActive = true;
        guards.push_back(_g);

    }
}


//** Events and Game Loop **


/*
* Update is called each frame and should only contain code desined to be called this often
*/
void GameController::Update(float dt)
{
    if (gameRunning)
    {
        for (auto guard : guards)
        {
          guard->Update(dt);
        }
        CheckGuardHearing();
        CheckGuardLOS();      
        CheckGuardAlarm();

        CheckGameOver();
    }
}



/*
* HandleKeyPress will handle the SFML key presses
*/
void GameController::HandleKeyPress(const sf::Event::KeyPressed* _keyPress)
{

    if (!gameRunning)
        return;

    if (_keyPress->code == sf::Keyboard::Key::Left)
    {
        player.x -= playerSpeed;
    }

    else if (_keyPress->code == sf::Keyboard::Key::Right)
    {
        player.x += playerSpeed;
    }
    else if (_keyPress->code == sf::Keyboard::Key::Up)
    {
        player.y -= playerSpeed;
    }
    else if (_keyPress->code == sf::Keyboard::Key::Down)
    {
        player.y += playerSpeed;
    }

    // check bounds

    if (player.x < 0)
        player.x = 0;

    if (player.y < 0)
        player.y = 0;

    if (player.x > mapWidth* mapSectionXY)
        player.x = mapWidth * mapSectionXY;

    if (player.y > mapHeight * mapSectionXY)
        player.y = mapHeight * mapSectionXY;


}

/*
* HandleKeyPress will handle the SFML mouse presses
*/
void GameController::HandleMousePress(const sf::Event::MouseButtonPressed* _mousePress)
{

    if (_mousePress->button == sf::Mouse::Button::Right)
    {

    }
    else if (_mousePress->button == sf::Mouse::Button::Left)
    {

    }
}


// ** Environment Checks **


void GameController::CheckGuardAlarm()
{
    for (int i = 0; i < guards.size(); i++)
    {
        if (guards[i]->isActive)
        {
            if (guards[i]->GetBBValueInt("HasRaisedAlarm") == 1)
            {
                // if alarm has been raised, reset flag and trigger the guards to appear
                TriggerAlarmGuards();

            }
        }
    }
}


/*
* TriggerAlarmGuards will spawn two new AI Guards, each with own Brain. Can only be called once per game. 
*/
void GameController::TriggerAlarmGuards()
{

    if (alarmRaised)
    {
        // can only be called once per game
        return;
    }


    for (int i = 0; i < alarmGuardCount; i++)
    {
        sf::Sprite _s(textureGuard);
        _s.setOrigin(sf::Vector2f(128, 0));
        guardChars.push_back(_s);


        AIActor_Guard* _g = new AIActor_Guard();
        std::string _name = "Alarm_Guard";
        _name.append(std::to_string(i));
        _g->Init(_name, btAIConstructor);

        // set initial blackboard data for the guards
        _g->AddBBValue("Energy", 20);
        _g->AddBBValue("CanSeePlayer", 0);
        _g->AddBBValue("CanHearPlayer", 0);
        _g->AddBBValue("ReachedDesintation", 0);
        _g->AddBBValue("HasRaisedAlarm", 0);
        _g->AddBBValue("IsRaisingAlarm", 0);
        _g->AddBBValue("IsHealing", 0);


        _g->SetPatrolBounds(mapWidth, mapHeight);

        int _ySpawn = (i % 2) * mapHeight;
        _g->Spawn(_math->ConvertGridPosToSreenPos(mapWidth - 2), _math->ConvertGridPosToSreenPos(_ySpawn));
        _g->isActive = true;
        guards.push_back(_g);
    }

    alarmRaised = true;
}



// ** Initialisation **

void GameController::CreateGround(bool alarm)
{
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            if (x == 0)
            {
                terrain[x][y] = TerrainType::StartZone;
            }else  if (x == mapWidth -1)
            {
                terrain[x][y] = TerrainType::EndZone;
            }else if(y == mapHeight/2 && x == mapWidth/2 && alarm)
            {
                terrain[x][y] = TerrainType::Alarm;
            }
            else
            {
                terrain[x][y] = TerrainType::Ground;
            }
        }

    }
}


// ** Rendering **


void GameController::DisplayUIText(sf::RenderWindow& window, std::string _text, float _yPos)
{

    sf::Text text(font); // a font is required to make a text object



    // set the string to display
    text.setString(_text);

    // set the character size
    text.setCharacterSize(28); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);
    text.setPosition({ 1400,_yPos });

    window.draw(text);

    ostringstream os2;

}



/*
DisplayUI can be used to display data useful for debugging or tracking on the right panel
*/
void GameController::DisplayUI(sf::RenderWindow& window)
{

    int _startY = 0;
    int _offset = 50;
    int _guardOffset = 450;

    for (int i = 0; i < startGuardCount; i++)
    {
   
        ostringstream os0;
        os0 << "Guard "<< i << " BB" << endl;
        DisplayUIText(window, os0.str(), _startY + (_offset* 1 ) + (_guardOffset*i));

        ostringstream os1;
        os1 << "Player Pos " << player.x << " " << player.y << endl;
        DisplayUIText(window, os1.str(), _startY + (_offset * 2) + (_guardOffset * i));

        ostringstream os2;
        os2 << "Energy " << guards[i]->GetBBValue("Energy") << " " << endl;
        DisplayUIText(window, os2.str(), _startY + (_offset * 3) + (_guardOffset * i));

        ostringstream os3;
        os3 << "CanSeePlayer" << guards[i]->GetBBValueInt("CanSeePlayer") << " " << endl;
        DisplayUIText(window, os3.str(), _startY + (_offset * 4) + (_guardOffset * i));

        ostringstream os4;
        AIMath_Global::Vector2f _posS = guards[i]->GetBBValueVec2f("PlayerSeen");
        os4 << "PlayerSeen " << _posS.x << " " << _posS.y << " " << endl;
        DisplayUIText(window, os4.str(), _startY + (_offset * 5) + (_guardOffset * i));

        ostringstream os5;
        os5 << "CanHearPlayer" << guards[i]->GetBBValueInt("CanHearPlayer") << " " << endl;
        DisplayUIText(window, os5.str(), _startY + (_offset * 6) + (_guardOffset * i));

        ostringstream os6;
        AIMath_Global::Vector2f _pos = guards[i]->GetBBValueVec2f("PlayerHeard");
        os6 << "PlayerHeard " << _pos.x << " " << _pos.y << " " << endl;
        DisplayUIText(window, os6.str(), _startY + (_offset * 7) + (_guardOffset * i));

    }


}



/*
* DrawMap will draw the background tiles for the map
*/
void GameController::DrawMap(sf::RenderWindow& window)
{
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            int _index = (x * mapHeight) + y;

            mapArea[_index].setPosition({ x * mapSectionXY, y * mapSectionXY });
            window.draw(mapArea[_index]);
        }
    }
}


void GameController::DrawGuards(sf::RenderWindow& window)
{
    for (int i = 0; i < guards.size(); i++)
    {
        if (guards[i]->isActive)
        {    
            guardChars[i].setPosition({ guards[i]->posX,guards[i]->posY });

            guardChars[i].setRotation(sf::radians(guards[i]->rotation));

            window.draw(guardChars[i]);
        }

    }
}


void GameController::DrawPlayer(sf::RenderWindow& window)
{
    for (int i = 0; i < playerCount; i++)
    {

        playerChar[i].setPosition({ player.x,player.y });
        window.draw(playerChar[i]);

    }
}


void GameController::Render(sf::RenderWindow& window)
{
    DrawMap(window);
    DrawGuards(window);
    DrawPlayer(window);
}



// ** Game Status **

/*
* StartGame will set the game status to running
*/
void GameController::StartGame()
{
    gameRunning = true;
    alarmRaised = false;
}


/*
* CheckGuardLOS will determine if each guard can see the player, and update the guard's status accordingly
*/
void GameController::CheckGuardLOS()
{
    for (int i = 0; i < guards.size(); i++)
    {
        if (guards[i]->isActive)
        {
            bool playerSeen = guards[i]->CanSeePoint(sf::Vector2f(player.x, player.y));

            if (playerSeen)
            {
                guards[i]->UpdateCanSeePlayer(player.x, player.y);
             
            }
            else if(!playerSeen)
            {
                guards[i]->UpdateCannotSeePlayer();
            }
        }
    }
}

/*
* CheckGuardLOS will determine if each guard can hear the player, and update the guard's status accordingly
*/
void GameController::CheckGuardHearing()
{
    for (int i = 0; i < guards.size(); i++)
    {
        if (guards[i]->isActive)
        {

            bool playerHeard = guards[i]->CanHearPoint(sf::Vector2f(player.x, player.y));
            bool hasPlayerBeenHeard = guards[i]->IsPlayerHeard();

            // if noise already heard, don't update again
            if (playerHeard && !hasPlayerBeenHeard)
            {
                guards[i]->UpdateCanHearPlayer(player.x, player.y);
            }
            else if (!playerHeard && hasPlayerBeenHeard)
            {
                guards[i]->UpdateCannotHearPlayer();
            }
        }
    }
}

/*
* CheckGameOver will check game over conditions - player win by reaching end of map, AI win by catching the player
*/
void GameController::CheckGameOver()
{
    int posX = _math->ConvertScreenPosToGridPos(player.x);
    bool gameOver = false;

    if (posX > mapWidth - 2)
    {
        gameOver = true;
        std::cout << "Game Ended: Player Win" << std::endl;
    }
    else
    {
        for (int i = 0; i < guards.size(); i++)
        {

            if (guards[i]->isActive)
            {

                float _distToPlayer = _math->CalcDistance(AIMath_Global::Vector2f(guards[i]->posX, guards[i]->posY), AIMath_Global::Vector2f(player.x, player.y));
             
                if (_distToPlayer < 48.f)
                {
                    gameOver = true;
                    std::cout << "Game Ended: AI Win - caught by guard " << i << std::endl;
                }
            }
        }
    }

    if (gameOver)
    {
        ResetGame();
    }

}

void GameController::ResetGame()
{
    gameRunning = false;

 }


