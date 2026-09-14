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
			subSpriteBoarders.setPosition(tempX, tempY);
			subSpriteBoarders.setSize(sf::Vector2f(tempWidth, tempHeight));
			spritePartitions.push_back(subSpriteBoarders);

			// Used for the actual sprites
			sf::Sprite subSprite;
			subSprite.setTexture(this->getTexture());
			subSprite.setTextureRect(subFrames[i*3+j]);
			subSprites.push_back(subSprite);
		}
	}
}

// ------------------ Setters ------------------

// ------------------ Getters ------------------

// ------------------ Adders -------------------

// ------------------ Actions ------------------
void NineSliceComponent::draw(sf::RenderTarget& window) {
	if (subSprites.size() != 9 ) {
		throw std::runtime_error("NineSliceComponent::draw::This class needs 9 sprites to do 9-slicing... Duh");
	}
}