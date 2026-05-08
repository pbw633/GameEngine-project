#pragma once
#include "MenuButton.h"
#include <iostream>

Button::Button() {
	std::cout << "Button created" << std::endl;
}

Button::Button(sf::RectangleShape buttonShape) {
	this->buttonShape = buttonShape;
}

Button::Button(float x, float y, float width, float height) {
	this->buttonShape.setPosition(x, y);
	this->buttonShape.setSize(sf::Vector2f(width, height));
}

void Button::initButtonShape(float x, float y, float width, float height) {
	this->buttonShape.setPosition(x, y);
	this->buttonShape.setSize(sf::Vector2f(width, height));
}

void Button::initButtonShape(sf::RectangleShape buttonShape) {
	this->buttonShape = buttonShape;
}


void Button::placeButton(float x, float y) {
	this->buttonShape.setPosition(x, y);
}

void Button::mouseHoverOverButton(sf::Vector2i mousePos) {
	if (this->buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		
		this->buttonShape.setFillColor(sf::Color(200, 200, 200)); // Lighter color on hover
	}
	else {
		this->buttonShape.setFillColor(sf::Color(150, 150, 150)); // Default color
	}
}

void Button::buttonPressed(sf::Vector2i mousePos) {
	if (this->buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		this->buttonPressedBool = true;
		std::cout << "Button pressed!" << std::endl;
	}
	else {
		this->buttonPressedBool = false;
	}
}

bool Button::buttonOverlapsButton(Button& otherButton) {
	if (this->buttonShape.getGlobalBounds().intersects(otherButton.buttonShape.getGlobalBounds())) {
		std::cout << "Buttons overlap!" << std::endl;
		return true;
	} else {
		return false;
	}
}

bool Button::buttonInsideMenu(sf::RectangleShape shape) {
	if (shape.getPoint(0).x < this->buttonShape.getPoint(0).x && 
		shape.getPoint(0).y < this->buttonShape.getPoint(0).y && 
		shape.getPoint(2).x > this->buttonShape.getPoint(2).x &&
		shape.getPoint(2).y > this->buttonShape.getPoint(2).y) {

		return true;
	} else {

		return false;
	}
}

// ------------------ getters ------------------	
sf::RectangleShape Button::getButtonShape() {
	return this->buttonShape;
}

sf::Text Button::getButtonText() {
	return this->buttonText;
}

sf::Texture Button::getButtonTexture() {
	return this->buttonTexture;
}

sf::Sprite Button::getButtonSprite() {
	return this->buttonSprite;
}

// ------------------ setters ------------------
void Button::setButtonShape( sf::RectangleShape buttonShape ) {
	this->buttonShape = buttonShape;
}

void Button::setButtonText( sf::Text buttonText ) {
	this->buttonText = buttonText;
}

void Button::setButtonTexture( sf::Texture buttonTexture ) {
	this->buttonTexture = buttonTexture;
}

void Button::setButtonSprite( sf::Sprite buttonSprite ) {
	this->buttonSprite = buttonSprite;
}