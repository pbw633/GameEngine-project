#pragma once
#include "baseMenu.h"
#include <iostream>
// ----------------- Initialization -----------------
void BaseMenu::initButton() { // placeholder

}

void BaseMenu::initButton(BaseButton button) { // placeholder

}

// ------------------- Setters --------------------
void BaseMenu::setToggleMenuStatus(bool status) {
	this->isToggled = status;
}

void BaseMenu::setDraggedStatus(bool status) {
	this->isDragged = status;
}

// ------------------- Getters -------------------
std::vector<std::unique_ptr<BaseButton>>& BaseMenu::getButtons() {
	return this->buttons;
}

sf::Vector2f BaseMenu::getCenter() {
	return sf::Vector2f(0, 0); // Placeholder implementation, should be overridden in derived classes
}

bool BaseMenu::getToggleState() {
	return this->isToggled;
}

bool BaseMenu::getDraggedStatus() {
	return this->isDragged;
}
// ------------------- Adders -------------------
void BaseMenu::addButton(std::unique_ptr<BaseButton> button) {
	// std::move moves the ownership from where it is currently to the new place it is moved to aka the vector
	this->buttons.push_back(std::move(button));
}

// ------------------- Actions -------------------

bool BaseMenu::containsPoint(sf::Vector2i point) {
	return false; // Placeholder implementation, should be overridden in derived classes
}

void BaseMenu::toggleMenuStatus() {
	this->setToggleMenuStatus(!(this->getToggleState()));
}
void BaseMenu::toggleDraggingIfPointContained(sf::Vector2i point) {
	if (this->containsPoint(point)) {
		isDragged = true;
	} else {
		isDragged = false;
	}

}

void BaseMenu::closeMenu() {
	// Placeholder implementation, should be overridden in derived classes
}

void BaseMenu::openMenu() {
	// Placeholder implementation, should be overridden in derived classes
}
void BaseMenu::resizeMenu(float sizeFactor) {
	// Placeholder implementation, should be overridden in derived classes
}	

void BaseMenu::calculateCenter() {
	// Placeholder implementation, should be overridden in derived classes
}


