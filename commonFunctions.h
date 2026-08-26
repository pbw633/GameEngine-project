#pragma once
//This header is created for common functions that are usefull in order to keep track of the program such as frameRate and so on 
#include <iostream>
#include "Game.h"

// --------------------- Actions --------------------
bool includesTile(std::vector<Tile*> set, Tile* object);

bool includes(std::vector<Tile>& set, Tile& object);

float heuristic(Tile* grid1, Tile* grid2);






