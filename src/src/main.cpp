#include <iostream>
#include <raylib.h>
#include "game.hpp"

using namespace std;

std::string FormatWithLeadingZeros(int number, int width)
{ // returns a 5 digit score, whether its used for current score or highscore
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length(); // makes sure text of score to be 5 digits
    return numberText = std::string(leadingZeros, '0') + numberText;
}
int main()
{

    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50; // is used to created a yellow rounded rectangle as the borders in the game, leaving some space for the user interface to display  the current score of game, all tie high score, how many lives are left, and when the game is over
    int windowWidth = 750;
    int windowHeight = 750;
    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invaders"); // creates game window with title space invaders
    InitAudioDevice();                                                             // initializes audio devices that will allow sounds to be played throughout the game
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);                         // loads font in
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");              // imports spaceship image
    SetTargetFPS(60);                                                              // game will run at 60 fps
    Game game;                                                                     // creates game object

    while (WindowShouldClose() == false)
    {
        /*   if the escape key or X(close button on top right of window) is pressed,
         windowShouldClose() close will return true and the while loop will end(thus ending the game by closing the window)*/
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);                                               // makes background color grey
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow); // draws a yellow rounded rectangle around the game board
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);                        // draws a yellow line below spacehsip. A message will be displayed below this line to show how many lives user has left, what level hes on, and when the game is over
        if (game.run)
        {
            DrawTextEx(font, "Level", {570, 740}, 34, 2, yellow); // displays level on screen
            std::string levelText = FormatWithLeadingZeros(game.level, 2);
            DrawTextEx(font, levelText.c_str(), {700, 740}, 34, 2, yellow); // displays level on screen
        }
        else
        {
            // if game is not running, display message that game is over
            DrawTextEx(font, "GAME  OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50; // will be used to make each spaceship is 50 pixels apart
        for (int i = 0; i < game.lives; i++)
        { // will display how many lives user has in terms of spaceships on bottom left of screen
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }
        // displays current score of top left of screen
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        // displays high score on top right of screen
        DrawTextEx(font, " HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);

        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
}