#include "UIComponent.h"
// ------------------ Initialization ------------------

void UIComponent::initVariables(sf::IntRect frame) {
	this->currentFrame = frame;
}


void UIComponent::initTexture(std::string textureFileName) {
	if (!this->texture.loadFromFile(textureFileName)) {
		throw std::invalid_argument("UIComponent::initTexture::Could not load textureFile from filename. Have you remembered location?");
	}

	if (!this->texture.loadFromFile(textureFileName)) {
		std::cout << "Failed loading texture: " << textureFileName << std::endl;
	}
	else {
		//std::cout << "Loaded texture: " << fileName << std::endl;
	}
}

void UIComponent::initSprite() {
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->currentFrame);
	// Resize the sprite
	this->sprite.scale(1.0f, 1.0f);
}

// ------------------- Setters ------------------

void UIComponent::setSpritePosition(float x, float y) {
	this->sprite.setPosition(x, y);
}

void UIComponent::setSpritePosition(sf::Vector2f position) {
	this->sprite.setPosition(position);
}

// scaling
void UIComponent::setSpriteScale(float scaleX, float scaleY) {
	this->sprite.setScale(scaleX, scaleY);
}	

void UIComponent::setSpriteScale(sf::Vector2f scale) {
	this->sprite.setScale(scale);
}
void UIComponent::setSpriteScale(float scale) {
	this->sprite.setScale(scale, scale);
}

// ------------------- Getters ------------------

float UIComponent::getSpriteWidth() {
	return this->sprite.getGlobalBounds().width;
}

float UIComponent::getSpriteHeight() {
	return this->sprite.getGlobalBounds().height;
}