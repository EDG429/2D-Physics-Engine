#include "./Force.h"

Vec2 Force::GenerateDragForce(const Particle& particle, float k) {
	Vec2 dragForce = Vec2(0, 0);

	if (particle.velocity.MagnitudeSquared() > 0) {
		// Calculate the drag direction (inverse velocityt unit vector)
		Vec2 dragDirection = particle.velocity.UnitVector() * -1.0;

		// Calculate the drag magnitude, k * |v|^2
		float dragMagnitude = k * particle.velocity.MagnitudeSquared();

		// Generate the final drag force with direction and magnitude
		dragForce = dragDirection * dragMagnitude;
	}
	return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Particle& particle, float k) {
	Vec2 frictionForce = Vec2(0, 0);

	// Calculate the friction direction (inverse of velocity unit)
	Vec2 frictionDirection = particle.velocity.UnitVector() * -1.0;

	// Calculate the friction magnitude
	float frictionMagnitude = k;

	// Calculate the final friction force
	frictionForce + frictionDirection * frictionMagnitude;

	return frictionForce;
}


// TODO Generate spring force