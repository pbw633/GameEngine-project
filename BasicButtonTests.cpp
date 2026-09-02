#include "BasicButtonTests.h"



/*
This file is made for the basic button class.

*/

void getBasicButtonValuesTest() {
	// Setup
	// set values for button
	int xValue = 100;
	int yValue = 150;
	int width = 200;
	int height = 300;
	BasicButton basicButton	= BasicButton(xValue, yValue, width, height);

	// expected values

	int expectedWidth = width;
	int expectedHeight = height;
	int expectedXValue = xValue;
	int expectedYValue = yValue;


	// Act
	int returnedWidth	= basicButton.getButtonWidth();
	int returnedHeight = basicButton.getButtonHeight();
	int returnedXValue = basicButton.getButtonPosition().x;
	int returnedYValue = basicButton.getButtonPosition().y;

	// Assert
	if (expectedWidth != returnedWidth) {
		throw std::runtime_error("Did not get expected width of basicButton");
	}
	if (expectedHeight != returnedHeight) {
		throw std::runtime_error("Did not get expected Height of basicButton");
	}
	if (expectedXValue != returnedXValue) {
		throw std::runtime_error("Did not get expected xValue of basicButton");
	}
	if (expectedYValue != returnedYValue) {
		throw std::runtime_error("Did not get expected yValue of basicButton");
	}
	
	if (xValue == yValue || xValue == height ||
		xValue == width ||
		yValue == width || yValue == height ||
		height == width) {
		throw std::runtime_error("Values has to be different to make the test complete");
	}
}

void setBasicButtonWidthTest() {
	// Setup
	int xValue = 0;
	int yValue = 0;
	int widthBeforeChange = 200;
	int widthAfterChange = 400;
	int height = 300;
	BasicButton basicButton = BasicButton(xValue, yValue, widthBeforeChange, height);

	int expectedWidthBeforeChange = widthBeforeChange;
	int expectedWidthAfterChange = widthAfterChange;
	
	// Act
	int returnedWidthBeforeChange = basicButton.getButtonWidth();
	basicButton.setButtonWidth(widthAfterChange);
	int returnedWidthAfterChange = basicButton.getButtonWidth();
	
	// Assert
	if (expectedWidthBeforeChange != returnedWidthBeforeChange) {
		throw std::runtime_error("Did not get expected width of basicButton before change");
	}
	if (returnedWidthAfterChange != expectedWidthAfterChange) {
		throw std::runtime_error("Did not get expected width of basicButton after change");
	}
}

void setBasicButtonHeightTest() {
	// Setup
	int xValue = 0;
	int yValue = 0;
	int width = 200;
	int heightBeforeChange = 250;
	int heightAfterChange = 300;
	BasicButton basicButton = BasicButton(xValue, yValue, width, heightBeforeChange);

	int expectedHeightBeforeChange = heightBeforeChange;
	int expectedHeightAfterChange = heightAfterChange;

	// Act
	int returnedHeightBeforeChange = basicButton.getButtonHeight();
	basicButton.setButtonHeight(heightAfterChange);
	int returnedHeightAfterChange = basicButton.getButtonHeight();

	// Assert
	if (expectedHeightBeforeChange != returnedHeightBeforeChange) {
		throw std::runtime_error("Did not get expected height of basicButton before change");
	}
	if (returnedHeightAfterChange != expectedHeightAfterChange) {
		throw std::runtime_error("Did not get expected height of basicButton after change");
	}
}

void setBasicButtonPositionTest() {
	// Setup
	int xValue = 0;
	int yValue = 100;
	int dim = 200;
	


	BasicButton basicButton = BasicButton(xValue, yValue, dim, dim);

	int xValueChange = 150;
	int yValueChange = 250;

	sf::Vector2f expectedPositonBeforeChange( xValue, yValue );
	sf::Vector2f expectedPositonAfterChange(xValueChange, yValueChange );

	// Act
	sf::Vector2f returnedBasicPositionBefore = basicButton.getButtonPosition();

	basicButton.setButtonPosition(xValueChange, yValueChange);

	sf::Vector2f returnedBasicPositionAfter = basicButton.getButtonPosition();

	// Assert
	if (expectedPositonBeforeChange.x != returnedBasicPositionBefore.x || expectedPositonBeforeChange.y != returnedBasicPositionBefore.y) {
		throw std::runtime_error("Did not get expected position of basicButton before change");
	}
	if (expectedPositonAfterChange.x != returnedBasicPositionAfter.x || expectedPositonAfterChange.y != returnedBasicPositionAfter.y) {
		throw std::runtime_error("Did not get expected position of basicButton after change");
	}

}

void buttonOverlapsButtonTest() {
	// Setup
	int dim = 10;
	BasicButton basicButton1 = BasicButton(0, 0, dim, dim);
	BasicButton basicButton2 = BasicButton(0, 0, dim, dim);
	
	bool expectedResultFirst = true;
	bool expectedResultSecond = false;

	// Act
	bool returnedResultFirst = basicButton1.buttonOverlapsButton(basicButton2);
	basicButton2.setButtonPosition(0, dim);
	bool returnedResultSecond = basicButton1.buttonOverlapsButton(basicButton2);

	// Assert
	if (expectedResultFirst != returnedResultFirst) {
		throw std::runtime_error("Buttons overlaps and result should indicate that");
	}
	if (expectedResultSecond != returnedResultSecond) {
		throw std::runtime_error("Buttons does not overlaps and result should indicate that");
	}

}

