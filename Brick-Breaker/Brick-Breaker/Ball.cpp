#include "Ball.h"

// Add a global game over flag
extern bool gameOver;  // global variable accessible to all the files

Ball::Ball(float radius, float x, float y) : velocity(0.15f, 0.15f) 
{
    shape.setRadius(radius);  //setRadius and setPosition are different functions of CircleShape class
    shape.setPosition(x, y);
}

void Ball::update() 
{
    shape.move(velocity);

    if (shape.getPosition().x < 0 || shape.getPosition().x + shape.getRadius() * 2 > 800) 
    {
        reboundSides();  //reverse the direction of the ball flow in X-axis
    }

    if (shape.getPosition().y < 0) 
    {
        reboundPaddleOrTop();  //reverse the direction of the ball flow in Y-axis
    }

    if (shape.getPosition().y + shape.getRadius() * 2 > 600) 
    {
        hitBottom();
    }
}

void Ball::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}

sf::CircleShape Ball::getShape() 
{
    return shape;
}

void Ball::reboundSides() 
{
    velocity.x = -velocity.x;
}

void Ball::reboundPaddleOrTop()
{
    velocity.y = -velocity.y;
}

void Ball::hitBottom()
{
    gameOver = true; // Set game over flag
}

void Ball::increaseSpeed(float factor)
{
    velocity.x *= factor;
    velocity.y *= factor;
}

