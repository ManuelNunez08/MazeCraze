
#pragma once
#include <string>
#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <set>
#include <stack>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "maze.h"

#ifndef PROJECT_3_FINAL_MAZEANALYSIS_H
#define PROJECT_3_FINAL_MAZEANALYSIS_H



class MazeAnalysis
{
    maze* analysisMaze;
    string AnalysisIntro;

    bool gameJustStarted;
public:

    sf::Text visited;
    sf::Text numVisited;
    sf::Text text;
    sf::Font font;
    sf::Text Select;
    sf::Text BFSButton;
    sf::Text DFSButton;
    sf::Text backToMenuButton;
    sf::Text startButton;
    sf::Text restartButton;
    sf::Text selectSpeed;
    sf::Text slow;
    sf::Text normal;
    sf::Text fast;

    int speedChoice;

    int choice;

    MazeAnalysis();

    // vector to store all the squares the algorithms have visited in order to display them
    vector<int> pathSquares;

    //Index to be used to iterate through pathSquares and display it
    int index;

    // vector to store locations from which to find the shortest path.
    vector<int> pathFromTo;

    // vector to store squares currently marking path
    vector<int> blues;


    bool startGame;

    // time variable to make red path show for a given amount of time;
    steady_clock::time_point start;

    void DrawBoard(sf::RenderWindow& window);

    void textHandler();

    void DrawPath(sf::RenderWindow& window, vector<int> squares, int source, int destination);

    // for testing (gotten of internet to test with: will implement our own later)
    bool BFS(int src, int dest, int v, map <int, int >& pred, map <int, int>& dist, sf::RenderWindow& window);
    bool DFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance, sf::RenderWindow& window);
    void ShortestDistance(int s, int dest, int v, int choice, sf::RenderWindow& window);

    void trackMouseClicks(sf::Event& event, sf::RenderWindow& window, string& MODE);
    void CorrectGraph(int index);

    void reset();
};


#endif //PROJECT_3_FINAL_MAZEANALYSIS_H
