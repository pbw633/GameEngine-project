#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
// This class is the base class for all buttons. It is used to define the basic properties of a button such as position, size, and shape. 
// It is not meant to be used directly, but rather to be inherited by other button classes that will implement specific functionality.
// Just by redefining the containsPoint function you can make a button of any shape. The button will then be able to detect if the mouse is over it or not.
class BaseButton{
public:
	//------------------ Initialization ------------------
	void initFont(std::string fontLocation);
	void initText(std::string buttonText);
	void initTextSize(int textSize);
	void initTextColor(sf::Color color);
	void initTextPosition(sf::Vector2f position);
	//-------------------- Adders ----------------------
	

	//------------------ Setters ------------------
	void setButtonMethod(std::is_function <void()> method);

	void setText(std::string buttonText);
	void setTextSize(int textSize);
	void setTextColor(sf::Color color);
	void setTextPosition(sf::Vector2f position);
	
	//------------------ Getters ------------------
	std::string getText();
	int getTextSize();
	sf::Color getTextColor();
	sf::Vector2f getTextPosition();
	
	bool getToggleState();


	//------------------ Actions ------------------
	bool isPressed(sf::Vector2i mousePos);
	void isToggled(sf::Vector2i mousePos);

	virtual bool containsPoint(sf::Vector2i point);
	//------------------ Variables ------------------

private:
	//------------------ Variables ------------------
	sf::Font font;
	sf::Text buttonText;
	bool togleState = false;

	//------------------- Actions ---------------------
	std::is_function <void()> buttonMethod;
};

