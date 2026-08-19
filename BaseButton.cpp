#include "BaseButton.h"
// ------------------ Initialization ------------------	
void BaseButton::initButtonShape(float x, float y, float width, float height) {
	this->buttonShape.setPosition(x, y);
	this->buttonShape.setSize(sf::Vector2f(width, height));
}

void BaseButton::initButtonShape(sf::RectangleShape buttonShape) {
	this->buttonShape = buttonShape;
}

// ------------------ Setters ------------------
void BaseButton::setButtonShape(sf::RectangleShape buttonShape) {
	this->buttonShape = buttonShape;
}

void BaseButton::setButtonText(sf::Text buttonText) {
	this->buttonText = buttonText;
}

void BaseButton::setButtonTexture(sf::Texture buttonTexture) {
	this->buttonTexture = buttonTexture;
}

void BaseButton::setButtonSprite(sf::Sprite buttonSprite) {
	this->buttonSprite = buttonSprite;
}

void BaseButton::setButtonLength(float length) {
	this->buttonLength = length;
}

void BaseButton::setButtonHeight(float height) {
	this->buttonHeight = height;
}

void BaseButton::setButtonPosition(float x, float y) {
	this->buttonShape.setPosition(x, y);
}

// ------------------ Getters ------------------
std::vector<float, float> BaseButton::getButtonPosition() {
	return { this->buttonShape.getPosition().x, this->buttonShape.getPosition().y };
}

float BaseButton::getButtonLength() {
	return this->buttonLength;
}

float BaseButton::getButtonHeight() {
	return this->buttonHeight;
}

sf::Texture BaseButton::getButtonTexture() {
	return this->buttonTexture;
}

sf::Sprite BaseButton::getButtonSprite() {
	return this->buttonSprite;
}

// ------------------ Actions ------------------
bool BaseButton::buttonOverlapsButton(BaseButton& otherButton) {
	if (this->buttonShape.getGlobalBounds().intersects(otherButton.buttonShape.getGlobalBounds())) {
		return true;
	} else {
		return false;
	}
}

//
//	- THis function could be generalised to check if a button is inside any shape. The shape could be a menu or any other shape. The function could be called buttonInsideShape and take a sf::Shape as parameter. This would make the function more general and reusable.
//

bool BaseButton::buttonInsideMenu(sf::RectangleShape shape) {
	if (shape.getPoint(0).x < this->buttonShape.getPoint(0).x &&
		shape.getPoint(0).y < this->buttonShape.getPoint(0).y &&
		shape.getPoint(2).x > this->buttonShape.getPoint(2).x &&
		shape.getPoint(2).y > this->buttonShape.getPoint(2).y) {
		
		return true;
	} else {
		return false;
	}
}

bool BaseButton::pointInsideButton(sf::Vector2i point) {
	if (this->buttonShape.getGlobalBounds().contains(point.x, point.y)) {
		return true;
	} else {
		return false;
	}
}

bool BaseButton::pointInsideSprite(sf::Vector2i point) {
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
