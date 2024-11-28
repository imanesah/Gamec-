#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    sf::CircleShape ball;
    sf::Vector2f velocity;

    Ball(float x, float y);
    void move();
    void checkCollision(float windowWidth, float windowHeight);
    void reset(float x, float y);
};

#endif
