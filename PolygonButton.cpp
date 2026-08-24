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
	for (auto& point : points) {
		point += position - center; // move each point by the difference between the new and old center
	}
	center = position;
}

// ------------------ Getters ------------------
sf::Vector2f PolygonButton::getPoint(int index) {
	if (index < 0 || index >= points.size()) {
		throw std::runtime_error("PolygonButton: index out of bounds");
	}
	return points[index];
}

sf::Vector2f PolygonButton::getCenter() {
	return this->center;
}




// ------------------ Actions ------------------


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

void PolygonButton::resize(float sizeFactor) {
	if (sizeFactor <= 0) {
		throw std::runtime_error("PolygonButton: sizeFactor must be strictly larger than 0");
	}
	for (auto& point: points ){
		point = (point-center)*sizeFactor + center;

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

	// then check if the point is within the polygon using the ray-casting algorithm or another algorihm
	return true;
}
// ------------------ Private Getters ------------------
float PolygonButton::getMaxDistanceFromCenter() {
	return this->maxDistanceFromCenter;
}

// ------------------ private Actions ------------------
void PolygonButton::calculateMaxDistanceFromCenter() {
	if (this->points.empty()) {
		throw std::runtime_error("PolygonButton: no points to calculate max distance");
	}
	float maxDistance = 0.0f;
	for (const auto& point : points) {
		float distance = std::sqrt(std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2));
		if (distance > maxDistance) {
			maxDistance = distance;
		}
	}
	maxDistanceFromCenter = maxDistance;
}

void PolygonButton::calculateCenter() {
	if (this->points.size() < 3) {
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
// the contains method can be impemented by one of the algoritms seen in https://en.wikipedia.org/wiki/Point_in_polygon
