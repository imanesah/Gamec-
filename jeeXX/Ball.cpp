#include "Ball.h"

Ball::Ball(float x, float y) : velocity(4.0f, 4.0f) {
    ball.setRadius(10);
    ball.setPosition(x, y);
    ball.setFillColor(sf::Color::White);
}

void Ball::move() {
    ball.move(velocity);
}

void Ball::checkCollision(float windowWidth, float windowHeight) {
    if (ball.getPosition().y < 0 || ball.getPosition().y > windowHeight - ball.getRadius() * 2)
        velocity.y = -velocity.y;
}

void Ball::reset(float x, float y) {
    ball.setPosition(x, y);
    velocity = { 4.0f, 4.0f };
}
