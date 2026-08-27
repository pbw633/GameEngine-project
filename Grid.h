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
	}

	// ----------------- Variables ---------------
	// ----------------- Initialize -------------
	void initGrid();

	// ----------------- Setters ----------------
	
	void setGridLocation(sf::Vector2f pos);

	// ----------------- Getters ----------------
	int getRowCount();
	int getColCount();
	Tile getTile(int Row, int Col);
	sf::Vector2i getGridDim();
	std::vector<std::vector<Tile>> getGrid();
	// ----------------- Adders -----------------
	void addRow();
	void addCol();
	
	// ----------------- Actions ----------------
	void placeOrganism(int Row, int Col, Organism& organism);
	void loadGridFromFile(sf::String filename);
	void moveInDirection(sf::Vector2f direction);
	// ------------------ update ----------------
	
	void update();

private:
	// ----------------- Variables ---------------
	int rows;
	int cols;
	sf::Transformable transform;
	sf::VertexArray gridTriangles;
	sf::VertexArray gridLines;
	std::vector<std::vector<Tile>> grid;
	
	// ----------------- Initialize -------------
	// ----------------- Setters -----------------
	void setRows(int numRows);
	void setCols(int numCols);
	// ----------------- Getters ----------------
	// ----------------- Adders -----------------
	// ----------------- Actions ----------------
};

