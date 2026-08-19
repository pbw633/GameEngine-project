#include "BaseButton.h"

// ------------------ Setters ------------------
void BaseButton::setPosition(sf::Vector2i newPosition) {
	this->position = newPosition;
}

// ------------------ Getters ------------------
sf::Vector2i BaseButton::getPosition() {
	return this->position;
}

