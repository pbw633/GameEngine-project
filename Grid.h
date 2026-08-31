#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "Tile.h"	
#include "Organism.h"

class Grid{
public:
	Grid(int Rows, int Cols) {
		this->rows = Rows;
		this->cols = Cols;
		this->initGrid();
		this->initVariables();
	}
	Grid(){}

	// ----------------- Variables ---------------
	// ----------------- Initialize -------------
	void initVariables();
	void initGrid();

	// ----------------- Setters ----------------
	
	void setGridLocation(sf::Vector2f pos);
	void setGridWallStatus( bool wallStatus );

	// ----------------- Getters ----------------
	int getRowCount();
	int getColCount();
	Tile& getTile(int Row, int Col);
	sf::Vector2i getGridDim();
	std::vector<std::vector<Tile>>& getGrid();
	sf::VertexArray& getGridTriangles();
	sf::VertexArray& getGridLines();

	std::pair<int, int> getTileAtPosition(sf::Vector2i mousePos);
	std::pair<int, int> getCurrentDetectedTileCoordinates();
	// ----------------- Adders -----------------
	void addRow();
	void addCol();
	
	// ----------------- Actions ----------------
	void placeOrganism(int Row, int Col, Organism& organism);
	void loadGridFromFile(sf::String filename);
	void moveInDirection(sf::Vector2f direction); // this is frameDependen
	void moveInDirectionWithSpeed(float speed, sf::Vector2f unitDirVec); // this is made to make the movement of the grid frameIndependent
	void resize( float sizeFactor);
	
	// ------------------ update ----------------
	
	void updateHoveredTileBorder();
	void updateHoveredTileFill();
	void updatePreviousHoveredTile();
	void update(sf::Vector2i mousePos);

private:
	// ----------------- Variables ---------------
	int rows;
	int cols;
	sf::Transformable transform;
	sf::VertexArray gridTriangles;
	sf::VertexArray gridLines;
	std::vector<std::vector<Tile>> grid;
	
	std::pair<int, int> currentDetectedTileByMouse;
	std::pair<int, int> previousDetectedTileByMouse;
	float dirVecBuffer; 
	// ----------------- Initialize -------------
	// ----------------- Setters -----------------
	void setRows(int numRows);
	void setCols(int numCols);
	// ----------------- Getters ----------------
	// ----------------- Adders -----------------
	// ----------------- Actions ----------------

	// ----------------- Update ----------------
	void updateBoundingBoxes();
};

