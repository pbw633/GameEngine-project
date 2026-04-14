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
//where the functions are defined 
//private functions
void Game::initVariables() { // like the void setup but for the values
	this->window = nullptr; // laver den til en nullpointer

	rows = 58;
	cols = 62;
	gridOffset = 100;
	grid = std::vector<std::vector<Tile>>(rows, std::vector<Tile>(cols));
	//std::cout << "Rows: " << rows << ", Cols: " << cols << std::endl;
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


void Game::initEnemies() {
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f,100.f)); // sets the size (uses float)
	this->enemy.setFillColor(sf::Color::Blue); // the color
	this->enemy.setOutlineColor(sf::Color::Green); //sets color of outline
	this->enemy.setOutlineThickness(1.f); //sets the thickness 
}

void Game::initCells() {
	// red weird object that can be removed now
	this->Cell.setPointCount(5);
	this->Cell.setPoint(0, sf::Vector2f(0, 0));
	this->Cell.setPoint(1, sf::Vector2f(150, 10));
	this->Cell.setPoint(2, sf::Vector2f(120, 90));
	this->Cell.setPoint(3, sf::Vector2f(30, 100));
	this->Cell.setPoint(4, sf::Vector2f(0, 50));

	this->Cell.setFillColor(sf::Color::Red);
		
}



void Game::initGrid() { // initialize the grid

	// actual initialize the grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//grid[i][j] = Tile(i, j);
			std::cout << "Setting grid[" << i << "][" << j << "]" << std::endl;
			grid[i][j] = Tile(i,j); // declare it exists
			grid[i][j].initializeTileShape(255, 0, 0); // declare the tile has a shape aka hexagon
		}
	}
	// each tile needs to know their neighbors
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].initializeNeighbors(i,j, grid);
		}
	}
	
}

void Game::initTestGrid() {
	// grid som faktisk vises da gamle version var langsommere

	testGrid = sf::VertexArray(sf::Triangles);
	testGridLines = sf::VertexArray(sf::Lines);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			Tile& t = grid[i][j];

			sf::Color col = t.getFillColor(); // eller beregn farve efter t.wall/occupied osv.

			// Make triangles and lines 

			for (int k = 0; k <= 5; k++) {
				testGrid.append(sf::Vertex(t.getCenter(), col));
				testGrid.append(sf::Vertex(t.getPoint(k),col));
				testGrid.append(sf::Vertex(t.getPoint(k == 5 ? 0 :k+1) , col));
				testGridLines.append(sf::Vertex(t.getPoint(k), sf::Color::Black ));
				testGridLines.append(sf::Vertex(t.getPoint(k == 5 ? 0 : k + 1), sf::Color::Black));
			}
			

		}
	}
}

void Game::initStartAndEndPoints(Tile& startPosition, Tile& endPosition) {
	
	
	this->start = &startPosition;
	this->end = &endPosition;

	this->end->wall = false;
	this->start->wall = false;
	sorter.insert(&startPosition);
	
	//openSet.push_back(&startPosition);
	//closedSet.push_back(&endPosition); // can't remember if this should be included
	

}
void Game::initPathStartCondition() {
	//openSet.push_back(&start);
}
void Game::initOrganism(int rowPos, int colPos, Organism& organism) {
	// This is temperary to try the organism object
	/*
		- if position is not out of bound, not occupied and not a wall
	*/
	if ( 0 <= rowPos && 0 <= colPos && colPos < cols && rowPos < rows &&
		this->grid[rowPos][colPos].occupiedByOrganism == false &&
		this->grid[rowPos][colPos].wall == false ) {
	
		
		organism.setPosition( &(this->grid[rowPos][colPos]) );

	} else {
		throw std::runtime_error("Organism position out of bound, tile is a wall or occupied");
	}
	
	organism.initTexture("Textures/Player/testSprites2.PNG");
	organism.initVariables();
}

