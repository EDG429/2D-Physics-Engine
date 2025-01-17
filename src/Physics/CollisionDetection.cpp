#include "CollisionDetection.h"

bool CollisionDetection::IsColliding(Body* a, Body* b, Contact& contact) {
	bool aIsCircle = a->shape->GetType() == CIRCLE;
	bool bIsCircle = a->shape->GetType() == CIRCLE;

	if (aIsCircle && bIsCircle) {
		return IsCollidingCircleCircle(a, b, contact);
	}
}

bool CollisionDetection::IsCollidingCircleCircle(Body* a, Body* b, Contact& contact) {
	CircleShape* aCircleShape = (CircleShape*)a->shape;
	CircleShape* bCircleShape = (CircleShape*)b->shape;

	const Vec2 ab = b->position - a->position;
	const float radiusSum = aCircleShape->radius + bCircleShape->radius;

	bool IsColliding = ab.MagnitudeSquared() <= (radiusSum * radiusSum);

	if (!IsColliding) return false;

	contact.a = a;
	contact.b = b;

	contact.normal = ab;
	contact.normal.Normalize();

	contact.start = b->position - contact.normal * bCircleShape->radius;
	contact.end = a->position + contact.normal * aCircleShape->radius;
	contact.depth = (contact.end - contact.start).Magnitude();

	// We have a collision
	return true;

}
// TODO Implement methods to detect collision between different shapes