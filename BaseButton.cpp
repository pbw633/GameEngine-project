#include "BaseButton.h"
// ------------------- Initialization --------------
void BaseButton::initFont( std::string fileLocation ) {
	this->font.loadFromFile(fileLocation);
	this->buttonText.setFont(font);
	
}


void BaseButton::initText(std::string buttonText) {
	this->buttonText.setString(buttonText);
}

void BaseButton::initTextSize(int textSize) {
	if (textSize <= 0) {
		throw std::runtime_error("BaseButton::initTextSize:: TextSize cannot be less than 1");
	}

	this->buttonText.setCharacterSize(textSize);
}

void BaseButton::initTextColor(sf::Color color) {
	this->buttonText.setFillColor(color);
}

void BaseButton::initTextPosition(sf::Vector2f position) {
	this->buttonText.setPosition(position);
}


// ------------------- Adders -------------------


// ------------------ Setters ------------------
void BaseButton::setButtonMethod(std::is_function <void()> method) {
	this->buttonMethod = method;
}


void BaseButton::setText(std::string buttonText) {
	this->buttonText.setString(buttonText);
}

void BaseButton::setTextSize(int textSize) {
	if (textSize <= 0) {
		throw std::runtime_error("BaseButton::initTextSize:: TextSize cannot be less than 1");
	}

	this->buttonText.setCharacterSize(textSize);
}

void BaseButton::setTextColor(sf::Color color) {
	this->buttonText.setFillColor( color );
}

void BaseButton::setTextPosition(sf::Vector2f position) {
	this->buttonText.setPosition(position);
}

// ------------------ Getters ------------------
std::string BaseButton::getText() {
	return this->buttonText.getString();
}
int BaseButton::getTextSize() {
	return this->getTextSize();
}
sf::Color BaseButton::getTextColor() {
	return this->buttonText.getFillColor();
}
sf::Vector2f BaseButton::getTextPosition() {
	return this->buttonText.getPosition();
}


bool BaseButton::getToggleState() {
	return togleState;
}

// ------------------ Actions ------------------
bool BaseButton::isPressed(sf::Vector2i mousePos) {
	return containsPoint(mousePos);
}

void BaseButton::isToggled(sf::Vector2i mousePos) {
	if (containsPoint(mousePos)) {
		togleState = !togleState;
	}
}

bool BaseButton::containsPoint(sf::Vector2i point) {
	return false; // Placeholder implementation, should be overridden in derived classes
}

