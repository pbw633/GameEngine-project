#pragma once
#include <vector>
#include <string>
#include <functional>
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
	virtual void initButtonMethod(std::function <void()> func, int index);
    // ------------------ Setters ------------------
	
	void setButtonMethod(std::function <void()> func, int index);

	void setToggleMenuStatus(bool status);
	void setDraggedStatus(bool status);
	// ------------------ Getters ------------------
	std::vector<std::unique_ptr<BaseButton>>& getButtons();
	virtual sf::Vector2f getCenter();
	bool getToggleState();
	bool getDraggedStatus();

	// ------------------ Adders -------------------
	void addButton(std::unique_ptr<BaseButton> button);
	// ------------------ Actions ------------------
	

    virtual bool containsPoint(sf::Vector2i point);
	virtual void isHovered(sf::Vector2i mousePos);

	virtual void toggleMenuStatus();
	void toggleDraggingIfPointContained(sf::Vector2i point);
	//virtual void removeButton(BaseButton* button);
	virtual	void closeMenu();
	virtual	void openMenu();
	virtual void resizeMenu(float sizeFactor);
	virtual void calculateCenter();
	virtual void handleButtonsPressed(sf::Vector2i mousePos);
	
	//void drawSubSpritePartitions(sf::RenderTarget& window);

private:
	// ------------------ Variables ------------------ 
	//std::vector<BaseButton> buttons;
	std::vector<std::unique_ptr<BaseButton>> buttons;

	bool isDragged = false;
	bool isToggled = false;

	// ------------------ Initialization ------------------
	// ------------------ Setters ------------------
	// ------------------ Getters ------------------
	// ------------------ Actions ------------------
	

};



