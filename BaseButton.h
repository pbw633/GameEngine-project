#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "UIComponent.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
// This class is the base class for all buttons. It is used to define the basic properties of a button such as position, size, and shape. 
// It is not meant to be used directly, but rather to be inherited by other button classes that will implement specific functionality.
// Just by redefining the containsPoint function you can make a button of any shape. The button will then be able to detect if the mouse is over it or not.
class BaseButton : public UIComponent 
{
public:
	//------------------ Initialization ------------------
	void initFont(std::string fontLocation);
	void initText(std::string buttonText);
	void initTextSize(int textSize);
	void initTextColor(sf::Color color);
	void initTextPosition(sf::Vector2f position);
	//-------------------- Adders ----------------------
	

	//------------------ Setters ------------------
	void setButtonMethod(std::function <void()> method);

	virtual void setPosition(sf::Vector2f position);

	void setText(std::string buttonText);
	void setTextSize(int textSize);
	void setTextColor(sf::Color color);
	void setTextPosition(sf::Vector2f position);
	
	virtual void setSize(sf::Vector2f dim);
	//------------------ Getters ------------------
	sf::Text& getText();
	int getTextSize();
	sf::Color getTextColor();
	sf::Vector2f getTextPosition();
	
	virtual sf::Vector2f getSize();


	bool getToggleState();


	//------------------ Actions ------------------
	virtual void isHovered(sf::Vector2i mousePos);
	bool isPressed(sf::Vector2i mousePos);
	void isToggled(sf::Vector2i mousePos);

	void executeButtonMethod();

	virtual bool containsPoint(sf::Vector2i point);

	virtual void draw(sf::RenderTarget& window);
	//------------------ Variables ------------------

private:
	//------------------ Variables ------------------
	sf::Font font;
	sf::Text buttonText;
	bool togleState = false;

	//------------------- Actions ---------------------
	std::function <void()> buttonMethod;

	
};

