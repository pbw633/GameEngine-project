#pragma once
#include <string>
// This is the base class of all items that can be used such as weapons, medicin, ammo and other
class Item{
	//  --------------- Variables ----------------
	// Item id and itemName should/can be used interchangably but should be Id if possible
	int id = 0;
	std::string itemName = "";

	int quality = 0;
	int price = 0;
	int condition = 0;
	
	
public:
	Item() {

	}
	// --------------- Variables ----------------

	// --------------- Initialization ----------------

	// --------------- Setters ----------------

	// --------------- Getters ----------------

	// --------------- Actions ----------------


private:
	// --------------- Variables ----------------
};

