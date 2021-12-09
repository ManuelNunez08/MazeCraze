#include "HomeScreen.h"


HomeScreen::HomeScreen(int screenWidth, int screenLength) {
    this->screenWidth = screenWidth;
    this->screenLength = screenLength;
    setText();
    initializeSquares();


}


void HomeScreen::drawScreen(sf::RenderWindow &window) {

    window.draw(titleText);
    window.draw(GameModeText);
    window.draw(MazeAnalysisText);

    for ( int i  = 0; i < squares.size(); i ++){
        squares[i].Draw(window);
    }

    if ((steady_clock::now() - start) > milliseconds(500)){
        alternateSquares();
    }
}



void HomeScreen::trackMouseClicks(sf::Event &event, sf::RenderWindow &window, string& MODE) {

        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // Iterate through all tiles and check what tile, if any the mouse is over.

            auto MazeAnalysisOption = MazeAnalysisText.getGlobalBounds();
            //If the mouse is over the tile in question and the game is still going
            if ((MazeAnalysisOption.contains(mousePos.x, mousePos.y))) {
                MODE = "Maze Analysis";
            }

            auto GameModeOption = GameModeText.getGlobalBounds();
            //If the mouse is over the tile in question and the game is still going
            if ((GameModeOption.contains(mousePos.x, mousePos.y))) {
                MODE = "Maze Game";
            }
        }
}




void HomeScreen::setText() {

    // define text font
    font.loadFromFile("SFCompact.ttf");



    // select the font
    titleText.setFont(font); // font is a sf::Font
    // set the string to display
    titleText.setString("MAZE CRAZE");
    // set the character size
    titleText.setCharacterSize(100); // in pixels, not points!
    // set the color
    titleText.setFillColor(sf::Color::White);
    // set the text style
    titleText.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
    titleText.setPosition(sf::Vector2f(10.0*((double)(screenWidth)/2.0f), 10.0*((double)screenLength/2.0f) - 10.0*((double)screenLength/ 5.0f)));



    GameModeText.setFont(font); // font is a sf::Font
    // set the string to display
    GameModeText.setString("Maze Game");
    // set the character size
    GameModeText.setCharacterSize(50);
    // set the color
    GameModeText.setFillColor(sf::Color::White);
    // set the text style
    GameModeText.setStyle(sf::Text::Bold);
    sf::FloatRect textRectTwo = GameModeText.getLocalBounds();
    GameModeText.setOrigin(textRectTwo.left + textRectTwo.width/2.0f,
                           textRectTwo.top  + textRectTwo.height/2.0f);
    GameModeText.setPosition(titleText.getPosition().x , titleText.getPosition().y + 100);


    MazeAnalysisText.setFont(font); // font is a sf::Font
    // set the string to display
    MazeAnalysisText.setString("Maze Analysis");
    // set the character size
    MazeAnalysisText.setCharacterSize(50);
    // set the color
    MazeAnalysisText.setFillColor(sf::Color::White);
    // set the text style
    MazeAnalysisText.setStyle(sf::Text::Bold);
    sf::FloatRect textRectThree = MazeAnalysisText.getLocalBounds();
    MazeAnalysisText.setOrigin(textRectThree.left + textRectThree.width/2.0f,
                               textRectThree.top  + textRectThree.height/2.0f);
    MazeAnalysisText.setPosition(titleText.getPosition().x , titleText.getPosition().y + 200);

}

void HomeScreen::initializeSquares() {

    string MODE = "Maze Analysis";
    int columnMargin = screenWidth/8;
    int rowMargin = screenLength/8;
    // A for loop adds squares onto the board and initially creates a maze with all edges present.
    string color = "white";
    int numSquare = 0;
    for (int i = 0; i < screenLength; i ++ ) {
        //Each iteration of the loop below completes a row
        for (int j = 0; j < screenWidth; j++) {
            if ( ((i < rowMargin) || (i > (screenLength - rowMargin )) ) ||
                 ((j < columnMargin) || (j > (screenWidth - columnMargin)))){
                // alternate colors
                if (j % 2 == 0 && i % 2 == 0) {
                    color = "white";
                } else {
                    color = "black";
                }
                // create new square and add to square vector
                square newSquare(color, numSquare, MODE );
                newSquare.SetSquarePosition((j * 10.0f), (i * 10.0f));
                squares.push_back(newSquare);
                numSquare++;
            }
        }
    }

    start = high_resolution_clock::now();

}

void HomeScreen::alternateSquares() {
    for ( int i =0; i < squares.size(); i++){
        squares[i].white = !squares[i].white;
        squares[i].black = !squares[i].black;
    }
    start = high_resolution_clock::now();
}
