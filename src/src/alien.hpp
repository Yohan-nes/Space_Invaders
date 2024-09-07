#pragma once
#include <raylib.h>

class Alien
{ // creates alien(enemy) spaceships the player will be trying to destroy in the game
public:
    Alien(int type, Vector2 position); // constructor initializing alien with a type and position.
    void Update(int direction);        // updates alien position on board
    void Draw();                       // draws alien on board
    int GetType();                     // returns a number associated with alien type
    static Texture2D alienImages[3];   // puts all 3 alien types in an array so that the program is loading the alien images from this array instead of from the disk/file, making the program load quicker
    int type;                          // there will be different types of aliens. Each type will be distinguished by a number
    Vector2 position;                  // position of alien
    static void UnloadImages();        // unloads and removes the images when the window is closed
    Rectangle getRect();               // returns a rectangle object of alien images to be used in raylib's CheckCollisionRecs method to check collision between aliens and other objects within the game
private:
};