#include "BasicMenu.h"	
// ------------------- public -------------------
// ------------------ Initialization ------------------
void BasicMenu::initBasicMenuByRectangleShape(sf::Vector2f position, float width, float height) {
	// This method should only be used for quick tests as we do not initialize textures and sprites 
	// Set the origin to the center of the rectangle
	//this->getSpriteBoarder().setOrigin(sf::Vector2f(width, height) * 0.5f);
	//this->getSpriteBoarder().setPosition(position);
	//this->getSpriteBoarder().setSize(sf::Vector2f(width, height));
	
	this->center = position;
}
/*
void BasicMenu::initBasicMenuByTexture(std::string textureFileName) {
	// Set the origin to the center of the rectangle
	
	
}
*/


// ------------------ Setters ------------------	
void BasicMenu::setMenuPosition(sf::Vector2f position) {
	this->setPosition(position.x, position.y);
	//this->calculateCenter();
	//this->setSpritePosition(position);
	//this->calculateCenter();
}
// ------------------ Getters ------------------
sf::Vector2f BasicMenu::getPoint(int index) {
	if (index < 0 || index >= 4) {
		throw std::runtime_error("BasicMenu: index out of bounds");
	}
	switch (index) {
	case 0:
		return sf::Vector2f(0,0);//this->getSpriteBoarder().getPoint(0) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 1:
		return sf::Vector2f(0, 0);//this->getSpriteBoarder().getPoint(1) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 2:
		return sf::Vector2f(0, 0);//this->getSpriteBoarder().getPoint(2) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 3:
		return sf::Vector2f(0, 0);//this->getSpriteBoarder().getPoint(3) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	}
}

sf::Vector2f BasicMenu::getCenter() {
	return this->center;
}
/*
sf::RectangleShape&	BasicMenu::getMenuShape() {
	return this->getSpriteBoarder();
}
*/

// ------------------ Adders -------------------

// ------------------ Actions ------------------	

void BasicMenu::toggleSpritePartition() {

}

// ------------------- private -------------------
// ------------------ Initialization ------------------

// ------------------ Setters ------------------	

// ------------------ Getters ------------------

// ------------------ Adders -------------------

// ------------------ Actions ------------------	

void BasicMenu::calculateCenter() {
	/*
	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < 4; i++) {
		sf::Vector2f point = this->getSpriteBoarder().getPoint(i);
		sumX += point.x;
		sumY += point.y;
	}
	center.x = sumX / 4;
	center.y = sumY / 4;
	*/
}