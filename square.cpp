#include "square.h"

square::square(string color, int numSquare, string MODE) {

    // assign mode
    this->MODE = MODE;


    // set textures for small squares
    smallWhiteSquare.setTexture(TextureManager::GetTexture("small_white_square"));
    smallBlackSquare.setTexture(TextureManager::GetTexture("small_black_square"));
    smallBlueSquare.setTexture(TextureManager::GetTexture("small_blue_square"));
    smallRedSquare.setTexture(TextureManager::GetTexture("small_red_square"));


    // set texture for big squares
    bigWhiteSquare.setTexture(TextureManager::GetTexture("road"));
    bigBlackSquare.setTexture(TextureManager::GetTexture("game_black_Square"));
    bigBlueSquare.setTexture(TextureManager::GetTexture("game_blue_square"));
    bigRedSquare.setTexture(TextureManager::GetTexture("game_red_square"));
    bigGreenSquare.setTexture(TextureManager::GetTexture("game_green_square"));


    // set square color
    if ( color == "white"){
        white = true;
        black = false;
    }
    else if (color == "black"){
        white = false;
        black = true;
    }

    blue  = false;
    red = false;
    green = false;


    this->numSquare = numSquare;

}




void square::Draw(sf::RenderWindow &window) {
    if (MODE == "Maze Analysis") {
        if (blue) {
            window.draw(smallBlueSquare);
        }
        if(red){
            window.draw(smallRedSquare);
        }
        else if (white && !black) {
            window.draw(smallWhiteSquare);
        }
        else if (!white && black) {
            window.draw(smallBlackSquare);
        }
    }
    else if (MODE == "Maze Game"){
        if (blue) {
            window.draw(bigBlueSquare);
        }
        else if (red){
            window.draw(bigRedSquare);
        }
        else if (green){
            window.draw(bigGreenSquare);
        }
        else if (white && !black) {
            window.draw(bigWhiteSquare);
        }
        else if (!white && black) {
            window.draw(bigBlackSquare);
        }
    }
}



void square::SetSquarePosition(float xPosition, float yPosition) {
    if (MODE == "Maze Analysis") {
        smallBlackSquare.setPosition(xPosition, yPosition);
        smallWhiteSquare.setPosition(xPosition, yPosition);
        smallBlueSquare.setPosition(xPosition, yPosition);
        smallRedSquare.setPosition(xPosition, yPosition);
    }
    else if (MODE == "Maze Game"){
        bigBlackSquare.setPosition(xPosition, yPosition);
        bigWhiteSquare.setPosition(xPosition, yPosition);
        bigBlueSquare.setPosition(xPosition, yPosition);
        bigRedSquare.setPosition(xPosition, yPosition);
        bigGreenSquare.setPosition(xPosition, yPosition);
    }
}


sf::Sprite square::SquarePosition() {

    if (MODE == "Maze Analysis") {
        return smallWhiteSquare;
    }
    else if (MODE == "Maze Game"){
        return bigWhiteSquare;
    }
}
