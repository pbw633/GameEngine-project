#include "Grid.h"

// ---------------------------- Public ------------------------------
// ----------------- Initialize -------------

void Grid::initVariables() {
	this->dirVecBuffer = 0.01;
}

void Grid::initGrid() {
	
	
	grid = std::vector<std::vector<Tile>>(this->rows, std::vector<Tile>(this->cols));
	
	gridTriangles = sf::VertexArray(sf::Triangles);
	gridLines = sf::VertexArray(sf::Lines);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			grid[i][j] = Tile(i, j); // declare it exists
			grid[i][j].initializeTileShape(255, 0, 0); // declare the tile has a shape aka hexagon

			sf::Color col = grid[i][j].getFillColor(); // eller beregn farve efter t.wall/occupied osv.

			// Make triangles and lines 
			for (int k = 0; k < 6; k++) {
				gridTriangles.append(sf::Vertex(grid[i][j].getCenter(), col));
				gridTriangles.append(sf::Vertex(grid[i][j].getPoint(k), col));
				gridTriangles.append(sf::Vertex(grid[i][j].getPoint(k == 5 ? 0 : k + 1), col));
				gridLines.append(sf::Vertex(grid[i][j].getPoint(k), sf::Color::Black));
				gridLines.append(sf::Vertex(grid[i][j].getPoint(k == 5 ? 0 : k + 1), sf::Color::Black));
			}

		}
	}
	// each tile needs to know their neighbors

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].initializeNeighbors(i, j, grid);
		}
	}
}
// -------------------------- Setters ------------------------------
void Grid::setGridLocation(sf::Vector2f pos) {
	this->transform.setPosition(pos);
}

//--------------------------- Getters ----------------------------
int Grid::getRowCount() {
	return grid.size();
}
int Grid::getColCount() {
	return grid[0].size();
}

Tile& Grid::getTile(int Row, int Col) {
	if (Row < 0 || Col < 0 || this->rows <= Row || this->cols <= Col) {
		throw std::runtime_error("Grid: gridcoordinates out of bound");
	}
	return this->grid[Row][Col];
}

std::vector<std::vector<Tile>>& Grid::getGrid() {
	return this->grid;
}

sf::VertexArray& Grid::getGridTriangles() {
	return this->gridTriangles;
}

sf::VertexArray& Grid::getGridLines() {
	return this->gridLines;
}

//----------------------------- Actions --------------------------
void Grid::placeOrganism(int Row, int Col, Organism& organism) {
	if ( Row < 0 || Col < 0 || this->rows <= Row || this-> cols <= Col ) {
		throw std::runtime_error("Grid: Organism should be placed inside of grid");
	}
	if ( this->grid[Row][Col].wall || this->grid[Row][Col].occupiedByOrganism ) {
		throw std::runtime_error("Grid: Tile is occupied or is a wall");
	}
	organism.setPosition( &(this->grid[Row][Col]) );

	//The texture is tempoary and is just for visualize the player:
	organism.initTexture("Textures/Player/testSprites2.PNG");
	organism.initVariables();
}

void Grid::moveInDirection(sf::Vector2f	direction) {
	sf::Vector2f currentTransformPosition = this->transform.getPosition();
	this->transform.setPosition(currentTransformPosition + direction );
}

void Grid::moveInDirectionWithSpeed(float speed, sf::Vector2f unitDirVec) {
	float dirVecLength = std::sqrt(std::pow(unitDirVec.x,2)+ std::pow(unitDirVec.y, 2));
	if (dirVecLength > 1+ dirVecBuffer){
		throw std::runtime_error("Grid: The direction Vector Length may not be Longer than 1");
	}

	sf::Vector2f currentTransformPosition = this->transform.getPosition();
	this->transform.setPosition(currentTransformPosition + speed*unitDirVec);
}

void Grid::resize( float sizeFactor ) {
	if ( sizeFactor <= 0 ) {
		throw std::runtime_error("Grid: sizeFactor cannot be negative or zero");
	}
	// reset the grid lines and triangles
	gridTriangles.clear();
	gridLines.clear();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].updateTileSize(sizeFactor);

			sf::Color col = grid[i][j].getFillColor(); // eller beregn farve efter t.wall/occupied osv.

			// Make triangles and lines 

			for (int k = 0; k < 6; k++) {
				gridTriangles.append(sf::Vertex(grid[i][j].getCenter(), col));
				gridTriangles.append(sf::Vertex(grid[i][j].getPoint(k), col));
				gridTriangles.append(sf::Vertex(grid[i][j].getPoint(k == 5 ? 0 : k + 1), col));
				gridLines.append(sf::Vertex(grid[i][j].getPoint(k), sf::Color::Black));
				gridLines.append(sf::Vertex(grid[i][j].getPoint(k == 5 ? 0 : k + 1), sf::Color::Black));
			}
		}
	}
	
	this->updateBoundingBoxes();
	std::cout << "Grid size updated" << "\n";

}


// ------------------- Update --------------------
void Grid::update() {

}

// ---------------------------- Private -----------------------------
// ----------------- Update ---------------
void Grid::updateBoundingBoxes() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].updateBoundingBox();
		}
	}
}