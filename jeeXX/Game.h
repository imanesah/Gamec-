#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.h"
#include "Ball.h"

class Game {
private:
    sf::RenderWindow window;
    Player player1;
    Player player2;
    Ball ball;
    const int winningScore;

    enum class GameState { Menu, Playing, GameOver };
    GameState state;

    sf::Font font;
    sf::Text startText;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text replayText;
    sf::Text quitText;

    sf::RectangleShape replayButton;
    sf::RectangleShape quitButton;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void resetGame();
};

#endif
