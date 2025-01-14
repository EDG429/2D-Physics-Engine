#include "shape.h"
#include <iostream>

CircleShape::CircleShape(float radius) {
	this->radius = radius;
	std::cout << "Circle Shape constructor called!\n";
};

CircleShape::~CircleShape() {
	std::cout << "Circle Shape destructor called!\n";
};

Shape* CircleShape::Clone() const {
	return new CircleShape(radius);
};

ShapeType CircleShape::GetType() const {
	return CIRCLE;
};

float CircleShape::GetMomentOfInertia() const {
	// For solid circles, the moment of inertia is 1/2 * r^2
	// But this still needs to be multiplied by the rigidbody's mass
	return 0.5 * (radius * radius);
};

PolygonShape::PolygonShape(const std::vector<Vec2> vertices) {
	//
};

Shape* PolygonShape::Clone() const {
	return new PolygonShape(localVertices);
};

PolygonShape::~PolygonShape() {
	//
};

ShapeType PolygonShape::GetType() const {
	return POLYGON;
};

float PolygonShape::GetMomentOfInertia() const {
	// TODO
	return 0.0;
};

void PolygonShape::UpdateVertices(float angle, const Vec2& position) {
	// Loop all the vertices transforming to local from world space
	for (int i = 0; i < localVertices.size(); i++) {
		// first rotate
		worldVertices[i] = localVertices[i].Rotate(angle);
		// then translate into world space
		worldVertices[i] += position;
	}
};

BoxShape::BoxShape(float width, float height) {
	this->width = width;
	this->height = height;

	// Load the vertices of the box polygon
	localVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
	localVertices.push_back(Vec2(width / 2.0, -height / 2.0));
	localVertices.push_back(Vec2(width / 2.0, height / 2.0));
	localVertices.push_back(Vec2(-width / 2.0, height / 2.0));

	worldVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
	worldVertices.push_back(Vec2(width / 2.0, -height / 2.0));
	worldVertices.push_back(Vec2(width / 2.0, height / 2.0));
	worldVertices.push_back(Vec2(-width / 2.0, height / 2.0));
};

Shape* BoxShape::Clone() const {
	return new BoxShape(width, height);
};

BoxShape::~BoxShape() {
	//
};

ShapeType BoxShape::GetType() const {
	return BOX;
};

float BoxShape::GetMomentOfInertia() const {
	// For a rectangle, the moment of inertia is 1/12 * (w^2 + h^2)
	// But this still needs to be multiplied by the rigidbody's mass
	return (0.083333) * (width * width + height * height);
}