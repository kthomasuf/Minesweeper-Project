#pragma once
#include <SFML/Graphics.hpp>

class Buttons {
private:
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    float xPixelCoordinate;
    float yPixelCoordinate;
public:
    Buttons();
    Buttons(int number);
    void gameWon();
    void gameLost();
    void setXPixelCoordinate(float xPixelCord, int index);
    void setYPixelCoordinate(float xPixelCord, int index);
    float getXPixelCoordinate() const;
    float getYPixelCoordinate() const;
    void movePosition(float xPixel, float yPixel);

    sf::Sprite getButtonSprite();
    sf::FloatRect getBounds();
};