#include <SFML/Graphics.hpp>
#include "Board.h"
#include "TextureManager.h"

int main() {
    Board testBoard;
    sf::RenderWindow window(sf::VideoMode(testBoard.getPixelColumns(),testBoard.getPixelRows()), "Test");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (testBoard.getGameStatus()) {
                    sf::Vector2i mouseCoordinates = sf::Mouse::getPosition(window);
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        testBoard.pressThisTile(window, mouseCoordinates.x, mouseCoordinates.y);
                        int test = testBoard.pressThisButton(window, mouseCoordinates.x, mouseCoordinates.y);
                        if (test == 0) {
                            Board newBoard;
                            testBoard = newBoard;
                        }
                        if (test == 2) {
                            Board newBoard(1);
                            testBoard = newBoard;
                        }
                        else if (test == 3) {
                            Board newBoard(2);
                            testBoard = newBoard;
                        }
                        else if (test == 4) {
                            Board newBoard(3);
                            testBoard = newBoard;
                        }
                    }
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        testBoard.flagThisTile(window, mouseCoordinates.x, mouseCoordinates.y);
                    }
                }
                else {
                    sf::Vector2i mouseCoordinates = sf::Mouse::getPosition(window);
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int test = testBoard.pressThisButton(window, mouseCoordinates.x, mouseCoordinates.y);
                        if (test == 0) {
                            Board newBoard;
                            testBoard = newBoard;
                        }
                        else if (test == 2) {
                            Board newBoard(1);
                            testBoard = newBoard;
                        }
                        else if (test == 3) {
                            Board newBoard(2);
                            testBoard = newBoard;
                        }
                        else if (test == 4) {
                            Board newBoard(3);
                            testBoard = newBoard;
                        }
                    }
                }
            }
        }
        testBoard.drawButtons(window);
        testBoard.drawCurrentBoard(window);
        testBoard.drawCounter(window);
        window.display();
        window.clear();
    }
    TextureManager::Clear();
    return 0;
}