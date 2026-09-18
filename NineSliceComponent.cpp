#include "NineSliceComponent.h"
// ----------------- Initialize ---------------
void NineSliceComponent::initPartition(sf::Vector2f partitionX, sf::Vector2f partitionY) {
	float minPartitionX = std::min(partitionX.x, partitionX.y);
	float minPartitionY = std::min(partitionY.x, partitionY.y);
	float maxPartitionX = std::max(partitionX.x, partitionX.y);
	float maxPartitionY = std::max(partitionY.x, partitionY.y);

	if (minPartitionX < 0.0f || minPartitionY < 0.0f || maxPartitionX > 1.0f || maxPartitionY > 1.0f) {
		throw std::invalid_argument("NineSliceComponent::initPartition:: Partition values must be between 0 and 1.");
	}

	this->spritePartitionX = sf::Vector2f(minPartitionX, maxPartitionX);
	this->spritePartitionY = sf::Vector2f(minPartitionY, maxPartitionY);
}

void NineSliceComponent::initSprites() {
	/*
		first initialize a mainSprite and then split 
	*/
	if (this->getTexture().getSize().x == 0 || this->getTexture().getSize().y == 0) {
		throw std::runtime_error("NineSliceComponent::initSprites:: There is no texture to slice");
	}
	//this->initSprite();

	float width = this->getTextureWidth();
	float height = this->getTextureHeight();

	float minPartitionY = spritePartitionY.x;
	float minPartitionX = spritePartitionX.x;
	float maxPartitionY = spritePartitionY.y;
	float maxPartitionX = spritePartitionX.y;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			float tempX = 0.0f;
			float tempY = 0.0f;
			float tempWidth = 0.0f;
			float tempHeight = 0.0f;

			// Calculate the position and size of each sub-rectangle
			if (i == 0) {
				tempY = 0.0f;
				tempHeight = minPartitionY * height;
			}
			else if (i == 1) {
				tempY = minPartitionY * height;
				tempHeight = (maxPartitionY - minPartitionY) * height;
			}
			else {
				tempY = maxPartitionY * height;
				tempHeight = (1.0f - maxPartitionY) * height;
			}

			if (j == 0) {
				tempX = 0.0f;
				tempWidth = minPartitionX * width;
			}
			else if (j == 1) {
				tempX = minPartitionX * width;
				tempWidth = (maxPartitionX - minPartitionX) * width;
			}
			else {
				tempX = maxPartitionX * width;
				tempWidth = (1.0f - maxPartitionX) * width;
			}

			// Used for Possible animation
			sf::IntRect subRect(tempX, tempY, tempWidth, tempHeight);
			this->subFrames.push_back(subRect); 

			// Used to show Boarders of the partition
			sf::RectangleShape subSpriteBoarders;
			//subSpriteBoarders.setPosition(tempX, tempY);
			subSpriteBoarders.setSize(sf::Vector2f(tempWidth, tempHeight));
			//subSpriteBoarders.setOrigin(tempWidth / 2, tempHeight / 2);
			subSpriteBoarders.setFillColor(sf::Color(0,0,0,0));
			subSpriteBoarders.setOutlineColor(sf::Color::Red);
			subSpriteBoarders.setOutlineThickness(1);
			spritePartitions.push_back(subSpriteBoarders);

			// Used for the actual sprites
			sf::Sprite subSprite;
			subSprite.setTexture(this->getTexture());
			subSprite.setTextureRect(subFrames[i*3+j]);
			//subSprite.setPosition(tempX, tempY);
			//subSprite.setOrigin(tempWidth/2, tempHeight/2);
			subSprites.push_back(subSprite);
		}
	}
}

