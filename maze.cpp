
#include "maze.h"


maze::maze(int numColumns, int numRows, string MODE, int numPixels) {

    // Mode defined for future squares to be created.
    this->MODE = MODE;
    // Size of board and initial number of whites initialized initialized.
    this->numColumns = numColumns;
    this->numRows = numRows;
    this->numWhite = 0;

    // the height and length of pixels is taken note of for quare creation
    this->numPixels = numPixels;

    InitializeMaze();
}

void maze::InitializeMaze() {

    // variables to dictate the type of squares
    numWhite = 0;
    string color = "white";
    int numSquare = 0;
    int rand;

    // A for loop adds squares onto the board and initially creates a maze with all edges present.
    for (int i = 0; i < numRows; i ++ ) {
        //Each iteration of the loop below completes a row
        for (int j = 0; j < numColumns; j++) {
            rand = Random::Int(0, 6);
            // alternate colors
            if ( j%2 == 0 && i%2 == 0){
                color = "white";
                numWhite++;
            }
            else {
                color = "black";
            }

            // create new square and adds to square vector
            square newSquare(color, numSquare, MODE);
            newSquare.SetSquarePosition((j*numPixels), (i*numPixels));

            //assign random building sprites to black squares (borders)
            if (rand == 0){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building1"));
            }
            else if (rand == 1){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building2"));
            }
            else if ( rand == 2 ){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building3"));
            }
            else if (rand == 3){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building4"));
            }
            else if (rand == 4){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building5"));
            }
            else if ( rand == 5){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building6"));
            }
            else if ( rand == 6){
                newSquare.bigBlackSquare.setTexture(TextureManager::GetTexture("building7"));
            }

            squares.push_back(newSquare);
            numSquare++;
        }
    }


    // all squares are given access to the two squares above, below , left and right of them
    ConnectSquares();

    //Now, with connected squares we can use Prim's algorithm to make a maze out of our current bard layout.
    MakeMaze();
    // with the maze made, we now connect al white squares and make them a graph
    ConnectGraph();

}



void maze::DrawMaze(sf::RenderWindow &window) {

    // each square is drawn using the draw function in square
    for ( int i  = 0; i < squares.size(); i ++){
        squares[i].Draw(window);
    }

}




void maze::ConnectSquares() {
    /* A for loop iterated through each square and connects each square to its corresponding adjacent squares.
     adjacent squares will be added in pairs where the first will represent the neighboring square
     and the second will represent the next one over*/
    for (int i = 0; i < squares.size(); i++){

        // If first square
        if (i == 0) {
            squares[i].adjacentSquares.emplace_back(&squares[i + 1], &squares[i + 2] );
            squares[i].adjacentSquares.emplace_back(&squares[i + (numColumns)], &squares[i + (2*numColumns)]);
        }
        // If last square
        else if (i == ((numColumns * numRows) - 1)) {
            squares[i].adjacentSquares.emplace_back(&squares[i - 1], &squares[i - 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i - (numColumns)], &squares[i - (2*numColumns)]);
        }
            // If upper right square
        else if ((i < numColumns) && (i % numColumns == numColumns - 1)) {
            squares[i].adjacentSquares.emplace_back(&squares[i - 1], &squares[i - 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i + (numColumns)], &squares[i + (2*numColumns)]);
        }
            // If lower left square
        else if ((i > ((numColumns * numRows) - numColumns - 1)) && (i % numColumns == 0)) {
            squares[i].adjacentSquares.emplace_back(&squares[i + 1], &squares[i + 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i - (numColumns)], &squares[i - (2*numColumns)]);
        }
            // If First row
        else if (i < numColumns) {
            squares[i].adjacentSquares.emplace_back(&squares[i - 1], &squares[i - 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i + 1], &squares[i + 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i + (numColumns)], &squares[i + (2*numColumns)]);
        }
            //If Last row
        else if (i > ((numColumns * numRows) - numColumns - 1)) {
            squares[i].adjacentSquares.emplace_back(&squares[i + 1], &squares[i + 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i - 1], &squares[i - 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i - (numColumns)], &squares[i - (2*numColumns)]);
        }
            //If left column
        else if (i % numColumns == 0) {
            squares[i].adjacentSquares.emplace_back(&squares[i + 1], &squares[i + 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i - (numColumns)], &squares[i - (2*numColumns)]);
            squares[i].adjacentSquares.emplace_back(&squares[i + (numColumns)], &squares[i + (2*numColumns)]);
        }
            //If right column
        else if (i % numColumns == numColumns - 1) {
            squares[i].adjacentSquares.emplace_back(&squares[i - 1], &squares[i - 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i + (numColumns)], &squares[i + (2*numColumns)]);
            squares[i].adjacentSquares.emplace_back(&squares[i - (numColumns)], &squares[i - (2*numColumns)]);
        }
            // If tile with 4 adjacent squares
        else {
            squares[i].adjacentSquares.emplace_back(&squares[i - (numColumns)], &squares[i - (2*numColumns)]);
            squares[i].adjacentSquares.emplace_back(&squares[i - 1], &squares[i - 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i + 1], &squares[i + 2]);
            squares[i].adjacentSquares.emplace_back(&squares[i + (numColumns)], &squares[i + (2*numColumns)]);
        }
    }
}