void resizeBasicButtonTest() {
	// Setup
	int width = 10;
	int height = 100;
	float resizeFactor = 1.5;
	BasicButton basicButton = BasicButton(0, 0, width, height);

	
	float expectedWidth = width*resizeFactor;
	float expectedHeight = height * resizeFactor;


	// Act
	basicButton.resizeButton(resizeFactor);
	float returnedWidth = basicButton.getButtonWidth();
	float returnedHeight = basicButton.getButtonHeight();

	// Assert
	if (expectedWidth != returnedWidth) {
		throw std::runtime_error("Button width is not resized correctly");
	}
	if (expectedHeight != returnedHeight) {
		throw std::runtime_error("Button height is not resized correctly");
	}
	
}

void basicButtonInsideMenuTest() {
	// Setup
	// button
	int width = 10;
	int height = 150;
	BasicButton basicButton = BasicButton(0, 0, width, height);
	
	// Menu
	int menuWidth = 200;
	int menuHeight = 200;
	sf::RectangleShape menuShape;
	menuShape.setSize(sf::Vector2f(menuWidth, menuHeight));
	menuShape.setPosition(0, 0);

	bool expectedResultBeforeMovement = true;
	bool expectedResultAfterMovement = false;

	// Act
	bool returnedValueBeforeMovement = basicButton.buttonInsideMenu(menuShape);
	basicButton.setButtonPosition(0,100);
	bool returnedValueAfterMovement = basicButton.buttonInsideMenu(menuShape);


	// Assert
	if (expectedResultBeforeMovement != returnedValueBeforeMovement) {
		throw std::runtime_error("BasicButton should be inside the menuShape");
	}
	if (expectedResultAfterMovement != returnedValueAfterMovement) {
		throw std::runtime_error("BasicButton should be partly outside the menuShape");
	}

}

void basicButtonGetPointTest() {
	// Setup
	BasicButton basicButton = BasicButton(20, 20, 100, 100);
	sf::Vector2f expectedPoint0(20, 20);
	sf::Vector2f expectedPoint1(120, 20);
	sf::Vector2f expectedPoint2(120, 120);
	sf::Vector2f expectedPoint3(20, 120);	

	// Act
	sf::Vector2f returnedPoint0 = basicButton.getPoint(0);
	sf::Vector2f returnedPoint1 = basicButton.getPoint(1);
	sf::Vector2f returnedPoint2 = basicButton.getPoint(2);
	sf::Vector2f returnedPoint3 = basicButton.getPoint(3);

	// Assert
	if (expectedPoint0.x != returnedPoint0.x || expectedPoint0.y != returnedPoint0.y) {
		throw std::runtime_error("BasicButton: Point 0 is not at the expected position");
	}
	if (expectedPoint1.x != returnedPoint1.x || expectedPoint1.y != returnedPoint1.y) {
		throw std::runtime_error("BasicButton: Point 1 is not at the expected position");
	}
	if (expectedPoint2.x != returnedPoint2.x || expectedPoint2.y != returnedPoint2.y) {
		throw std::runtime_error("BasicButton: Point 2 is not at the expected position");
	}
	if (expectedPoint3.x != returnedPoint3.x || expectedPoint3.y != returnedPoint3.y) {
		throw std::runtime_error("BasicButton: Point 3 is not at the expected position");
	}

}

void basicButtonContainsPointTest() {
	// Setup
	int xValue = 20;
	int yValue = 20;
	BasicButton basicButton = BasicButton(xValue, yValue, 100, 100);
	int numberOfChecksAlongX = 10;
	int numberOfChecksAlongY = 10;
	float widthStep = basicButton.getButtonWidth() / numberOfChecksAlongX;
	float heightStep = basicButton.getButtonHeight() / numberOfChecksAlongY;

	std::vector<bool> expectedResultsInside;
	for (int i = 0; i < numberOfChecksAlongX * numberOfChecksAlongY; i++){
		expectedResultsInside.push_back(true);
	}

	std::vector<sf::Vector2i> pointsToCheckOutside = {
		sf::Vector2i(xValue - 1, yValue - 1), // top-left
		sf::Vector2i(xValue + basicButton.getButtonWidth() + 1, yValue - 1), // top-right
		sf::Vector2i(xValue - 1, yValue + basicButton.getButtonHeight() + 1), // bottom-left
		sf::Vector2i(xValue + basicButton.getButtonWidth() + 1, yValue + basicButton.getButtonHeight() + 1) // bottom-right
	};

	// Act
	std::vector<bool> returnedResultsInside;	
	returnedResultsInside.reserve(numberOfChecksAlongX * numberOfChecksAlongY);
	for (int i = 0; i < numberOfChecksAlongX; ++i) {
		for (int j = 0; j < numberOfChecksAlongY; ++j) {
			sf::Vector2i point(xValue + i * widthStep, yValue + j * heightStep);
			returnedResultsInside.push_back(basicButton.containsPoint(point));
		}	
	}
	std::vector<bool> returnedResultsoutside;
	for (int i = 0; i < pointsToCheckOutside.size(); i++) {
		returnedResultsoutside.push_back(basicButton.containsPoint(pointsToCheckOutside[i]	));
	}

	// Assert
	for (int i = 0; i < numberOfChecksAlongX * numberOfChecksAlongY; i++) {
		if (expectedResultsInside[i] != returnedResultsInside[i]) {
			throw std::runtime_error("BasicButton: containsPoint inside shape should return true");
		}
	}

	for (int i = 0; i < pointsToCheckOutside.size(); i++) {
		if ( returnedResultsoutside[i]) {	
			throw std::runtime_error("BasicButton: containsPoint outside of shape should return false");
		}	
	}
}