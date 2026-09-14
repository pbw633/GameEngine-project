#pragma once
#include "baseMenu.h"
#include <iostream>
// ----------------- Initialization -----------------
/*
void BaseMenu::initSubSpritePartitionByFraction(sf::Vector2f partitionX, sf::Vector2f partitionY) {
	float minPartitionX = std::min(partitionX.x, partitionX.y);
	float minPartitionY = std::min(partitionY.x, partitionY.y);
	float maxPartitionX = std::max(partitionX.x, partitionX.y);	
	float maxPartitionY = std::max(partitionY.x, partitionY.y);	
	if (minPartitionX < 0.0f || minPartitionY < 0.0f || maxPartitionX > 1.0f || maxPartitionY > 1.0f) {
		throw std::invalid_argument("BaseMenu::initSubSpritePartitionByFraction:: Partition values must be between 0 and 1.");
	}
	if (this->getTexture().getSize().x == 0 || this->getTexture().getSize().y == 0) {
		throw std::runtime_error("BaseMenu::initSubSpritePartitionByFraction:: Texture not initialized. Please call initTexture() before calling this function.");
	}
	
	float width = this->getSpriteWidth();
	float height = this->getSpriteHeight();
	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 3; ++col) {
			float tempX = 0.0f;
			float tempY = 0.0f;
			float tempWidth = 0.0f;
			float tempHeight = 0.0f;
			// Calculate the position and size of each sub-rectangle
			if (row == 0) {
				tempY = 0.0f;
				tempHeight = minPartitionY * height;
			} else if (row == 1) {
				tempY = minPartitionY * height;
				tempHeight = (maxPartitionY - minPartitionY) * height;
			} else {
				tempY = maxPartitionY * height;
				tempHeight = (1.0f - maxPartitionY) * height;
			}

			if (col == 0) {
				tempX = 0.0f;
				tempWidth = minPartitionX * width;
			} else if (col == 1) {
				tempX = minPartitionX * width;
				tempWidth = (maxPartitionX - minPartitionX) * width;
			} else {
				tempX = maxPartitionX * width;
				tempWidth = (1.0f - maxPartitionX) * width;
			}

			sf::FloatRect subRect(tempX, tempY, tempWidth, tempHeight);
			this->subFrames.push_back(subRect);
		}
	}

}

void BaseMenu::initSubSpritePartitionComponents() {
	for (const auto& subFrame : this->subFrames) {
		sf::RectangleShape rectShape;
		rectShape.setPosition(subFrame.left, subFrame.top);
		rectShape.setSize(sf::Vector2f(subFrame.width, subFrame.height));
		rectShape.setFillColor(sf::Color(0, 0, 0, 0)); // Transparent fill
		rectShape.setOutlineColor(sf::Color::Red); // Red outline
		rectShape.setOutlineThickness(1.0f);
		spritePartitions.push_back(rectShape);
	}
}
*/
// ------------------- Getters -------------------
std::vector<BaseButton*>& BaseMenu::getButtons() {
	return this->buttons;
}

sf::Vector2f BaseMenu::getCenter() {
	return sf::Vector2f(0, 0); // Placeholder implementation, should be overridden in derived classes
}

// ------------------- Adders -------------------
void BaseMenu::addButton(BaseButton* button) {
	this->buttons.push_back(button);
}

// ------------------- Actions -------------------

bool BaseMenu::containsPoint(sf::Vector2i point) {
	return false; // Placeholder implementation, should be overridden in derived classes
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
/*
void BaseMenu::drawSubSpritePartitions(sf::RenderTarget& window) {
	for (const auto& rectShape : this->spritePartitions) {
		window.draw(rectShape);
	}
}
*/