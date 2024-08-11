#ifndef BALL_H  // prevent multiple inclusions of the same header file in main.cpp
#define BALL_H

#include <SFML/Graphics.hpp>  //SFML library

class Ball
{
public:
    Ball(float radius, float x, float y);
    void update();
    void draw(sf::RenderWindow& window);  //RenderWindow is a class that provides a window for rendering graphics.
    sf::CircleShape getShape();
    void reboundSides();
    void reboundPaddleOrTop();
    void hitBottom();
    void increaseSpeed(float factor); // Method to increase speed

private:
    sf::CircleShape shape;  //sf is a namespace used by SFML. It help organize code and prevent naming conflicts.
                            //CircleShape is a class provided by SFML that represents a circle shape and position
    sf::Vector2f velocity;  //Vector2f is a class used to represent a two-dimensional vector with floating-point coordinates.
};

#endif // BALL_H  // ends ifndef pre-processor directive
