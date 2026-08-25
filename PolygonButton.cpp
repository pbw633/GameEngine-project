#include "PolygonButton.h"
// ------------------ Initialization ------------------
void PolygonButton::initButtonShape(std::vector<sf::Vector2f> points) {
	if (points.size()<3) {
		throw std::runtime_error("PolygonButton: to few points");
	}
	this->buttonShape.setPointCount(points.size());
	for (int i = 0; i < points.size(); i++){
		this->buttonShape.setPoint(i, points[i]);
	}
	//this->points = points;
	this->calculateCenter();
}
// ----------------- Adders ------------------
void PolygonButton::addPoint(sf::Vector2f point) {
	this->buttonShape.setPointCount(this->buttonShape.getPointCount() + 1);
	this->buttonShape.setPoint(this->buttonShape.getPointCount() - 1, point);

	this->calculateCenter();
}

// ------------------ Setters ------------------
void PolygonButton::setCenter(sf::Vector2f position) {
	this->buttonShape.setPosition(position);
	center = position;
}

// ------------------ Getters ------------------
sf::Vector2f PolygonButton::getPoint(int index) {
	if (index < 0 || index >= points.size()) {
		throw std::runtime_error("PolygonButton: index out of bounds");
	}
	return this->buttonShape.getPoint(index);
}

sf::Vector2f PolygonButton::getCenter() {
	return this->center;
}




// ------------------ Actions ------------------


void PolygonButton::changePointAtIndex(sf::Vector2f point, int index) {
	if (index < 0 || index >= this->buttonShape.getPointCount()) {
		throw std::runtime_error("PolygonButton: index out of bounds");
	}
	this->buttonShape.setPoint(index, point);
	this->calculateCenter();
}

void PolygonButton::removePoint(int index) {
	if (index < 0 || index >= this->buttonShape.getPointCount()) {
		throw std::runtime_error("PolygonButton: index out of bounds");
	}
	if( this->buttonShape.getPointCount() <= 3) {
		throw std::runtime_error("PolygonButton: cannot remove point, polygon must have at least 3 points");
	}
	sf::ConvexShape tempShape;
	tempShape.setPointCount(this->buttonShape.getPointCount() - 1);
	
	int tempIndex = 0;
	for (int i = 0; i < this->buttonShape.getPointCount(); i++){
		if (i != index) {
			tempShape.setPoint(tempIndex, this->buttonShape.getPoint(i));
			tempIndex++;
		}
	}
	this->buttonShape = tempShape;
	this->calculateCenter();
}

void PolygonButton::resize(float sizeFactor) {
	if (sizeFactor <= 0) {
		throw std::runtime_error("PolygonButton: sizeFactor must be strictly larger than 0");
	}

	for( int i = 0; i < this->buttonShape.getPointCount(); i++ ){
		sf::Vector2f point = this->buttonShape.getPoint(i);
		point = (point - center) * sizeFactor + center;
		this->buttonShape.setPoint(i, point);
	}
	
}

void PolygonButton::update() {
	this->calculateCenter();
	this->calculateMaxDistanceFromCenter();
}


bool PolygonButton::containsPoint(sf::Vector2i point) {
	if (this->points.size() < 3) {
		throw std::runtime_error("PolygonButton: to few points");
	}
	// first check if the point is within the bounding box of the polygon
	float distanceFromCenter = std::sqrt(std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2));
	if (distanceFromCenter > this->getMaxDistanceFromCenter()) {
		return false;
	}

	int n = this->points.size();
	int intersectionCount = 0;

	for (int i = 0; i < n; i++) {
		sf::Vector2f point1 = this->buttonShape.getPoint(i);
		sf::Vector2f point2 = this->buttonShape.getPoint((i + 1) % n);

		// Check if the point's y-coordinate is within the
		// edge's y-range and if the point is to the left of
		// the edge
		if ( point.y > std::min(point1.y , point2.y) &&
			 point.y <= std::max(point1.y, point2.y) &&
			 point.x <= std::max(point1.x, point2.x) ) {
			
			float xIntersect = (point.y - point1.y) * (point2.x - point1.x) / (point2.y - point1.y) + point1.x;

			if (point1.x == point2.x || point.x <= xIntersect) {
				intersectionCount++;
			}
		}
	}
	// If the number of intersections is odd, the point is
	// inside the polygon
	return intersectionCount % 2 == 1;;
}
// ------------------ Private Getters ------------------
float PolygonButton::getMaxDistanceFromCenter() {
	return this->maxDistanceFromCenter;
}

// ------------------ private Actions ------------------
void PolygonButton::calculateMaxDistanceFromCenter() {
	int numPoints = this->buttonShape.getPointCount();
	if ( numPoints == 0 ) {
		throw std::runtime_error("PolygonButton: no points to calculate max distance");
	}
	float maxDistance = 0.0f;
	for (int i = 0; i < numPoints; i++) {
		sf::Vector2f point = this->buttonShape.getPoint(i);
		float distance = std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2); 
		if (distance > maxDistance) {
			maxDistance = distance;
		}
	}
	maxDistanceFromCenter = std::sqrt(maxDistance);
}

void PolygonButton::calculateCenter() {
	int numPoints = this->buttonShape.getPointCount();
	if (numPoints < 3) {
		throw std::runtime_error("PolygonButton: to few points");
	}

	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < numPoints; i++) {
		sf::Vector2f point = this->buttonShape.getPoint(i);
		sumX += point.x;
		sumY += point.y;
	}
	center.x = sumX / numPoints;
	center.y = sumY / numPoints;
}
// the contains method can be impemented by one of the algoritms seen in https://en.wikipedia.org/wiki/Point_in_polygon
