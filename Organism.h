#pragma once
#include "StorageContainer.h"

#include "Heap.h"

class Game;
/*
TODO:
	-make pathDirection bidirectional
		-make the algorithm end early if each openSet find the same tile
	- It shoulld be enough just to pass the initial tile for the organism to be placed on.
*/
class Organism : public StorageContainer{
	// Variables
	bool moving = false;

	// Basic stats
	int Health = 1;
	int attackDamage = 1;
	int defence = 0;
	int movementPoints = 20;

	//GameGrid
	std::vector<std::vector<Tile>>* grid = nullptr;
	int rows;
	int cols;

	
public:
	Organism() {};
	Organism(std::vector<std::vector<Tile>>* gameGrid) {
		// TODO: are not necessary. just pass the initial tile for the organism to be placed on.
		grid = gameGrid; 
		rows = grid->size();
		cols = (*grid)[0].size();
	}

	//---------------- Initialize ----------------
	void initSprite() override; // interTileTimer is restarted here. it should when init the object 
	void initVariables() override;

	//---------------- Setters ----------------
	void setPosition( Tile* newPosition );

	//---------------- Getters ----------------
	std::vector<Tile*> getCalculatedPath();
	
	// ---------------- Actions ----------------
	// Animations
	void rotateOrganism(sf::Vector2i mousePos);
	void calculatePath( Tile* targetPosition );
	
	
	
	// ---------------- Updaters ----------------
	// Animations
	void updatePosition();
	void updateMovement(int nextTileX, int nextTileY);
	void updateSprite();
	void updateSpriteLocation(); // rename to update sprite location walking
	

private:
	//---------------- Variables ----------------
	// For pathfinding
	bool runPathfinding = true;
	bool pathFindingComplete = false;
	std::vector<Tile*> closedSet;
	std::vector<Tile*> pathForOrganism;
	Min_heap sorter = Min_heap();

	//Animation
	int initialFrame = 0; // should be timeDEpendent and not frameDependent
	int usedMovementPoints = 0;
	int playerPosition;
	
	

	// For position of sprite
	int interTileSprites = 10;
	sf::Clock interTileTimer;

	// Movement
	Tile* moveStart = nullptr;
	Tile* moveTarget = nullptr;

	float movementTimer = 0.f;
	float movementDuration = 2.f; // fx 250 ms per tile som i Fallout 1/2

	// ---------------- Helper methods ----------------
	void resetPathfinding();


	
};

