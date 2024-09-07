#pragma once
#include <vector>
#include "block.hpp"

/* This class will create the four obstacles the spaceship can hide behind to avoid
taking damage from alien lasers. The obstacles will be created by a series of blocks added together.
A 13 by 23 grid(will be created as a vector of subvectors in the program) will be created by the form of an array. Each spot in the grid will have the number 0 or 1.
If the number is 0, the color of the space will by black(the color will not be drawn in, it's just invisible).
If its 1, the color will be yellow. By using this grid, the grid will be shown as a series of blocks on the game board,
with each block having a color depending on its number. The blocks will be created using the block class and an upside-down U like shape
will be created for the obstacles. During the game, if an alien laser, hits the obstacle, the specific yellow block
that was hit by the obstacle will be destroyed, and that's block's number in the grid(array) will be turned to 0
and its color black, signifying that it's been hit by an enemy laser and is now destroyed. If the block was originally black,
then it cannot be hit by an alien laser and is considered invisible.
*/
class Obstacle
{
public:
    Obstacle(Vector2 position);
    void Draw();
    Vector2 position;
    std::vector<Block> blocks;                 // an attribute that contains all blocks created
    static std::vector<std::vector<int>> grid; // a vector of vectors grid for the blocks
};