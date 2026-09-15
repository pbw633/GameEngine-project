#include "NineSliceComponent.h"
// ----------------- Initialize ---------------
void NineSliceComponent::initPartition(sf::Vector2f partitionX, sf::Vector2f partitionY) {
	float minPartitionX = std::min(partitionX.x, partitionX.y);
	float minPartitionY = std::min(partitionY.x, partitionY.y);
	float maxPartitionX = std::max(partitionX.x, partitionX.y);
	float maxPartitionY = std::max(partitionY.x, partitionY.y);

	if (minPartitionX < 0.0f || minPartitionY < 0.0f || maxPartitionX > 1.0f || maxPartitionY > 1.0f) {
		throw std::invalid_argument("NineSliceComponent::initPartition:: Partition values must be between 0 and 1.");
	}

	this->spritePartitionX = sf::Vector2f(minPartitionX, maxPartitionX);
	this->spritePartitionY = sf::Vector2f(minPartitionY, maxPartitionY);
}

void NineSliceComponent::initSprites() {
	/*
		first initialize a mainSprite and then split 
	*/
	if (this->getTexture().getSize().x == 0 || this->getTexture().getSize().y == 0) {
		throw std::runtime_error("NineSliceComponent::initSprites:: There is no texture to slice");
	}
	//this->initSprite();

	float width = this->getTextureWidth();
	float height = this->getTextureHeight();

	float minPartitionY = spritePartitionY.x;
	float minPartitionX = spritePartitionX.x;
	float maxPartitionY = spritePartitionY.y;
	float maxPartitionX = spritePartitionX.y;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float tempX = 0.0f;
			float tempY = 0.0f;
			float tempWidth = 0.0f;
			float tempHeight = 0.0f;

			// Calculate the position and size of each sub-rectangle
			if (i == 0) {
				tempY = 0.0f;
				tempHeight = minPartitionY * height;
			}
			else if (i == 1) {
				tempY = minPartitionY * height;
				tempHeight = (maxPartitionY - minPartitionY) * height;
			}
			else {
				tempY = maxPartitionY * height;
				tempHeight = (1.0f - maxPartitionY) * height;
			}

			if (j == 0) {
				tempX = 0.0f;
				tempWidth = minPartitionX * width;
			}
			else if (j == 1) {
				tempX = minPartitionX * width;
				tempWidth = (maxPartitionX - minPartitionX) * width;
			}
			else {
				tempX = maxPartitionX * width;
				tempWidth = (1.0f - maxPartitionX) * width;
			}

			// Used for Possible animation
			sf::IntRect subRect(tempX, tempY, tempWidth, tempHeight);
			this->subFrames.push_back(subRect); 

			// Used to show Boarders of the partition
			sf::RectangleShape subSpriteBoarders;
			//subSpriteBoarders.setPosition(tempX, tempY);
			subSpriteBoarders.setSize(sf::Vector2f(tempWidth, tempHeight));
			subSpriteBoarders.setOrigin(tempWidth / 2, tempHeight / 2);
			spritePartitions.push_back(subSpriteBoarders);

			// Used for the actual sprites
			sf::Sprite subSprite;
			subSprite.setTexture(this->getTexture());
			subSprite.setTextureRect(subFrames[i*3+j]);
			//subSprite.setPosition(tempX, tempY);
			subSprite.setOrigin(tempWidth/2, tempHeight/2);
			subSprites.push_back(subSprite);
		}
	}
}

