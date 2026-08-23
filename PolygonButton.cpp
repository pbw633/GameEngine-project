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