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

class BasicButton : public BaseButton {
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
	void initButtonByText(float x, float y, std::string text);
	void initButtonShape(float x, float y, float width, float height);
	void initButtonShape(sf::RectangleShape buttonShape);

	


	// ------------------ Setters ------------------
	void setButtonShape(sf::RectangleShape buttonShape);
	void setButtonText(sf::Text buttonText);
	void setButtonTexture(sf::Texture buttonTexture);
	void setButtonSprite(sf::Sprite buttonSprite);

	//void setButtonPosition(float x, float y);
	void setPosition(sf::Vector2f position) override;
	void setButtonWidth(float Width);
	void setButtonHeight(float height);
	void setSize(sf::Vector2f dim) override;

	// ------------------ Getters ------------------
	sf::Vector2f getSize() override;
	
	float getButtonWidth();
	float getButtonHeight();
	sf::Vector2f getButtonPosition();
	sf::RectangleShape& getButtonShape();
	sf::Vector2f getPoint(int index);

	sf::Texture getButtonTexture();
	sf::Sprite getButtonSprite();

	// ------------------ Actions ------------------
	void isHovered(sf::Vector2i mousePos) override;

	bool buttonOverlapsButton(BasicButton& otherButton);
	bool buttonInsideMenu(sf::RectangleShape shape);
	bool containsPoint(sf::Vector2i point) override;

	bool pointInsideSprite(sf::Vector2i point);

	void resizeButton(float sizeFactor);

	void draw(sf::RenderTarget& window) override;

private:
	// ------------------ variables ------------------
	//std::vector<sf::Vector2f> points;

	sf::RectangleShape basicButtonShape;
	//sf::Text buttonText;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;


	
};