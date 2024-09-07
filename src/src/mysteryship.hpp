#pragma once
#include <raylib.h>

class MysteryShip
{ /* this class will create a mystery ship that appears from time
to time on the board. It will not shoot lasers at the player, but it allows the player to shoot lasers
at it to gain extra points throughout the game session.*/

public:
    MysteryShip();
    ~MysteryShip();
    void Update();       // updates mystery ships position on the screen
    void Draw();         // draws mystery ship
    void Spawn();        // helps create one mystery ship object that is stored and reappears from time to time
    bool alive;          // keeps track of whether the mystery ship is alive or dead
    Rectangle getRect(); // will be used to create a rectangle object for the mystery spaceship to utilize the raylib's method CheckCollisionRecs to see if there are any collision between lasers and  mystery spaceship
private:
    Vector2 position; // holds position of mystery ship
    Texture2D image;  // holds image of mystery ship
    int speed;        // holds speed of mystery ship
};