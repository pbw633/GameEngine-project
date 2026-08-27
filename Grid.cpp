#include "Grid.h"

// ---------------------------- Public ------------------------------
// ----------------- Initialize -------------
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

//----------------------------- Actions --------------------------

// ---------------------------- Private -----------------------------