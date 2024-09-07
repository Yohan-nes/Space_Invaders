#pragma once
#include "Spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include <chrono>
#include <thread>

class Game
{
public:
    Game();
    ~Game();
    void Draw();        // will draw all game objects(objects include the spaceship, enemy attackers, and shields the spaceship can hide behind to avoid getting hit by a laser)
    void Update();      // will update position of all the game objects
    void HandleInput(); // handles player's/user's input
    bool run;           // will be true if game is running, false if game is not running/ over
    int lives;          // amount of lives user spaceship will have
    int score;          // keeps track of score in game
    int highscore = 0;  // keeps track of highest score of games played in program
    Music music;
    int level = 1; // will keep track of level user is on

private:
    void DeleteInactiveLasers(); // deletes any inactive lasers(lasers that are out of the board)
    Spaceship spaceship;
    MysteryShip mysteryShip;
    std::vector<Obstacle> obstacles;                       // vector of obstacles
    std::vector<Obstacle> CreateObstacles();               // a method that will create 4 obstacles for the game and store and return them in a vector
    std::vector<Alien> aliens;                             // vector of alien objects
    std::vector<Alien> CreateAliens();                     // will be used to create aliens
    void MoveAliens();                                     // helps move aliens on board
    int aliensDirection;                                   // value contain direction of aliens movements
    void MoveDownAliens(int distance);                     // this method will use the parameter value to move the aliens downwards at specified distance
    std::vector<Laser> alienLasers;                        // a vector that will contain all lasers shot by aliens
    void AlienShootLaser();                                // will allow aliens to shoot lasers
    constexpr static float alienLaserShootInterval = 0.35; // want to put some delay(350 milliseconds) in how often an alien can shoot a laser
    float timeLastAlienFired;                              // keeps track of how long its been before alien last fired  a laser
    float mysteryShipSpawnInterval;                        // will hold the value of how often mystery ship will appear
    float timeLastSpawn;                                   // keep track of when last time mystery ship spawned
    void CheckForCollisions();                             // will check for collisions between various game objects in the program(lasers, alien, obstacles, mystery ship, user spaceships)
    void GameOver();                                       // will be used to end the game once spaceship has run out of lives
    void Reset();                                          // will reset all the variables/objects to their initial values
    void InitGame();                                       // will reset all the variables/objects to their initial values
    void checkForHighscore();                              // will be used to check and update high score
    void saveHighscoreToFile(int highscore);               // saves all time high score in file
    int loadHighscoreFromFile();                           // loads high score from highscore file tex
    Sound explosionSound;                                  // will be played when a spaceship laser has hit an alien or a mystery ship
};