void NineSliceComponent::initSpriteOffsets() {
	// Calculate the offsets of each sub-sprite relative to the center sprite origin

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (col == 0 && row == 0) {// Top-left
				//spriteOffsets.push_back(sf::Vector2f(std::ceil( - subSprites[row * 3 + col].getOrigin().x - subSprites[4].getOrigin().x),
				//										std::ceil( - subSprites[row * 3 + col].getOrigin().y - subSprites[4].getOrigin().y)));
				spriteOffsets.push_back(sf::Vector2f(std::ceil(-subSprites[row * 3 + col].getTextureRect().getSize().x), 
														std::ceil(-subSprites[row * 3 + col].getTextureRect().getSize().y)));
			}
			else if (col == 1 && row == 0) { // Top-center
				spriteOffsets.push_back(sf::Vector2f(0,
					std::ceil(-subSprites[row * 3 + col].getTextureRect().getSize().y)));
			}
			else if (col == 2 && row == 0) { // Top-right
				spriteOffsets.push_back(sf::Vector2f(std::ceil(subSprites[1].getTextureRect().getSize().x),
														std::ceil(-subSprites[row * 3 + col].getTextureRect().getSize().y)));
			}
			else if (col == 0 && row == 1) { // Middle-left
				spriteOffsets.push_back(sf::Vector2f(std::ceil( - subSprites[row * 3 + col].getTextureRect().getSize().x),
																0));
			}
			else if (col == 1 && row == 1) { // Center
				spriteOffsets.push_back(sf::Vector2f(0, 0));
			}
			else if (col == 2 && row == 1) { // Middle-right
				spriteOffsets.push_back(sf::Vector2f(std::floor(subSprites[4].getTextureRect().getSize().x),
																0));
			}
			else if (col == 0 && row == 2) {// bottom left
				spriteOffsets.push_back(sf::Vector2f(-std::ceil(subSprites[row * 3 + col].getTextureRect().getSize().x),
															std::floor(subSprites[4].getTextureRect().getSize().y)));
			}
			else if (col == 1 && row == 2) { // bottom center
				spriteOffsets.push_back(sf::Vector2f(0, 
															std::floor(subSprites[4].getTextureRect().getSize().y )));
			}
			else if (col == 2 && row == 2) { // bottom right
				spriteOffsets.push_back(sf::Vector2f(std::floor(subSprites[4].getTextureRect().getSize().x ),
														std::floor(subSprites[4].getTextureRect().getSize().y)));
			}

		}
	}
}

// ------------------ Setters ------------------
void NineSliceComponent::setPosition(float x, float y) {
	
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::setPosition::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	
	sf::Vector2f centeringByMiddleSprite = sf::Vector2f(subSprites[4].getTextureRect().getSize().x * subSprites[4].getScale().x,
															subSprites[4].getTextureRect().getSize().y * subSprites[4].getScale().y);
	for (int i = 0; i < 3; i++) {
		//spriteOffset.y = spriteOffset.y + subSprites[i * 3].getOrigin().y;
		for (int j = 0; j < 3; j++) {
			
				
			subSprites[i*3+j].setPosition(spriteOffsets[i*3+j].x + x- centeringByMiddleSprite.x/2, spriteOffsets[i*3+j].y + y- centeringByMiddleSprite.y/2);
			spritePartitions[i * 3 + j].setPosition(spriteOffsets[i * 3 + j].x + x - centeringByMiddleSprite.x / 2, spriteOffsets[i * 3 + j].y + y - centeringByMiddleSprite.y / 2);
			
		}
	}
	
	
}
// ------------------ Getters ------------------
sf::RectangleShape& NineSliceComponent::getSpritePartition(int index) {
	if (index < 0 || index >= 9) {
		throw std::runtime_error("NineSliceComponent::getSpritePartition::Index out of bounds. Must be between 0 and 8.");
	}
	if (spritePartitions.size() != 9 ) {
		throw std::runtime_error("NineSliceComponent::getSpritePartition::Sprite partitions not initialized.");	
	}
	return spritePartitions[index];
}

std::vector<sf::RectangleShape>& NineSliceComponent::getSpritePartitions() {
	if (spritePartitions.size() != 9) {
		throw std::runtime_error("NineSliceComponent::getSpritePartition::Sprite partitions not initialized.");
	}
	return spritePartitions;
}

// ------------------ Adders -------------------

// ------------------ Actions ------------------
void NineSliceComponent::draw(sf::RenderTarget& window) {
	if (subSprites.size() != 9 ) {
		throw std::runtime_error("NineSliceComponent::draw::This class needs 9 sprites to do 9-slicing... Duh");
	}
	
	for (int i=0; i<9; i++) {
		window.draw(subSprites.at(i));
		
	}
}


void NineSliceComponent::drawSpritePartition(sf::RenderTarget& window) {
	if (spritePartitions.size() != 9) {
		throw std::runtime_error("NineSliceComponent::drawSpritePartition::This class needs 9 sprite partitions");
	}
	for (int i = 0; i < 9; i++) {

		window.draw(spritePartitions.at(i));
	}
}

