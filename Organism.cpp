#include "Organism.h"
#include "commonFunctions.h"
#include <cassert>
/*
// notes to self:
//		- you can move down as usual but if you try to move again you start from initial point and then it crashes 
*/
void Organism::initVariables() {
	this->moveTileTimer.restart();
	this->interTileTimer.restart();
	this->animationTimer.restart();
}


void Organism::initSprite() {
	// Set the texture to the sprite
	this->currentFrame = sf::IntRect(0, 0, 45, 62);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setOrigin(this->currentFrame.width / 2, this->currentFrame.height);
	this->sprite.setPosition(currerntPosition->midx, currerntPosition->midy);

	// Resize the sprite
	this->sprite.scale(1.0f, 1.0f);
}

void Organism::calculatePath( Tile* targetPosition ) {
	//THis can probably be optimized since our steps are limited.
	
	if (targetPosition == currerntPosition) {
		return;
	}
	resetPathfinding();
	targetPosition->mousePressedTile = true;
	runPathfinding = true; 
	while (runPathfinding) {
		if (this->sorter.heap.size() > 0) {
			size_t winner = 0;

			auto current = this->sorter.heap[0];

			//did we finish?
			if (current->yRow == targetPosition->yRow && current->xRow == targetPosition->xRow) {

				Tile* temp = current;
				pathForOrganism.push_back(temp);
				while (!((temp->previous) == NULL) && temp->previous != temp) {
					pathForOrganism.push_back(temp->previous);
					temp = temp->previous;
				}
				playerPosition = pathForOrganism.size() - 1;
				pathFindingComplete = true;
				moving=true;
				this->runPathfinding = false;
			}

			this->sorter.delMin();
			this->closedSet.push_back(current);
			std::vector<Tile*> neighbors = current->neighbors;

			for (size_t i = 0; i < neighbors.size(); i++) {
				Tile* neighbor = neighbors[i];
				if (!includesTile(closedSet, neighbor) && !neighbor->wall) { // include wall here
					double tempG = current->g + 1;
					// maybe a new path?
					bool newPath = false;
					if (includesTile(sorter.heap, neighbor)) {
						if (tempG < neighbor->g) {
							neighbor->g = tempG;
						}
					}
					else {
						neighbor->g = tempG;
						newPath = true;
						sorter.insert(neighbor);
					}
					if (newPath) {
						neighbor->h = heuristic(neighbor, targetPosition);
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

// Animations

void Organism::updatePosition(){
	if (moveTileTimer.getElapsedTime().asSeconds() >= interTileTime &&
		pathFindingComplete &&
		0 < movementPoints  &&
		usedMovementPoints <= movementPoints) {

		moving = true;

		// if used all movementPoints then reset usedMovementPoints and sorter with current playerposition as its initial point 
		// this can probably be a part of the other if-statement inside
		if (movementPoints == usedMovementPoints ||
			currerntPosition == pathForOrganism[0]) {
			std::cout << "got to here" << "\n";
			moving = false;
			resetPathfinding();
			return;
		}

		//move PlayerPosition if not at the and the we have not used all the movementPoints
		if (playerPosition != 0 &&
			movementPoints != usedMovementPoints) {

			movementTimer = 0.f; // can be removed

			//std::cout << "used MovementPoints: " << usedMovementPoints << "\n";
			playerPosition--;
			usedMovementPoints++;
			if (playerPosition < pathForOrganism.size() - 1) {
				pathForOrganism[playerPosition + 1]->occupiedByOrganism = false;
			}
			pathForOrganism[playerPosition]->occupiedByOrganism = true;
			this->currerntPosition = pathForOrganism[playerPosition];

			this->sprite.setPosition(this->currerntPosition->midx, this->currerntPosition->midy);

			if (playerPosition == 0) {
				moving = false;
			}
		}

		this->moveTileTimer.restart();
		this->interTileTimer.restart();
		this->animationTimer.restart();
	}
}

void Organism::updateSpriteLocation() {
	/*
		- Update the interTile location
	*/
	std::vector<float> speed; // should be a private variable
	int timeSteps = 20; // should be a private variable

	if (moving && interTileTimer.getElapsedTime().asSeconds() >=interTileTime/(timeSteps) && usedMovementPoints != movementPoints ) {
		// calculations of speed should calculated as seen position is updated or the screen is moved (later) and not every frame 
		// figure out why it is neccesary to say * 2
		
		speed = {(float)(pathForOrganism[playerPosition - 1]->midx - currerntPosition->midx) / interTileTime,
				 (float)(pathForOrganism[playerPosition - 1]->midy - currerntPosition->midy) / interTileTime};

		this->sprite
			.setPosition(
				this->sprite.getPosition().x + speed[0]/timeSteps , 
				this->sprite.getPosition().y + speed[1]/timeSteps );

		
		interTileTimer.restart();

	}
}


void Organism::updateSprite() { // skal rettes
	/*
		- Checks the direction of the next tile and compares it to the current
	*/
	if (moving && usedMovementPoints != movementPoints) {
		if (animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) {
			//std::cout << "Moving from:" << "(" << currerntPosition->xRow << "," << currerntPosition->yRow << ")" << " -> " << "(" << pathForOrganism[playerPosition - 1]->xRow << "," << pathForOrganism[playerPosition - 1]->yRow << ")" << "\n";
		}
		if (pathForOrganism[playerPosition - 1]->xRow == currerntPosition->xRow &&
			pathForOrganism[playerPosition - 1]->yRow < currerntPosition->yRow &&
			animationTimer.getElapsedTime().asSeconds()>= interTileTime/interTileSprites) { // moving left

			spriteIndexX += 1;
			spriteIndexY = 1;
			this->sprite.setScale(1.f,1.f);
			
		} else if (pathForOrganism[playerPosition - 1]->xRow == currerntPosition->xRow &&
					pathForOrganism[playerPosition - 1]->yRow > currerntPosition->yRow &&
					animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) { // moving right
			
			spriteIndexX += 1;
			spriteIndexY = 0;
			this->sprite.setScale(1.f, 1.f);
			
		} else if ( (pathForOrganism[playerPosition - 1]->midx < currerntPosition->midx &&
					pathForOrganism[playerPosition - 1]->midy >  currerntPosition->midy) &&
					animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) { // down left

			

			spriteIndexX += 1;
			spriteIndexY = 3;
			this->sprite.setScale(1.f, 1.f);
			
		} else if ((pathForOrganism[playerPosition - 1]->midx < currerntPosition->midx &&
					pathForOrganism[playerPosition - 1]->midy < currerntPosition->midy ) &&
					animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) { // up left

			spriteIndexX += 1;
			spriteIndexY = 2;
			this->sprite.setScale(1.f, 1.f);
			
		} else if ((pathForOrganism[playerPosition - 1]->midx > currerntPosition->midx &&
					pathForOrganism[playerPosition - 1]->midy < currerntPosition->midy) &&
					animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) { // up right

			
			spriteIndexX += 1;
			spriteIndexY = 2;
			this->sprite.setScale(-1.f, 1.f);
			
		} else if ((pathForOrganism[playerPosition - 1]->midx > currerntPosition->midx &&
			pathForOrganism[playerPosition - 1]->midy > currerntPosition->midy) &&
			animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) { // down right

			spriteIndexX += 1;
			spriteIndexY = 3;
			this->sprite.setScale(-1.f, 1.f);
			
		}

		if (animationTimer.getElapsedTime().asSeconds() >= interTileTime / interTileSprites) {
			
			currentFrame = sf::IntRect(spriteIndexX* currentFrame.width, spriteIndexY*currentFrame.height, currentFrame.width, currentFrame.height);
			this->sprite.setTextureRect(currentFrame);
			if (spriteIndexX == 7) {
				spriteIndexX = 0;
			}
			animationTimer.restart();
		}

	} else {
		// stopped moving
		int scalingFactorSign = this->sprite.getScale().x;
		

		if (spriteIndexY == 0 && scalingFactorSign > 0 ) {// right
			this->sprite.setScale(1.f, 1.f);
			currentFrame = sf::IntRect(0, 4*currentFrame.height, currentFrame.width, currentFrame.height);

		} else if (spriteIndexY == 1 && scalingFactorSign >0 ) {// left
			this->sprite.setScale(1.f, 1.f);
			currentFrame = sf::IntRect(currentFrame.width, 4*currentFrame.height, currentFrame.width, currentFrame.height);

		} else if (spriteIndexY==2 && scalingFactorSign > 0) {// up left
			this->sprite.setScale(1.f, 1.f);
			currentFrame = sf::IntRect(spriteIndexY*currentFrame.width, 4*currentFrame.height, currentFrame.width, currentFrame.height);

		} else if (spriteIndexY == 3 && scalingFactorSign >0 ) { // down left
			this->sprite.setScale(1.f, 1.f);
			currentFrame = sf::IntRect(spriteIndexY*currentFrame.width, 4*currentFrame.height, currentFrame.width, currentFrame.height);

		} else if (spriteIndexY == 2 && scalingFactorSign < 0) {// up right
			this->sprite.setScale(-1.f, 1.f);
			currentFrame = sf::IntRect(spriteIndexY*currentFrame.width, 4*currentFrame.height, currentFrame.width, currentFrame.height);

		} else if (spriteIndexY == 3 && scalingFactorSign < 0) { // down right
			this->sprite.setScale(-1.f, 1.f);
			currentFrame = sf::IntRect(spriteIndexY*currentFrame.width, 4*currentFrame.height, currentFrame.width, currentFrame.height);
		}
		this->sprite.setTextureRect(currentFrame);
	}

	
}
/*
	- If mouse is in sprite while pressed and not moving then update sprite by rotating clockwise
	- should be scale safe for future
*/
void Organism::rotateOrganism(sf::Vector2i mousePos) {
	if (mouseInSprite( mousePos) && !moving ) {
		int scalingFactorSign = this->sprite.getScale().x;
		// Last movement direction should rotate clockwise
		if (spriteIndexY == 0 && scalingFactorSign > 0) {// East to South East
			spriteIndexY = 3;
			this->sprite.setScale(-1.f* this->sprite.getScale().x, 1.f);

		} else if ( spriteIndexY == 3  && scalingFactorSign < 0) { // South East to South West
			this->sprite.setScale(-1.f* this->sprite.getScale().x,1.f);

		} else if (spriteIndexY == 3 && scalingFactorSign > 0) { // South West to West
			spriteIndexY = 1;

		} else if (spriteIndexY == 1 && scalingFactorSign > 0 ) { // West to north West
			spriteIndexY = 2;
		
		} else if (spriteIndexY == 2 && scalingFactorSign > 0) { // north west to north East
			this->sprite.setScale(-1.f* this->sprite.getScale().x,1.f);

		} else if (spriteIndexY == 2 && scalingFactorSign < 0) { // north east to east
			spriteIndexY = 0;
			this->sprite.setScale(-1.f* this->sprite.getScale().x,1.f);
		}

		this->updateSprite();
	}
}

// Helper methods

void Organism::resetPathfinding() {
	usedMovementPoints = 0;
	pathFindingComplete = false;
	// Remove all elements after index 0
	
	// reInitialize sorter
	sorter.clear();
	sorter.insert(currerntPosition);
	
	if (grid != nullptr) {
		for (auto& row : *grid) {
			for (auto& tile : row) {
				tile.previous = nullptr;
				tile.g = 0;
				tile.h = 0;
				tile.mousePressedTile = false;
			}
		}
	}
	this->closedSet.clear();
	this->pathForOrganism.clear();

	//restart all timers
	moveTileTimer.restart();
	interTileTimer.restart();
	animationTimer.restart();
}

void Organism::setPosition( Tile* newPosition ) {
	if (newPosition->wall == false) { // should also do something with the position tile aka set the tiles value
		newPosition->occupiedByOrganism = true;
		newPosition->placeOrganismInTile(*this);
		this->currerntPosition = newPosition;
		this->sorter.insert(newPosition);
	}else{
		throw std::runtime_error("Chosen position is a wall");
	}
}

std::vector<Tile*> Organism::returnCalculatedPath() {
	return pathForOrganism;
}

void Organism::updateMovement(int nextTileX, int nextTileY) {
	//debugging for now
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {// right
		this->sprite.move(1.f,0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {// left
		this->sprite.move(-1.f, 0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {// up
		this->sprite.move(0.f, -1.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { // down
		this->sprite.move(0.f, 1.f);
	}
}