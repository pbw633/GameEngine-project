#pragma once
#include "UIComponent.h"

/* 
	This class is made to split up a sprite into 9 pieces but they would appear as just one collective sprite
*/
class NineSliceComponent : public UIComponent {
public:

	//------------------ Initialize ------------------
	void initPartition(sf::Vector2f partitionX, sf::Vector2f partitionY);
	
	void initSprites();
	//------------------ Setters ---------------------
	void setPosition(float x, float y) override;
	//------------------ Getters ---------------------

	//------------------ Adders ----------------------
	//------------------ Actions ---------------------
	void draw(sf::RenderTarget& window) override;

private:
	//------------------ Variables ------------------
	//sf::Texture texture;
	std::vector<sf::IntRect> subFrames;
	std::vector<sf::Sprite> subSprites;

	// helper for debugging the subSprites
	std::vector<sf::RectangleShape> spritePartitions;
	sf::Vector2f spritePartitionX;
	sf::Vector2f spritePartitionY;

	std::vector<sf::Sprite > nineSliceArray;
};