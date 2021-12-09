#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include "TextureManager.h"

#ifndef PROJECT_3_FINAL_SQUARE_H
#define PROJECT_3_FINAL_SQUARE_H


using namespace std;
using namespace std::chrono;


class square{
    // small maze analysis squares
    sf::Sprite smallWhiteSquare;
    sf::Sprite smallBlackSquare;
    sf::Sprite smallBlueSquare;
    sf::Sprite smallRedSquare;

    // large maze game squares
    sf::Sprite bigWhiteSquare;
    sf::Sprite bigBlueSquare;
    sf::Sprite bigRedSquare;
    sf::Sprite bigGreenSquare;


public:
    // sprites defined by outside class
    sf::Sprite bigBlackSquare;

    //Constructor
    square(string color, int numSquare, string MODE);

    string MODE;

    //Booleans to control tile state
    bool white;
    bool black;
    bool blue;
    bool red;
    bool green;
    int numSquare;

    steady_clock::time_point start;

    vector<pair<square*,square*>> adjacentSquares;

    void Draw(sf::RenderWindow& window);
    void SetSquarePosition(float xPosition, float yPosition);
    sf::Sprite SquarePosition();
};


#endif //PROJECT_3_FINAL_SQUARE_H
