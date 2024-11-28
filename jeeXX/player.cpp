#include "Player.h"

Player::Player(float x, float y) : speed(5.0f), score(0) {
    paddle.setSize({ 10, 100 });
    paddle.setPosition(x, y);
    paddle.setFillColor(sf::Color::White);
}

void Player::moveUp() {
    if (paddle.getPosition().y > 0)
        paddle.move(0, -speed);
}

void Player::moveDown(float windowHeight) {
    if (paddle.getPosition().y + paddle.getSize().y < windowHeight)
        paddle.move(0, speed);
}

void Player::incrementScore() {
    score++;
}
