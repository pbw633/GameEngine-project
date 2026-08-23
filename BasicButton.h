#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "BaseButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class BasicButton : BaseButton {
public:

	// ------------------ variables ------------------
	bool buttonPressedBool = false;

	//------------------Initialization------------------
	void initButtonShape(float x, float y, float width, float height);
	void initButtonShape(sf::RectangleShape buttonShape);



	// ------------------ Setters ------------------
	void setButtonShape(sf::RectangleShape buttonShape);
	void setButtonText(sf::Text buttonText);
	void setButtonTexture(sf::Texture buttonTexture);
	void setButtonSprite(sf::Sprite buttonSprite);

	void setButtonPosition(float x, float y);

	void setButtonLength(float length);
	void setButtonHeight(float height);


	// ------------------ Getters ------------------
	float getButtonLength();
	float getButtonHeight();
	sf::Vector2f getButtonPosition();
	sf::Texture getButtonTexture();
	sf::Sprite getButtonSprite();

	// ------------------ Actions ------------------
	bool buttonOverlapsButton(BasicButton& otherButton);
	bool buttonInsideMenu(sf::RectangleShape shape);
	bool containsPoint(sf::Vector2i point) override;

	bool pointInsideSprite(sf::Vector2i point);

	void resizeButton(float sizeFactor);

private:
	// ------------------ variables ------------------
	//std::vector<sf::Vector2f> points;

	sf::RectangleShape basicButtonShape;
	sf::Text buttonText;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;
	float buttonLength;
	float buttonHeight;

	
};