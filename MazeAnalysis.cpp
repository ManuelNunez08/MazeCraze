#include "MazeAnalysis.h"
using namespace std;
using namespace std::chrono;

typedef high_resolution_clock Clock;

MazeAnalysis::MazeAnalysis() {
    string mode = "Maze Analysis";
    analysisMaze = new maze(251, 149, mode, 5);

    AnalysisIntro = "BFS\nV.S\nDFS";

    choice = 1;
    index = 0;
    speedChoice = 2;

    gameJustStarted = true;

    textHandler();
}

void MazeAnalysis::DrawBoard(sf::RenderWindow& window) {
    if ( gameJustStarted){
        this_thread::sleep_for(milliseconds(100));
        gameJustStarted = false;
    }

    analysisMaze->DrawMaze(window);

    window.draw(text);
    if (choice == 1) {
        BFSButton.setFillColor(sf::Color::Green);
        DFSButton.setFillColor(sf::Color::Blue);
    }
    else {
        BFSButton.setFillColor(sf::Color::Blue);
        DFSButton.setFillColor(sf::Color::Green);
    }
    if (speedChoice == 1) {
        slow.setFillColor(sf::Color::Green);
        normal.setFillColor(sf::Color::Blue);
        fast.setFillColor(sf::Color::Blue);
    }
    else if (speedChoice == 2) {
        slow.setFillColor(sf::Color::Blue);
        normal.setFillColor(sf::Color::Green);
        fast.setFillColor(sf::Color::Blue);
    }
    else if (speedChoice == 3) {
        slow.setFillColor(sf::Color::Blue);
        normal.setFillColor(sf::Color::Blue);
        fast.setFillColor(sf::Color::Green);
    }
    window.draw(selectSpeed);
    window.draw(slow);
    window.draw(normal);
    window.draw(fast);
    window.draw(DFSButton);
    window.draw(BFSButton);
    window.draw(visited);
    window.draw(startButton);
    window.draw(restartButton);
    window.draw(backToMenuButton);
    window.draw(Select);

    numVisited.setString(to_string(index));
    window.draw(numVisited);

    if (pathFromTo.size() == 2 && startGame && blues.size() <= 2) {
        ShortestDistance(pathFromTo[0], pathFromTo[1], analysisMaze->getNumVertices(), choice, window);
    }

    milliseconds time;
    if (speedChoice == 1) {
        time = milliseconds(1000);
    } else if (speedChoice == 2) {
        time = milliseconds(300);
    }
    else if (speedChoice == 3) {
        time = milliseconds(10);
    }

    // When the BFS / DFS path is done being showed, show the shortest path and clear the red squares
    if (index == pathSquares.size() && index != 0) {
        for (int i = 0; i < blues.size(); i++) {
            analysisMaze->squares[blues[i]].blue = true;
        }

        for (int i = 0; i < pathSquares.size(); i++) {
            analysisMaze->squares[pathSquares[i]].red = false;
        }
        pathSquares.clear();
    }

    if (!pathSquares.empty() && (steady_clock::now() - start) > time) {
        analysisMaze->squares[pathSquares[index]].red = true;
        index++;
        start = steady_clock::now();
    }
    // When the restart button is pressed reset the path
    if (!startGame) {
        for (int i = 0; i < pathSquares.size(); i++) {
            analysisMaze->squares[pathSquares[i]].red = false;
        }
        index = 0;
        pathSquares.clear();
    }

    // Reset blue squares
    if (!startGame && blues.size() > 2) {

        if (!blues.empty()) {
            //revert path to normal
            for (int i = 0; i < blues.size(); i++) {
                analysisMaze->squares[blues[i]].blue = false;
            }
            for (int i = 0; i < pathFromTo.size(); i++) {
                analysisMaze->squares[pathFromTo[i]].blue = false;
            }
            // clear blues
            blues.clear();

            // clear starting and ending squares of the path from vector
            pathFromTo.clear();
        }

    }
}

