#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "UIComponent.h"
#include "BasicButton.h"
#include "PolygonButton.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class BaseMenu {
   

public:
    BaseMenu() {};
	
	// ------------------ Variables ------------------ 
	//void initSubSpritePartitionByFraction( sf::Vector2f partitionX, sf::Vector2f partitionY ); // used to partition into 3 x 3
	//void initSubSpritePartitionComponents();
	// ------------------ Initialization ------------------
	

    // ------------------ Setters ------------------
	// ------------------ Getters ------------------
	std::vector<BaseButton*>& getButtons();
	virtual sf::Vector2f getCenter();

	//sf::Texture& getTexture();
	//sf::Sprite& getSprite();

	// ------------------ Adders -------------------
	void addButton(BaseButton* button);
	// ------------------ Actions ------------------


    virtual bool containsPoint(sf::Vector2i point);

	virtual void removeButton(BaseButton* button);	
	virtual	void closeMenu();
	virtual	void openMenu();
	virtual void resizeMenu(float sizeFactor);
	virtual void calculateCenter();

	//void drawSubSpritePartitions(sf::RenderTarget& window);

private:
	// ------------------ Variables ------------------ 
	std::vector<BaseButton*> buttons;
	
	

	// ------------------ Initialization ------------------
	// ------------------ Setters ------------------
	// ------------------ Getters ------------------
	// ------------------ Actions ------------------
	

};



