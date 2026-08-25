#pragma once
#include <iostream>
#include <vector>
#include <vector>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Item.h"
#include "Tile.h"
//This class is the lowest class which has an inventory and can not do anything else

class StorageContainer{
	
public:
	
	StorageContainer() {
		
	}
	// ---------------- Variables ----------------
	Tile* currerntPosition = nullptr;

	bool mouesInSpriteBool = false;
	std::vector<Item*> inventory; // bør ikke være en pointer. Test fejler muligvis.

	// ---------------- Initialization ----------------
	virtual void initVariables();

	void initTexture(std::string fileName);
	
	// ---------------- Setters ----------------
	// ---------------- Getters ----------------
	// ---------------- Actions ----------------

	void dropItem( int itemIndex );
	void addItem( Item* item );	
	void render(sf::RenderTarget& target);

	bool pointInSprite(sf::Vector2i mousePos);
	
	//---------------- Updaters ----------------	
	void updateSpriteLocationInTile();
	
protected:
//protected so it can be used in larger classes
	//--------------- Variables ---------------
	//Animation/sprites
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect currentFrame; // The rectangle of the picture

	sf::Clock moveTileTimer;
	sf::Clock animationTimer;

	float interTileTime = 1.f;

	int spriteIndexX = 0;
	int spriteIndexY = 0;
	int lastSpriteIndexX = 0;
	int lastSpriteIndexY = 0;

	// ---------------- Initialization ----------------
	void initTextureSheet(std::string fileName);
	virtual void initSprite();



	
};

