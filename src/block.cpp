#include "block.hpp"

Block::Block(Vector2 position)
{
    this->position = position;
}
void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255}); // create a  rectangle 3 by 3 pixel yellow block
}

Rectangle Block::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    // each block is a 3 by 3 pixel square
    rect.width = 3;
    rect.height = 3;
    return rect;
}