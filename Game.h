#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Tile.h"
#include "MapCSVExporter.h"
#include "Heap.h"
#include "Organism.h"
#include "Grid.h"

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
	- Make a class for the mousePosition that contains window/screen- and grid coordinates and whether or not the coordinates are valid
*/


// class that acts as the game engine



class Game{
private:
	// --------------------- Variables --------------------
	//variables
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	float gridOffset;
	bool isFullscreen = false;
	sf::Transformable transform;

	//mousePosition
	sf::Vector2i mousePosWindow;
	
	//game objects aka enemies and cell. This is temp
	sf::RectangleShape enemy;

	

	Organism playerObject;

	//--------------------- Initialization --------------------
	void initVariables();
	void initFonts();
	void initWindow();

	

	
	void initOrganism(int rowPos, int colPos, Organism& organism);
	
	// --------------------- Setters --------------------
	
	// ---------------------- Getters --------------------

	// --------------------- Update --------------------
	
	//move objects
	void chooseDirectionOfGridMovement(sf::Vector2f mousePos);
	void moveGrid(sf::Vector2f direction);
	void movePlayerPosition();
	
	
	void updatePlayerObject();

	

	// --------------- debugging ----------------------------
	void debugModeActivationSwitch();
public:
	//----------------- constructors / Destructors ---------------
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

	// game grid variables
	int rows;
	int cols;
	Grid grid;

	float tileSizeFactor = 1.0;

	Tile tile;
	

	//variables and other objects for pathfinding

	int initialFrame = 0;
	
	// map creation
	MapCSVExporter mapHelper;

	//Variables for creating, loading and deleting levels
	bool createModeActive	= false; 
	bool loadModeActive		= false;
	bool deleteModeActive	= false;
	// ----------------------- Grid ---------------------------
	std::pair<int, int> detectedTileByMouse;
	std::pair<int, int> lastDetectedTileByMouse;


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
	void updateMouseToGrid();
	void updateTileBorder();
	void updateTileInsides();
	void updateLastDetectedTileByMouse();

	void toggleFullScreen();
	void switchWindowMode();

	void updateGridSize(float sizeIndex);
	void updateBoundingBoxsForTiles();

	void updateMousePositions();
	void pollEvents();

	//----------------- Rendering ------------------
	void renderPlayer();
	void render();

	
};

