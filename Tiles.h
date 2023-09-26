#pragma once
#include <SFML/Graphics.hpp>

class Tiles {
private:
    sf::Texture tileTexture;
    sf::Sprite tileSprite;
    sf::Sprite topLayerSprite;
    sf::Sprite numberSprite;
    sf::Sprite mineSprite;
    int xCoordinate;
    int yCoordinate;
    int nearbyMines;
    float xPixelCoordinate;
    float yPixelCoordinate;
    bool tileRevealed = false;
    bool hasMine = false;
    bool drawFlagLayer = false;
    bool minePressed = false;
    bool isEdgeLeft = false;
    bool isEdgeRight = false;
    bool isEdgeTop = false;
    bool isEdgeBottom = false;
public:
    Tiles();
    void tilePressed(sf::RenderWindow &window);
    void revealMine(sf::RenderWindow &window);
    void tileFlagged(sf::RenderWindow &window);
    void setXCoordinate(int xValue);
    int getXCoordinate();
    void setYCoordinate(int yValue);
    int getYCoordinate();
    float getXPixelCoordinate() const;
    float getYPixelCoordinate() const;
    void movePosition(float xPixel, float yPixel);
    void setTileRevealed(bool value);
    bool getTileRevealed();
    void setMineBool(bool value);
    bool getMineBool();
    void setFlagBool(bool value);
    bool getFlagBool();
    void setMinePressedBool(bool value);
    bool getMinePressedBool();
    void setEdgeLeft(bool value);
    bool getEdgeLeft();
    void setEdgeRight(bool value);
    bool getEdgeRight();
    void setEdgeTop(bool value);
    bool getEdgeTop();
    void setEdgeBottom(bool value);
    bool getEdgeBottom();
    void setNearbyMines(int value);
    int getNearbyMines();

    sf::Texture getTileTexture();
    sf::Sprite getTileSprite();
    sf::Sprite getTopLayerSprite();
    sf::Sprite getMineSprite();
    sf::Sprite getNumberSprite();
    sf::FloatRect getBounds();
};