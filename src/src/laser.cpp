#include "laser.hpp"

Laser::Laser(Vector2 position, int speed)
{
    this->position = position;
    this->speed = speed;
    active = true;
}

void Laser::Draw()
{ // drawing the lasers if the laser is considered active and inside the game board, which will be yellow rectangles
    if (active)
    {
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
    }
}

void Laser::Update()
{
    position.y += speed;
    if (active)
    {
        if ((position.y > GetScreenHeight() - 100) || position.y < 25) // destroys lasers when it passed spaceships position, not when it goes out of the screen
        {
            active = false;
        } // when laser leaves the game boundary, it is considered inactive and destroyed
    }
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    // the laser is a 4 by 15 pixel rectangle
    rect.width = 4;
    rect.height = 15;
    return rect;
}