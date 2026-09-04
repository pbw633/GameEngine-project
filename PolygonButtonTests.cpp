#include "PolygonButtonTests.h"

void initPolygonButtonTest() {
	// Setup
	std::vector<sf::Vector2f> points = {sf::Vector2f(0,0), sf::Vector2f(2,0), sf::Vector2f(1,3)};
	PolygonButton button;

	sf::Vector2f expectedCenter = sf::Vector2f(1,1);
	std::vector<sf::Vector2f> expectedPoints = points;

	// Act
	button.initButtonShape(points);
	sf::Vector2f returnedCenter = button.getCenter();
	std::vector<sf::Vector2f> returnedPoints;
	for (int i = 0; i < points.size(); i++) {
		returnedPoints.push_back(button.getPoint(i));
	}


	// Assert
	if (expectedCenter.x != returnedCenter.x || expectedCenter.y != returnedCenter.y) {
		throw std::runtime_error("PolygonButtonTest: Did not get expected center");
	}

	for ( int i = 0; i < points.size(); i++ ) {
		if (returnedPoints[i].x != expectedPoints[i].x || returnedPoints[i].y != expectedPoints[i].y) {
			throw std::runtime_error("PolygonButtonTest: Point did not match expected result");
		}
	}
}

void addPointToPolygonTest() {
	// Setup 
	std::vector<sf::Vector2f> points = { sf::Vector2f(0,0), sf::Vector2f(12,0), sf::Vector2f(0,12) };
	PolygonButton button;
	button.initButtonShape(points);

	int expectedPointCountBeforeExtraPoint = points.size();
	int expectedPointCountAfterExtraPoint = points.size() + 1;

	sf::Vector2f centerBeforeExtraPoint = button.getCenter();
	sf::Vector2f expectedCenterAfterExtraPoint = sf::Vector2f(6, 6);

	sf::Vector2f extraPoint = sf::Vector2f(12,12);



	// Act
	int returnedPointCountBefore = button.getPointCount();
	button.addPoint(extraPoint);
	sf::Vector2f returnedCenter = button.getCenter();
	int returnedPointCountAfter = button.getPointCount();

	// Assert
	if ( expectedCenterAfterExtraPoint.x != returnedCenter.x || expectedCenterAfterExtraPoint.y != returnedCenter.y ) {
		throw std::runtime_error("PolygonButtonTest: Center not updated correctly");
	}

	if (expectedPointCountBeforeExtraPoint != returnedPointCountBefore) {
		throw std::runtime_error("PolygonButtonTest: incorrent number of points");
	}

	if (expectedPointCountAfterExtraPoint != returnedPointCountAfter) {
		throw std::runtime_error("PolygonButtonTest: incorrent number of points after adding a new point");
	}

}

void setCenterOfPolygonButtonTest() {
	// Setup
	std::vector<sf::Vector2f> points = { sf::Vector2f(0,0), sf::Vector2f(12,0), sf::Vector2f(0,12), sf::Vector2f(12,12) };
	PolygonButton button;
	button.initButtonShape(points);
	
	sf::Vector2f newCenter = sf::Vector2f(7, 7);
	std::vector<sf::Vector2f> expectedPoints = { sf::Vector2f(1,1), sf::Vector2f(13,1), sf::Vector2f(1,13), sf::Vector2f(13,13) };

	// Act
	button.setCenter(newCenter);
	std::vector<sf::Vector2f> returnedPoints;
	for (int i = 0; i < button.getPointCount(); i++) {
		returnedPoints.push_back(button.getPoint(i));
	}

	// Assert
	for (int i = 0; i < expectedPoints.size(); i++) {
		if (returnedPoints[i].x != expectedPoints[i].x || returnedPoints[i].y != expectedPoints[i].y) {
			throw std::runtime_error("PolygonButtonTest: Point did not match expected result");
		}
	}
}