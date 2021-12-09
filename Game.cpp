
#include "Game.h"
#include <iostream>


typedef high_resolution_clock Clock;


Game::Game(int windowWidth, int windowLength){

    gameIntro = "OH NO!\nYou're late for work and\nhave 1 minute"
                       " to cross\nthe city or else you'll be \nfired!\n"
                       "Better get going...";

    hintText = "**You are the Green Square*"
               "\n**Your Boss is the Red Square**\n**Move with Arrow Keys**"
               "\n**PRESS H FOR A HINT** \nnumber of Hints remaining: ";

    // initialize start game to false
    startGame = false;
    showingPath = false;

    // define width and length of window
    this->windowWidth = windowWidth;
    this->windowLength = windowLength;

    // declare maze
    string mode = "Maze Game";
    gameBoard = new maze (51, 37, mode, 20);

    //choose where the user will start and end
    assignStartAndEnd();

    // define text
    textHandler();


    this->secondsLeft = 60;
    this->currtime = 0;
    this->remainingHints = 3;

}

void Game::DrawGame(sf::RenderWindow& window) {
    gameBoard->DrawMaze(window);
    window.draw(startButton);
    window.draw(restartButton);
    window.draw(backToMenuButton);
    window.draw(text);

    //draw the player and the destination
    DrawDestination(window);
    DrawPlayer(window);

    if ((steady_clock::now() - startText) > milliseconds(250)){
        backToMenuButton.setFillColor(sf::Color::White);
        startButton.setFillColor(sf::Color::White);
        restartButton.setFillColor(sf::Color::White);
    }


    if (!startGame) {
        time.setString("Seconds Left: " + to_string(secondsLeft - currtime) );
        window.draw(time);
        hint.setString(hintText + to_string(remainingHints));
        window.draw(hint);
    }
    else {
        //draw clock and text
        time.setString("Seconds Left: " + to_string(secondsLeft - currtime));
        window.draw(time);
        hint.setString(hintText + to_string(remainingHints));
        window.draw(hint);


        //different cases for if game is going/ is over
        elapsedTime = Clock::now();



        if ((steady_clock::now() - start) > seconds(1)) {
            if (!blues.empty()) {
                //revert path to normal
                for (int i = 0; i < blues.size(); i++) {
                    gameBoard->squares[blues[i]].blue = false;
                }
                // clear blues
                blues.clear();
            }
            showingPath = false;

        }

        //showtime
        if (duration_cast<seconds>(elapsedTime - startTime).count() != currtime) {
            currtime = duration_cast<seconds>(elapsedTime - startTime).count();
        }

        //win condition: player square = destination square and time > 0
        if (playerSquare == destSquare &&
            secondsLeft - (duration_cast<seconds>(elapsedTime - startTime).count() - 1) > 0) {
            text.setCharacterSize(40);
            startGame = false;
            text.setString("YOU WIN!\nYou did not get\n fired! :)");
        }
        //loose condition: time up
        if (duration_cast<seconds>(elapsedTime - startTime).count() == secondsLeft) {
            text.setCharacterSize(40);
            startGame = false;
            text.setString("YOU LOSE!\nTime to find a new\n job :(");
        }
    }
}


void Game::DrawPlayer(sf::RenderWindow& window) {
    gameBoard->squares[playerSquare].green = true;
}

void Game::DrawDestination(sf::RenderWindow& window) {
    gameBoard->squares[destSquare].red = true;
}

