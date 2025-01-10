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
