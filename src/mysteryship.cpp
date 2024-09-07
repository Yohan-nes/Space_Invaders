#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image); // unloads/removes image after window/screen closes
}

void MysteryShip::Spawn()
{ // sets position of where mystery ship will spawn
    // chooses randomly if it will spawn from left or right side and set its speed and direction according to each side
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0)
    {
        position.x = 25; // starts spawning the mystery ship within the yellow rounded rectangle
        speed = 2;
    }
    else
    {
        position.x = GetScreenWidth() - image.width - 25; // starts spawning the mystery ship within the yellow rounded
        speed = -2;
    }
    alive = true; // will signify ship is on the board and has not been hit yet
}

void MysteryShip::Update()
{ // updates position of mystery ship
    // if ship moves out of screen boundaries, it is considered dead.
    // It will not go from each side back and forth until it gets hit,
    // rather it just goes across the screen
    // and doesn't come back until it spawns again
    if (alive)
    {
        position.x += speed;
    }

    if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25) // THe 25 pixels is included to make sure the ship's activity is determined by when its in the yellow rounded rectangle
    {
        alive = false;
    }
}

void MysteryShip::Draw()
{
    if (alive)
    { // if mystery ship is alive, it will be drawn on the board
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle MysteryShip::getRect()
{
    // if mystery ship is alive, then a rectangle object of mystery ship image will be returned, else a rectangle of size 0 is returned.
    if (alive)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else
    {
        return {position.x, position.y, 0, 0};
    }
}