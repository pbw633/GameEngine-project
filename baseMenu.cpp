#pragma once
#include "baseMenu.h"
#include <iostream>
// ----------------- Initialization -----------------
void baseMenu::initTexture(std::string fileName) {
	// Load Texture from file'
	if (!this->texture.loadFromFile(fileName)) {
		std::cout << "Failed to initialize texture: " << fileName << std::endl;
		throw std::runtime_error("Failed to initialize texture");
	} else {
		std::cout << "Texture initialized successfully: " << fileName << std::endl;
		this->sprite.setTexture(this->texture);
	}
}

void baseMenu::initSprite() {
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->menuBackground.getPosition());
	this->sprite.setScale(
		this->menuBackground.getSize().x / this->texture.getSize().x,
		this->menuBackground.getSize().y / this->texture.getSize().y
	);
}

// ----------------- Setters -----------------	
void baseMenu::setBackgroundColor(sf::Color color) {
	this->menuBackground.setFillColor(color);
}

void baseMenu::setMenuBorderColor(sf::Color color) {
	this->menuBackground.setOutlineColor(color);
}

void baseMenu::setMenuSprite(sf::Texture& texture) {
	this->sprite.setTexture(texture);
}	

void baseMenu::setPosition(float x, float y) {
	this->menuBackground.setPosition(x, y);
}

void baseMenu::setSize(float width, float height) {
	this->menuBackground.setSize(sf::Vector2f(width, height));
}