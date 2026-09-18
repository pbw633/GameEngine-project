#pragma once
#include <cmath>
#include "UIComponent.h"

/* 
	This class is made to split up a sprite into 9 pieces but they would appear as just one collective sprite
*/
class NineSliceComponent : public UIComponent {
public:

	//------------------ Initialize ------------------
	void initPartition(sf::Vector2f partitionX, sf::Vector2f partitionY);
	
	void initSprites();
	void initSpriteOffsets();
	//------------------ Setters ---------------------
	void setPosition(float x, float y) override;
	//------------------ Getters ---------------------
	sf::RectangleShape& getSpritePartition(int index);
	std::vector<sf::RectangleShape>& getSpritePartitions();
	//------------------ Adders ----------------------
	//------------------ Actions ---------------------
	void draw(sf::RenderTarget& window) override;
	void drawSpritePartition( sf::RenderTarget& window );

	void expandUpToPoint(sf::Vector2i point);
	void expandDownToPoint(sf::Vector2i point);
	void expandLeftToPoint(sf::Vector2i point);
	void expandRightToPoint(sf::Vector2i point);

	void moveSlicesToPoint(sf::Vector2i point);
private:
	//------------------ Variables ------------------
	//sf::Texture texture;
	float scalingFactorSafety = 0.01;

	std::vector<sf::IntRect> subFrames;
	std::vector<sf::Sprite> subSprites;

	std::vector<sf::Vector2f> spriteOffsets; // used to store the offsets of each sub-sprite relative to the center sprite

	// helper for debugging the subSprites
	std::vector<sf::RectangleShape> spritePartitions;
	sf::Vector2f spritePartitionX;
	sf::Vector2f spritePartitionY;

	//std::vector<sf::Sprite > nineSliceArray;
};