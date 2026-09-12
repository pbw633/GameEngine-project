#pragma once
#include "baseMenu.h"
#include "BasicButton.h"
#include "PolygonButton.h"
class BasicMenu : public BaseMenu
{
public:
	BasicMenu() {};

	//~BasicMenu();

	// ------------------ Variables ------------------

	// ------------------ Initialization ------------------
	void initBasicMenuByRectangleShape(sf::Vector2f position, float width, float height);	
	void initBasicMenuByTexture(std::string textureFileName);
	// ------------------ Setters ------------------

	void setMenuPosition(sf::Vector2f position	);

	// ------------------ Getters ------------------
	sf::RectangleShape& getMenuShape();
	//sf::Vector2f getMenuPosition();
	float getWidth();
	float getHeight();

	sf::Vector2f getPoint(int index);
	sf::Vector2f getCenter() override;
	

	// ------------------ Adders -------------------


	// ------------------ Actions ------------------
	void calculateCenter() override;

private:
	// ------------------ Variables ------------------
	sf::RectangleShape menuShape;
	sf::Vector2f center;

	// ------------------ Initialization ------------------

	// ------------------ Setters ------------------

	// ------------------ Getters ------------------

	// ------------------ Adders -------------------

	// ------------------ Actions ------------------
	
};