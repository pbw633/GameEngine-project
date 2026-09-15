#pragma once
#include "baseMenu.h"
#include "BasicButton.h"
#include "PolygonButton.h"
#include "NineSliceComponent.h"
/*
TODO:
	- MenuShape does not make sense as we already have spriteBoarder which is a square already. fix methods to take this into account
*/

class BasicMenu : public BaseMenu, public NineSliceComponent
{
public:
	BasicMenu() {};

	//~BasicMenu();

	// ------------------ Variables ------------------

	// ------------------ Initialization ------------------
	void initBasicMenuByRectangleShape(sf::Vector2f position, float width, float height);	
	//void initBasicMenuByTexture(std::string textureFileName);

	//void initSubSpritePartitions(sf::Vector2f partitionX, sf::Vector2f partitionY);
	//void initSubSprites(std::string fileName); // used to partition into 3 x 3
	// ------------------ Setters ------------------

	void setMenuPosition(sf::Vector2f position	);

	// ------------------ Getters ------------------
	//sf::RectangleShape& getMenuShape();
	//sf::Vector2f getMenuPosition();
	float getWidth();
	float getHeight();

	sf::Vector2f getPoint(int index);
	sf::Vector2f getCenter() override;
	

	// ------------------ Adders -------------------


	// ------------------ Actions ------------------
	

	void calculateCenter() override;

	void toggleSpritePartition();

private:
	// ------------------ Variables ------------------
	sf::RectangleShape menuShape;
	sf::Vector2f center;

	// used for partioning the sprite into subSprites (3x3)
	std::vector<sf::IntRect> subFrames;
	std::vector<sf::Sprite> subSprites;

	// helper for debugging the subSprites
	std::vector<sf::RectangleShape> spritePartitions;
	sf::Vector2f spritePartitionX;
	sf::Vector2f spritePartitionY;


	bool showSpritePartition = false;

	// ------------------ Initialization ------------------

	// ------------------ Setters ------------------

	// ------------------ Getters ------------------

	// ------------------ Adders -------------------

	// ------------------ Actions ------------------
	
};