#include "BasicMenu.h"	
// ------------------- public -------------------
// ------------------ Initialization ------------------
void BasicMenu::initBasicMenuByRectangleShape(sf::Vector2f position, float width, float height) {
	// This method should only be used for quick tests as we do not initialize textures and sprites 
	// Set the origin to the center of the rectangle
	//this->getSpriteBoarder().setOrigin(sf::Vector2f(width, height) * 0.5f);
	//this->getSpriteBoarder().setPosition(position);
	//this->getSpriteBoarder().setSize(sf::Vector2f(width, height));
	
	this->center = position;
}

void BasicMenu::initButtons() {
	sf::Sprite middleSprite = this->getCenterSprite();
	
	auto exitButton = std::make_unique<BasicButton>(middleSprite.getGlobalBounds().getPosition().x + middleSprite.getTextureRect().getSize().x * middleSprite.getScale().x/2,
														middleSprite.getGlobalBounds().getPosition().y + middleSprite.getTextureRect().getSize().y / 4,
														middleSprite.getTextureRect().getSize().x,
														middleSprite.getTextureRect().getSize().y / 4);

	exitButton->initFont("Fonts/alagard.ttf");
	
	
	exitButton->initTextColor(sf::Color::Black);
	exitButton->initTextSize(20);
	exitButton->initText("Test Of button");

	sf::Vector2f pos = sf::Vector2f(exitButton->getButtonPosition()) 
						+ sf::Vector2f(exitButton->getSize().x/2, exitButton->getSize().y / 2) 
							- sf::Vector2f(exitButton->getText().getGlobalBounds().getSize().x/2, exitButton->getText().getGlobalBounds().getSize().y / 2);
	exitButton->initTextPosition( pos );
	this->addButton(std::move(exitButton) );
}


// ------------------ Setters ------------------	
void BasicMenu::setMenuPosition(sf::Vector2f position) {
	this->setPosition(position.x, position.y);
	int numOfButtons = this->getButtons().size();
	if (0 < this->getButtons().size()) {
		float placementY = 0;
		for (int i = 0; i < numOfButtons; i++) {
			sf::Vector2f position = sf::Vector2f(this->getCenterSprite().getTextureRect().getPosition().x + (this->getCenterSprite().getTextureRect().getSize().y * this->getCenterSprite().getScale().x/2), 
													this->getCenterSprite().getTextureRect().getPosition().y + this->getButtons()[i]->getSize().y * this->getCenterSprite().getScale().y / 2);
			
			this->getButtons()[i]->setPosition(position);
		}
	}
}
// ------------------ Getters ------------------
sf::Vector2f BasicMenu::getPoint(int index) {
	if (index < 0 || index >= 4) {
		throw std::runtime_error("BasicMenu: index out of bounds");
	}
	switch (index) {
	case 0:
		return sf::Vector2f(0,0);//this->getSpriteBoarder().getPoint(0) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 1:
		return sf::Vector2f(0, 0);//this->getSpriteBoarder().getPoint(1) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 2:
		return sf::Vector2f(0, 0);//this->getSpriteBoarder().getPoint(2) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	case 3:
		return sf::Vector2f(0, 0);//this->getSpriteBoarder().getPoint(3) + this->getSpriteBoarder().getPosition() - this->getSpriteBoarder().getOrigin();
	}
}

sf::Vector2f BasicMenu::getCenter() {
	return this->center;
}
/*
sf::RectangleShape&	BasicMenu::getMenuShape() {
	return this->getSpriteBoarder();
}
*/

// ------------------ Adders -------------------

// ------------------ Actions ------------------	

// ------------------- private -------------------
// ------------------ Initialization ------------------

// ------------------ Setters ------------------	

// ------------------ Getters ------------------

// ------------------ Adders -------------------

// ------------------ Actions ------------------
bool BasicMenu::containsPoint(sf::Vector2i point) {
	if (this->getSpritePartition(0).getGlobalBounds().getPosition().x < point.x && this->getSpritePartition(0).getGlobalBounds().getPosition().y < point.y &&
		this->getSpritePartition(8).getGlobalBounds().getPosition().x+ this->getSpritePartition(8).getSize().x > point.x && 
		this->getSpritePartition(8).getGlobalBounds().getPosition().y + this->getSpritePartition(8).getSize().y > point.y) {
		
		return true;
	}
	return false;
}

void BasicMenu::isHovered(sf::Vector2i mousePos) {
	if (this->containsPoint(mousePos)) {
		int numOfButtons = this->getButtons().size();
		
		if (0 < numOfButtons) {
			for (int i = 0; i < numOfButtons; i++) {
				this->getButtons()[i]->isHovered(mousePos);
			}
		}
	}
}

void BasicMenu::drawMenu(sf::RenderTarget& window) {
	if (this->getToggleState()) {
		this->draw(window);
		int numOfButtons = this->getButtons().size();
		if (0 < numOfButtons) {
			
			for (int i = 0; i < numOfButtons; i++ ) {
				
				(this->getButtons()[i])->draw(window);
			}
		}
	}
	if (this->getToggleState() && showSpritePartition) {
		this->drawSpritePartition(window);
	}
}

void BasicMenu::calculateCenter() {
	/*
	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < 4; i++) {
		sf::Vector2f point = this->getSpriteBoarder().getPoint(i);
		sumX += point.x;
		sumY += point.y;
	}
	center.x = sumX / 4;
	center.y = sumY / 4;
	*/
}

void BasicMenu::toggleMenuStatus() {
	this->setToggleMenuStatus( !(this->getToggleState())) ;
	if ( !(this->getToggleState()) ) {
		this->showSpritePartition = false;
	}
}

void BasicMenu::toggleSpritePartition() {
	this->showSpritePartition = !(this->showSpritePartition);
}

void BasicMenu::handleByDrag(sf::Vector2i point) {
	if (this->getDraggedStatus()) {

		this->expandUpToPoint(point);
		this->expandDownToPoint(point);
		this->expandLeftToPoint(point);
		this->expandRightToPoint(point);
		this->moveSlicesToPoint(point);
		this->updateButtons();
	}
}

// ---------------------------- Private -----------------------------
// ----------------- Actions -------------
void BasicMenu::updateButtons() {
	int numOfButtons = this->getButtons().size();
	if (0 < numOfButtons) {
		
		float posX = this->getCenterSprite().getGlobalBounds().getPosition().x + this->getCenterSprite().getTextureRect().getSize().x * this->getCenterSprite().getScale().x / 2;
		for (int i = 0; i < numOfButtons; i++) {
			this->getButtons()[i]->setSize(sf::Vector2f(this->getCenterSprite().getTextureRect().getSize().x * this->getCenterSprite().getScale().x,
															this->getButtons()[i]->getSize().y));

			this->getButtons()[i]->setPosition(sf::Vector2f(posX, this->getCenterSprite().getGlobalBounds().getPosition().y + this->getButtons()[i]->getSize().y));
		}
	}
}