void Game::movePlayer(sf::RenderWindow& window, string direction) {
    if (direction == "left" && gameBoard->squares[playerSquare - 1].white && playerSquare % gameBoard->getNumColumns() != 0){
        gameBoard->squares[playerSquare].green = false;
        playerSquare = playerSquare - 1;
    }
    else if (direction == "right" && gameBoard->squares[playerSquare + 1].white && (playerSquare + 1) % gameBoard->getNumColumns() != 0) {
        gameBoard->squares[playerSquare].green = false;
        playerSquare = playerSquare + 1;
    }
    else if (direction == "up" && playerSquare - gameBoard->getNumColumns() >= 0) {
        if(gameBoard->squares[playerSquare - gameBoard->getNumColumns()].white) {
            gameBoard->squares[playerSquare].green = false;
            playerSquare = playerSquare - gameBoard->getNumColumns();
        }
    }
    else if(direction == "down" && playerSquare + gameBoard->getNumColumns() < gameBoard->getNumColumns() * gameBoard->getNumRows()) {
        if(gameBoard->squares[playerSquare + gameBoard->getNumColumns()].white) {
            gameBoard->squares[playerSquare].green = false;
            playerSquare = playerSquare + gameBoard->getNumColumns();
        }
    }
}

void Game::ShowHint(sf::RenderWindow& window) {
    if (startGame && remainingHints > 0) {
        remainingHints--;
        ShortestDistance(playerSquare, destSquare, gameBoard->getNumVertices());
    }
    showingPath = true;
}



bool Game::BFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance) {

    // declare queue
    list<int> queue;

    // use a queue to keep track of visited nodes
    unordered_set <int> visited;

    // initialize all distances to max and all predecessors to -1
    for (auto iter = gameBoard->adjacencyList.begin(); iter != gameBoard->adjacencyList.end(); iter++) {
        predecessor[(*iter).first] = -1;
        distance[(*iter).first] = INT_MAX;
    }

    // add source to visited, define its distance, and add it to the queue.
    visited.insert(source);
    distance[source] = 0;
    queue.push_back(source);


    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        for (auto iter = gameBoard->adjacencyList[current].begin(); iter != gameBoard->adjacencyList[current].end(); iter++) {

            if (visited.find((*iter).first) == visited.end()) {
                // add on to visited
                visited.insert((*iter).first);
                //update distance and define predecessor
                distance[(*iter).first] = distance[current] + 1;
                predecessor[(*iter).first] = current;
                // add on to queue
                queue.push_back((*iter).first);

                // if element found return true
                if ((*iter).first == destination)
                    return true;
            }
        }
    }

    return false;
}

void Game::ShortestDistance(int sourceSquare, int destinationSquare, int numVertices) {

    // define to maps to keep track of path
    map <int, int> predecessor;
    map <int, int> distance;

    // perform bfs to check if elements are connected and if they are not print message
    if (!BFS(sourceSquare, destinationSquare, numVertices, predecessor, distance)) {
        cout << "vertices are disconnected";
    }
        // if vertices are connected show path
    else {


        int current = destinationSquare;
        blues.push_back(current);

        //until we reach the source node
        while (predecessor[current] != -1) {
            blues.push_back(predecessor[current]);
            current = predecessor[current];
        }


        //print path info
        cout << "The shortest path length is : " << distance[destinationSquare] << endl;

        // printing path from source to destination
        cout << "Vertices covered in path";
        for (int i = blues.size() - 1; i >= 0; i--)
            cout << blues[i] << " ";

        // change squares that are part of the path
        for (int i = 0; i < blues.size(); i++) {
            gameBoard->squares[blues[i]].blue = true;
        }
        //define start to know how long to show path for
        start = high_resolution_clock::now();
    }

}



