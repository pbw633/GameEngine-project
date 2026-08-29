#include "Game.h"
#include "Tile.h"
#include "commonFunctions.h"
/*
Notes to self:
	- If you use new you NEED to delete otherwise leaks might be usefull if total know objekts are know such as essential npc if those exists or for projectiles
		that should be created, do its thing and then be deleted
	- by f.x declaring Organism player in Game then the object disappears when Game is deleted since it is "connected" to the game

	- look into smart pointers f.x std::make_unique<Player>();
*/

/*
	- make update counter that counts the number of updates in each loop so if we can exit the update loop early
*/
// ------------------------ Initialization -------------------
void Game::initVariables() { // like the void setup but for the values
	this->window = nullptr; // laver den til en nullpointer
	//transform.setPosition(100.f,100.f);
	rows = 58;
	cols = 62;
	gridOffset = 100;
	//grid = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(cols));
	detectedTileByMouse = { -1,-1 };
	lastDetectedTileByMouse = { -1,-1 };

	grid = Grid(rows,cols);
	
	
}
void Game::initFonts() {
	font.loadFromFile("Fonts/ARIAL.ttf");

	fpsText.setFont(font);
	fpsText.setCharacterSize(14);
	fpsText.setPosition(10.f, 10.f);
	fpsText.setFillColor(sf::Color::White);
}


void Game::initWindow() {
	//this greates the window with the height and width 
	this->videomode.height = 1000;
	this->videomode.width = 1900;
	this->window = new sf::RenderWindow(this->videomode, "my first game", sf::Style::Titlebar | sf::Style::Close);

	//this->window->setFramerateLimit(144); // sets frameRate limit 
}

/*
		- tempeary method
*/
void Game::initOrganism(int rowPos, int colPos, Organism& organism) {
	// This is temperary to try the organism object
	/*
		- if position is not out of bound place organism
	*/
	if ( 0 <= rowPos && 0 <= colPos && colPos < cols && rowPos < rows &&
		this->grid.getGrid()[rowPos][colPos].occupiedByOrganism == false ) {
		
		this->grid.getGrid()[rowPos][colPos].wall = false;
		
		organism.setPosition( &(this->grid.getGrid()[rowPos][colPos]) );

	} else {
		throw std::runtime_error("Organism position out of bound, tile is a wall or occupied");
	}
	
	organism.initTexture("Textures/Player/testSprites2.PNG");
	organism.initVariables();
}


//---------------------- constructors/ destructors ------------------
Game::Game() { //when you start the game somethings need to be initialized
	//importend to first initialize the variables before the window
	this->initVariables();
	this->initFonts();
	this->initWindow();
	

	//this->initEnemies();
	/*
	- Declare the grid and its tiles with their variables and properties
	- Add their neighbors for each tile.
			>Both steps happen in initGrid
	- Declare start- and end positions for the path
	- Add the starting point to the openSet
	*/
	
	this->start_time = std::chrono::high_resolution_clock::now();
	/*
	- Declare objects for testíng
	*/
	this->playerObject = Organism( &(this->grid.getGrid() ) );
	this->initOrganism( 0,cols-1,playerObject );

}

Game::~Game() {
	//kill the window
	delete this->window;
}

//Accessors 
const bool Game::running() const 
{
	return this->window->isOpen();
}

//functions

//  -------------------- Updating methods ------------------------
void Game::updateMousePositions() {
	//updates mouse position mouseposition relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateGrid() {
	/*
	this->updateMouseToGrid();
	this->updateTileBorder();
	this->updateTileInsides();
	this->updateLastDetectedTileByMouse();
	*/
}

void Game::updateMouseToGrid() {
	/*
	this->mouseToGrid( this->mousePosWindow );
	*/
}


void Game::toggleFullScreen() {
	isFullscreen = !isFullscreen;

	if (isFullscreen) {
		this->window->create(sf::VideoMode::getDesktopMode(), "Game", sf::Style::Fullscreen);
	} else {
		this->window->create(this->videomode, "Game", sf::Style::Default);
	}
}

void Game::switchWindowMode() {
	/*
		- Open a menu to choose between different window modes (fullscreen, windowed, borderless)
	*/



}

void Game::updateFrameRate() {
	// mål delta-time
	float dt = fpsClock.restart().asSeconds();
	float currentFPS = 1.f / dt;

	// glidende gennemsnit (smooth)
	const float smoothing = 0.1f;
	smoothedFPS = (smoothedFPS * (1.f - smoothing)) + (currentFPS * smoothing);

	// opdater tekst kun hver 0.25 sek (4x per sekund)
	if (fpsUpdateClock.getElapsedTime().asSeconds() > 0.25f)
	{
		fpsText.setString("FPS: " + std::to_string((int)smoothedFPS));

		// farveskift for synlig performance
		if (smoothedFPS >= 120)
			fpsText.setFillColor(sf::Color::Green);
		else if (smoothedFPS >= 60)
			fpsText.setFillColor(sf::Color::Yellow);
		else
			fpsText.setFillColor(sf::Color::Red);

		fpsUpdateClock.restart();
	}
}

void Game::renderFrameRate(){
	this->window->draw(fpsText);
}

void Game::createLevel() {
	//this method should:
	// - activate mode if key is pressed (keyPressed C) (key release detection) check
	// - make an place (e.g console) to write the filename.
	// - create a csv-file with that name 
	// - copy the level that was painted 
	// - exit create mode by pressing enter check
	
	// Activate or deactivate the mode
	if (ev.type == sf::Event::KeyReleased && 
		ev.key.code == sf::Keyboard::C 
		&& createModeActive == false &&
		loadModeActive == false) { 
		createModeActive = true;
	}
	if ( ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Enter && createModeActive == true) {
		createModeActive = false; 
	}
	
	if (createModeActive) {
		std::string filename; 
		std::cout << "Please enter name of the level: ";
		getline( std::cin, filename );
		
		if (filename.length() == 0) {
			filename = "unspecifiedLevelName";
		}

		//this->mapHelper.saveMap(filename, this->grid);
		createModeActive = false;
		std::cout << "Map succesfully saved with name: "<< filename << "!" << "\n";
	}
	
}

