#include "BaseButton.h"
// ------------------- Initialization --------------
void BaseButton::initFont( std::string fileLocation ) {
	if (!this->font.loadFromFile(fileLocation)) {
		throw std::runtime_error("BaseButton::initFont:: Font did not load");
	}
	this->buttonText.setFont(font);
	
}


void BaseButton::initText(std::string buttonText) {
	this->buttonText.setString(buttonText);
	//this->buttonText.set
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
void BaseButton::setButtonMethod(std::function <void()> method) {
	this->buttonMethod = std::move(method);
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

void BaseButton::setPosition(sf::Vector2f position) {
	// placeholder
}

void BaseButton::setSize(sf::Vector2f dim) {
	// placeholder;
}


// ------------------ Getters ------------------
sf::Text& BaseButton::getText() {
	return this->buttonText;
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

sf::Vector2f BaseButton::getSize() {
	return sf::Vector2f(0, 0);
}

// ------------------ Actions ------------------

void BaseButton::isHovered(sf::Vector2i	mousePos) {
	//placeholder 
}


bool BaseButton::isPressed(sf::Vector2i mousePos) {
	return containsPoint(mousePos);
}

void BaseButton::isToggled(sf::Vector2i mousePos) {
	if (containsPoint(mousePos)) {
		togleState = !togleState;
	}
}

void BaseButton::executeButtonMethod() {
	// If buttonMethod exists then use it
	if (this->buttonMethod) {
		this->buttonMethod();
	}
}

bool BaseButton::containsPoint(sf::Vector2i point) {
	return false; // Placeholder implementation, should be overridden in derived classes
}

void BaseButton::draw(sf::RenderTarget& window) {
	std::cout << "BaseButton draw" << "\n";
	// Placehodler
}