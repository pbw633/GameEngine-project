#pragma once
//This header is created for common functions that are usefull in order to keep track of the program such as frameRate and so on 
#include <iostream>
#include "Game.h"
/*
void frameRate(Game& game);
*/
//bool includes(std::vector<Tile>& set, Tile& object) {};
bool includesTile(std::vector<Tile*> set, Tile* object);

bool includes(std::vector<Tile>& set, Tile& object);

float heuristic(Tile* grid1, Tile* grid2);




/*
class Min_heap {
public:
	Min_heap();

	void insert(Tile* tile);
	Tile* delMin();
private:
	std::vector<Tile*> heap;
	void exch(int i, int j);
	void swim(int k);
	void sink(int k);
};
*/


