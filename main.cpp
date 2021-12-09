#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "HomeScreen.h"
#include "MazeAnalysis.h"
#include "Game.h"


int main() {

    // initialize a window objected (Hardcoded length and width)
    sf::RenderWindow window(sf::VideoMode((143 * 10), (75 * 10)), "Prims's Maze");

    // set the default mode to "Home SCreen"
    string MODE = "Home Screen";


    // initialize a HomeScreen screen
    HomeScreen homeScreen(143, 75);
    // initialize a  game screen
    Game gameScreen (143, 75);
    // initializing a maze analysis screen
    MazeAnalysis analysisScreen;




    // This while loop controls the state of the window.
    while (window.isOpen())
    {
        sf::Event event;

        //while something is happenieng
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // If a mouse is clicked determine what mode the game is in and what actions to track accordingly.
            if (event.type == sf::Event::MouseButtonPressed){
                if (MODE == "Home Screen"){
                    homeScreen.trackMouseClicks(event, window, MODE);
                }
                else if (MODE == "Maze Analysis") {
                    analysisScreen.trackMouseClicks(event, window, MODE);
                }
                else if (MODE == "Maze Game") {
                    gameScreen.trackMouseClicks(event, window, MODE);
                }

            }

            // if a key is pressed and the current mode is maze game act accordingly
            if (event.type == sf::Event::KeyPressed){
                if (MODE == "Maze Game") {
                    gameScreen.trackKeyBoard(event, window);
                }
            }


        }
        window.clear();

        // draw the corresponding mode
        if (MODE == "Home Screen"){
            // draw home screen
            homeScreen.drawScreen(window);
        }
        else if (MODE == "Maze Analysis"){
            // draw maze analysis game
            analysisScreen.DrawBoard(window);
        }
        else if (MODE == "Maze Game"){
            gameScreen.DrawGame(window);
        }


        window.display();
    }



    return 0;
}