void Game::textHandler() {
    //handles text
    font.loadFromFile("SFCompact.ttf");
    text.setFont(font);
    text.setString(gameIntro);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    //sets position
    text.setPosition(gameBoard->squares[(6*gameBoard->getNumColumns())-1].SquarePosition().getPosition().x + 35,
                     gameBoard->squares[(6*gameBoard->getNumColumns())-1].SquarePosition().getPosition().y);
    //for the clock
    time.setFont(font);
    time.setString(to_string(currtime));
    time.setCharacterSize(40);
    time.setFillColor(sf::Color::Red);
    //sets position
    time.setPosition(gameBoard->squares[(2*gameBoard->getNumColumns())-1].SquarePosition().getPosition().x + 30,
                     gameBoard->squares[(2*gameBoard->getNumColumns())-1].SquarePosition().getPosition().y);
    //handles text
    hint.setFont(font);
    hint.setString(hintText);
    hint.setCharacterSize(25);
    hint.setFillColor(sf::Color::Blue);
    //sets position
    hint.setPosition(gameBoard->squares[(18*gameBoard->getNumColumns())-1].SquarePosition().getPosition().x + 35,
                     gameBoard->squares[(18*gameBoard->getNumColumns())-1].SquarePosition().getPosition().y);

    //handles text
    startButton.setFont(font);
    startButton.setString("START");
    startButton.setCharacterSize(35);
    startButton.setFillColor(sf::Color::White);
    //sets position
    startButton.setPosition(gameBoard->squares[(27*gameBoard->getNumColumns())-1].SquarePosition().getPosition().x + 50,
                     gameBoard->squares[(27*gameBoard->getNumColumns())-1].SquarePosition().getPosition().y);

    restartButton.setFont(font);
    restartButton.setString("RESTART");
    restartButton.setCharacterSize(35);
    restartButton.setFillColor(sf::Color::White);
    //sets position
    restartButton.setPosition(gameBoard->squares[(27*gameBoard->getNumColumns())-1].SquarePosition().getPosition().x + 225,
                            gameBoard->squares[(27*gameBoard->getNumColumns())-1].SquarePosition().getPosition().y);

    backToMenuButton.setFont(font);
    backToMenuButton.setString("BACK TO\n  MENU");
    backToMenuButton.setCharacterSize(35);
    backToMenuButton.setFillColor(sf::Color::White);
    //sets position
    backToMenuButton.setPosition(gameBoard->squares[(30*gameBoard->getNumColumns())-1].SquarePosition().getPosition().x + 130,
                              gameBoard->squares[(30*gameBoard->getNumColumns())-1].SquarePosition().getPosition().y);
}

void Game::trackKeyBoard(sf::Event &event, sf::RenderWindow &window){

    if (startGame) {
        // track player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movePlayer(window, "left");
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movePlayer(window, "right");
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            movePlayer(window, "up");
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            movePlayer(window, "down");
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && !showingPath) {
            this_thread::sleep_for(chrono::milliseconds(100));
            ShowHint(window);
        }
    }
}



void Game::trackMouseClicks(sf::Event &event, sf::RenderWindow &window, string &MODE) {


    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Iterate through all tiles and check what tile, if any the mouse is over.

        auto HomeScreenOption = backToMenuButton.getGlobalBounds();
        if ((HomeScreenOption.contains(mousePos.x, mousePos.y))) {
            backToMenuButton.setFillColor(sf::Color::Green);
            MODE = "Home Screen";
            reset();
        }

        auto startOption = startButton.getGlobalBounds();
        if ((startOption.contains(mousePos.x, mousePos.y)) && !startGame) {
            startButton.setFillColor(sf::Color::Green);
            secondsLeft = 60;
            startTime = Clock::now();
            startGame = true;
            startText = steady_clock::now();
        }

        auto restartOption = restartButton.getGlobalBounds();
        //If the mouse is over the tile in question and the game is still going
        if ((restartOption.contains(mousePos.x, mousePos.y))) {
            restartButton.setFillColor(sf::Color::Green);
            startText = steady_clock::now();
            reset();
        }



    }
}


void Game::assignStartAndEnd(){
    //randomly picks start and end locations which are originally white squares
    bool isWhite = false;
    int squareNo = 0;
    while (!isWhite) {
        if (gameBoard->squares[squareNo].white)
            isWhite = true;
        else
            squareNo++;
    }
    startSquare = squareNo;
    playerSquare = startSquare;

    squareNo = gameBoard->squares.size() - 1;
    isWhite = false;
    while (!isWhite) {
        if (gameBoard->squares[squareNo].white)
            isWhite = true;
        else
            squareNo--;
    }
    destSquare = squareNo;
}


void Game::reset() {
    gameBoard->reset();
    assignStartAndEnd();
    startGame = false;
    currtime = 0;
    remainingHints = 3;
    secondsLeft = 60;
}
