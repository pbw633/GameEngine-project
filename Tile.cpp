#include "Tile.h"
#include "Game.h"
#include "Organism.h"
#include <cassert>
#include <SFML/Graphics.hpp>

void Tile::initializeTileShape(int x, int y, int z) {
	/*
	creates the hexagon
	*/
	this->hexagon.setPointCount(6);
	this->hexagon.setFillColor(sf::Color(x, y, z));

	for (int k = 0; k < 6; k++) {
		if (k == 0) {
			angle = PI * construcangle / 180.0;
			radius = r_1;
		}
		else if (k == 1) {
			angle = angle + (PI * (90 - construcangle) / 180);
			radius = r_2;
		}
		else if (k == 2) {
			angle = angle + ((PI * (90 - construcangle)) / 180.0);
			radius = r_1;
		}
		else if (k == 3) {
			angle = angle + (PI * (construcangle * 2) / 180.0);
			radius = r_1;
		}
		else if (k == 4) {
			angle = angle + (PI * (90 - construcangle) / 180.0);
			radius = r_2;
		}
		else if (k == 5) {
			angle = angle + (PI * (90 - construcangle) / 180.0);
			radius = r_1;
		}

		sx = midx + cos(angle) * radius;
		sy = midy + sin(angle) * radius;
		points.emplace_back(sf::Vector2f(sx,sy)); // this is for the new version of the grid 

		this->hexagon.setPoint(k, sf::Vector2f(float(sx), float(sy)));
	}
	this->hexagon.setOutlineColor(sf::Color::Blue); //sets color of outline
	this->hexagon.setOutlineThickness(1.f); //sets the thickness 

	this->initBoundingBoxIndex();
}

void Tile::initBoundingBoxIndex() {
	// find the indexes of the figure which then is the same always unless something wrong happens
	std::vector<int> tempIndexValues = { 0,0,0,0 };
	
	for (int i = 0; i < 6; i++) {
		if (this->getPoint(i).x < this->getPoint(tempIndexValues[0]).x ) { // min X
			tempIndexValues[0] = i;
		}
		if (this->getPoint(i).y < this->getPoint(tempIndexValues[1]).y) { // min Y
			tempIndexValues[1] = i;
		}
		if (this->getPoint(i).x > this->getPoint(tempIndexValues[2]).x) { // max X
			tempIndexValues[2] = i;
		}
		if (this->getPoint(i).y > this->getPoint(tempIndexValues[3]).y) { // max Y
			tempIndexValues[3] = i;
		}

	}
	
	boundingBoxIndex = tempIndexValues;
}

void Tile::initializeNeighbors(int i, int j ,Game& game) { // no need to pass the game as this object is very big
	// might have to do something here since it does not like emplace_back
	int cols = game.cols;
	int rows = game.rows;
	std::vector<std::vector<Tile>>& grid = game.grid;

	if (j < cols - 1) { // right horizontal neighbor 
		neighbors.emplace_back(&grid[i][j+1]);
	}
	
	if (j > 0) { // left horizontal neighbor 
		neighbors.emplace_back(&grid[i][j-1]);
	}
	// ctrl K C and ctrl K U
	
	// even rows
	if (i % 2 == 0 && i > 0) { // upper left neighbor for row 0,2,4,6... 
		neighbors.emplace_back(&grid[i - 1][j ]);
	}
	
	if (i % 2 == 0 && i > 0 && j < cols - 1) { // upper right neighbor for  row 0,2,4,6... 
		neighbors.emplace_back(&grid[i - 1][j + 1]);
	}

	if (i % 2 == 0 && i < rows - 1) { // down left neighbor for row 0,2,4,6... 
		neighbors.emplace_back(&grid[i+1][j]);
	}
	if (i % 2 == 0 && i < rows - 1 && j < cols - 1) { //lower right neighbor  for row 0,2,4,6... 
		neighbors.emplace_back(&grid[i + 1][j + 1]);
	}
	
	
	// odd rows
	if (!(i % 2 == 0) && j > 0) { // upper left 
		neighbors.emplace_back(&grid[i - 1][j - 1]);
	}
	if (!(i % 2 == 0) ) { // && j < cols - 1 // upper right (always there) 
		neighbors.emplace_back(&grid[i-1][j]);
	}
	if (!(i % 2 == 0) && j > 0 && i < rows - 1) {  // lower left 
		neighbors.emplace_back(&grid[i + 1][j - 1]);
	}
	if (!(i % 2 == 0) && i < rows - 1) { // lower right 
		neighbors.emplace_back(&grid[i+1][j]);
	}
	

	std::cout << "Everything is good at " << i << " " << j << std::endl;
}

