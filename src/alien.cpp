#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};
Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;
    if (alienImages[type - 1].id == 0)
    { // means array has not been initalized yet and the images will be loaded into the array

        switch (type) // depending on type of alien(1,2, or 3) a different alien will appear on the screen
        {
        case 1:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            break;
        default: // default alien if no type is specified
            alienImages[1] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type - 1], position, WHITE);
}

int Alien::GetType()
{
    return type; // returns alien type
}

void Alien::UnloadImages()
{
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

void Alien::Update(int direction)
{ // updates alien's horizontal direction with parameter value
    position.x += direction;
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)}; // returns rectangle object of specific alien
}