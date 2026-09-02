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
	BasicButton(){}

	BasicButton( float x, float y, float width, float height ) {
		initButtonShape( x, y, width, height);
	}

	BasicButton(sf::RectangleShape buttonShape) {
		initButtonShape( buttonShape );
	}


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

	void setButtonWidth(float Width);
	void setButtonHeight(float height);


	// ------------------ Getters ------------------
	float getButtonWidth();
	float getButtonHeight();
	sf::Vector2f getButtonPosition();
	sf::RectangleShape& getButtonShape();
	sf::Vector2f getPoint(int index);

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


	
};