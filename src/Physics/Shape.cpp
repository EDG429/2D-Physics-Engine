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
	return new PolygonShape(vertices);
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
}

BoxShape::BoxShape(float width, float height) {
	//
};

Shape* BoxShape::Clone() const {
	return new BoxShape;
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