void Game::loadLevel() {
	//this method should:
	// - load mode if key is pressed (keyPressed L) (key release detection) check
	// - write level to be loaded
	// - load a csv-file with that name 

	// Activate or deactivate the mode
	if (ev.type == sf::Event::KeyReleased && 
		ev.key.code == sf::Keyboard::L && 
		loadModeActive == false &&
		createModeActive == false ) {

		loadModeActive = true;
	}
	if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Enter && loadModeActive == true) {
		loadModeActive = false;
	}

	if (loadModeActive) {
		std::string filename;
		std::cout << "Please enter name of the level that should be loaded." << "\n";
		std::cout << "Remember to use .csv" << "\n";
		getline(std::cin, filename);

		if (filename.length() == 0) {
			filename = "unspecifiedLevelName";
		}

		//this->mapHelper.loadMap(filename, this->grid);
		loadModeActive = false;
		std::cout << "Map succesfully loaded map with name: " << filename << "!" << "\n";
	}
}

void Game::deleteLevel() {

}

void Game::chooseDirectionOfGridMovement(sf::Vector2f mousePos ) {
	/*
	// choose direction depending on where the mouse is. Areas around the edge
	*/
	if (mousePos.x) {

	}
}

void Game::moveGrid(sf::Vector2f direction) {
	//this->transform.setPosition(this->transform.getPosition() + direction);
}


/*
TODO:
	- A valid tile check should be made either inside the click execution or inside the method. 
	- best if it as early as possible
*/
void Game::leftMouseClickExecution() {
	/*
	// complete List of what to execute when right mouse buttom is pressed:
	//	-Detction of mouse press in a tile
	*/
	std::pair<int, int> detectedTile = this->grid.getCurrentDetectedTileCoordinates();
	if (detectedTile.first != -1 && detectedTile.second != -1) {
		if (!(this->grid.getGrid()[detectedTile.first][detectedTile.second].wall)) {
			this->playerObject.calculatePath(&(this->grid.getGrid()[detectedTile.first][detectedTile.second]));
		}
	}
	
	
}

void Game::rightMouseClickExecution() {
	/*
	// complete List of what to execute when left mouse buttom is pressed:
	//	-Detction if mouse pressed player
	*/
	//this->playerObject.pointInSprite(this->mousePosWindow);
	
	this->playerObject.rotateOrganism(this->mousePosWindow);
	
}

void Game::pollEvents() {
	// what is happening
	while (this->window->pollEvent(this->ev)) {
		//closing the window. when you press close the window/program shall end and so will it if you press escape
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window -> close();
			break;
		case sf::Event::MouseButtonReleased:
			if (this->ev.mouseButton.button == sf::Mouse::Left) {
				this->leftMouseClickExecution();
				std::cout << "Left-buttonRealese" << "\n";

			} else if (this->ev.mouseButton.button == sf::Mouse::Right) {
				this->rightMouseClickExecution();
				std::cout << "Right-buttonRealese" << "\n";
			}
			break;
		case sf::Event::MouseWheelMoved:
			if ( this->ev.mouseWheel.delta> 0 ) {
				std::cout << "scrolled up" << "\n";
				//this->updateGridSize(1.02f);
				//this->updateBoundingBoxsForTiles();
				this->playerObject.updateSpriteLocationInTile();

			} else if ( this->ev.mouseWheel.delta < 0 ) {
				std::cout << "scrolled down" << "\n";
				
				//this->updateGridSize(0.98f);
				//this->updateBoundingBoxsForTiles();
				this->playerObject.updateSpriteLocationInTile();
			}
			break;
		}
	}
}

void Game::update() {
	//update according to events
	//need to poll events when you update
	this->pollEvents(); 
	this->updateMousePositions();
	this->moveGrid(sf::Vector2f(1, 1)); // should take our vector as an input
	this->createLevel();

	this->updateFrameRate();
	
	this->updateGrid();
	this->grid.update(mousePosWindow);
	//Player
	this->updatePlayerObject();

}

/*
TODO
	- Update so only tiles within the window is shown/calculated
*/


// player stuff
void Game::updatePlayerObject() {
	playerObject.updatePosition();
	playerObject.updateSpriteLocation();
	playerObject.updateMovement(0,0); // remove. this is old code
	playerObject.updateSprite();
}


void Game::renderPlayer() {
	playerObject.render(*this->window);
}


void Game::render() {
	//clear last frame
	/*
		- clear old frame
		- render objects
		-display frame in window
	*/
	
	this->window->clear(); 

	// draw next frame
	
	// Renders the grid
	// This part slows performance greatly when many rows or columns are applied

	this->window->draw(grid.getGridTriangles());
	this->window->draw(grid.getGridLines());
	
	this->renderPlayer();
	this->renderFrameRate();

	this->window->display();
}


// ------------------ debugging -----------

//Activation of debug mode
void Game::debugModeActivationSwitch() {
	if (ev.type == sf::Event::KeyReleased &&
		ev.key.code == sf::Keyboard::C &&
		ev.key.code == sf::Keyboard::LControl) {
		debugModeActivated = !debugModeActivated;
		
		if (debugModeActivated) {
			std::cout << "Debugmode Activated" << "\n";
		} else {
			std::cout << "Debugmode off" << "\n";
		}
	}
}