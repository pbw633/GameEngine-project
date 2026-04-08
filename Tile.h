#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <iostream>  
//#include "Game.h"

/*
TODO:
	- Make a global list of point we can pick from to create a tile instead of calculate the same point up to 3 times
*/

// Forward declaration of Game class so that i can use the class here
class Game;
class Organism;

class Tile {
private:
	double PI = 3.14159265; // just PI
	void initBoundingBoxIndex();
	sf::Text coordinateText;

public:// i need to access position, Neighbors, wall or not
	//variables for construction
	double midx = 100; //should be called offset
	double midy = 100; //should be called offset
	double r_1 = 15;
	double r_2 = 9;
	double radius;
	double angle = 0;
	double construcangle = 18;
	double sx;
	double sy;

	std::vector<sf::Vector2f> points;
	std::vector<int> boundingBoxIndex;

	//placement of the tile 
	int xRow;
	int yRow;
	double displace = 0;

	//Variables for pathFinding
	float f = 0.f;
	float g = 0.f;
	float h = 0.f;

	std::vector<Tile*> neighbors; //The neighbors to the tile. Used for pathfinding (might cause trouble with neighbors) why not just a normal vector of tiles and then pass by reference?
	Tile* previous = NULL;

	bool wall = false;
	
	bool occupiedByOrganism = false; 
	
	Organism* organismInTile = nullptr;

	// Interaction
	bool mouseIsInTile = false;
	bool mousePressedTile = false;

	//hexagon shape
	sf::ConvexShape hexagon;

	
	Tile(int x, int y) {
		xRow = x;
		yRow = y;
		
		// Second row has to be displaced
		if (xRow % 2 == 0) {
			displace = r_1 * cos(PI * 18 / 180.0);
		}
		//placement of the middle of the hexagon compared to its coordinate in grid
		midx = midx + displace + yRow * 2 * r_1*cos(PI*construcangle / 180); 
		midy = midy + xRow * (r_1 * 2 * sin(PI*construcangle / 180) + (r_2 - cos(PI*(90 - construcangle) / 180)*r_1));

		if ((rand() % 100) + 1 < 30) {
			wall = true;
		}
	}
	Tile() {}// just for overloading

	//------------- initialize ---------------
	void initializeTileShape(int x, int y, int z);
	void initializeNeighbors(int i, int j ,Game& game);
	void initializeNeighbors(int i, int j, std::vector<std::vector<Tile>>& grid);
	void initializeText();
	
	//------------- get Information ----------
	sf::Vector2f getPoint(size_t i);
	sf::Vector2f getCenter();
	sf::Color getFillColor();

	// get coordinates of bounding box
	float getBoundingBoxMinX();
	float getBoundingBoxMinY();
	float getBoundingBoxMaxX();
	float getBoundingBoxMaxY();

	//------------- Update --------------
	void moveTile( sf::Vector2f direction );
	void isMouseInTile( sf::Vector2i& mousePos );
	void isMousePressedInTile( sf::Vector2i& mousePos );
	void placeOrganismInTile( Organism& organism );
	
	//------------- Render -----------------
	void display( sf::RenderWindow&, int x, int y, int z );

	bool operator==(const Tile& otherTile);

	//----------- Debugging -------------
	void displayGridCoordinates(bool activateDebugMode);


};