void Game::initMouseInTileDetection() {
	/*
		- look at the grid and see if the mouse is in one of the tiles via raycasting
	*/

	
	// Konverter musens position fra vindueskoordinater til verdenskoordinater
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->grid[i][j].isMouseInTile(this->mousePosWindow);
			
			if (this->grid[i][j].mouseIsInTile) {
				mouseInsideOfGrid = true;
				lastDetectedTileByMouse = &(this->grid[i][j]);
				break;
			} else {
				mouseInsideOfGrid = false;
			}
		}
		if (mouseInsideOfGrid) {
			break;
		}
	}

	

}

//constructors/ destructors
Game::Game() { //when you start the game somethings need to be initialized
	//importend to first initialize the variables before the window
	this->initVariables();
	this->initFonts();
	this->initWindow();
	

	this->initEnemies();
	this->initCells();

	/*
	- Declare the grid and its tiles with their variables and properties
	- Add their neighbors for each tile.
			>Both steps happen in initGrid
	- Declare start- and end positions for the path
	- Add the starting point to the openSet
	*/
	this->initGrid();
	this->initTestGrid();
	this->initStartAndEndPoints(grid[0][0], grid[rows-1][cols-1]);
	this->initPathStartCondition();
	this->start_time = std::chrono::high_resolution_clock::now();
	this->initMouseInTileDetection();
	/*
	- Declare objects for testíng
	*/
	this->playerObject = Organism( &(this->grid) );
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
void Game::updateMousePositions() {
	//updates mouse position mouseposition relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::updateGrid() {
	/*
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].isMouseInTile(mousePosWindow);
		}
	}
	*/
	this->mouseInGridDetection();
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

		this->mapHelper.saveMap(filename, this->grid);
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

		this->mapHelper.loadMap(filename, this->grid);
		loadModeActive = false;
		std::cout << "Map succesfully loaded map with name: " << filename << "!" << "\n";
	}
}

void Game::deleteLevel() {

}

void Game::moveCells() { // just for test
	this->Cell.setPoint(0, this->Cell.getPoint(0) + sf::Vector2f(1.001, 0));
}

void Game::chooseDirectionOfGridMovement(sf::Vector2f mousePos ) {
	/*
	// choose direction depending on where the mouse is. Areas around the edge
	*/
	if (mousePos.x) {

	}
}

void Game::moveGrid(sf::Vector2f direction) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//grid[i][j].moveTile(direction);
		}
	}
}
/*
void Game::movePlayerPosition() {
	this->playerObject.updatePosition( );

}*/


void Game::mouseInGridDetection() {
	// activate upon Mouse Movement
	/*
	if (lastDetectedTileByMouse == nullptr ) {
		std::cout << "Debug" << "\n";
		this->initMouseInTileDetection();
	} else if (!mouseInsideOfGrid && lastDetectedTileByMouse != nullptr) {
		// check egdes
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (!(0 < i && i < rows - 1 && 0< j && j< cols-1 )) {
					grid[i][j].isMouseInTile(mousePosWindow);
					if (grid[i][j].mouseIsInTile) {
						lastDetectedTileByMouse = &grid[i][j];
						mouseInsideOfGrid = true;
						std::cout << "mouse is in: " << i << "," << j <<  "and came from outside" <<"\n";
						return;
					}
				}
			}
		}

	} else {
		// check if still in the same tile
		lastDetectedTileByMouse->isMouseInTile( mousePosWindow );
		if (lastDetectedTileByMouse->mouseIsInTile) {
			//std::cout << "mousePos not changed and is at: " << lastDetectedTileByMouse->xRow << ","<< lastDetectedTileByMouse->yRow << "\n";
			return;
		}
		//check if the mouse is now in one of the neighbors
		int numOfNeighbors = lastDetectedTileByMouse->neighbors.size();
		for (int i = 0; i < numOfNeighbors; i++) {
			Tile* currentNeighbor = lastDetectedTileByMouse->neighbors[i];
			currentNeighbor->isMouseInTile(this->mousePosWindow);
			if (currentNeighbor->mouseIsInTile) {
				std::cout << "new tile " << "\n";
				lastDetectedTileByMouse = currentNeighbor;
				return;
			}
		}
		mouseInsideOfGrid = false;
		lastDetectedTileByMouse = nullptr; // if you tap out this is for safety
	}

	*/
}

