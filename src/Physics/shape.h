#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Vec2.h"

enum ShapeType {
	CIRCLE,
	POLYGON,
	BOX
};

struct Shape {
	virtual ~Shape() = default;
	virtual ShapeType GetType() const;
};

struct CircleShape : public Shape {
	float radius;
	CircleShape(const float radius);

	virtual ~CircleShape();
	ShapeType GetType() const override;
};

struct PolygonShape : public Shape {
	std::vector<Vec2> vertices;

	PolygonShape(const std::vector<Vec2> vertices);
	virtual ~PolygonShape();
	ShapeType GetType() const override;
};

struct BoxShape : public PolygonShape {
	float width;
	float height;

	BoxShape(float width, float height);
	virtual ~BoxShape();
	ShapeType GetType() const override;
};

#endif