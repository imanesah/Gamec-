#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    sf::RectangleShape paddle;
    float speed;
    int score;

    Player(float x, float y);
    void moveUp();
    void moveDown(float windowHeight);
    void incrementScore();
};

#endif
