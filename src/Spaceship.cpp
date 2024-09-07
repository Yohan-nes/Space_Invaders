#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png"); // spaceship image
    // loads image at the bottom center of the board
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = (GetScreenHeight() - image.height) - 100;
    lastFireTime = 0.0;
    laserSound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() // ~ in front of any method name means the method is a destructor. A destructor destroys the object that was created by original constructor
{
    UnloadTexture(image);
    UnloadSound(laserSound);
}

void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE); // draws spaceship on specified position on board in white
}

void Spaceship::MoveLeft()
{
    position.x -= 7; // moves space by 7 pixels to left
    if (position.x < 25)
    {
        position.x = 25;
    }
}

void Spaceship::MoveRight()
{
    position.x += 7;                                       // moves spaceship by 7 pixels to the right
    if (position.x >= GetScreenWidth() - image.width - 25) // the addition of the 15 pixels makes sure the spaceship stays within yellow rounded rectangle
    {
        position.x = GetScreenWidth() - image.width - 25; // the addition of the 15 pixels makes sure the spaceship says within the yellow rounded rectangle
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime >= 0.35)
    {                                                                                // makes sure the user can only fire a laser every 350 milliseconds, cannot continuously fire lasers
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6)); // creates laser right on top of the spaceship's position and includes the speed(-6 speed in pixels means its going up)
        lastFireTime = GetTime();                                                    // updates the fire time variable to keep track of how long its been since the user last fired a laser
        PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)}; // a rectangle object of spaceship image
}

void Spaceship::Reset()
{
    // resets spaceship's position to bottom center of screen
    position.x = GetScreenWidth() / 2 - image.width / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear(); // clears all of spaceships lasers
}