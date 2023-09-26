#include "Board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Buttons.h"
#include "Random.h"

Board::Board() {
    std::ifstream boardTest;
    boardTest.open("boards/config.cfg");
    getline(boardTest, columns);
    getline(boardTest, rows);
    getline(boardTest, numberOfMines);
    boardTest.close();
    totalTiles = (std::stoi(columns) * std::stoi(rows));
    gameTiles.resize(totalTiles);
    unFlaggedMines = std::stoi(numberOfMines);
    unPressedTiles = (totalTiles - (std::stoi(numberOfMines)));

    for (int i = 0; i < getBoardRows(); i++) {
        for (int j = 0; j < getBoardColumns(); j++) {
            int currentPosition = getCurrentPosition(i,j);
            gameTiles[currentPosition].setXCoordinate(j);
            gameTiles[currentPosition].setYCoordinate(i);
        }
    }

    for (int i = 0; i < 5; i++) {
        Buttons tempButton(i);
        boardTiles.push_back(tempButton);
        float xPixelCordTemp = ((getBoardColumns() * 32) / 2);
        float yPixelCordTemp = (getBoardRows() * 32);
        boardTiles[i].setXPixelCoordinate(xPixelCordTemp,i);
        boardTiles[i].setYPixelCoordinate(yPixelCordTemp,i);
        boardTiles[i].movePosition(boardTiles[i].getXPixelCoordinate(),boardTiles[i].getYPixelCoordinate());
    }

    for (int i = 0; i < 3; i++) {
        Counter tempCounter;
        counterTiles.push_back(tempCounter);
        float xPixelCordTemp = 0;
        float yPixelCordTemp = (getBoardRows() * 32);
        counterTiles[i].setXPixelCoordinate(xPixelCordTemp,i);
        counterTiles[i].setYPixelCoordinate(yPixelCordTemp,i);
        counterTiles[i].movePosition(counterTiles[i].getXPixelCoordinate(),counterTiles[i].getYPixelCoordinate());
        counterTiles[i].setNumber(0);
    }

    determineEdges();
    initializeMines();
    determineNearbyMines();
    changeCounter(unFlaggedMines);
}
Board::Board(int testBoardNumber) {
    std::ifstream boardTest;
    boardTest.open("boards/config.cfg");
    getline(boardTest,columns);
    getline(boardTest,rows);
    boardTest.close();
    totalTiles = (std::stoi(columns) * std::stoi(rows));
    gameTiles.resize(totalTiles);

    for (int i = 0; i < getBoardRows(); i++) {
        for (int j = 0; j < getBoardColumns(); j++) {
            int currentPosition = getCurrentPosition(i,j);
            gameTiles[currentPosition].setXCoordinate(j);
            gameTiles[currentPosition].setYCoordinate(i);
        }
    }

    for (int i = 0; i < 5; i++) {
        Buttons tempButton(i);
        boardTiles.push_back(tempButton);
        float xPixelCordTemp = ((getBoardColumns() * 32) / 2);
        float yPixelCordTemp = (getBoardRows() * 32);
        boardTiles[i].setXPixelCoordinate(xPixelCordTemp,i);
        boardTiles[i].setYPixelCoordinate(yPixelCordTemp,i);
        boardTiles[i].movePosition(boardTiles[i].getXPixelCoordinate(), boardTiles[i].getYPixelCoordinate());
    }

    for (int i = 0; i < 3; i++) {
        Counter tempCounter;
        counterTiles.push_back(tempCounter);
        float xPixelCordTemp = 0;
        float yPixelCordTemp = (getBoardRows() * 32);
        counterTiles[i].setXPixelCoordinate(xPixelCordTemp,i);
        counterTiles[i].setYPixelCoordinate(yPixelCordTemp,i);
        counterTiles[i].movePosition(counterTiles[i].getXPixelCoordinate(),counterTiles[i].getYPixelCoordinate());
        counterTiles[i].setNumber(0);
    }

    determineEdges();
    readTestBoards(testBoardNumber);
    determineNearbyMines();
    unFlaggedMines = numberOfMinesInt;
    unPressedTiles = (totalTiles - numberOfMinesInt);
    changeCounter(unFlaggedMines);
}
void Board::readTestBoards(int testBoardNumber) {
    std::ifstream testBoard;
    if (testBoardNumber == 1) {
        testBoard.open("boards/testboard1.brd");
    }
    else if (testBoardNumber == 2) {
        testBoard.open("boards/testboard2.brd");
    }
    else if (testBoardNumber == 3) {
        testBoard.open("boards/testboard3.brd");
    }

    std::vector<std::string> testBoardStringData;
    for (int i = 0; i < getBoardRows(); i++) {
        std::string boardData;
        getline(testBoard, boardData);
        testBoardStringData.push_back(boardData);
    }
    for (int i = 0; i < getBoardRows(); i++) {
        for (int j = 0; j < getBoardColumns(); j++) {
            std::string tempString = testBoardStringData[i];
            char locator = tempString[j];
            if (locator == '1') {
                int currentPosition = getCurrentPosition(i,j);
                gameTiles[currentPosition].setMineBool(true);
                numberOfMinesInt++;
            }
        }
    }
    testBoard.close();
}
void Board::initializeMines() {
    for (int i = 0; i < (std::stoi(numberOfMines)); i++) {
        int randomTile = Random::Int(0, totalTiles);
        if (gameTiles[randomTile].getMineBool()) {
            i--;
        }
        else {
            gameTiles[randomTile].setMineBool(true);
            numberOfMinesInt++;
        }
    }
}
void Board::determineEdges() {
    for (int i = 0; i < totalTiles; i++) {
        if (i % getBoardColumns() == 0) {
            if (i != 0) {
                gameTiles[i - 1].setEdgeRight(true);
            }
            gameTiles[i].setEdgeLeft(true);
            gameTiles[totalTiles - 1].setEdgeRight(true);
        }
        if (gameTiles[i].getYCoordinate() == 0 || gameTiles[i].getYCoordinate() == (getBoardRows() - 1)) {
            if (gameTiles[i].getYCoordinate() == 0) {
                gameTiles[i].setEdgeTop(true);
            }
            else {
                gameTiles[i].setEdgeBottom(true);
            }
        }
    }
}
void Board::setGameStatus(bool value) {
    gameStatus = value;
}
bool Board::getGameStatus() {
    return gameStatus;
}
int Board::getBoardColumns() {
    int boardColumns = std::stoi(columns);
    return boardColumns;
}
int Board::getBoardRows() {
    int boardRows = std::stoi(rows);
    return boardRows;
}
int Board::getPixelColumns() {
    int pixelColumns = std::stoi(columns) * 32;
    return pixelColumns;
}
int Board::getPixelRows() {
    int pixelRows = (std::stoi(rows) * 32) + 100;
    return pixelRows;
}
int Board::getBoardTiles() {
    return totalTiles;
}
int Board::getCurrentPosition(int rowPosition, int columnPosition) {
    int currentPosition = (rowPosition * getBoardColumns()) + columnPosition;
    return currentPosition;
}
void Board::drawCurrentBoard(sf::RenderWindow &window) {
    for (int i = 0; i < totalTiles; i++) {
        float currentXCoordinate = gameTiles[i].getXPixelCoordinate();
        float currentYCoordinate = gameTiles[i].getYPixelCoordinate();

        gameTiles[i].movePosition(currentXCoordinate, currentYCoordinate);
        window.draw(gameTiles[i].getTileSprite());

        if (gameTiles[i].getTileRevealed()) {
            window.draw(gameTiles[i].getNumberSprite());
        }
        if (gameTiles[i].getMineBool()) {
            if (gameTiles[i].getMinePressedBool()) {
                revealAllMines(window);
                boardTiles[0].gameLost();
                gameStatus = false;
            }
            //window.draw(gameTiles[i].getMineSprite());
        }
        if (gameTiles[i].getFlagBool()) {
            window.draw(gameTiles[i].getTopLayerSprite());
        }
        if (debugActive) {
            if (gameTiles[i].getMineBool()) {
                gameTiles[i].revealMine(window);
            }
            window.draw(gameTiles[i].getMineSprite());
        }
    }
}
void Board::drawButtons(sf::RenderWindow &window) {
    for (int i = 0; i < 5; i++) {
        window.draw(boardTiles[i].getButtonSprite());
    }
}
void Board::drawCounter(sf::RenderWindow &window) {
    for (int i = 0; i < 3; i++) {
        window.draw(counterTiles[i].getCounterSprite());
    }
}
void Board::changeCounter(int value) {
    if (value >= 0) {
        if (value / 100 != 0) {
            int temp = (value / 100);
            int temp2 = ((value % 100) / 10);
            int temp3 = (value % 10);
            counterTiles[0].setNumber(temp);
            counterTiles[1].setNumber(temp2);
            counterTiles[2].setNumber(temp3);
        }
        else {
            int temp = (value / 10);
            int temp2 = (value % 10);
            counterTiles[0].setNumber(0);
            counterTiles[1].setNumber(temp);
            counterTiles[2].setNumber(temp2);
        }
    }
    else {
        int temp = (abs(value) / 10);
        int temp2 = (abs(value) % 10);
        counterTiles[0].setNumber(10);
        counterTiles[1].setNumber(temp);
        counterTiles[2].setNumber(temp2);
    }
}