void Tile::initializeNeighbors(int i, int j, std::vector<std::vector<Tile>>& grid) {
	// might have to do something here since it does not like emplace_back
	neighbors.clear();   //just for safety
	

	int rows = grid.size();
	int cols = (grid)[0].size();

	if (j < cols - 1) { // right horizontal neighbor 
		neighbors.emplace_back(&grid[i][j + 1]);
	}

	if (j > 0) { // left horizontal neighbor 
		neighbors.emplace_back(&grid[i][j - 1]);
	}
	// ctrl K C and ctrl K U

	// even rows
	if (i % 2 == 0 && i > 0) { // upper left neighbor for row 0,2,4,6... 
		neighbors.emplace_back(&grid[i - 1][j]);
	}

	if (i % 2 == 0 && i > 0 && j < cols - 1) { // upper right neighbor for  row 0,2,4,6... 
		neighbors.emplace_back(&grid[i - 1][j + 1]);
	}

	if (i % 2 == 0 && i < rows - 1) { // down left neighbor for row 0,2,4,6... 
		neighbors.emplace_back(&grid[i + 1][j]);
	}
	if (i % 2 == 0 && i < rows - 1 && j < cols - 1) { //lower right neighbor  for row 0,2,4,6... 
		neighbors.emplace_back(&grid[i + 1][j + 1]);
	}


	// odd rows
	if (!(i % 2 == 0) && j > 0) { // upper left 
		neighbors.emplace_back(&grid[i - 1][j - 1]);
	}
	if (!(i % 2 == 0)) { // && j < cols - 1 // upper right (always there) 
		neighbors.emplace_back(&grid[i - 1][j]);
	}
	if (!(i % 2 == 0) && j > 0 && i < rows - 1) {  // lower left 
		neighbors.emplace_back(&grid[i + 1][j - 1]);
	}
	if (!(i % 2 == 0) && i < rows - 1) { // lower right 
		neighbors.emplace_back(&grid[i + 1][j]);
	}

}

void Tile::initializeText() {
	sf::Font coordinateFont;
	coordinateFont.loadFromFile("Fonts/ARIAL.ttf");
	
	coordinateText.setFont(coordinateFont);
	coordinateText.setCharacterSize(2);
	coordinateText.setPosition(this->midx , this->midy);
	coordinateText.setFillColor(sf::Color::Black);
}

// Information about the tile
sf::Vector2f Tile::getPoint(size_t i) { 
	if (i > 5) {
		throw std::invalid_argument("Tile::getPoint:: Points goes from 0 to 5");
		std::cout << "Index out of bound" << "\n";
		
	}
	return points[i];
}

sf::Vector2f Tile::getCenter() {
	return sf::Vector2f(midx,midy);
}
// return the points for the min and max of the bounding box
float Tile::getBoundingBoxMinX() {
	return this->getPoint(boundingBoxIndex[0]).x;
}
float Tile::getBoundingBoxMinY() {
	return this->getPoint(boundingBoxIndex[1]).y;
}
float Tile::getBoundingBoxMaxX() {
	return this->getPoint(boundingBoxIndex[2]).x;
}
float Tile::getBoundingBoxMaxY() {
	return this->getPoint(boundingBoxIndex[3]).y;
}

sf::Color Tile::getFillColor() {
	if (wall) {
		return sf::Color(100, 100, 100); 
	} else if (occupiedByOrganism) { 
		return sf::Color::Green; 
	} else { 
		return sf::Color::White; 
	} 

}



void Tile::placeOrganismInTile(Organism& organism) {
	organismInTile = &organism;
	occupiedByOrganism = true;
}

