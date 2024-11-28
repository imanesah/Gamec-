#include "Game.h"
#include <stdexcept>

Game::Game()
    : window(sf::VideoMode(800, 600), "Pong Game"), player1(10, 200), player2(780, 200),
    ball(400, 300), winningScore(5), state(GameState::Menu) {

    window.setFramerateLimit(60);

    if (!font.loadFromFile("arial.ttf"))
        throw std::runtime_error("Failed to load font.");
    if (!backgroundTexture.loadFromFile("background.jpg"))
        throw std::runtime_error("Failed to load background image.");

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        window.getSize().x / backgroundSprite.getGlobalBounds().width,
        window.getSize().y / backgroundSprite.getGlobalBounds().height);

    startText.setFont(font);
    startText.setString("Press Enter to Start");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(250, 500);

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 200);

    replayButton.setSize({ 200, 50 });
    replayButton.setFillColor(sf::Color::White);
    replayButton.setPosition(300, 300);

    quitButton.setSize({ 200, 50 });
    quitButton.setFillColor(sf::Color::White);
    quitButton.setPosition(300, 400);

    replayText.setFont(font);
    replayText.setString("Rejouer");
    replayText.setCharacterSize(20);
    replayText.setFillColor(sf::Color::Black);
    replayText.setPosition(350, 315);

    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(20);
    quitText.setFillColor(sf::Color::Black);
    quitText.setPosition(350, 415);
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (state == GameState::Menu && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            state = GameState::Playing;

        if (state == GameState::GameOver) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (replayButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    resetGame();
                    state = GameState::Playing;
                }
                else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            }
        }
    }

    if (state == GameState::Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player1.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player1.moveDown(window.getSize().y);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player2.moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player2.moveDown(window.getSize().y);
    }
}

void Game::update() {
    if (state == GameState::Playing) {
        ball.move();
        ball.checkCollision(window.getSize().x, window.getSize().y);

        if (ball.ball.getGlobalBounds().intersects(player1.paddle.getGlobalBounds()) ||
            ball.ball.getGlobalBounds().intersects(player2.paddle.getGlobalBounds())) {
            ball.velocity.x = -ball.velocity.x;
        }

        if (ball.ball.getPosition().x < 0) {
            player2.incrementScore();
            ball.reset(400, 300);
        }
        else if (ball.ball.getPosition().x > window.getSize().x) {
            player1.incrementScore();
            ball.reset(400, 300);
        }

        if (player1.score >= winningScore || player2.score >= winningScore)
            state = GameState::GameOver;
    }
}

void Game::render() {
    window.clear();

    window.draw(backgroundSprite);

    if (state == GameState::Menu) {
        window.draw(startText);
    }
    else if (state == GameState::Playing) {
        window.draw(player1.paddle);
        window.draw(player2.paddle);
        window.draw(ball.ball);

        scoreText.setString("Player 1: " + std::to_string(player1.score) +
            " | Player 2: " + std::to_string(player2.score));
        scoreText.setPosition(300, 10);
        window.draw(scoreText);
    }
    else if (state == GameState::GameOver) {
        gameOverText.setString(player1.score >= winningScore ? "Player 1 Wins!" : "Player 2 Wins!");
        window.draw(gameOverText);
        window.draw(replayButton);
        window.draw(quitButton);
        window.draw(replayText);
        window.draw(quitText);
    }

    window.display();
}

void Game::resetGame() {
    player1.score = 0;
    player2.score = 0;
    ball.reset(400, 300);
}
