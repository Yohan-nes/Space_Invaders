#pragma once
#include <raylib.h>

class Block // this class will create blocks that will be used to make the obstacles the spaceship can hide behind in to avoid taking damage from aliens
{
public:
    Block(Vector2 position);
    void Draw();
    Rectangle getRect(); // will be used to create a rectangle object of blocks to use  raylib's CheckCollisionRecs method to determined any collision between obstacles(shields for the user) and any other objects within the game(lasers, aliens)

private:
    Vector2 position;
};