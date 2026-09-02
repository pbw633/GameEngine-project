#include "BasicButton.h"
/*
	- 
*/


// ------------------ Initialization ------------------	
void BasicButton::initButtonShape(float x, float y, float width, float height) {
	this->basicButtonShape.setPosition(x, y);
	this->basicButtonShape.setSize(sf::Vector2f(width, height));
}

void BasicButton::initButtonShape(sf::RectangleShape buttonShape) {
	this->basicButtonShape = buttonShape;
}

// ------------------ Setters ------------------
void BasicButton::setButtonShape(sf::RectangleShape buttonShape) {
	this->basicButtonShape = buttonShape;
}

void BasicButton::setButtonText(sf::Text buttonText) {
	this->buttonText = buttonText;
}

void BasicButton::setButtonTexture(sf::Texture buttonTexture) {
	this->buttonTexture = buttonTexture;
}

void BasicButton::setButtonSprite(sf::Sprite buttonSprite) {
	this->buttonSprite = buttonSprite;
}

void BasicButton::setButtonWidth(float Width) {
	this->basicButtonShape.setSize(sf::Vector2f(Width, this->getButtonHeight()));
	
}

void BasicButton::setButtonHeight(float height) {
	this->basicButtonShape.setSize(sf::Vector2f(this->getButtonWidth(), height));
	
}

void BasicButton::setButtonPosition(float x, float y) {
	this->basicButtonShape.setPosition(x, y);
}

// ------------------ Getters ------------------
sf::Vector2f BasicButton::getButtonPosition() {
	return { this->basicButtonShape.getPosition().x, this->basicButtonShape.getPosition().y };
}

float BasicButton::getButtonWidth() {
	return this->basicButtonShape.getSize().x;
}

float BasicButton::getButtonHeight() {
	return this->basicButtonShape.getSize().y;
}

sf::RectangleShape& BasicButton::getButtonShape() {
	return this->basicButtonShape;
}

sf::Texture BasicButton::getButtonTexture() {
	return this->buttonTexture;
}

sf::Sprite BasicButton::getButtonSprite() {
	return this->buttonSprite;
}

sf::Vector2f BasicButton::getPoint(int index) {
	if (index < 0 || index >= 4	) {
		throw std::runtime_error("BasicButton: Index out of bound");
	}
	switch (index) {
		case 0:
			return this->basicButtonShape.getPoint(0)+this->basicButtonShape.getPosition();
		case 1:
			return this->basicButtonShape.getPoint(1)+this->basicButtonShape.getPosition();
		case 2:
			return this->basicButtonShape.getPoint(2)+this->basicButtonShape.getPosition();
		case 3:
			return this->basicButtonShape.getPoint(3)+this->basicButtonShape.getPosition();
	}
}

// ------------------ Actions ------------------
bool BasicButton::buttonOverlapsButton(BasicButton& otherButton) {
	if (this->basicButtonShape.getGlobalBounds().intersects(otherButton.basicButtonShape.getGlobalBounds())) {
		return true;
	} else {
		return false;
	}
}

//
//	- THis function could be generalised to check if a button is inside any shape. The shape could be a menu or any other shape. The function could be called buttonInsideShape and take a sf::Shape as parameter. This would make the function more general and reusable.
//

bool BasicButton::buttonInsideMenu(sf::RectangleShape shape) {
	sf::FloatRect buttonBounds = this->basicButtonShape.getGlobalBounds();
	sf::FloatRect menuBounds = shape.getGlobalBounds();

	return menuBounds.left <= buttonBounds.left &&
		menuBounds.top <= buttonBounds.top &&
		menuBounds.left + menuBounds.width >= buttonBounds.left + buttonBounds.width &&
		menuBounds.top + menuBounds.height >= buttonBounds.top + buttonBounds.height;
}

bool BasicButton::containsPoint(sf::Vector2i point) {
	if (this->getPoint(0).x <= point.x && point.x <= this->getPoint(1).x && 
		this->getPoint(0).y <= point.y && point.y <= this->getPoint(3).y) {

		return true;
	}
	return false;
}



bool BasicButton::pointInsideSprite(sf::Vector2i point) {
	// can be optimized as the convertion to img is very heavy but is alright since it is only done once 
	sf::Vector2f localPos = this->buttonSprite.getInverseTransform().transformPoint((sf::Vector2f)point);
	sf::IntRect rect = this->buttonSprite.getTextureRect();

	int x = static_cast<int>(localPos.x);
	int y = static_cast<int>(localPos.y);

	// if mouse is not even in the sprite then leave
	if (x < 0 || y < 0 || x >= rect.width || y >= rect.height) {
		return false;
	}

	// Konverter lokale coords 
	x += rect.left;
	y += rect.top;

	// convert texture to image 
	sf::Image img = this->buttonSprite.getTexture()->copyToImage();

	// look at the alpha value 
	if (img.getPixel(x, y).a > 0) {
		std::cout << "sprite pressed" << "\n";
		return true;
	}
	else {
		return false;
	}
}

void BasicButton::resizeButton(float sizeFactor) {
	this->basicButtonShape.setSize(sf::Vector2f(this->getButtonWidth() * sizeFactor, this->getButtonHeight() * sizeFactor));
}