void maze::MakeMaze() {


    /* Employ prims Algorithm:
     1. randomly choose a white space in the graph and add it to set V (processed white spaces)
     until all white spaces have been processed
          2. randomly choose one of the white spaces that's adjacent to any of the processed squares
          3. add that white space to the processed whites and clear the border between it and the square
          that accessed it the vertex selected to the set V

    ...Ultimately we have a growing "island" of processed white squares and we have  multitude of "frontier
    squares" to consider randomly when expanding the island of white squares

    */



    //declare a set to hold squares indices that could potentially be added to the maze path
    set<int> frontierSquares;
    // declare a set that holds white squares that are already part of the path
    set<int> pathSquares;


    // randomly choose a white space
    bool whiteFound = false;
    int j;
    while (!whiteFound){
        j = Random::Int(0, squares.size()-1);

        if (squares[j].white){
            whiteFound = true;
        }
    }


    // mark the white square selected
    mark(j, frontierSquares, pathSquares);

    while (!frontierSquares.empty()){

        // randomly choose an available frontier square
        int frontierSquare = randomElement(frontierSquares);

        // a vector of all squares in the path adjacent to the randomly chosen frontier square is chosen
        vector <int> tempVector = pathNeighbors(frontierSquare, pathSquares);

        // if a vector with elements is returned
        if ( !tempVector.empty()) {

            // randomly choose an element in the vector and connect the square it refers to with the frontier square.
            int rand = Random::Int(0, tempVector.size() - 1);
            connect(tempVector[rand], frontierSquare);

            // mark the current frontier square and remove it from the frontier squares set
            mark(frontierSquare, frontierSquares, pathSquares);
            frontierSquares.erase(frontierSquare);
        }

    }

    cout << numWhite << endl << endl;
}


// a given square is made part of the maze and its adjacent squares not in the maze path are made frontier squares.
void maze::mark(int squareIndex, set <int>& frontierCells, set <int>& mazePath) {
    mazePath.insert(squareIndex);
    for ( int i  = 0; i < squares[squareIndex].adjacentSquares.size(); i++){

        if (mazePath.find(squares[squareIndex].adjacentSquares[i].second->numSquare) == mazePath.end()){
            frontierCells.insert(squares[squareIndex].adjacentSquares[i].second->numSquare);
        }

    }
}


/* a vector is returned storing the indices of all squares adjacent to the frontier square which are
   already part of the maze path */
vector<int> maze::pathNeighbors(int frontierSquare, set <int>& mazePath) {
    vector <int> pathSquares;
    for (int i = 0; i < squares[frontierSquare].adjacentSquares.size(); i++){
        if (mazePath.find(squares[frontierSquare].adjacentSquares[i].second->numSquare) != mazePath.end()){
            pathSquares.push_back(squares[frontierSquare].adjacentSquares[i].second->numSquare);
        }
    }
    return pathSquares;
}


// a random element from a given set is chosen
int maze::randomElement(set<int>& squaresSet) {
    int j = Random::Int(0, squaresSet.size()-1);
    int counter = 0;
    for ( auto iter = squaresSet.begin(); iter != squaresSet.end(); iter++){
        if ( counter == j){
            return (*iter);
        }
        counter++;
    }
    return 0;
}


// a helper function to build the graph that connects two squares provided through the maze's adjaceny list.
void maze::connect(int sourceIndex, int destIndex) {

    for ( int i = 0; i < squares[sourceIndex].adjacentSquares.size(); i++){
        if (squares[sourceIndex].adjacentSquares[i].second->numSquare == destIndex){
            squares[sourceIndex].adjacentSquares[i].first->white = true;
            squares[sourceIndex].adjacentSquares[i].first->black = false;
            numWhite++;
            break;
        }
    }
}


// make a graph out of the newly made maze
void maze::ConnectGraph() {

    // after already creating the maze, connect all white squares with an adjacency list.
    for ( int i = 0; i < squares.size(); i++){
        if ( squares[i].white){
            map < int, int> adjacentWhites;
            for ( int j = 0; j < squares[i].adjacentSquares.size(); j++){
                if (squares[i].adjacentSquares[j].first->white){
                    adjacentWhites[squares[i].adjacentSquares[j].first->numSquare] = 1;
                }
            }
            adjacencyList[squares[i].numSquare] = adjacentWhites;
        }

    }

}

// getter for number of columns
int maze::getNumColumns() {
    return numColumns;
}
// getter for number of rows
int maze::getNumRows() {
    return numRows;
}
//getter for number of white squares (aka white squares in the maze)
int maze::getNumVertices() {
    return numWhite;
}

// a reset function for the maze that reinitialize the maze after resetting class variables.
void maze::reset() {
    squares.clear();
    adjacencyList.clear();
    InitializeMaze();
}
