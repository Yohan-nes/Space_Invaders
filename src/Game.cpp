#include "Game.hpp"
#include <iostream>
#include <fstream>

using namespace std::this_thread;     // will use sleep_for method
using namespace std::chrono_literals; // used to define specific prefix of seconds.  ns, us, ms, s, h, etc

Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg"); // loads music background that will play during the game
    PlayMusicStream(music);                      // plays background music
    InitGame();
    explosionSound = LoadSound("Sounds/explosion.ogg");
}

Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

void Game::Update()
{
    if (run)
    {
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            mysteryShip.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }
        for (auto &laser : spaceship.lasers)
        {
            laser.Update(); // will update the each lasers position in the lasers vector
        }
        DeleteInactiveLasers();
        MoveAliens();
        AlienShootLaser();
        for (auto &laser : alienLasers)
        {
            laser.Update();
        }
        DeleteInactiveLasers();
        mysteryShip.Update();
        CheckForCollisions();
    }
    // if game is not running, this will check if user has pressed enter. If they have, the game will start running
    if (IsKeyDown(KEY_ENTER))
    {               // will reset the game
        Reset();    // clears all objects from object
        InitGame(); // initializes and redraws all object in the game
    }
}

void Game::Draw()
{
    spaceship.Draw(); // draws spaceship on the game board
    for (auto &laser : spaceship.lasers)
    { // for every laser in the lasers vector, the laser.Draw() method needs to be called to draw each laser
        laser.Draw();
    }
    // draws 4 obstacles on the board
    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }

    for (auto &alien : aliens)
    { // draws all aliens on grid
        alien.Draw();
    }

    for (auto &laser : alienLasers)
    { // draws all aliens on grid
        laser.Draw();
    }
    mysteryShip.Draw(); // draws mystery ship
}

void Game::HandleInput()
{
    if (run)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft(); // if user presses left arrow key, the spaceship will move to the left
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight(); // if user presses right arrow key, the spaceship will move to the right
        }
        else if (IsKeyDown(KEY_SPACE))
        { // if the user presses the spacebar, the laser will be shot out of the spaceship
            spaceship.FireLaser();
        }
    }
}

