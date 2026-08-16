/*
#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "baseMenu.h"

class Button{
public:
	bool buttonPressedBool = false;	

	sf::RectangleShape buttonShape;
	sf::Text buttonText;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	Button();
	Button(sf::RectangleShape buttonShape);
	Button(float x, float y, float width, float height);
	

	void initButtonShape(float x, float y, float width, float height);
	void initButtonShape(sf::RectangleShape buttonShape);

	void placeButton( float x, float y );	

	void mouseHoverOverButton(sf::Vector2i mousePos);
	void buttonPressed(sf::Vector2i);

	bool buttonOverlapsButton(Button& otherButton);
	bool buttonInsideMenu(sf::RectangleShape shape);
	bool buttonInsideMenu(baseMenu& menu);

	// ------------------ getters ------------------
	sf::RectangleShape getButtonShape();
	sf::Text getButtonText();
	sf::Texture getButtonTexture();
	sf::Sprite getButtonSprite();

	// ------------------ setters ------------------
	void setButtonShape(sf::RectangleShape buttonShape);
	void setButtonText(sf::Text buttonText);
	void setButtonTexture(sf::Texture buttonTexture);
	void setButtonSprite(sf::Sprite buttonSprite);
private:

};

*/