#pragma once
#include <iostream>
#include <vector>
#include <vector>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Item.h"
//This class is the lowest class which has an inventory and can not do anything else

class StorageContainer{
	
public:
	bool mouesInSpriteBool = false;
	
	std::vector<Item*> inventory; // bør ikke være en pointer. Test fejler muligvis.
	

	StorageContainer() {
		
	}

	// Defining functions
	void dropItem( int itemIndex );
	void addItem( Item* item );

	// initialization
	virtual void initVariables();

	// Animation/sprites
	void initTexture(std::string fileName);
	void render(sf::RenderTarget& target);

	// Core
	bool mouseInSprite(sf::Vector2i mousePos);
	
	void update();
	
protected:
//protected so it can be used in larger classes
	//Animation/sprites
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect currentFrame; // The rectangle of the picture we use

	sf::Clock moveTileTimer;
	//sf::Clock interTileTimer;
	sf::Clock animationTimer;

	float interTileTime = 1.f;

	int spriteIndexX = 0;
	int spriteIndexY = 0;
	int lastSpriteIndexX = 0;
	int lastSpriteIndexY = 0;

	void initTextureSheet(std::string fileName);
	virtual void initSprite();

	
};