void Game::DeleteInactiveLasers()
{ // iterates through lasers Vector to see if any of them are inactive and removes them

    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
    // iterates through aliens lasers Vector to see if any of them are inactive and removes them
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->active)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;         // multiples amount of obstacles columns by block width(3 pixels) to find obstacle width
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5; // creating 4 obstacles with a total of 5 spaces. This calculation determines how space should be between each of the 4 obstacles
    for (int i = 0; i < 4; i++)
    {                                                                             // creates 4 obstacles
        float offsetX = (i + 1) * gap + i * obstacleWidth;                        // ensures theres an equal amount of space between the 4 obstacles
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)})); // create the obstacles  to be above spaceship and adds it to obstacle vector
    }
    return obstacles; // return obstacles vector
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    int cellSize = 55; // will make each alien a 55 by 55 square in pixels
    // iterates through 5 by 11 grid to create aliens to fill the grid
    for (int row = 0; row < 5; row++)
    {
        // these if statement will change the alien type based on the row in the for loop so that there is a variety of aliens in the game
        int alienType;
        if (row == 0)
        {
            alienType = 3;
        }
        else if ((row == 1) || (row == 2))
        {
            alienType = 2;
        }
        else
        {
            alienType = 1;
        }
        for (int column = 0; column < 11; column++)
        {

            // calculate x and y coordinates for alien on board
            float x = 75 + column * cellSize;           // adding the 75 pixels positions the aliens in the middle of the board
            float y = 110 + row * cellSize;             // adding the 110 pixels positions the aliens in the middle of the board
            aliens.push_back(Alien(alienType, {x, y})); // add alien object to vector of all alien
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        // if any of the aliens are out of the yellow rounded rectangle, the direction of all the aliens will be switched so that they go in the opposite direction
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : aliens)
    { // moves all aliens down a specific distance every time they hit the horizontal boundaries of the screen
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{ // chooses a random alien from which it will shoot lasers
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    { // if time of when last alien fired a laser is greater than 35 milliseconds and the aliens vector is not empty, then a random alien can shoot a laser
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                                     alien.position.y + alien.alienImages[alien.type - 1].height},
                                    6)); // will add an alien laser to vector alienLaser so that the laser shoots out of the bottom center of the alien and a speed of 6 pixels going downwards
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{

    // Checking collision between Spaceship Lasers and other objects within the program
    for (auto &laser : spaceship.lasers)
    {
        // Checking collisions between spaceship lasers and aliens
        auto it = aliens.begin(); // iterator created to start at the beginning of aliens vector
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                // this if will check for which alien was hit by a spaceship laser and add the according points to the score
                // each type of alien is associated with the 3 different aliens in the game
                if (it->type == 1)
                {
                    score += 100;
                }
                else if (it->type == 2)
                {
                    score += 200;
                }
                else if (it->type == 3)
                {
                    score += 300;
                }
                checkForHighscore();
                it = aliens.erase(it); // alien that was hit is removed
                laser.active = false;
                if (aliens.empty() && lives > 0)
                {
                    sleep_for(2s); // 2 second delay before creating new set of aliens
                    level++;
                    aliens = CreateAliens();
                    it = aliens.begin();
                }
            }

            else
            {
                ++it;
            }
        }
        // Checking with collisions between lasers and obstacles(shield for user spaceship)
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            { // iterates to end of blocks vector
                if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase(it); // removes specific block that was hit
                    laser.active = false;           // removes laser
                }
                else
                {
                    ++it;
                }
            }
        }
        // collision between spaceship laser and mystery ship
        if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect()))
        {
            mysteryShip.alive = false; // mystery ship is longer in play and has been hit
            laser.active = false;      // removes laser
            score += 500;              // adds 500 to score if the mystery ship is hit
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    // checking for collisions between Alien lasers and other objects within the program
    for (auto &laser : alienLasers)
    {
        // checking for collision between alien laser and user spaceship
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
        {
            laser.active = false;
            lives--; // loses a life when it by alien laser
            if (lives == 0)
            {
                GameOver(); // ends the game if spaceship runs out of lives.
            }
        }
        // Checking with collisions between lasers and obstacles(shield for user spaceship)
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            { // iterates to end of blocks vector
                if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase(it); // removes specific block that was hit
                    laser.active = false;           // removes laser
                }
                else
                {
                    ++it;
                }
            }
        }
    }
    // Checking collision with between aliens and obstacles(shields)

    for (auto &alien : aliens)
    {
        for (auto &obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(alien.getRect(), it->getRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        // Checking for collision between aliens and user spaceship
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        {
            GameOver();
        }
    }
}
void Game::GameOver()
{
    run = false; // when game ends, all the elements will freeze  the user will not be able to take any actions via keyboard
}

void Game::Reset()
{
    // resets all game objects to initial position before the game starts
    spaceship.Reset();
    aliens.clear();      // clears aliens vector storing all aliens
    alienLasers.clear(); // clears all aliens' lasers from alien laser vector
    obstacles.clear();   // removes all obstacles from obstacles vector
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20); // randomized value of how often mystery ship spawns
    lives = 3;                                         // amount of lives spaceship user has
    run = true;
    score = 0;
    highscore = loadHighscoreFromFile();
}

void Game::checkForHighscore()
{
    if (score > highscore)
    {
        highscore = score;
        saveHighscoreToFile(highscore); // saves new high score
    }
}

void Game::saveHighscoreToFile(int highScore)
{
    std::ofstream highscoreFile("highscore.txt"); // creates file to keep track of high score throughout all gams played
    if (highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::loadHighscoreFromFile()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file" << std::endl;
    }
    return loadedHighscore;
}