void NineSliceComponent::initSpriteOffsets() {
	// Calculate the offsets of each sub-sprite relative to the center sprite origin

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (col == 0 && row == 0) {// Top-left
				spriteOffsets.push_back(sf::Vector2f(std::ceil( - subSprites[row * 3 + col].getOrigin().x - subSprites[4].getOrigin().x),
														std::ceil( - subSprites[row * 3 + col].getOrigin().y - subSprites[4].getOrigin().y)));
			}
			else if (col == 1 && row == 0) { // Top-center
				spriteOffsets.push_back(sf::Vector2f(0,
					std::ceil( - subSprites[row * 3 + col].getOrigin().y - subSprites[4].getOrigin().y)));
			}
			else if (col == 2 && row == 0) { // Top-right
				spriteOffsets.push_back(sf::Vector2f(std::floor(subSprites[4].getOrigin().x + subSprites[row * 3 + col].getOrigin().x),
														std::ceil( - subSprites[row * 3 + col].getOrigin().y - subSprites[4].getOrigin().y)));
			}
			else if (col == 0 && row == 1) { // Middle-left
				spriteOffsets.push_back(sf::Vector2f(std::ceil( - subSprites[row * 3 + col].getOrigin().x - subSprites[4].getOrigin().x),
																0));
			}
			else if (col == 1 && row == 1) { // Center
				spriteOffsets.push_back(sf::Vector2f(0, 0));
			}
			else if (col == 2 && row == 1) { // Middle-right
				spriteOffsets.push_back(sf::Vector2f(std::floor(subSprites[row * 3 + col].getOrigin().x + subSprites[4].getOrigin().x),
																0));
			}
			else if (col == 0 && row == 2) {// bottom left
				spriteOffsets.push_back(sf::Vector2f(std::ceil( - subSprites[row * 3 + col].getOrigin().x - subSprites[4].getOrigin().x),
															std::floor(subSprites[row * 3 + col].getOrigin().y + subSprites[4].getOrigin().y)));
			}
			else if (col == 1 && row == 2) { // bottom center
				spriteOffsets.push_back(sf::Vector2f(0, 
															std::floor(subSprites[row * 3 + col].getOrigin().y + subSprites[4].getOrigin().y)));
			}
			else if (col == 2 && row == 2) { // bottom right
				spriteOffsets.push_back(sf::Vector2f(std::floor(subSprites[row * 3 + col].getOrigin().x + subSprites[4].getOrigin().x),
														std::floor(subSprites[row * 3 + col].getOrigin().y + subSprites[4].getOrigin().y)));
			}

		}
	}
}

// ------------------ Setters ------------------
void NineSliceComponent::setPosition(float x, float y) {
	std::cout << "NineSliceComponent::draw::subSprites.size() = " << subSprites.size() << std::endl;
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::setPosition::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	sf::Vector2f initialCenter = subSprites[4].getPosition(); // The center sprite is at index 4
	
	sf::Vector2f spriteOffset = sf::Vector2f(0,0);
	sf::Vector2f interSpriteSpacing = sf::Vector2f(subSprites[0].getGlobalBounds().getSize().x / 2 + subSprites[1].getGlobalBounds().getSize().x / 2,
													subSprites[0].getGlobalBounds().getSize().y / 2 + subSprites[1].getGlobalBounds().getSize().y / 2);
	for (int i = 0; i < 3; i++) {
		//spriteOffset.y = spriteOffset.y + subSprites[i * 3].getOrigin().y;
		for (int j = 0; j < 3; j++) {
			//spriteOffset.x = spriteOffset.x + subSprites[i * 3 + j].getOrigin().x;
				
			subSprites[i*3+j].setPosition(spriteOffsets[i*3+j].x + x, spriteOffsets[i*3+j].y + y);
			// Implementation for setting position of each sub-sprite
		}
	}
	
	/*
	for (int i = 0; i < 9; i++) {
		subSprites[i].setPosition(
			subSprites[i].getPosition().x- initialCenter.x + x- subSprites[4].getOrigin().x,
			subSprites[i].getPosition().y - initialCenter.y + y- subSprites[4].getOrigin().y);
	}
	*/
}
// ------------------ Getters ------------------

// ------------------ Adders -------------------

// ------------------ Actions ------------------
void NineSliceComponent::draw(sf::RenderTarget& window) {
	if (subSprites.size() != 9 ) {
		
		throw std::runtime_error("NineSliceComponent::draw::This class needs 9 sprites to do 9-slicing... Duh");
	}
	
	for (int i=0; i<9; i++) {
		window.draw(subSprites.at(i));
	}
	//window.draw(subSprites.at(4));
	

}