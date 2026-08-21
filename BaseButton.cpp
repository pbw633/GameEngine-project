#include "BaseButton.h"

// ------------------- Adders -------------------


// ------------------ Setters ------------------

// ------------------ Getters ------------------

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

