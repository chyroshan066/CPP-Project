#include "Brick.h"

Brick::Brick(float startX, float startY) 
{
    shape.setSize(sf::Vector2f(60, 20));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(startX, startY);
}

void Brick::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::RectangleShape Brick::getShape() 
{
    return shape;
}