void Board::revealAllMines(sf::RenderWindow &window) {
    for (int i = 0; i < totalTiles; i++) {
        if (gameTiles[i].getMineBool()) {
            gameTiles[i].tilePressed(window);
        }
    }
}
void Board::revealAllTiles(sf::RenderWindow &window) {
    for (int i = 0; i < totalTiles; i++) {
        gameTiles[i].tilePressed(window);
    }
}
void Board::pressThisTile(sf::RenderWindow &window, float xCord, float yCord) {
    int index = checkThisTile(xCord, yCord);
    if (gameStatus) {
        if (!(gameTiles[index].getTileRevealed())) {
            if (index >= 0) {
                gameTiles[index].tilePressed(window);
                if ((!(gameTiles[index].getMineBool())) && (!(gameTiles[index].getFlagBool()))) {
                    pressNearbyTiles(window, index, true);
                }
            }
        }
    }
}
int Board::pressThisButton(sf::RenderWindow &window, float xCord, float yCord) {
    int indexBoard = checkThisBoardButton(xCord, yCord);
    if (indexBoard >= 0) {
        if (indexBoard == 0) {
            gameStatus = true;
        }
        if (indexBoard == 1) {
            if (gameStatus) {
                debugActive = (!debugActive);
            }
        }
        // TestBoard functions are handled in main due to creation of new board
        return indexBoard;
    }
    return -1;
}