void NineSliceComponent::expandUpToPoint(sf::Vector2i point) {
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::expandUpToPoint::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	// if the point is within the bounds of the top  middle partition, then expand the top partition to that point
	if (this->getSpritePartition(1).getGlobalBounds().getPosition().y < point.y &&
		this->getSpritePartition(1).getGlobalBounds().getPosition().y + this->getSpritePartition(1).getSize().y > point.y &&
		this->getSpritePartition(1).getGlobalBounds().getPosition().x < point.x &&
		this->getSpritePartition(1).getGlobalBounds().getPosition().x + this->getSpritePartition(1).getSize().x > point.x) {
		// used for the scaling factor of the sprites
		
		

		sf::Vector2i upperMiddleSpriteDimensions = subSprites[1].getTextureRect().getSize();
		
		// move the top partitions up to the point
		for (int i=0; i<3; i++) {
			this->subSprites[i].setPosition(this->subSprites[i].getPosition().x, point.y - upperMiddleSpriteDimensions.y/2);
			this->spritePartitions[i].setPosition(this->spritePartitions[i].getPosition().x, point.y - upperMiddleSpriteDimensions.y / 2);
		}
		
		float scalingFactorY = ((this->subSprites[6].getPosition().y - (subSprites[1].getGlobalBounds().getPosition().y+ subSprites[1].getTextureRect().getSize().y)) / 
											subSprites[4].getTextureRect().getSize().y)+ scalingFactorSafety;
		// resize the middle partitions and their corresponding sprites
		for (int j=3; j<6; j++) {
			

			// Resize the sprite partitions
			this->spritePartitions[j].setSize(sf::Vector2f(this->spritePartitions[j].getSize().x, 
															this->spritePartitions[6].getPosition().y - (this->spritePartitions[0].getSize().y+this->spritePartitions[0].getPosition().y)
																));
			
			this->spritePartitions[j].setPosition(this->spritePartitions[j].getPosition().x, 
													(this->spritePartitions[0].getGlobalBounds().getPosition().y + this->spritePartitions[0].getSize().y) );
			
			// resize the sprites
			this->subSprites[j].setScale(sf::Vector2f(this->subSprites[j].getScale().x, scalingFactorY));
			this->subSprites[j].setPosition(this->subSprites[j].getPosition().x, 
				(this->spritePartitions[0].getGlobalBounds().getPosition().y + this->spritePartitions[0].getSize().y) + this->spritePartitions[j].getOrigin().y);
		}

	}
	calculateSpriteOffsetsAtIndices({ 1,2,3 });
}
void NineSliceComponent::expandDownToPoint(sf::Vector2i point) {
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::expandUpToPoint::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	// if the point is within the bounds of the buttom  middle partition, then expand the top partition to that point
	if (this->getSpritePartition(7).getGlobalBounds().getPosition().y < point.y &&
		this->getSpritePartition(7).getGlobalBounds().getPosition().y + this->getSpritePartition(7).getSize().y > point.y &&
		this->getSpritePartition(7).getGlobalBounds().getPosition().x < point.x &&
		this->getSpritePartition(7).getGlobalBounds().getPosition().x + this->getSpritePartition(7).getSize().x > point.x) {
		// used for the scaling factor of the sprites



		sf::Vector2i lowerMiddleSpriteDimensions = subSprites[7].getTextureRect().getSize();

		// move the down partitions up to the point
		for (int i = 6; i < 9; i++) {
			this->subSprites[i].setPosition(this->subSprites[i].getPosition().x, point.y - lowerMiddleSpriteDimensions.y / 2);
			this->spritePartitions[i].setPosition(this->spritePartitions[i].getPosition().x, point.y - lowerMiddleSpriteDimensions.y / 2);
		}

		float scalingFactorY = ((this->subSprites[7].getPosition().y - (subSprites[1].getGlobalBounds().getPosition().y + subSprites[1].getTextureRect().getSize().y)) /
			subSprites[4].getTextureRect().getSize().y) + scalingFactorSafety;

		// resize the middle partitions and their corresponding sprites
		for (int j = 3; j < 6; j++) {


			// Resize the sprite partitions
			this->spritePartitions[j].setSize(sf::Vector2f(this->spritePartitions[j].getSize().x,
				this->spritePartitions[6].getPosition().y - (this->spritePartitions[0].getSize().y + this->spritePartitions[0].getPosition().y)));

			this->spritePartitions[j].setPosition(this->spritePartitions[j].getPosition().x,
				(this->spritePartitions[0].getGlobalBounds().getPosition().y + this->spritePartitions[0].getSize().y));

			// resize the sprites
			this->subSprites[j].setScale(sf::Vector2f(this->subSprites[j].getScale().x, scalingFactorY));
			this->subSprites[j].setPosition(this->subSprites[j].getPosition().x,
				(this->spritePartitions[0].getGlobalBounds().getPosition().y + this->spritePartitions[0].getSize().y) + this->spritePartitions[j].getOrigin().y);
		}

	}
	calculateSpriteOffsetsAtIndices({ 6,7,8 });
}
void NineSliceComponent::expandLeftToPoint(sf::Vector2i point) {
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::expandUpToPoint::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	// if the point is within the bounds of the left  middle partition, then expand the top partition to that point
	if (this->getSpritePartition(3).getGlobalBounds().getPosition().y < point.y &&
		this->getSpritePartition(3).getGlobalBounds().getPosition().y + this->getSpritePartition(3).getSize().y > point.y &&
		this->getSpritePartition(3).getGlobalBounds().getPosition().x < point.x &&
		this->getSpritePartition(3).getGlobalBounds().getPosition().x + this->getSpritePartition(3).getSize().x > point.x) {
		// used for the scaling factor of the sprites



		sf::Vector2i middleLeftSpriteDimensions = subSprites[3].getTextureRect().getSize();

		// move the left partitions up to the left
		for (int i = 0; i < 3; i++) {
			this->subSprites[i*3].setPosition( point.x - middleLeftSpriteDimensions.x / 2, this->subSprites[i * 3].getPosition().y);
			this->spritePartitions[i * 3].setPosition(point.x - middleLeftSpriteDimensions.x / 2,this->spritePartitions[i * 3].getPosition().y );
		}

		float scalingFactorX = (( (subSprites[2].getGlobalBounds().getPosition().x ) 
									- (subSprites[3].getGlobalBounds().getPosition().x + subSprites[3].getTextureRect().getSize().x)) /
											subSprites[4].getTextureRect().getSize().x) + scalingFactorSafety;

		// resize the middle partitions and their corresponding sprites
		for (int j = 0; j < 3; j++) {


			// Resize the sprite partitions
			
			sf::RectangleShape leftPartition = this->spritePartitions[3 * j];
			this->spritePartitions[j * 3 + 1]
				.setSize(sf::Vector2f( (spritePartitions[j * 3 + 1].getPosition().x + spritePartitions[j * 3 + 1].getSize().x)- (leftPartition.getPosition().x + leftPartition.getSize().x),
										spritePartitions[j * 3 + 1].getSize().y));

			this->spritePartitions[j * 3 + 1].setPosition(leftPartition.getPosition().x + leftPartition.getSize().x,
													leftPartition.getPosition().y);
			
			// resize the sprites
			this->subSprites[j * 3 + 1].setScale(sf::Vector2f(scalingFactorX, this->subSprites[j * 3 + 1].getScale().y));
			this->subSprites[j * 3 + 1].setPosition(leftPartition.getPosition().x+ leftPartition.getSize().x,
														leftPartition.getPosition().y);
		}

	}
	calculateSpriteOffsetsAtIndices({ 0,3,6 });
}
void NineSliceComponent::expandRightToPoint(sf::Vector2i point) {
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::expandUpToPoint::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	// if the point is within the bounds of the left  middle partition, then expand the top partition to that point
	if (this->getSpritePartition(5).getGlobalBounds().getPosition().y < point.y &&
		this->getSpritePartition(5).getGlobalBounds().getPosition().y + this->getSpritePartition(3).getSize().y > point.y &&
		this->getSpritePartition(5).getGlobalBounds().getPosition().x < point.x &&
		this->getSpritePartition(5).getGlobalBounds().getPosition().x + this->getSpritePartition(3).getSize().x > point.x) {
		// used for the scaling factor of the sprites



		sf::Vector2i middleRightSpriteDimensions = subSprites[5].getTextureRect().getSize();

		// move the left partitions up to the left
		for (int i = 0; i < 3; i++) {
			this->subSprites[i * 3 + 2].setPosition(point.x - middleRightSpriteDimensions.x / 2, this->subSprites[i * 3 + 2].getPosition().y);
			this->spritePartitions[i * 3 + 2].setPosition(point.x - middleRightSpriteDimensions.x / 2, this->spritePartitions[i * 3 + 2].getPosition().y);
		}

		float scalingFactorX = (((subSprites[5].getGlobalBounds().getPosition().x) - (subSprites[4].getGlobalBounds().getPosition().x)) /
			subSprites[4].getTextureRect().getSize().x) + scalingFactorSafety;

		// resize the middle partitions and their corresponding sprites
		for (int j = 0; j < 3; j++) {
			// Resize the sprite partitions

			sf::RectangleShape rightPartition = this->spritePartitions[3 * j + 2];
			this->spritePartitions[j * 3 + 1]
				.setSize(sf::Vector2f((rightPartition.getPosition().x) - (spritePartitions[j * 3 + 1].getPosition().x),
					spritePartitions[j * 3 + 1].getSize().y));

			this->spritePartitions[j * 3 + 1].setPosition(this->spritePartitions[j * 3 + 1].getPosition());

			// resize the sprites
			this->subSprites[j * 3 + 1].setScale(sf::Vector2f(scalingFactorX, this->subSprites[j * 3 + 1].getScale().y));
			this->subSprites[j * 3 + 1].setPosition(this->subSprites[j * 3 + 1].getPosition());
		}
	}
	// recalculate the offsets of the sprites after 
	calculateSpriteOffsetsAtIndices( { 2,5,8 } );
}

