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


	//-------------------- Adders ----------------------
	

	//------------------ Setters ------------------
	
	
	
	//------------------ Getters ------------------
	bool getToggleState();

	//------------------ Actions ------------------
	bool isPressed(sf::Vector2i mousePos);
	void isToggled(sf::Vector2i mousePos);

	virtual bool containsPoint(sf::Vector2i point);
	//------------------ Variables ------------------

private:
	//------------------ Variables ------------------	
	bool togleState = false;
};

