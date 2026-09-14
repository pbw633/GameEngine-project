#include "UIComponent.h"
// ------------------ Initialization ------------------

void UIComponent::initVariables(sf::IntRect frame) {
	this->currentFrame = frame;
}


void UIComponent::initTexture(std::string textureFileName) {
	if (!this->texture.loadFromFile(textureFileName)) {
		throw std::invalid_argument("UIComponent::initTexture::Could not load textureFile from filename. Have you remembered location?");
	} else {
		//std::cout << "Loaded texture: " << fileName << std::endl;
	}
}

void UIComponent::initSprite() {
	
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->currentFrame);
	// Resize the sprite
	this->sprite.scale(1.0f, 1.0f);

	this->spriteBoarder.setSize( this->sprite.getGlobalBounds().getSize() );
	this->spriteBoarder.setFillColor(sf::Color(0,0,0,0)); // transparent background
	this->spriteBoarder.setOutlineColor(sf::Color::Red);
	this->spriteBoarder.setOutlineThickness(1);
}

// ------------------- Setters ------------------

void UIComponent::setPosition(float x, float y) {
	this->sprite.setPosition(x, y);
	this->spriteBoarder.setPosition(x, y);
}

void UIComponent::setSpritePosition(sf::Vector2f position) {
	this->sprite.setPosition(position);
	this->spriteBoarder.setPosition(position);
}

// scaling
void UIComponent::setSpriteScale(float scaleX, float scaleY) {
	this->sprite.setScale(scaleX, scaleY);
	this->spriteBoarder.setScale(scaleX,scaleY);
}	

void UIComponent::setSpriteScale(sf::Vector2f scale) {
	this->sprite.setScale(scale);
	this->spriteBoarder.setScale(scale);
}
void UIComponent::setSpriteScale(float scale) {
	this->sprite.setScale(scale, scale);
	this->spriteBoarder.setScale(scale,scale);
}


void UIComponent::setOrigin(sf::Vector2f position) {
	this->sprite.setOrigin(position);
	this->spriteBoarder.setOrigin(position);
}

void UIComponent::setOrigin(float positionX, float positionY) {
	this->sprite.setOrigin(positionX,positionY);
	this->spriteBoarder.setOrigin(positionX, positionY);
}

// ------------------- Getters ------------------

float UIComponent::getSpriteWidth() {
	return this->sprite.getGlobalBounds().width;
}

float UIComponent::getSpriteHeight() {
	return this->sprite.getGlobalBounds().height;
}

float UIComponent::getTextureWidth() {
	return this->texture.getSize().x;
}

float UIComponent::getTextureHeight() {
	return this->texture.getSize().y;
}

sf::Texture& UIComponent::getTexture() {
	return this->texture;
}

sf::Sprite& UIComponent::getSprite() {
	return this->sprite;
}

sf::RectangleShape& UIComponent::getSpriteBoarder() {
	return this->spriteBoarder;
}

// ------------------- Actions ------------------	
void UIComponent::draw(sf::RenderTarget& window) { // method should be virtual so it can be overriden 
	window.draw(this->sprite); 
	window.draw(this->spriteBoarder); // this should be removed
}

void UIComponent::toggleSpriteBoarder() {

}