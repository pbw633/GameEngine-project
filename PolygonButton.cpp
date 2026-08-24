#include "PolygonButton.h"
// ------------------ Initialization ------------------
void PolygonButton::initButtonShape(std::vector<sf::Vector2f> points) {
	if (points.size()<3) {
		throw std::runtime_error("PolygonButton: to few points");
	}
	this->points = points;
	this->calculateCenter();
}
// ----------------- Adders ------------------
void PolygonButton::addPoint(sf::Vector2f point) {
	this->points.push_back(point);
	this->calculateCenter();
}

// ------------------ Setters ------------------
void PolygonButton::setCenter(sf::Vector2f position) {
	//this->center = position;
}

// ------------------ Getters ------------------
sf::Vector2f PolygonButton::getCenter() {
	return this->center;
}


// ------------------ Actions ------------------
void PolygonButton::calculateCenter() {
	if( this->points.size() < 3 ){
		throw std::runtime_error("PolygonButton: to few points");
	}
	
	float sumX = 0;
	float sumY = 0;
	for (const auto& point : points) {
		sumX += point.x;
		sumY += point.y;
	}
	center.x = sumX / points.size();
	center.y = sumY / points.size();
}

void PolygonButton::changePointAtIndex(sf::Vector2f point, int index) {
	if (index < 0 || index >= points.size()) {
		throw std::runtime_error("PolygonButton: index out of bounds");
	}
	points[index] = point;
	this->calculateCenter();
}

void PolygonButton::removePoint(int index) {
	if (index < 0 || index >= points.size()) {
		throw std::runtime_error("PolygonButton: index out of bounds");
	}
	if( points.size() <= 3) {
		throw std::runtime_error("PolygonButton: cannot remove point, polygon must have at least 3 points");
	}
	points.erase(points.begin() + index);
	this->calculateCenter();
}

// ------------------ Actions ------------------
// the contains method can be impemented by one of the algoritms seen in https://en.wikipedia.org/wiki/Point_in_polygon
void PolygonButton::update() {
	this->calculateCenter();
	this->calculateMaxDistanceFromCenter();
}