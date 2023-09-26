#include "Counter.h"
#include "Board.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>

Counter::Counter() {
    counterSprite.setTexture(TextureManager::GetTexture("digits"));
}
void Counter::setNumber(int value) {
    if (value >= 0) {
        counterSprite.setTextureRect(sf::IntRect((value * 21),0,21,32));
    }
    else {
        counterSprite.setTextureRect(sf::IntRect(210,0,21,32));
    }
}
void Counter::setXPixelCoordinate(float xPixelCord, int index) {
    if (index == 0) {
        xPixelCoordinate = xPixelCord + 21;
    }
    else {
        xPixelCoordinate = (xPixelCord + (index * 21) + 21);
    }
}
void Counter::setYPixelCoordinate(float yPixelCord, int index) {
    yPixelCoordinate = yPixelCord;
}
float Counter::getXPixelCoordinate() const {
    return xPixelCoordinate;
}
float Counter::getYPixelCoordinate() const {
    return yPixelCoordinate;
}
void Counter::movePosition(float xPixel, float yPixel) {
    counterSprite.setPosition(xPixel,yPixel);
}
sf::Sprite Counter::getCounterSprite() {
    return counterSprite;
}