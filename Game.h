#pragma once
#include "maze.h"
#include "TextureManager.h"
#include "Random.h"
#include <thread>

#ifndef PROJECT_3_FINAL_GAME_H
#define PROJECT_3_FINAL_GAME_H


class Game{
    int startSquare;
    int destSquare;
    int playerSquare;  //square number of the green square that the player will control
    string gameIntro;
    string hintText;
    int secondsLeft;
    int currtime;
    int remainingHints;
    bool showingPath;

    int windowWidth;
    int windowLength;

    bool startGame;

public:
    //game board object that will be worked with
    maze* gameBoard;

    //for hints
    vector<int> blues;

    //start time
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point elapsedTime;
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point startText;

    sf::Text time;
    sf::Text text;
    sf::Text hint;
    sf::Font font;
    sf::Text startButton;
    sf::Text restartButton;
    sf::Text backToMenuButton;

    //constructor that takes int the complete board
    Game(int windowWidth, int windowLength);
    void textHandler();
    void DrawGame(sf::RenderWindow& window);

    void trackMouseClicks(sf::Event &event, sf::RenderWindow &window, string& MODE);
    void trackKeyBoard(sf::Event &event, sf::RenderWindow &window);
    void DrawPlayer(sf::RenderWindow& window);
    void DrawDestination(sf::RenderWindow& window);
    void movePlayer(sf::RenderWindow& window, string direction);
    void ShowHint(sf::RenderWindow& window);
    void assignStartAndEnd();
    void reset();
    //for the hints
    bool BFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance);
    void ShortestDistance(int sourceSquare, int destinationSquare, int numVertices);
};


#endif //PROJECT_3_FINAL_GAME_H