//mouse in grid detection will be outdated afterwards
void Game::mouseInTileDetection() {
	// can this be optimized?
	
	double rHorizontal =  grid[0][0].r_1; // cos(grid[0][0].construcangle) *
	double rVertical = grid[0][0].r_2;

	int colGuess = (int) (this->mousePosWindow.x-gridOffset)/(rHorizontal*2);
	int rowGuess = (int)(this->mousePosWindow.y - gridOffset) / (rVertical * 2);
	




	std::cout << "Guess coordinates: " << rowGuess << ","<< colGuess << "\n";
}


std::pair<int, int> Game::mouseToGrid(sf::Vector2i mousePos) {
	float x = static_cast<float>(mousePos.x);
	float y = static_cast<float>(mousePos.y);

	const float angle = this->grid[0][0].construcangle * 3.14159265f / 180.f;

	const float dx = 2.f * this->grid[0][0].r_1 * cos(angle); // r_1 = 15
	const float dy = this->grid[0][0].r_1 * 2.f * sin(angle) + (this->grid[0][0].r_2 - cos((90.f - this->grid[0][0].construcangle) * 3.14159265f / 180.f) * this->grid[0][0].r_1);

	int approxRow = static_cast<int>((y - 100.f) / dy);
	approxRow = std::max(0, std::min(rows - 1, approxRow));

	float offsetX = (approxRow % 2 == 0) ? (15.f * cos(angle)) : 0.f;

	int approxCol = static_cast<int>((x - 100.f - offsetX) / dx);
	approxCol = std::max(0, std::min(cols - 1, approxCol));

	// refine by checking this tile + neighbors only
	Tile* bestTile = nullptr;

	std::vector<Tile*> candidates;
	candidates.push_back(&grid[approxRow][approxCol]);

	for (Tile* n : grid[approxRow][approxCol].neighbors)
		candidates.push_back(n);

	for (Tile* t : candidates)
	{
		if (t->getBoundingBoxMinX() <= x && x <= t->getBoundingBoxMaxX() &&
			t->getBoundingBoxMinY() <= y && y <= t->getBoundingBoxMaxY())
		{
			// final precise check
			bool inside = false;
			size_t numPoints = t->hexagon.getPointCount();

			for (size_t i = 0, j = numPoints - 1; i < numPoints; j = i++)
			{
				sf::Vector2f vi = t->getPoint(i);
				sf::Vector2f vj = t->getPoint(j);

				bool intersect = ((vi.y > y) != (vj.y > y)) &&
					(x < (vj.x - vi.x) * (y - vi.y) / (vj.y - vi.y) + vi.x);

				if (intersect)
					inside = !inside;
			}

			if (inside)
				std::cout << "the guess is: " << t->xRow << "," << t->yRow << "\n";
				return { t->xRow, t->yRow };
		}
	}
	std::cout << "fail " << "\n";
	return { -1, -1 };
}

void Game::leftMouseClickExecution() {
	/*
	// complete List of what to execute when right mouse buttom is pressed:
	//	-Detction of mouse press in a tile
	*/
	
	
	//this->mouseInGridDetection();
}

void Game::rightMouseClickExecution() {
	/*
	// complete List of what to execute when left mouse buttom is pressed:
	//	-Detction if mouse pressed player
	*/
	//this->playerObject.mouseInSprite(this->mousePosWindow);
	
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
				this->mouseInTileDetection();
				std::cout << "there was a buttonRealese" << "\n";

			} else if (this->ev.mouseButton.button == sf::Mouse::Right) {
				this->rightMouseClickExecution();
				std::cout << "there was a buttonRealese" << "\n";
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
	//this->moveCells();
	this->updatePath();
	this->updateFrameRate();
	//this->frameRate();
	//this->mouseInGridDetection();
	this->mouseToGrid(mousePosWindow);
	//this->movePlayerPosition(); // move playerPosition
	
	//Player
	this->updatePlayerObject();

}

