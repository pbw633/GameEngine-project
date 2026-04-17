#include "StorageContainer.h"
#include <stdexcept>

void StorageContainer::initVariables() {
	this->moveTileTimer.restart();
	//this->interTileTimer.restart();
	this->animationTimer.restart();
}

void StorageContainer::initSprite() {
	// Set the texture to the sprite
	this->currentFrame = sf::IntRect(0, 0, 45, 63);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(this->currentFrame);

	// Resize the sprite
	this->sprite.scale(1.0f, 1.0f);
}

void StorageContainer::initTexture(std::string fileName) {
	this->initTextureSheet(fileName);
	this->initSprite();
}

void StorageContainer::initTextureSheet(std::string fileName) {
	// Load Texture from file'
	if (!this->texture.loadFromFile(fileName)) {
		throw std::invalid_argument("StorageContainer::initTexture::Could not load textureFile from filename. Have you remembered location?");
	}

	if (!texture.loadFromFile(fileName)) {
		std::cout << "Failed loading texture: " << fileName << std::endl;
	}
	else {
		//std::cout << "Loaded texture: " << fileName << std::endl;
	}
}

bool StorageContainer::mouseInSprite(sf::Vector2i mousePos){
	// can be optimized as the convertion to img is very heavy but is alright since it is only done once
	sf::Vector2f localPos = this->sprite.getInverseTransform().transformPoint((sf::Vector2f) mousePos);
	sf::IntRect rect = this->sprite.getTextureRect();

	int x = static_cast<int>(localPos.x);
	int y = static_cast<int>(localPos.y);

	// if mouse is not even in the sprite then leave
	if (x < 0 || y < 0 || x >= rect.width || y >= rect.height){
		mouesInSpriteBool = false;
		return false;
	}

	// Konverter lokale coords 
	x += rect.left;
	y += rect.top;

	// convert texture to image 
	sf::Image img = this->sprite.getTexture()->copyToImage();

	// look at the alpha value 
	if (img.getPixel(x, y).a > 0) {
		mouesInSpriteBool = true;
		std::cout << "sprite pressed" << "\n";
		return true;
	} else {
		return false;
		mouesInSpriteBool = false;
	}
}

void StorageContainer::dropItem( int itemIndex ) {
	if (itemIndex < inventory.size() && itemIndex > -1) {
		inventory.erase(inventory.begin() + itemIndex);
	} else {
		throw std::invalid_argument("Item Index out of storage range");
	}
}

void StorageContainer::addItem(Item* item) {
	inventory.push_back( item );
}




void StorageContainer::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
}