void Tile::updateTileSize( float sizeIndex ) {
	if (sizeIndex>0) {
		sf::Vector2f center = this->getCenter();

		//displacement of center of hexagon (this is vectors and therefore probably wrong.)
		sf::Vector2f leftSkewedVector = (this->getPoint(0) - center);
		float lenthOfLeftSkewedVector = std::sqrt(leftSkewedVector.x * leftSkewedVector.x + leftSkewedVector.y * leftSkewedVector.y);
		
		float displacementFactorX = ((lenthOfLeftSkewedVector) * sizeIndex * cos(PI * construcangle / 180.0) - lenthOfLeftSkewedVector * cos(PI * construcangle / 180.0));
		
		float displacementFactorY = (lenthOfLeftSkewedVector * sizeIndex * sin(PI * construcangle / 180.0) - lenthOfLeftSkewedVector * sin(PI * construcangle / 180.0)) * (this->xRow);
		
		//sf::Vector2f displacementFactor( displacementFactorX, displacementFactorY);
		std::vector<sf::Vector2f> newPoints;
		sf::Vector2f newCenter( center*sizeIndex) ;
		
		for (int i = 0; i < this->points.size(); i++) {
			newPoints.emplace_back(newCenter + (this->getPoint(i) - center) * sizeIndex);
		}

		points = newPoints;
		this->setCenter(newCenter.x, newCenter.y);
		this->r_1 = this->r_1 * sizeIndex;	
		this->r_2 = this->r_2 * sizeIndex;
	} else {
		std::cout << "Size index must be greater than 0" << "\n";
	}
	

}
void Tile::setCenter(float x, float y) {
	this->midx = x;
	this->midy = y;
}

void Tile::updateBoundingBox(){
	this->initBoundingBoxIndex();
}

void Tile::moveTile(sf::Vector2f direction) { // should be removed
	/*
		move the corners of the hexagon in the given direction
	*/
	
	this->hexagon.move(direction.x,direction.y);
}

void Tile::isMouseInTile(sf::Vector2i& mousePos) { // this method is really expensive to run each frame
	
	// Konverter musens position fra vindueskoordinater til verdenskoordinater
	sf::Vector2f worldMousePos = static_cast<sf::Vector2f>(mousePos);

	
	
			
		// Check if the mouse position is inside the hexagon using point-in-polygon test
		bool isInside = false;
		size_t numPoints = hexagon.getPointCount();



		// Use a ray-casting algorithm to check if the point is inside the polygon
		for (size_t i = 0, j = numPoints - 1; i < numPoints; j = i++) {
			sf::Vector2f vi = this->getPoint(i);
			sf::Vector2f vj = this->getPoint(j);

			bool intersect = ((vi.y > worldMousePos.y) != (vj.y > worldMousePos.y)) &&
				(worldMousePos.x < (vj.x - vi.x) * (worldMousePos.y - vi.y) / (vj.y - vi.y) + vi.x);
			if (intersect) {
				isInside = !isInside;
			}
		}

		mouseIsInTile = isInside;

}

void Tile::isMousePressedInTile(sf::Vector2i& mousePos) {
	isMouseInTile(mousePos);

	if (mouseIsInTile && !wall){
		mousePressedTile = true;
		std::cout << "pressed tile" << xRow << "," << yRow << "\n";
	} else {
		mousePressedTile = false;
		
	}
}
void Tile::display(sf::RenderWindow& window, int x, int y, int z) {
	/*
	display the hexagon
	*/
	if (this->wall) {
		this->hexagon.setFillColor(sf::Color(0, 0, 0));
	} else if (occupiedByOrganism){
		this->hexagon.setFillColor(sf::Color(140,0,10));
	} else if (mousePressedTile) {
		this->hexagon.setFillColor(sf::Color(255, 50, 110)); 
	} else {
		this->hexagon.setFillColor(sf::Color(x, y, z));
	}

	
	window.draw(this->hexagon);
}


//operators
bool Tile::operator==(const Tile& otherTile) {
	bool equalOrNot = false;
	// the xRow and yRow are unique for each Tile
	if (otherTile.xRow == this->xRow && otherTile.yRow == this->yRow) {
		equalOrNot = true;
	}
	return equalOrNot;
}

// ---------------- Debugging ------------------
void Tile::displayGridCoordinates( bool activateDebugMode ) {
	if (activateDebugMode) {
		coordinateText.setString(std::to_string(xRow) + "," + std::to_string(yRow));
	}

}