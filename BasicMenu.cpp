#include "BasicMenu.h"	
// ------------------- public -------------------
// ------------------ Initialization ------------------
void BasicMenu::initBasicMenu(sf::Vector2f position, float width, float height) {
	// Set the origin to the center of the rectangle
	this->menuShape.setOrigin(sf::Vector2f(width, height) * 0.5f);
	// Set the position of the rectangle
	this->menuShape.setPosition(position);
	// Set the size of the rectangle
	this->menuShape.setSize(sf::Vector2f(width, height));
	
	
	this->center = position;

}

// ------------------ Setters ------------------	

// ------------------ Getters ------------------
sf::Vector2f BasicMenu::getPoint(int index) {
	if (index < 0 || index >= 4) {
		throw std::runtime_error("BasicMenu: index out of bounds");
	}
	switch (index) {
	case 0:
		return this->menuShape.getPoint(0) + this->menuShape.getPosition() - this->menuShape.getOrigin();
	case 1:
		return this->menuShape.getPoint(1) + this->menuShape.getPosition() - this->menuShape.getOrigin();
	case 2:
		return this->menuShape.getPoint(2) + this->menuShape.getPosition() - this->menuShape.getOrigin();
	case 3:
		return this->menuShape.getPoint(3) + this->menuShape.getPosition() - this->menuShape.getOrigin();
	}
}

sf::Vector2f BasicMenu::getCenter() {
	return this->center;
}

// ------------------ Adders -------------------

// ------------------ Actions ------------------	



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
		sf::Vector2f point = this->menuShape.getPoint(i);
		sumX += point.x;
		sumY += point.y;
	}
	center.x = sumX / 4;
	center.y = sumY / 4;
	
}