void NineSliceComponent::moveSlicesToPoint(sf::Vector2i point) {
	if (subSprites.size() != 9) {
		throw std::runtime_error("NineSliceComponent::expandUpToPoint::This class needs 9 subSprites. Try calling initPartitions() and initSprites() first.");
	}
	
	sf::FloatRect middleSprite = subSprites[4].getGlobalBounds();
	if (middleSprite.getPosition().x <= point.x &&
		middleSprite.getPosition().y <= point.y && 
		point.x <= middleSprite.getPosition().x + middleSprite.getSize().x && 
		point.y <= middleSprite.getPosition().y + middleSprite.getSize().y) {
		
		this->setPosition(point.x, point.y);
	}

}

// --------------------------------- Private ----------------------------------------

// ---------------- Actions ---------------------
void NineSliceComponent::calculateSpriteOffsetsAtIndices(std::vector<int> indicies) {
	for (int i = 0; i < indicies.size(); i++) {
		if (9 <= indicies[i] || indicies[i] < 0) {
			throw std::runtime_error("NineSliceComponent::calculateSpriteOffsetsAtIndices:: index can at most equal 8 and not negative");
		}
	}

	for (int i = 0; i < indicies.size(); i++) {
		switch (indicies[i]) {
		case 0:
			spriteOffsets[0] = sf::Vector2f(-subSprites[0].getTextureRect().getSize().x * subSprites[0].getScale().x,
												-subSprites[0].getTextureRect().getSize().y * subSprites[0].getScale().y);
		case 1:
			spriteOffsets[1] = sf::Vector2f(0,
												-subSprites[1].getTextureRect().getSize().y * subSprites[1].getScale().y);
		case 2:
			spriteOffsets[2] = sf::Vector2f(subSprites[4].getTextureRect().getSize().x * subSprites[4].getScale().x,
												-subSprites[2].getTextureRect().getSize().y * subSprites[2].getScale().y);
		case 3:
			spriteOffsets[3] = sf::Vector2f(-subSprites[3].getTextureRect().getSize().x * subSprites[3].getScale().x,
												0);
		case 4:
			spriteOffsets[4] = sf::Vector2f(0, 0);
		case 5:
			spriteOffsets[5] = sf::Vector2f(subSprites[4].getTextureRect().getSize().x * subSprites[4].getScale().x,
												0);
		case 6:
			spriteOffsets[6] = sf::Vector2f( -subSprites[6].getTextureRect().getSize().x * subSprites[6].getScale().x,
												subSprites[4].getTextureRect().getSize().y * subSprites[4].getScale().y	);
		case 7:
			spriteOffsets[7] = sf::Vector2f( 0, 
												subSprites[4].getTextureRect().getSize().y * subSprites[4].getScale().y);
		case 8:
			spriteOffsets[8] = sf::Vector2f( subSprites[4].getTextureRect().getSize().x * subSprites[4].getScale().x,
												subSprites[4].getTextureRect().getSize().y * subSprites[4].getScale().y);
		}
	}
}
