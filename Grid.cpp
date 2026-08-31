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

void Grid::setGridWallStatus(bool wallStatus) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].wall = wallStatus;
		}
	}
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

std::pair<int, int> Grid::getTileAtPosition(sf::Vector2i mousePos) {
	float x = static_cast<float>(mousePos.x);
	float y = static_cast<float>(mousePos.y);

	const float angle = this->grid[0][0].construcangle * 3.14159265f / 180.f;

	const float dx = 2.f * this->grid[0][0].r_1 * cos(angle); // r_1 = 15
	const float dy = this->grid[0][0].r_1 * 2.f * sin(angle) + (this->grid[0][0].r_2 - cos((90.f - this->grid[0][0].construcangle) * 3.14159265f / 180.f) * this->grid[0][0].r_1);

	int approxRow = static_cast<int>((y - 100.f) / dy);
	approxRow = std::max(0, std::min(rows - 1, approxRow));

	float offsetX = (approxRow % 2 == 0) ? (this->grid[0][0].r_1 * cos(angle)) : 0.f;

	int approxCol = static_cast<int>((x - 100.f - offsetX) / dx);
	approxCol = std::max(0, std::min(cols - 1, approxCol));

	// refine by checking this tile + neighbors only
	Tile* bestTile = nullptr;

	std::vector<Tile*> candidates;
	candidates.push_back(&grid[approxRow][approxCol]);

	for (Tile* n : grid[approxRow][approxCol].neighbors)
		candidates.push_back(n);

	for (Tile* t : candidates)
	{
		if (t->getBoundingBoxMinX() <= x && x <= t->getBoundingBoxMaxX() &&
			t->getBoundingBoxMinY() <= y && y <= t->getBoundingBoxMaxY()) {
			// final precise check
			bool inside = false;
			size_t numPoints = t->hexagon.getPointCount();

			for (size_t i = 0, j = numPoints - 1; i < numPoints; j = i++) {
				sf::Vector2f vi = t->getPoint(i);
				sf::Vector2f vj = t->getPoint(j);

				bool intersect = ((vi.y > y) != (vj.y > y)) &&
					(x < (vj.x - vi.x) * (y - vi.y) / (vj.y - vi.y) + vi.x);

				if (intersect)
					inside = !inside;
			}

			if (inside) {
				//std::cout << "the guess is: " << t->xRow << "," << t->yRow << "\n";
				currentDetectedTileByMouse = { t->xRow, t->yRow };
				return { t->xRow, t->yRow };
			}
		}

	}
	//std::cout << "fail " << "\n";
	return { -1, -1 };
}

std::pair<int, int> Grid::getCurrentDetectedTileCoordinates() {
	return this->currentDetectedTileByMouse;
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
void Grid::updateHoveredTileBorder() {
	if (previousDetectedTileByMouse.first != -1 || previousDetectedTileByMouse.second != -1) {
		int tileIndexToArrayIndex = previousDetectedTileByMouse.first * cols + previousDetectedTileByMouse.second;
		// convert tileIndexToArrayIndex to gridLines coordinates
		int lineStart = tileIndexToArrayIndex * 12;
		for (int i = 0; i < 12; i++) {
			gridLines[lineStart + i].color = sf::Color::Black;
		}
	}

	if (currentDetectedTileByMouse.first != -1 || currentDetectedTileByMouse.second != -1) {
		//convert tile coordinates to tileArray coordinates
		int tileIndexToArrayIndex = currentDetectedTileByMouse.first * cols + currentDetectedTileByMouse.second;
		// convert tileIndexToArrayIndex to gridLines coordinates
		int lineStart = tileIndexToArrayIndex * 12;
		for (int i = 0; i < 12; i++) {
			gridLines[lineStart + i].color = sf::Color::Red;
		}
	}
}

void Grid::updateHoveredTileFill() {
	if (previousDetectedTileByMouse.first != -1 || previousDetectedTileByMouse.second != -1) {
		if (!grid[previousDetectedTileByMouse.first][previousDetectedTileByMouse.second].wall) {
			int tileIndex = previousDetectedTileByMouse.first * cols + previousDetectedTileByMouse.second;
			int triangleStart = tileIndex * 18;

			for (int i = 0; i < 18; i++) {
				gridTriangles[triangleStart + i].color = sf::Color::White;
			}
		}
	}
	if (currentDetectedTileByMouse.first != -1 || currentDetectedTileByMouse.second != -1) {
		if (!grid[currentDetectedTileByMouse.first][currentDetectedTileByMouse.second].wall) {
			int tileIndex = currentDetectedTileByMouse.first * cols + currentDetectedTileByMouse.second;
			int triangleStart = tileIndex * 18;

			for (int i = 0; i < 18; i++) {
				gridTriangles[triangleStart + i].color = sf::Color::Red;
			}
		}
	}
}

void Grid::updatePreviousHoveredTile() {
	previousDetectedTileByMouse = currentDetectedTileByMouse;
}

void Grid::update( sf::Vector2i mousePos ) {
	this->getTileAtPosition(mousePos);
	this->updateHoveredTileBorder();
	this->updateHoveredTileFill();
	this->updatePreviousHoveredTile();
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