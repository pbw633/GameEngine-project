#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//TODO
// 1. Try to use templates to make this class more generic and compact so there is no need for overloading maybe
// 2. base is tthe button is a square but the button should be able to be any shape. Maybe use a vector of points to define the shape of the button.


class BaseButton{
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

	void setButtonPosition(float x, float y);

	// ------------------ Getters ------------------
	std::vector	<float, float> getButtonPosition();
	float getButtonLength();
	float getButtonHeight();
	sf::Texture getButtonTexture();	
	sf::Sprite getButtonSprite();

	// ------------------ Actions ------------------
	bool buttonOverlapsButton(BaseButton& otherButton);	
	bool buttonInsideMenu(sf::RectangleShape shape);


private:
	// ------------------ variables ------------------
	sf::RectangleShape buttonShape;
	sf::Text buttonText;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;
	float buttonLength;	
	float buttonHeight;

};

