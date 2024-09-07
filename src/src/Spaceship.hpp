#pragma once // ensures this file is only called once when compiling to avoid duplicate definition
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship // handles the spaceship creation and its function
{
public:
    Spaceship();
    ~Spaceship();
    void Draw();               // will draw the spaceship
    void MoveLeft();           // will help move the spaceship to the left
    void MoveRight();          // will help move the spaceship to the right
    void FireLaser();          // will help the spaceship fire lasers at the enemy objects
    std::vector<Laser> lasers; // an attribute to hold all lasers used in the game
    Rectangle getRect();       // will be used to create a rectangle object for the spaceship to utilize raylib's method CheckCollisionRecs to see if there are any collision between lasers and spaceship
    void Reset();              // resets spacheship to bottom center of game and deletes all of its laser
private:
    Texture2D image;
    Vector2 position;
    double lastFireTime; // will be used to make sure the user cannot continuously fire a laser with no delay in between
    Sound laserSound;    // will be played when spaceship fires a laser
};