#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Tiles.h"
#include "Buttons.h"
#include "Counter.h"

class Board {
private:
    std::string columns;
    std::string rows;
    std::string numberOfMines;
    int numberOfMinesInt = 0;
    int unFlaggedMines;
    int unPressedTiles;
    int totalTiles;
    std::vector<Tiles> gameTiles;
    std::vector<Buttons> boardTiles;
    std::vector<Counter> counterTiles;
    bool gameStatus = true;
    bool debugActive = false;
public:
    Board();
    Board(int testBoardNumber);

    void readTestBoards(int testBoardNumber);
    void initializeMines();
    void determineEdges();
    int getBoardColumns();
    int getBoardRows();
    int getPixelColumns();
    int getPixelRows();
    int getBoardTiles();
    int getCurrentPosition(int rowPosition, int columnPosition);
    void drawCurrentBoard(sf::RenderWindow &window);
    void drawButtons(sf::RenderWindow &window);
    void drawCounter(sf::RenderWindow &window);
    void changeCounter(int value);
    void revealAllMines(sf::RenderWindow &window);
    void revealAllTiles(sf::RenderWindow &window);
    void pressThisTile(sf::RenderWindow &window, float xCord, float yCord);
    int pressThisButton(sf::RenderWindow &window, float xCord, float yCord);
    void pressNearbyTiles(sf::RenderWindow &window, int index, bool origin);
    void flagThisTile(sf::RenderWindow &window, float xCord, float yCord);
    int checkThisTile(float xCord, float yCord);
    int checkThisBoardButton(float xCord, float yCord);
    void checkUnPressedTiles();
    void setGameStatus(bool value);
    bool getGameStatus();
    void determineNearbyMines();
};