void MazeAnalysis::textHandler() {
    //handles text
    font.loadFromFile("SFCompact.ttf");


    text.setFont(font);
    text.setString(AnalysisIntro);
    text.setCharacterSize(80);
    text.setFillColor(sf::Color::Red);
    //sets position
    text.setPosition(analysisMaze->squares[(6 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                     analysisMaze->squares[(3 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    Select.setFont(font);
    Select.setString("Select Algorithm");
    Select.setCharacterSize(18);
    Select.setFillColor(sf::Color::Blue);
    Select.setStyle(sf::Text::Underlined);
    //sets position
    Select.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                       analysisMaze->squares[(60 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    BFSButton.setFont(font);
    BFSButton.setString("BFS");
    BFSButton.setCharacterSize(25);
    BFSButton.setFillColor(sf::Color::Blue);
    //sets position
    BFSButton.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                          analysisMaze->squares[(65 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    DFSButton.setFont(font);
    DFSButton.setString("DFS");
    DFSButton.setCharacterSize(25);
    DFSButton.setFillColor(sf::Color::Blue);
    //sets position
    DFSButton.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 80,
                          analysisMaze->squares[(65 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    visited.setFont(font);
    visited.setString("Nodes Visited: ");
    visited.setCharacterSize(15);
    visited.setFillColor(sf::Color::Cyan);
    //sets position
    visited.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                        analysisMaze->squares[(95 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    numVisited.setFont(font);
    numVisited.setString("0");
    numVisited.setCharacterSize(15);
    numVisited.setFillColor(sf::Color::Cyan);
    //sets position
    numVisited.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 130,
                           analysisMaze->squares[(95 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    selectSpeed.setFont(font);
    selectSpeed.setString("Select Speed");
    selectSpeed.setCharacterSize(15);
    selectSpeed.setFillColor(sf::Color::Blue);
    //sets position
    selectSpeed.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                            analysisMaze->squares[(75 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    slow.setFont(font);
    slow.setString("Slow");
    slow.setCharacterSize(15);
    slow.setFillColor(sf::Color::Blue);
    //sets position
    slow.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                     analysisMaze->squares[(80 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    normal.setFont(font);
    normal.setString("Normal");
    normal.setCharacterSize(15);
    normal.setFillColor(sf::Color::Blue);
    //sets position
    normal.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 65,
                       analysisMaze->squares[(80 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    fast.setFont(font);
    fast.setString("Fast");
    fast.setCharacterSize(15);
    fast.setFillColor(sf::Color::Blue);
    //sets position
    fast.setPosition(analysisMaze->squares[(18 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 130,
                     analysisMaze->squares[(80 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    //handles text
    startButton.setFont(font);
    startButton.setString("START");
    startButton.setCharacterSize(35);
    startButton.setFillColor(sf::Color::White);
    //sets position
    startButton.setPosition(analysisMaze->squares[(25 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                            analysisMaze->squares[(110 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    restartButton.setFont(font);
    restartButton.setString("RESTART");
    restartButton.setCharacterSize(35);
    restartButton.setFillColor(sf::Color::White);
    //sets position
    restartButton.setPosition(analysisMaze->squares[(25 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                              analysisMaze->squares[(120 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);

    backToMenuButton.setFont(font);
    backToMenuButton.setString("BACK TO\n  MENU");
    backToMenuButton.setCharacterSize(35);
    backToMenuButton.setFillColor(sf::Color::Green);
    //sets position
    backToMenuButton.setPosition(analysisMaze->squares[(30 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().x + 15,
                                 analysisMaze->squares[(130 * analysisMaze->getNumColumns()) - 1].SquarePosition().getPosition().y);
}

bool MazeAnalysis::BFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance, sf::RenderWindow& window) {

    // Starting a clock to time how long BFS will take
    auto t1 = Clock::now();

    // declare queue
    list<int> queue;

    // use a set to keep track of visited nodes
    unordered_set <int> visited;


    // initialize all distances to max and all predecessors to -1
    for (auto iter = analysisMaze->adjacencyList.begin(); iter != analysisMaze->adjacencyList.end(); iter++) {
        predecessor[(*iter).first] = -1;
        distance[(*iter).first] = INT_MAX;
    }

    // add source to visited, define its distance, and add it to the queue.
    visited.insert(source);
    distance[source] = 0;
    queue.push_back(source);
    pathSquares.push_back(source);



    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        for (auto iter = analysisMaze->adjacencyList[current].begin(); iter != analysisMaze->adjacencyList[current].end(); iter++) {

            if (visited.find((*iter).first) == visited.end()) {
                // add on to visited
                visited.insert((*iter).first);
                //update distance and define predecessor
                distance[(*iter).first] = distance[current] + 1;
                predecessor[(*iter).first] = current;
                // add on to queue
                queue.push_back((*iter).first);
                pathSquares.push_back((*iter).first);


                // if element found return true
                if ((*iter).first == destination) {
                    auto t2 = Clock::now();
                    cout << "Time BFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

                    cout << "Vertices visited: " << pathSquares.size() << endl;

                    return true;
                }
            }
        }
    }
    auto t2 = Clock::now();
    cout << "Time BFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

    cout << "Vertices visited: " << pathSquares.size() << endl;

    return false;
}

bool MazeAnalysis::DFS(int source, int destination, int numVertices, map <int, int >& predecessor, map <int, int>& distance, sf::RenderWindow& window) {

    // Starting a clock to time how long BFS will take
    auto t1 = Clock::now();

    // declare stack
    stack<int> stack;

    // use a set to keep track of visited nodes for BFS
    unordered_set <int> visited;

    // initialize all distances to max and all predecessors to -1
    for (auto iter = analysisMaze->adjacencyList.begin(); iter != analysisMaze->adjacencyList.end(); iter++) {
        predecessor[(*iter).first] = -1;
        distance[(*iter).first] = INT_MAX;
    }

    // add source to visited, define its distance, and add it to the stack.
    visited.insert(source);
    distance[source] = 0;
    stack.push(source);



    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        pathSquares.push_back(current);

        for (auto iter = analysisMaze->adjacencyList[current].begin(); iter != analysisMaze->adjacencyList[current].end(); iter++) {

            if (visited.find((*iter).first) == visited.end()) {
                // add on to visited
                visited.insert((*iter).first);
                //update distance and define predecessor
                distance[(*iter).first] = distance[current] + 1;
                predecessor[(*iter).first] = current;
                // add on to stack
                stack.push((*iter).first);


                // if element found return true
                if ((*iter).first == destination) {
                    auto t2 = Clock::now();
                    cout << "Time DFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

                    cout << "Vertices visited: " << pathSquares.size() << endl;

                    return true;
                }
            }
        }
    }
    auto t2 = Clock::now();
    cout << "Time DFS took: " << duration_cast<nanoseconds>(t2 - t1).count() << endl;

    cout << "Vertices visited: " << pathSquares.size() << endl;

    return false;
}



void MazeAnalysis::ShortestDistance(int sourceSquare, int destinationSquare, int numVertices, int choice, sf::RenderWindow& window) {

    // define to maps to keep track of path
    map <int, int> predecessor;
    map <int, int> distance;

    if (sourceSquare == destinationSquare) {
        cout << "Same square chosen!" << endl << endl;
        blues.push_back(sourceSquare);
        // change squares that are part of the path
        for (int i = 0; i < blues.size(); i++) {
            analysisMaze->squares[blues[i]].blue = true;
        }
    }
    else {
        bool worked = true;
        // perform bfs/dfs to check if elements are connected and if they are not print message
        if (choice == 1) {
            worked = BFS(sourceSquare, destinationSquare, numVertices, predecessor, distance, window);
        }
        if (choice == 2) {
            worked = DFS(sourceSquare, destinationSquare, numVertices, predecessor, distance, window);
        }
        if (!worked) {
            cout << "Vertices are disconnected" << endl << endl;
            for (int i = 0; i < blues.size(); i++) {
                analysisMaze->squares[blues[i]].blue = true;
            }
        }
            // if vertices are connected show path
        else {


            int current = destinationSquare;

            //until we reach the source node
            while (predecessor[current] != -1) {
                blues.push_back(predecessor[current]);
                current = predecessor[current];
            }


            //print path info
            cout << "The shortest path length is : " << distance[destinationSquare] << endl;

            // printing path from source to destination
            cout << "Vertices covered in path : ";
            for (int i = blues.size() - 1; i >= 0; i--)
                cout << blues[i] << " ";
            cout << endl << endl;
            // change squares that are part of the path
            /*for (int i = 0; i < blues.size(); i++) {
                analysisMaze->squares[blues[i]].blue = true;
            }*/
        }
    }
    //define start to know how long to show path for
    start = high_resolution_clock::now();

}

void MazeAnalysis::DrawPath(sf::RenderWindow& window, vector<int> squares, int source, int destination) {
    sf::Sprite S;
    sf::Sprite D;
    int numColumns = analysisMaze->getNumColumns();
    int xS = (source % numColumns) * 5;
    int yS = (source / numColumns) * 5;
    int xD = (destination % numColumns) * 5;
    int yD = (destination / numColumns) * 5;
    S.setTexture(TextureManager::GetTexture("blue_square"));
    D.setTexture(TextureManager::GetTexture("blue_square"));
    S.setPosition(xS, yS);
    D.setPosition(xD, yD);
    sf::Sprite redSquare;
    redSquare.setTexture(TextureManager::GetTexture("red_square"));
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < i; j++) {
            int square = squares[j];
            int x = (square % numColumns) * 5;
            int y = (square / numColumns) * 5;
            redSquare.setPosition(x, y);
            window.draw(redSquare);
        }
        window.draw(S);
        window.draw(D);
        this_thread::sleep_for(chrono::milliseconds(100));
        window.display();
    }
}

void MazeAnalysis::trackMouseClicks(sf::Event& event, sf::RenderWindow& window, string& MODE) {


    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Iterate through all tiles and check what tile, if any the mouse is over.

        auto HomeScreenOption = backToMenuButton.getGlobalBounds();
        if ((HomeScreenOption.contains(mousePos.x, mousePos.y))) {
            MODE = "Home Screen";
            startGame = false;
            reset();
        }

        auto startOption = startButton.getGlobalBounds();
        if ((startOption.contains(mousePos.x, mousePos.y)) && !startGame) {
            startGame = true;
        }

        auto restartOption = restartButton.getGlobalBounds();
        //If the mouse is over the tile in question and the game is still going
        if ((restartOption.contains(mousePos.x, mousePos.y))) {
            startGame = false;
        }

        auto BFSOption = BFSButton.getGlobalBounds();
        if ((BFSOption.contains(mousePos.x, mousePos.y))) {
            choice = 1;
        }

        auto DFSOption = DFSButton.getGlobalBounds();
        if ((DFSOption.contains(mousePos.x, mousePos.y))) {
            choice = 2;
        }

        auto SlowOption = slow.getGlobalBounds();
        if ((SlowOption.contains(mousePos.x, mousePos.y))) {
            speedChoice = 1;
        }

        auto normalOption = normal.getGlobalBounds();
        if ((normalOption.contains(mousePos.x, mousePos.y))) {
            speedChoice = 2;
        }

        auto fastOption = fast.getGlobalBounds();
        if ((fastOption.contains(mousePos.x, mousePos.y))) {
            speedChoice = 3;
        }



        // Iterate through all tiles and check what tile, if any the mouse is over.
        for (int i = 0; i < analysisMaze->squares.size(); i++) {
            auto currentSquare = analysisMaze->squares[i].SquarePosition().getGlobalBounds();
            //If the mouse is over the tile in question and the game is still going
            if ((currentSquare.contains(mousePos.x, mousePos.y)) && analysisMaze->squares[i].white && blues.size() < 2) {
                analysisMaze->squares[i].blue = true;
                pathFromTo.push_back(analysisMaze->squares[i].numSquare);
                blues.push_back(analysisMaze->squares[i].numSquare);
            }
        }

    }
    if (event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // Iterate through all tiles and check what tile, if any the mouse is over.
        for (int i = 0; i < analysisMaze->squares.size(); i++) {
            auto currentSquare = analysisMaze->squares[i].SquarePosition().getGlobalBounds();
            //If the mouse is over the tile in question and the game is still going
            if ((currentSquare.contains(mousePos.x, mousePos.y)) && blues.size() < 2) {
                if (analysisMaze->squares[i].white) {
                    analysisMaze->squares[i].black = true;
                    analysisMaze->squares[i].white = false;
                    CorrectGraph(analysisMaze->squares[i].numSquare);
                }
            }
        }
    }



    // picking the shortest path i between two squares
    if (event.mouseButton.button == sf::Mouse::Left) {
    }
}
void MazeAnalysis::CorrectGraph(int index) {
    set <int> indexesToCorrect;

    // identify all indices surrounding the square being made black
    for (auto iter = analysisMaze->adjacencyList[index].begin(); iter != analysisMaze->adjacencyList[index].end(); iter++) {
        indexesToCorrect.insert((*iter).first);
    }

    // for all said indices, delete their connection to the deleted square.
    for (auto iter = indexesToCorrect.begin(); iter != indexesToCorrect.end(); iter++) {
        analysisMaze->adjacencyList[(*iter)].erase(index);
    }

    // delete black square from adjacent list
    analysisMaze->adjacencyList.erase(index);
}

void MazeAnalysis::reset() {
    analysisMaze->reset();
    index = 0;
    choice = 1;
    speedChoice = 2;
}