void Board::pressNearbyTiles(sf::RenderWindow &window, int index, bool origin) {
    if (!(gameTiles[index].getFlagBool())) {
        if (gameTiles[index].getNearbyMines() == 0) {
            if (gameTiles[index].getEdgeLeft() && gameTiles[index].getEdgeTop()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index + 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index + 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns())), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) + 1), false);
                }
            }
            else if (gameTiles[index].getEdgeLeft() && gameTiles[index].getEdgeBottom()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index + 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index + 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns())), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) + 1), false);
                }
            }
            else if (gameTiles[index].getEdgeRight() && gameTiles[index].getEdgeTop()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index - 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index - 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns())), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) - 1), false);
                }
            }
            else if (gameTiles[index].getEdgeRight() && gameTiles[index].getEdgeBottom()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index - 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index - 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns())), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) - 1), false);
                }
            }
            else if (gameTiles[index].getEdgeLeft()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index + 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index + 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns())), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) + 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns())), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) + 1), false);
                }
            }
            else if (gameTiles[index].getEdgeRight()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index - 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index - 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns())), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) - 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns())), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) - 1), false);
                }
            }
            else if (gameTiles[index].getEdgeTop()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index + 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index + 1), false);
                }
                if (!(gameTiles[index - 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index - 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns())), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) + 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) - 1), false);
                }
            }
            else if (gameTiles[index].getEdgeBottom()) {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index + 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index + 1), false);
                }
                if (!(gameTiles[index - 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index - 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns())), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) + 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) - 1), false);
                }

            }
            else {
                gameTiles[index].tilePressed(window);
                if (!(gameTiles[index + 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index + 1), false);
                }
                if (!(gameTiles[index - 1].getTileRevealed())) {
                    pressNearbyTiles(window, (index - 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns())), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) + 1), false);
                }
                if (!(gameTiles[(index + getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index + getBoardColumns()) - 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns())].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns())), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) + 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) + 1), false);
                }
                if (!(gameTiles[(index - getBoardColumns()) - 1].getTileRevealed())) {
                    pressNearbyTiles(window, ((index - getBoardColumns()) - 1), false);
                }
            }
        }
        else {
            gameTiles[index].tilePressed(window);
        }
        unPressedTiles--;
    }
    checkUnPressedTiles();
}
void Board::flagThisTile(sf::RenderWindow &window, float xCord, float yCord) {
    if (gameStatus) {
        int index = checkThisTile(xCord, yCord);
        if (!(gameTiles[index].getTileRevealed())) {
            if (index >= 0) {
                if (gameTiles[index].getFlagBool()) {
                    gameTiles[index].setFlagBool(false);
                    unFlaggedMines++;
                }
                else {
                    gameTiles[index].tileFlagged(window);
                    unFlaggedMines--;
                }
            }
        }
        changeCounter(unFlaggedMines);
    }
}
int Board::checkThisTile(float xCord, float yCord) {
    for (int i = 0; i < totalTiles; i++) {
        if (gameTiles[i].getBounds().contains(xCord, yCord)) {
            return i;
        }
    }
    return -1;
}
int Board::checkThisBoardButton(float xCord, float yCord) {
    for (int i = 0; i < 5; i++) {
        if (boardTiles[i].getBounds().contains(xCord, yCord)) {
            return i;
        }
    }
    return -1;
}
void Board::checkUnPressedTiles() {
    if (unPressedTiles == 0) {
        gameStatus = false;
        boardTiles[0].gameWon();
    }
}
void Board::determineNearbyMines() {
    for (int index = 0; index < totalTiles; index++) {
        int numberOfMinesNearby = 0;
        if (gameTiles[index].getEdgeLeft() || gameTiles[index].getEdgeRight() || gameTiles[index].getEdgeTop() || gameTiles[index].getEdgeBottom()) {
            if (gameTiles[index].getEdgeLeft() && gameTiles[index].getEdgeTop()) {
                if (gameTiles[index + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns()) + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeLeft() && gameTiles[index].getEdgeBottom()) {
                if (gameTiles[index + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns()) + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeRight() && gameTiles[index].getEdgeTop()) {
                if (gameTiles[index - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns()) - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeRight() && gameTiles[index].getEdgeBottom()) {
                if (gameTiles[index - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns()) - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeLeft()) {
                if (gameTiles[index + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns()) + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns()) + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeRight()) {
                if (gameTiles[index - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns()) - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns()) - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeTop()) {
                if (gameTiles[index - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[index + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns()) - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index + getBoardColumns()) + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
            else if (gameTiles[index].getEdgeBottom()) {
                if (gameTiles[index - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[index + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns())].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns()) - 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                if (gameTiles[(index - getBoardColumns()) + 1].getMineBool()) {
                    numberOfMinesNearby++;
                }
                gameTiles[index].setNearbyMines(numberOfMinesNearby);
            }
        }
        else {
            if (gameTiles[index - 1].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[index + 1].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[(index - getBoardColumns())].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[(index - getBoardColumns()) - 1].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[(index - getBoardColumns()) + 1].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[(index + getBoardColumns())].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[(index + getBoardColumns()) - 1].getMineBool()) {
                numberOfMinesNearby++;
            }
            if (gameTiles[(index + getBoardColumns()) + 1].getMineBool()) {
                numberOfMinesNearby++;
            }
            gameTiles[index].setNearbyMines(numberOfMinesNearby);
        }
    }
}