void Game::updatePath() {
	
	//if there is more to check'
	if (runPathfinding) {
		if (sorter.heap.size() > 0) {
		//if (openSet.size() > 0) {
			//best Option
			size_t winner = 0;
			/*
			for (size_t i = 0; i < openSet.size(); i++) {
				if (openSet[i]->f < openSet[winner]->f) {
					winner = i;
				}
			}
			*/
			auto current = sorter.heap[0];
			//auto current = openSet[winner];
			
			//did we finish?
			if (current->yRow == end->yRow && current->xRow == end->xRow) {

				Tile* temp = current;
				path.push_back(temp);
				while (!((temp->previous) == NULL)) {
					path.push_back(temp->previous);
					temp = temp->previous;
				}
				playerPosition = path.size() - 1; 
				pathFindingComplete = true;

				std::cout << "mission is complete!";
				this->end_time = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsed_seconds = this->end_time - this->start_time;
				std::cout << "Time spent from start to end: " << (elapsed_seconds).count() << std::endl;
				this->runPathfinding = false;
			}
			//openSet.erase(current);
			//std::remove: Denne funktion flytter de elementer, der skal fjernes, til slutningen af vektoren og returnerer en iterator til den første af disse elementer
			//erase: Fjerner de flyttede elementer fra vektoren ved hjælp af iteratoren, der blev returneret af std::remove.
			
			//openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end()); // this is the correct one to comment back in
			
			sorter.delMin();
			closedSet.push_back(current);
			std::vector<Tile*> neighbors = current->neighbors;
			
			for (size_t i = 0; i < neighbors.size(); i++) {
				Tile* neighbor = neighbors[i];
				if (!includesTile(closedSet, neighbor) && ! neighbor->wall) { // include wall here
					double tempG = current->g + 1;
					// maybe a new path?
					bool newPath = false;
					if (includesTile(sorter.heap, neighbor)) {
					//if (includesTile(openSet, neighbor)) {
						if (tempG < neighbor->g) {
							neighbor->g = tempG;
						}
					}
					else {
						neighbor->g = tempG;
						newPath = true;
						//openSet.push_back(neighbor);
						sorter.insert(neighbor);
					}
					if (newPath) {
						neighbor->h = heuristic(neighbor, end);
						//neighbor->f = neighbor->g + neighbor->h
						sorter.changeFValue(sorter.latestInsertedIndex, neighbor->g + neighbor->h);
						
						neighbor->previous = current;
					}
				}
			}
		}
		else {
			std::cout << "no solution... Panic!!!!";
			this->runPathfinding = false;
			return;
		}
	}
}
// player stuff
void Game::updatePlayerObject() {
	playerObject.updatePosition();
	playerObject.updateSpriteLocation();
	playerObject.updateMovement(0,0); // later this should instead be the next tile should be moving towards Keyboard movement
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
	//this->window->clear(sf::Color(255, 0, 0, 255)); // just makes the background a color
	this->window->clear(); 

	// draw next frame
	
	// Renders the grid
	// This part slows performance greatly when many rows or columns are applied
	this->window->draw(testGrid);
	this->window->draw(testGridLines);
	/*
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].display( *this->window, 250,250,250);
		}
	}
	*/
	
	
	// the closed set
	for (int i = 0; i < closedSet.size(); i++) {
		closedSet[i]->display(*this->window , 250, 0, 0);
	}
	
	// the open set
	
	for (int i = 0; i < openSet.size(); i++) {
		openSet[i]->display(*this->window, 0, 250,0);
	}
	
	
	for (int i = 0; i < sorter.heap.size(); i++) {
		sorter.heap[i]->display(*this->window, 0, 250, 0);
	}

	// the path
	for (int i = 0; i < path.size(); i++) {
		path[i]->display(*this->window, 0, 0, 255);
	}
	
	//movement along the path
	if (pathFindingComplete) {
		
		if (initialFrame % 10 == 0 && playerPosition != 0 ){
			playerPosition--;
		}
		path[playerPosition]->display(*this->window, 100, 100, 255);
		
		initialFrame++;
	}
	
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