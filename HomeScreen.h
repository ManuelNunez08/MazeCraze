#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "square.h"
#include "maze.h"


#ifndef PROJECT_3_FINAL_HOMESCREEN_H
#define PROJECT_3_FINAL_HOMESCREEN_H

using namespace std;
using namespace std::chrono;

class HomeScreen{
public:
    HomeScreen(int screenWidth, int ScreenLength);
    int screenWidth, screenLength;


    sf::Font font;
    sf::Text titleText;
    sf::Text GameModeText;
    sf::Text MazeAnalysisText;

    steady_clock::time_point start;

    vector<square> squares;

    void alternateSquares();
    void initializeSquares();
    void setText();
    void drawScreen(sf::RenderWindow &window);
    void trackMouseClicks(sf::Event &event, sf::RenderWindow &window, string& MODE);
};


#endif //PROJECT_3_FINAL_HOMESCREEN_H
