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
	
	// ------------------ Initialization ------------------
	virtual void initButton();
	virtual void initButton(BaseButton button);

    // ------------------ Setters ------------------
	
	void setToggleMenuStatus(bool status);
	void setDraggedStatus(bool status);
	// ------------------ Getters ------------------
	std::vector<BaseButton*>& getButtons();
	virtual sf::Vector2f getCenter();
	bool getToggleState();
	bool getDraggedStatus();

	// ------------------ Adders -------------------
	void addButton(BaseButton* button);
	// ------------------ Actions ------------------


    virtual bool containsPoint(sf::Vector2i point);

	virtual void toggleMenuStatus();
	void toggleDraggingIfPointContained(sf::Vector2i point);
	virtual void removeButton(BaseButton* button);
	virtual	void closeMenu();
	virtual	void openMenu();
	virtual void resizeMenu(float sizeFactor);
	virtual void calculateCenter();

	//void drawSubSpritePartitions(sf::RenderTarget& window);

private:
	// ------------------ Variables ------------------ 
	std::vector<BaseButton*> buttons;
	
	bool isDragged = false;
	bool isToggled = false;

	// ------------------ Initialization ------------------
	// ------------------ Setters ------------------
	// ------------------ Getters ------------------
	// ------------------ Actions ------------------
	

};



