#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Tile.h"
#include "MapCSVExporter.h"
#include "Heap.h"
#include "Organism.h"

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
TODO:
	- consider only to clear the part that is neccesary since some parts are should only be cleared and then redrawn if there's an update to the area
	- add delta time so that the animetions are independent of the framerate
	- Introduuce debug mode while program is running
*/


// class that acts as the game engine



class Game{
private:
	//variables
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	float gridOffset;

	//mousePosition
	sf::Vector2i mousePosWindow;
	
	//game objects aka enemies and cell. This is temp
	sf::RectangleShape enemy;
	sf::ConvexShape Cell;

	

	//private functions
	void initVariables();
	void initFonts();
	void initWindow();

	void initEnemies(); //initialize the enemies (temp)
	void initCells(); // initialize each Cell (temp)
	void initGrid(); //initialize the grid
	void initTestGrid();

	void initStartAndEndPoints(Tile& startPosition , Tile& endPosition); // initialize start and end of the path. just some random points
	void initPathStartCondition();
	void initOrganism(int rowPos, int colPos, Organism& organism);
	void initMouseInTileDetection();
	
	//void initGridNeighbors(const Game& game); // initialize the neighbors of each Tile in the grid


	//move objects
	void chooseDirectionOfGridMovement(sf::Vector2f mousePos);
	void moveCells(); // (temp)
	void moveGrid(sf::Vector2f direction);
	void movePlayerPosition();
	//Game objects
	Organism playerObject; 
	void updatePlayerObject();

	

	// debugging
	void mouseInGridDetection(); // remove
	void mouseInTileDetection(); // remove
	void debugModeActivationSwitch();
public:
	//constructors / Destructors
	Game();
	virtual ~Game();

	//--------------------other variables---------------------------
	// used for time-manegement
	float fps;
	sf::Clock fpsClock;        // calculate frameRate clock
	sf::Clock fpsUpdateClock;  // Timer for updating fps text on screen
	float smoothedFPS = 0.f;   // smoothing fps
	sf::Font font;
	sf::Text fpsText;


	sf::Clock clock;
	sf::Clock timer;
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::chrono::time_point<std::chrono::high_resolution_clock> end_time;

	//creating the grid for you to walk on
	int rows;
	int cols;

	Tile tile;
	std::vector<std::vector<Tile>> grid;
	sf::VertexArray testGrid;
	sf::VertexArray testGridLines;

	//variables and other objects for pathfinding
	bool runPathfinding = true;

	int initialFrame = 0;
	int playerPosition = 0;
	bool pathFindingComplete = false;
	Tile* start;
	Tile* end;
	Tile current;
	std::vector<Tile*> openSet;
	std::vector<Tile*> closedSet;
	std::vector<Tile*> path;

	Min_heap sorter; // later each npc should have this
	MapCSVExporter mapHelper;

	//Variables for creating, loading and deleting levels
	bool createModeActive	= false; 
	bool loadModeActive		= false;
	bool deleteModeActive	= false;
	// ----------------------- Grid ---------------------------
	bool mouseInsideOfGrid = false;
	Tile* lastDetectedTileByMouse = nullptr;

	//----------------------- Debugging----------------------
	bool debugModeActivated = false;
	
	//-----------------------accessors------------------------------
	const bool running() const;

	//--------------------declare functions---------------------------
	//-------------------- FrameRate ---------------
	void updateFrameRate();
	void renderFrameRate();

	//---------------------Mouse Methods----------
	std::pair<int, int> mouseToGrid(sf::Vector2i mousePos);
	void rightMouseClickExecution(); //maybe in pollEvents?
	void leftMouseClickExecution();

	// ------------------ Level design -------------
	void createLevel();
	void loadLevel();
	void deleteLevel();

	// --------------------Update objects --------------
	void update();
	void updateGrid();
	void updatePath();

	void updateMousePositions();
	void pollEvents();

	//----------------- Rendering ------------------
	void renderPlayer();
	void render();

	
};

