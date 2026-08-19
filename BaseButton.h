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
class BaseButton{
public:
	//------------------ Initialization ------------------

	//------------------ Setters ------------------

	
	void setPosition(sf::Vector2i newPosition);
	//------------------ Getters ------------------
	sf::Vector2i getPosition();

	//------------------ Actions ------------------
private:
	sf::Vector2i position;

};

