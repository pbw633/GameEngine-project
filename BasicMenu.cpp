#include "BasicMenu.h"	
// ------------------- public -------------------
// ------------------ Initialization ------------------
void BasicMenu::initBasicMenuByRectangleShape(sf::Vector2f position, float width, float height) {
	// This method should only be used for quick tests as we do not initialize textures and sprites 
	// Set the origin to the center of the rectangle
	this->getSpriteBoarder().setOrigin(sf::Vector2f(width, height) * 0.5f);
	this->getSpriteBoarder().setPosition(position);
	this->getSpriteBoarder().setSize(sf::Vector2f(width, height));
	
	this->center = position;
}

void BasicMenu::initBasicMenuByTexture(std::string textureFileName) {
	// Set the origin to the center of the rectangle
	this->initTexture(textureFileName);
	this->initVariables(sf::IntRect(0, 0, this->getTexture().getSize().x, this->getTexture().getSize().y)); // full texture as the sprite used
	this->initSprite();
	
	
	this->setOrigin(this->getSprite().getLocalBounds().width / 2.f, this->getSprite().getLocalBounds().height / 2.f);
	
}

void BasicMenu::initSubSpritePartitions(sf::Vector2f partitionX, sf::Vector2f partitionY) {
	float minPartitionX = std::min(partitionX.x, partitionX.y);
	float minPartitionY = std::min(partitionY.x, partitionY.y);
	float maxPartitionX = std::max(partitionX.x, partitionX.y);
	float maxPartitionY = std::max(partitionY.x, partitionY.y);

	if (minPartitionX < 0.0f || minPartitionY < 0.0f || maxPartitionX > 1.0f || maxPartitionY > 1.0f) {
		throw std::invalid_argument("BaseMenu::initSubSpritePartitionByFraction:: Partition values must be between 0 and 1.");
	}
	
	this->spritePartitionX = sf::Vector2f(minPartitionX, maxPartitionX);
	this->spritePartitionY = sf::Vector2f(minPartitionY, maxPartitionY);
}

void BasicMenu::initSubSprites(std::string fileName) {
	this->initTexture(fileName);
	float minPartitionY = this->spritePartitionY.x;
	float minPartitionX = this->spritePartitionX.x;
	float maxPartitionY = this->spritePartitionY.y;
	float maxPartitionX = this->spritePartitionX.y;

	float width = this->getSpriteWidth();
	float height = this->getSpriteHeight();
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			float tempX = 0.0f;
			float tempY = 0.0f;
			float tempWidth = 0.0f;
			float tempHeight = 0.0f;
			
			// Calculate the position and size of each sub-rectangle
			if (row == 0) {
				tempY = 0.0f;
				tempHeight = minPartitionY * height;
			}
			else if (row == 1) {
				tempY = minPartitionY * height;
				tempHeight = (maxPartitionY - minPartitionY) * height;
			}
			else {
				tempY = maxPartitionY * height;
				tempHeight = (1.0f - maxPartitionY) * height;
			}

			if (col == 0) {
				tempX = 0.0f;
				tempWidth = minPartitionX * width;
			}
			else if (col == 1) {
				tempX = minPartitionX * width;
				tempWidth = (maxPartitionX - minPartitionX) * width;
			}
			else {
				tempX = maxPartitionX * width;
				tempWidth = (1.0f - maxPartitionX) * width;
			}

			sf::IntRect subRect(tempX, tempY, tempWidth, tempHeight);
			this->subFrames.push_back(subRect);


			sf::RectangleShape subSpriteBoarders;
			subSpriteBoarders.setPosition(tempX,tempY);
			subSpriteBoarders.setSize(sf::Vector2f(tempWidth, tempHeight));
			spritePartitions.push_back(subSpriteBoarders);
		}
	}

	for (int i = 0; i < 9; i++) {
		sf::Sprite subSprite;
		subSprite.setTexture(this->getTexture());
		subSprite.setTextureRect(subFrames[i]);
		this->subSprites.push_back(subSprite);
	}
	
}

// ------------------ Setters ------------------	
void BasicMenu::setMenuPosition(sf::Vector2f position) {

	//this->calculateCenter();
	this->setSpritePosition(position);
	this->calculateCenter();
}
// ------------------ Getters ------------------
sf::Vector2f BasicMenu::getPoint(int index) {
	if (index < 0 || index >= 4) {
		throw std::runtime_error("BasicMenu: index out of bounds");
	}
	switch (index) {
	case 0:
		return this->getSpriteBoarder().getPoint(0) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 1:
		return this->getSpriteBoarder().getPoint(1) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 2:
		return this->getSpriteBoarder().getPoint(2) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 3:
		return this->getSpriteBoarder().getPoint(3) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	}
}

sf::Vector2f BasicMenu::getCenter() {
	return this->center;
}

sf::RectangleShape&	BasicMenu::getMenuShape() {
	return this->getSpriteBoarder();
}

// ------------------ Adders -------------------

// ------------------ Actions ------------------	
void BasicMenu::draw(sf::RenderTarget& window) {
	for (int i = 0; i < 9;i++) {
		window.draw(this->subSprites[i]);
	}
}

void BasicMenu::toggleSpritePartition() {

}

// ------------------- private -------------------
// ------------------ Initialization ------------------

// ------------------ Setters ------------------	

// ------------------ Getters ------------------

// ------------------ Adders -------------------

// ------------------ Actions ------------------	

void BasicMenu::calculateCenter() {
	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < 4; i++) {
		sf::Vector2f point = this->getSpriteBoarder().getPoint(i);
		sumX += point.x;
		sumY += point.y;
	}
	center.x = sumX / 4;
	center.y = sumY / 4;
	
}