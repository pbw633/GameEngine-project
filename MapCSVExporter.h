#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Tile.h"




class MapCSVExporter{

public:
	void saveMap(std::string& filename, std::vector<std::vector<Tile>>& grid);
	bool loadMap(std::string& filename, std::vector<std::vector<Tile>>& grid);

		
	
private:
	
};

