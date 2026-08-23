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

class PolygonButton : BaseButton {
public:
	// ------------------ variables ------------------
	

	// ------------------Initialization------------------
	void initButtonShape(std::vector<sf::Vector2f> points);	

	// ----------------- Adders ------------------
	void addPoint(sf::Vector2f point);

	// ------------------ Setters ------------------	
	void setCenter(sf::Vector2f position);
	
	// ------------------ Getters ------------------
	sf::Vector2f getPoint(int index);
	sf::Vector2f getCenter();

	// ------------------ Actions ------------------
	void changePointAtIndex(sf::Vector2f point, int index);
	void removePoint(int index);
	bool containsPoint(sf::Vector2i point) override;
private:
	// ------------------ variables ------------------
	std::vector<sf::Vector2f> points;
	sf::Vector2f center;

	// ------------------ Actions ------------------
	void calculateCenter();
};