#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <list>
#include "square.h"
#include "Random.h"
#include <SFML/Graphics.hpp>

#ifndef PROJECT_3_FINAL_MAZE_H
#define PROJECT_3_FINAL_MAZE_H


class maze {
    int numColumns;
    int numRows;
    int numWhite;
    string MODE;
    int numPixels;

    // Main functions
    void InitializeMaze();
    void ConnectSquares();
    void MakeMaze();
    void ConnectGraph();

    // helper functions
    void mark( int SquareIndex, set <int>& frontierCells, set <int>& mazePath);
    vector<int> pathNeighbors(int frontierSquare, set <int>& mazePath);
    int randomElement(set <int>& squaresSet);
    void connect(int sourceIndex, int destIndex);

public:
    //constructor (sets size of board)
    maze(int numColumns, int numRows, string MODE, int numPixels);

    //Vector of squares contained within the board
    vector <square> squares;
    // adjacency list of white squares that form part of the graph.
    map < int, map<int, int> > adjacencyList;

    // public functions
    void DrawMaze( sf::RenderWindow& window);
    void reset();
    //getter functions
    int getNumColumns();
    int getNumRows();
    int getNumVertices();
};


#endif //PROJECT_3_FINAL_MAZE_H
