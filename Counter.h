#pragma once
#include <SFML/Graphics.hpp>

class Counter {
private:
    sf::Sprite counterSprite;
    float xPixelCoordinate;
    float yPixelCoordinate;
public:
    Counter();
    void setNumber(int value);
    void setXPixelCoordinate(float xPixelCord, int index);
    void setYPixelCoordinate(float xPixelCord, int index);
    float getXPixelCoordinate() const;
    float getYPixelCoordinate() const;
    void movePosition(float xPixel, float yPixel);

    sf::Sprite getCounterSprite();
};