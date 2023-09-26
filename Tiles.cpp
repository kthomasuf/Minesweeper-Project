#include "Tiles.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

Tiles::Tiles() {
    tileSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
}
void Tiles::tilePressed(sf::RenderWindow &window) {
    if (!(drawFlagLayer)) {
        tileRevealed = true;
        tileSprite.setTexture(TextureManager::GetTexture("tile_revealed"));
        window.draw(tileSprite);

        if (hasMine) {
            minePressed = true;
            mineSprite.setTexture(TextureManager::GetTexture("mine"));
            window.draw(mineSprite);
            return;
        }

        if (getNearbyMines() == 1) {
            numberSprite.setTexture(TextureManager::GetTexture("number_1"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 2) {
            numberSprite.setTexture(TextureManager::GetTexture("number_2"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 3) {
            numberSprite.setTexture(TextureManager::GetTexture("number_3"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 4) {
            numberSprite.setTexture(TextureManager::GetTexture("number_4"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 5) {
            numberSprite.setTexture(TextureManager::GetTexture("number_5"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 6) {
            numberSprite.setTexture(TextureManager::GetTexture("number_6"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 7) {
            numberSprite.setTexture(TextureManager::GetTexture("number_7"));
            window.draw(numberSprite);
        }
        if (getNearbyMines() == 8) {
            numberSprite.setTexture(TextureManager::GetTexture("number_8"));
            window.draw(numberSprite);
        }
    }
}
void Tiles::revealMine(sf::RenderWindow &window) {
    mineSprite.setTexture(TextureManager::GetTexture("mine"));
    window.draw(mineSprite);
}
void Tiles::tileFlagged(sf::RenderWindow &window) {
    drawFlagLayer = true;
    topLayerSprite.setTexture(TextureManager::GetTexture("flag"));
    window.draw(topLayerSprite);
}
void Tiles::setXCoordinate(int xValue) {
    xCoordinate = xValue;
    xPixelCoordinate = (xCoordinate * 32.0f);
}
int Tiles::getXCoordinate() {
    return xCoordinate;
}
void Tiles::setYCoordinate(int yValue) {
    yCoordinate = yValue;
    yPixelCoordinate = (yCoordinate * 32.0f);
}
int Tiles::getYCoordinate() {
    return yCoordinate;
}
float Tiles::getXPixelCoordinate() const {
    return xPixelCoordinate;
}
float Tiles::getYPixelCoordinate() const {
    return yPixelCoordinate;
}
sf::Texture Tiles::getTileTexture() {
    return tileTexture;
}
sf::Sprite Tiles::getTileSprite() {
    return tileSprite;
}
sf::Sprite Tiles::getTopLayerSprite() {
    return topLayerSprite;
}
sf::Sprite Tiles::getMineSprite() {
    return mineSprite;
}
sf::Sprite Tiles::getNumberSprite() {
    return numberSprite;
}
sf::FloatRect Tiles::getBounds() {
    return tileSprite.getGlobalBounds();
}
void Tiles::movePosition(float xPixel, float yPixel) {
    tileSprite.setPosition(xPixel, yPixel);
    topLayerSprite.setPosition(xPixel, yPixel);
    mineSprite.setPosition(xPixel, yPixel);
    numberSprite.setPosition(xPixel, yPixel);
}
void Tiles::setTileRevealed(bool value) {
    tileRevealed = value;
}
bool Tiles::getTileRevealed() {
    return tileRevealed;
}
void Tiles::setMineBool(bool value) {
    hasMine = value;
}
bool Tiles::getMineBool() {
    return hasMine;
}
void Tiles::setFlagBool(bool value) {
    drawFlagLayer = value;
}
bool Tiles::getFlagBool() {
    return drawFlagLayer;
}
void Tiles::setMinePressedBool(bool value) {
    minePressed = value;
}
bool Tiles::getMinePressedBool() {
    return minePressed;
}

void Tiles::setEdgeLeft(bool value) {
    isEdgeLeft = value;
}
bool Tiles::getEdgeLeft() {
    return isEdgeLeft;
}
void Tiles::setEdgeRight(bool value) {
    isEdgeRight = value;
}
bool Tiles::getEdgeRight() {
    return isEdgeRight;
}
void Tiles::setEdgeTop(bool value) {
    isEdgeTop = value;
}
bool Tiles::getEdgeTop() {
    return isEdgeTop;
}
void Tiles::setEdgeBottom(bool value) {
    isEdgeBottom = value;
}
bool Tiles::getEdgeBottom() {
    return isEdgeBottom;
}
void Tiles::setNearbyMines(int value) {
    nearbyMines = value;
}
int Tiles::getNearbyMines() {
    return nearbyMines;
}