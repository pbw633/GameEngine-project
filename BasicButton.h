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
//TODO
// 1. Try to use templates to make this class more generic and compact so there is no need for overloading maybe
// 2. base is the button is a square but the button should be able to be any shape. Maybe use a vector of points to define the shape of the button.
//		- methods should later be changed to use the shape of the button instead of the rectangle shape. This would make the button more flexible and allow for more complex shapes.
//		- If that is the case then this should be child and this class could be named "basicButton"


class BasicButton : public BaseButton {
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


	void setButtonLength(float length);
	void setButtonHeight(float height);


	// ------------------ Getters ------------------
	float getButtonLength();
	float getButtonHeight();
	sf::Texture getButtonTexture();
	sf::Sprite getButtonSprite();

	// ------------------ Actions ------------------
	bool buttonOverlapsButton(BasicButton& otherButton);
	bool buttonInsideMenu(sf::RectangleShape shape);
	bool pointInsideButton(sf::Vector2i point);
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