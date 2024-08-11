#include "Paddle.h"

Paddle::Paddle(float startX, float startY) 
{
    shape.setSize(sf::Vector2f(100, 20));
    shape.setPosition(startX, startY);
}

void Paddle::update() 
{
    shape.move(velocity);

    if (shape.getPosition().x < 0)
    {
        shape.setPosition(0, shape.getPosition().y);
    }
    else if (shape.getPosition().x + shape.getSize().x > 800)
    {
        shape.setPosition(800 - shape.getSize().x, shape.getPosition().y);
    }

    velocity.x = 0; // Reset velocity after movement
}

void Paddle::moveLeft() 
{
    velocity.x = -0.3f; // Adjusted paddle speed
}

void Paddle::moveRight() 
{
    velocity.x = 0.3f; // Adjusted paddle speed
}

void Paddle::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}

sf::RectangleShape Paddle::getShape() 
{
    return shape;
}
