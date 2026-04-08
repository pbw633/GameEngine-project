#include <iostream>
#include <cassert>
#include <functional>
#include "Heap.h"
#include "Organism.h"
#include "StorageContainer.h"
#include "MapCSVExporter.h"
/*
TODO:
This is a list of tests that should be done:
- test the pathfinding of an organism and make a wall it should get passed 
- Delete minimum with multiple elements in heap
*/
int failedTests = 0;

void runTest(const std::string& testName, std::function<void()> testFunc) {
	try {
		testFunc();
		std::cout << "[PASS] " << testName << "\n";
	}
	catch (const std::exception& e) {
		std::cerr << "[FAIL] " << testName << "\n";
		std::cerr << "  Error: " << e.what() << "\n";
		failedTests++;
	}
	catch (...) {
		std::cerr << "[FAIL] " << testName << "\n";
		failedTests++;
	}
}

// Simple function to initialize a grid but not its neighbors
std::vector<std::vector<Tile>> declareTestGrid(int numberOfTiles) {
	int cols = 1;
	int rows = numberOfTiles; 
	std::vector<std::vector<Tile>> grid = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(cols));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j] = Tile(i, j); // declare it exists
			grid[i][j].initializeTileShape(255, 0, 0); // declare the tile has a shape aka hexagon
		}
	}
	return(grid);
}

std::vector<std::vector<Tile>> declareTestGrid(int rows,int cols) {
	std::vector<std::vector<Tile>> grid = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(cols));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j] = Tile(i, j); // declare it exists
			grid[i][j].wall = false;
			grid[i][j].initializeTileShape(255, 0, 0); // declare the tile has a shape aka hexagon
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].initializeNeighbors(i, j, grid);
		}
	}
	return(grid);
}

//Heap-tests
void minHeapInsertTest() {
	//Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(4);
	grid[0][0].f = 3;
	grid[1][0].f = 2;
	grid[2][0].f = 5;
	grid[3][0].f = 1;
	std::vector<int> expectedValues = { 1,2,5,3 };

	Min_heap sorter;

	//act
	sorter.insert( &grid[0][0] );
	sorter.insert( &grid[1][0] );
	sorter.insert( &grid[2][0] );
	sorter.insert( &grid[3][0] );
	
	int lengthOfHeap = sorter.heap.size();

	
	// assert
	if (sorter.heap.size() != expectedValues.size()) {
		throw std::runtime_error("heap size mismatch");
	}

	for (int i = 0; i < lengthOfHeap; i++) {
		if ( (int)sorter.heap[i]->f != expectedValues[i] ) {
			throw std::runtime_error("heap is not as expected");
		}
	}
	
}
/*
- The test asserts that the size of initial size, size after insert, size after delMin and checks if it is the correct value that is returned 
- The minimum size should be 1 where we might have a nullptr at the first entrance.
*/
void delMinTestOneElement() {
	// Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(4);
	grid[0][0].f = 3;
	Min_heap sorter;
	
	// Act
	std::vector<Tile*> heapBeforeInsert = sorter.heap;
	int lengthBeforeInsert = sorter.heap.size();
	
	sorter.insert(&grid[0][0]);

	int lengthBeforeRemoval = sorter.heap.size();

	Tile* minimumTile = sorter.delMin();
	std::vector<Tile*> heapAfterDeletion = sorter.heap;
	int lengthAfterRemoval = sorter.heap.size();

	// Assert
	if (lengthBeforeInsert != 1 || heapBeforeInsert[0] != nullptr) {
		throw std::runtime_error("heap size mismatch with initial size");
	}

	if (lengthBeforeRemoval != 1 || lengthAfterRemoval != 1) {
		throw std::runtime_error("heap size mismatch");
	}

	if ((int) minimumTile->f != 3) {
		throw std::runtime_error("Wrong tile-value returned");
	}
	
	if (heapAfterDeletion[0] != nullptr) {
		throw std::runtime_error("Not a null-pointer after deletion");
	}
}

void changeFValueToLessThanParentTest() {
	//Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(4);
	grid[0][0].f = 3;
	grid[1][0].f = 2;
	grid[2][0].f = 5;
	grid[3][0].f = 1;
	std::vector<int> expectedValues = {0, 2, 1,3 };

	Min_heap sorter;

	//act
	sorter.insert(&grid[0][0]);
	sorter.insert(&grid[1][0]);
	sorter.insert(&grid[2][0]);
	sorter.insert(&grid[3][0]);

	sorter.changeFValue(2,0);

	int lengthOfHeap = sorter.heap.size();


	// assert
	if (sorter.heap.size() != expectedValues.size()) {
		throw std::runtime_error("heap size mismatch");
	}

	for (int i = 0; i < lengthOfHeap; i++) {
		if ((int)sorter.heap[i]->f != expectedValues[i]) {
			throw std::runtime_error("heap is not as expected");
		}
	}
}
void changeFValueToMoreThanParentTest() {
	//Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(5);
	grid[0][0].f = 3;
	grid[1][0].f = 2;
	grid[2][0].f = 5;
	grid[3][0].f = 1;
	grid[4][0].f = 10;
	std::vector<int> expectedValues = { 1,3,5,6,10 };

	Min_heap sorter;

	//act
	sorter.insert(&grid[0][0]);
	sorter.insert(&grid[1][0]);
	sorter.insert(&grid[2][0]);
	sorter.insert(&grid[3][0]);
	sorter.insert(&grid[4][0]);

	sorter.changeFValue(1, 6);

	int lengthOfHeap = sorter.heap.size();


	// assert
	if (sorter.heap.size() != expectedValues.size()) {
		throw std::runtime_error("heap size mismatch");
	}

	for (int i = 0; i < lengthOfHeap; i++) {
		if ((int)sorter.heap[i]->f != expectedValues[i]) {
			throw std::runtime_error("heap is not as expected");
		}
	}

}

