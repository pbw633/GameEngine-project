#pragma once
#include "baseMenu.h"
#include <iostream>
// ----------------- Initialization -----------------

// ------------------- Setters --------------------
void BaseMenu::setToggleMenuStatus(bool status) {
	this->isToggled = status;
}
// ------------------- Getters -------------------
std::vector<BaseButton*>& BaseMenu::getButtons() {
	return this->buttons;
}

sf::Vector2f BaseMenu::getCenter() {
	return sf::Vector2f(0, 0); // Placeholder implementation, should be overridden in derived classes
}

bool BaseMenu::getToggleState() {
	return this->isToggled;
}

// ------------------- Adders -------------------
void BaseMenu::addButton(BaseButton* button) {
	this->buttons.push_back(button);
}

// ------------------- Actions -------------------

bool BaseMenu::containsPoint(sf::Vector2i point) {
	return false; // Placeholder implementation, should be overridden in derived classes
}

void BaseMenu::toggleMenuStatus() {
	this->setToggleMenuStatus(!(this->getToggleState()));
}

void BaseMenu::removeButton(BaseButton* button) {
	auto it = std::find(this->buttons.begin(), this->buttons.end(), button);
	if (it != this->buttons.end()) {
		this->buttons.erase(it);
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
