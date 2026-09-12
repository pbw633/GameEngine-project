#include "BasicMenuTests.h"

void getBasicMenuPointsTest() {
	// Setup
	BasicMenu basicMenu;
	sf::Vector2f center = sf::Vector2f(200, 200);
	basicMenu.initBasicMenuByRectangleShape(center, 100, 200);
	
	std::vector<sf::Vector2f> expectedPoints = {
		sf::Vector2f(150, 100),
		sf::Vector2f(250, 100),
		sf::Vector2f(250, 300),
		sf::Vector2f(150, 300)
	};

	sf::Vector2f expectedCenter = center;



	// Act
	std::vector<sf::Vector2f> returnedPoints;
	for(int i = 0; i < 4; i++) {
		returnedPoints.push_back(basicMenu.getPoint(i));
	}
	sf::Vector2f returnedCenter = basicMenu.getCenter();

	// Assert
	if (returnedCenter.x != expectedCenter.x || returnedCenter.y != expectedCenter.y) {
		throw std::runtime_error("BasicMenuTest: Center is not at the expected position");
	}

	for (int i=0; i < 4; i++) {
		if (returnedPoints[i].x != expectedPoints[i].x || returnedPoints[i].y != expectedPoints[i].y) {
			throw std::runtime_error("BasicMenuTest: Point " + std::to_string(i) + " is not at the expected position");
		}
	}
}