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
class BaseMenu : UIComponent{
   

public:
    BaseMenu() {};
	
	// ------------------ Variables ------------------ 
	void initSubSpritePartitionByFraction( sf::Vector2f partitionX, sf::Vector2f partitionY ); // used to partition into 3 x 3
	
	// ------------------ Initialization ------------------
	

    // ------------------ Setters ------------------
	// ------------------ Getters ------------------
	std::vector<BaseButton*>& getButtons();
	virtual sf::Vector2f getCenter();

	// ------------------ Adders -------------------
	void addButton(BaseButton* button);
	// ------------------ Actions ------------------


    virtual bool containsPoint(sf::Vector2i point);

	virtual void removeButton(BaseButton* button);	
	virtual	void closeMenu();
	virtual	void openMenu();
	virtual void resizeMenu(float sizeFactor);
	virtual void calculateCenter();

	void showSubSpritePartition();

private:
	// ------------------ Variables ------------------ 
	std::vector<BaseButton*> buttons;
	
	std::vector<sf::FloatRect> subRects;
	std::vector<sf::Sprite> subSprites;
	

	// ------------------ Initialization ------------------
	// ------------------ Setters ------------------
	// ------------------ Getters ------------------
	// ------------------ Actions ------------------
	

};



