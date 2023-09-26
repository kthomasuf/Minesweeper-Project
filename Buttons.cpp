#include "Buttons.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>

Buttons::Buttons() {
    buttonSprite.setTexture(TextureManager::GetTexture("face_happy"));
}
Buttons::Buttons(int number) {
    if (number == 0) {
        buttonSprite.setTexture(TextureManager::GetTexture("face_happy"));
    }
    else if (number == 1) {
        buttonSprite.setTexture(TextureManager::GetTexture("debug"));
    }
    else if (number == 2) {
        buttonSprite.setTexture(TextureManager::GetTexture("test_1"));
    }
    else if (number == 3) {
        buttonSprite.setTexture(TextureManager::GetTexture("test_2"));
    }
    else if (number == 4) {
        buttonSprite.setTexture(TextureManager::GetTexture("test_3"));
    }
}
void Buttons::gameWon() {
    buttonSprite.setTexture(TextureManager::GetTexture("face_win"));
}
void Buttons::gameLost() {
    buttonSprite.setTexture(TextureManager::GetTexture("face_lose"));
}
void Buttons::setXPixelCoordinate(float xPixelCord, int index) {
    if (index == 0) {
        xPixelCoordinate = (xPixelCord - 32);
    }
    else {
        if (index == 1) {
            xPixelCoordinate = ((xPixelCord * 2) - (4 * 64));
        }
        else if (index == 2) {
            xPixelCoordinate = ((xPixelCord * 2) - (3 * 64));
        }
        else if (index == 3) {
            xPixelCoordinate = ((xPixelCord * 2) - (2 * 64));
        }
        else if (index == 4) {
            xPixelCoordinate = ((xPixelCord * 2) - (1 * 64));
        }
        //xPixelCoordinate = (xPixelCord + (index * 64) + 32);
    }
}
void Buttons::setYPixelCoordinate(float yPixelCord, int index) {
    yPixelCoordinate = yPixelCord;
}
float Buttons::getXPixelCoordinate() const {
    return xPixelCoordinate;
}
float Buttons::getYPixelCoordinate() const {
    return yPixelCoordinate;
}
void Buttons::movePosition(float xPixel, float yPixel) {
    buttonSprite.setPosition(xPixel, yPixel);
}
sf::Sprite Buttons::getButtonSprite() {
    return buttonSprite;
}
sf::FloatRect Buttons::getBounds() {
    return buttonSprite.getGlobalBounds();
}