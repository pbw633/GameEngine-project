#pragma once
#include "StorageContainer.h"
#include "Tile.h"
#include "Heap.h"

class Game;
/*
TODO:
	-make pathDirection bidirectional
		-make the algorithm end early if each openSet find the same tile
*/
class Organism : public StorageContainer{
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

	// Position
	Tile* currerntPosition = nullptr; 
public:
	Organism() {};
	Organism(std::vector<std::vector<Tile>>* gameGrid) {
		grid = gameGrid; 
		rows = grid->size();
		cols = (*grid)[0].size();
	}

	//void initVariables() override;
	void initSprite() override; // interTileTimer is restarted here. it should when init the object 
	void initVariables() override;

	void setPosition( Tile* newPosition );
	void calculatePath( Tile* targetPosition );
	void updatePosition( );
	std::vector<Tile*> returnCalculatedPath();

	// Animations
	void rotateOrganism(sf::Vector2i mousePos);
	void updateMovement(int nextTileX, int nextTileY);
	void updateSprite();
	void updateSpriteLocation();

private:
	// For pathfinding

	bool runPathfinding = true;
	bool pathFindingComplete = false;
	std::vector<Tile*> closedSet;
	std::vector<Tile*> pathForOrganism;
	Min_heap sorter = Min_heap();

	int initialFrame = 0; // should be timeDEpendent and not frameDependent
	int usedMovementPoints = 0;
	int playerPosition;
	
	void resetPathfinding();

	// For position of sprite
	int interTileSprites = 10;
	sf::Clock interTileTimer;


	Tile* moveStart = nullptr;
	Tile* moveTarget = nullptr;

	float movementTimer = 0.f;
	float movementDuration = 2.f; // fx 250 ms per tile som i Fallout 1/2


	
};

