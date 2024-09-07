#pragma once
#include <raylib.h>

class Laser
{
public:
    Laser(Vector2 position, int speed); // constructor that sets position and speed of laser
    void Draw();                        // draws laser on the screen
    void Update();                      // updates position of laser on screen
    bool active;                        // will be used to remove laser's activity when its outside the board, removing and destroying it from computer's memory
    Rectangle getRect();                // creates rectangle object for lasers so that they can be used in raylib's GetCollisionRecs method to see if there was any collision between  lasers and any other objects within the game(obstacles, user spaceship, aliens, mystery ships)
private:
    Vector2 position; // position of laser on board
    int speed;        // speed of laser
};