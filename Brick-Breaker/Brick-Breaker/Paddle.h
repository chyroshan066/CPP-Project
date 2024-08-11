#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle
{
public:
    Paddle(float startX, float startY);
    void update();
    void moveLeft();
    void moveRight();
    void draw(sf::RenderWindow& window);
    sf::RectangleShape getShape();

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
};

#endif // PADDLE_H
