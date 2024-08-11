#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

class Brick
{
public:
    Brick(float startX, float startY);
    void draw(sf::RenderWindow& window);
    sf::RectangleShape getShape();

private:
    sf::RectangleShape shape;  //RectangleShape is a class provided by SFML that represents a rectangle shape
};

#endif // BRICK_H
