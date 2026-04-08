#include "MapCSVExporter.h"
//#include "Game.h"
 // string stream

void MapCSVExporter::saveMap(std::string& filename, std::vector<std::vector<Tile>>& grid) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		//return false;
	}

	int rows = grid.size();
	int cols = grid[0].size();


	file << "x,y,walkable,tile_type,elevation\n";

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			file << grid[i][j].xRow << ","
				<< grid[i][j].yRow << ","
				<< grid[i][j].wall  << ","
				<< "futureTileType" << ","
				<< "futureElevationLevel" << "\n";
		}
	}
}

bool MapCSVExporter::loadMap(std::string& filename, std::vector<std::vector<Tile>>& grid) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	}
	int rows = grid.size();
	int cols = grid[0].size();

	std::string line;
	std::getline(file, line); // skip header line

	while ( std::getline(file, line) ) {
		std::stringstream ss(line);
		
		std::string xValue;
		std::string yValue;
		std::string wallValue;

		// coordinates
		std::getline(ss, xValue, ',');
		std::getline(ss, yValue, ',');
		
		int xRow = std::stoi(xValue);
		int yCol = std::stoi(yValue);

		//attributes
		std::getline(ss, wallValue, ',');
		bool wall = std::stoi(wallValue) == 1 ? true : false;

		//Safety 
		// - Do not try to insert if the grid is smaller than the map
		if (xRow > rows || yCol > cols) {
			break;
		}

		//loading
		grid[xRow][yCol].wall = wall;

	}

	
	return true;
}