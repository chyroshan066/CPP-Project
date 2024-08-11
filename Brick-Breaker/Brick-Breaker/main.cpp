#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>  //provides functionalities for reading from and writing to files. Includes the classes std::ifstream, std::ofstream, and std::fstream, which are used to handle file input and output operations.
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include <vector>   //provides a dynamic array that can grow and shrink in size automatically.
#include <string>

// Global variables
bool gameOver = false; // Game over flag
bool restartRequested = false; // Flag to check if restart is requested
bool gameWon = false; // Flag to check if game is won
std::string userName;
std::string highScoreUserName;
int highScore = 0;

// Function to reset the game state
void resetGame(Ball& ball, Paddle& paddle, std::vector<Brick>& bricks, int& score)
{
    // Reset ball
    ball = Ball(10.f, 400.f, 300.f);

    // Reset paddle
    paddle = Paddle(350.f, 550.f);

    // Reset bricks
    bricks.clear();
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 5; ++j) {
            bricks.push_back(Brick(i * 70 + 35, j * 30 + 30));
        }
    }

    // Reset score and flags
    score = 0;
    gameOver = false;
    restartRequested = false;
    gameWon = false;
}

void loadHighScoreAndUserName()
{
    std::ifstream file("highscore.txt");  //open the file highscore.txt for reading.   ifstream --> for reading files
    if (file.is_open())
    {
        file >> highScore;  // Read the high score
        file.ignore();      // Ignore the newline after the high score
        std::getline(file, highScoreUserName);  // Read the associated username
        file.close();
    }
}

void saveScore(int score, const std::string& userName)
{
    /*std::ofstream file("highscore.txt");  //open the file highscore.txt for writing.   ofstream --> for writing files
    if (file.is_open())
    {
        if (score > highScore)
        {
            highScore = score;  // Update high score
            highScoreUserName = userName;  // Update high score username
            file << highScoreUserName << "\t";  // Save the associated username
            file << highScore ;  // Save the new high score
        }
        else
        {
            file << highScoreUserName << '\t';  // Save the existing username
            file << highScore;  // Save the existing high score
        }
        file.close();
    }*/
    if (score > highScore)
    {
        std::ofstream file("highscore.txt");
        if (file.is_open())
        {
            file << score << '\n' << userName;
            file.close();
        }
    }
}

int main()
{
    loadHighScoreAndUserName();

    std::cout << "Enter your name: ";
    std::getline(std::cin, userName);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Brick Breaker");  //sf::VideoMode constructs object that specifies the dimensions of the window.
    //height --> 600px, width --> 800px
    //Brick Breaker is the title of the window
    //object window is created with specified title and size

    Ball ball(10.f, 400.f, 300.f);
    Paddle paddle(350.f, 550.f);

    std::vector<Brick> bricks;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            bricks.push_back(Brick(i * 70 + 35, j * 30 + 30));
        }
    }

    // Score variables
    int score = 0;
    sf::Font font;  //Font is a class provided by SFML library for handling texts
    if (!font.loadFromFile("arial.ttf"))
    { // Ensure the font file is in the project directory
        return -1;  // Ends the function
    }
    sf::Text scoreText;  //Text is a class provided by SFML library for handling texts
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200.f, 250.f);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(200.f, 350.f);

    sf::Text victoryText;
    victoryText.setFont(font);
    victoryText.setCharacterSize(48);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setPosition(50.f, 250.f);

    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::Yellow);
    highScoreText.setPosition(10.f, 50.f);

    while (window.isOpen())  //returns 'true' when window is open and 'false' if the window is closed
    {
        sf::Event event;  //object to store information about events that occur such as  keyboard presses, mouse movements, window resizing
        while (window.pollEvent(event))  //Retrieves the next event from the event queue and stores it in the event object. Returns true if there are more events to process and false if the queue is empty.
        {
            if (event.type == sf::Event::Closed)
                window.close();  //Closes the window and causes the while (window.isOpen()) loop to terminate.
        }

        if (gameOver || gameWon)
        {
            if (gameWon)
            {
                victoryText.setString("Hurray! You Successfully\n Completed The Game\nPress R to Restart");
            }
            else
            {
                gameOverText.setString("Game Over!\nScore: " + std::to_string(score) + "\nPress R to Restart");
            }

            if (score > highScore)
                highScoreText.setString("High Score: " + std::to_string(score) + "\nBy: " + userName);
            else
                highScoreText.setString("High Score: " + std::to_string(highScore) + "\nBy: " + highScoreUserName);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))   //Keyboard is an SFML class which handles keyboard input
                //sf::Keyboard::isKeyPressed checks the state of the key in real-time, so it will continuously set restartRequested to true as long as the key is pressed
            {
                restartRequested = true;
            }

            if (restartRequested)
            {
                resetGame(ball, paddle, bricks, score);
                highScoreText.setString("");
            }

            window.clear();
            if (gameWon)
            {
                window.draw(victoryText); // Display victory message
            }
            else
            {
                window.draw(gameOverText); // Display game over text
            }
            window.draw(highScoreText);
            window.display();
            continue; // Skip the rest of the loop
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            paddle.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            paddle.moveRight();
        }

        ball.update();
        paddle.update();

        sf::RectangleShape paddleShape = paddle.getShape();
        sf::CircleShape ballShape = ball.getShape();

        if (ballShape.getGlobalBounds().intersects(paddleShape.getGlobalBounds()))  //Checks whether the paddle and ball intersects or not
        {
            ball.reboundPaddleOrTop();
        }

        for (auto it = bricks.begin(); it != bricks.end();)  //auto keyword automatically deduce the type of a variable from its initializer.
            //Checking for the collision of the ball and bricks to remove the bricks which has been collided
        {
            if (ballShape.getGlobalBounds().intersects(it->getShape().getGlobalBounds()))
            {
                ball.reboundPaddleOrTop();
                it = bricks.erase(it);
                score++; // Increment the score when a brick is broken
                ball.increaseSpeed(1.02f); // Slightly increase ball speed (2% increase)
            }
            else
            {
                ++it;
            }
        }

        // Check for victory
        if (bricks.empty())
        {
            gameWon = true; // Set victory flag if all bricks are gone
        }

        // Update the score text
        scoreText.setString("Score: " + std::to_string(score));

        window.clear();
        ball.draw(window);
        paddle.draw(window);

        for (auto& brick : bricks)  //populate the bricks and & avoids copying of the same variable
        {
            brick.draw(window);
        }

        window.draw(scoreText); // Draw the score text
        window.draw(highScoreText);
        window.display();
    }
    saveScore(score, userName); // Save score when game ends

    return 0;
}