//Map-tests
void createMapTest() {
	// Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(3,3);
	grid[0][0].wall = true;
	grid[1][0].wall = true;
	grid[2][0].wall = true;
	grid[2][1].wall = true;

	std::vector<int> expectedXValue		 = {0,0,0,
											1,1,1,
											2,2,2 };
	std::vector<int> expectedYValue		 = {0,1,2,
											0,1,2,
											0,1,2 };
	std::vector<int> expectedWallValue	 = {1,0,0,
											1,0,0,
											1,1,0 };

	MapCSVExporter mapHelper; 
	std::string filename = "testMapCreationTest.csv";

	// Act
	mapHelper.saveMap( filename , grid );

	// Assert
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("File did not open!");
	}
	std::string line;
	std::getline(file, line); // skip header line
	
	int i = 0;
	while (std::getline(file, line)) {
		std::stringstream ss(line);

		std::string xValue;
		std::string yValue;
		std::string wallValue;

		// coordinates
		std::getline(ss, xValue, ',');
		std::getline(ss, yValue, ',');
		std::getline(ss, wallValue, ',');

		int xRow = (int) std::stoi(xValue);
		int yCol = (int) std::stoi(yValue);
		bool wall = (int) std::stoi(wallValue) == 1 ? true : false;
		
		if (xRow != expectedXValue[i] || yCol != expectedYValue[i] || wall != expectedWallValue[i]) {
			throw std::runtime_error("We did not save file correct!");
		}
		
		i=i+1;
	}
}

void loadMapTest() {
	// Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(3, 3);
	
	std::vector<std::vector<int>> expectedWallValue = { {1,0,0},{1,0,0},{1,1,0},};

	MapCSVExporter mapHelper;
	std::string filename = "testMapCreationTest.csv";
	
	// Act 
	mapHelper.loadMap(filename, grid);

	// Assert
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (grid[i][j].wall != expectedWallValue[i][j]) {
				throw std::runtime_error("File was not loaded correctly!");
			}
		}
	}
}

// Entity-tests
void storageAddTest() {
	// Setup
	Item item = Item();
	StorageContainer storage = StorageContainer();
	
	// Act
	int sizeOfInventoryBeforeAddition = storage.inventory.size();
	storage.addItem( &item );
	int sizeOfInventoryAfterAddition = storage.inventory.size();

	// Assert
	if ( sizeOfInventoryBeforeAddition != 0 ) {
		throw std::runtime_error("Initial size of storage is not 0!");
	}
	if (sizeOfInventoryAfterAddition != 1) {
		throw std::runtime_error("Item was not added to the storage");
	}
}

void storageRemovalTest() {
	// Setup
	Item item0 = Item();
	Item item1 = Item();
	Item item2 = Item();
	Item item3 = Item();
	Item item4 = Item();

	StorageContainer storage = StorageContainer();

	// Act
	storage.addItem(&item0);
	storage.addItem(&item1);
	storage.addItem(&item2);
	storage.addItem(&item3);
	storage.addItem(&item4);

	int storageSize = storage.inventory.size();

	storage.dropItem(0);
	int storageSizeFirst = storage.inventory.size();

	storage.dropItem(3);
	int storageSizeSecond = storage.inventory.size();
	
	storage.dropItem(1);
	int storageSizeThird = storage.inventory.size();
	
	// Assert
	if ( storageSize != 5 ) {
		throw std::runtime_error("Expected 5 items");
	}
	if ( storageSizeFirst != 4 && storageSizeSecond != 3 && storageSizeThird != 2) {
		throw std::runtime_error("Did not remove item");
	}
	if (storage.inventory[0] != &item1 || storage.inventory[1] != &item3) {
		throw std::runtime_error("Wrong items have been removed");
	}

}

//Test organism can calculate the path
void organismPathCalculationTest() {
	// Setup
	std::vector<std::vector<Tile>> grid = declareTestGrid(7, 7);
	// creates a wall between the goal and the starting point
	
	for (int i = 0; i < 6; i++){ 
		grid[i][1].wall = true; 
	}
	
	Organism organism = Organism(&grid);
	organism.setPosition(&grid[0][6]);
	
	// Act
	organism.calculatePath(&grid[0][0]);
	
	std::vector<Tile*> path = organism.returnCalculatedPath();

	// Assert
	if (path[0] != &grid[0][0]) {
		throw std::runtime_error("The end location of the calculated path is not equal to the desired path");
	}
	
}

#ifdef TEST_MODE  // debug-Test to run this
int main() {
	minHeapInsertTest();
	
	// run tests
	runTest("Min_Heap Insert Test", minHeapInsertTest);
	runTest("Change F-Value To Less Than Parent Test", changeFValueToLessThanParentTest);
	runTest("Change F-Value To More Than Parent Test", changeFValueToMoreThanParentTest);
	runTest("Save grid Test", createMapTest);
	runTest("Load grid Test", loadMapTest);
	runTest("Delete minimum in heap Test", delMinTestOneElement);
	runTest("Add item to storage Test", storageAddTest);
	runTest("Remove items from storage Test", storageRemovalTest);
	runTest("calculation of path for organism", organismPathCalculationTest);
	// Number of failed tests
	if (failedTests > 0) {
		std::cerr << "Amount of failed tests: " << failedTests << "\n";
		return 1;
	}

	std::cout << "All tests completed! \n";

	return 0;
}
#endif