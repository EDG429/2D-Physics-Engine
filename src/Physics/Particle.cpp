#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass) {
	this->position = Vec2(x, y);
	this->mass = mass;
	if (mass != 0.0)
	{
		this->invMass = 1.0 / mass;
	}else{
		this->invMass = 0.0;
	}
	std::cout << "Particle constructor called!\n";
}

Particle::~Particle() {
	std::cout << "Particle destructor called!\n";
}

void Particle::AddForce(const Vec2& force) {
	sumForces += force;
}

void Particle::ClearForces() {
	sumForces = Vec2(0.0, 0.0);
}

void Particle::Integrate(float dT) {
	// Find the acceleration based on the forces that are being applied and the mass
	acceleration = sumForces * invMass;

	// Integrate the acceleration to find the new velocity
	velocity += acceleration * dT;

	// Integrate the velocity to find the position (Euler)
	position += velocity * dT;

	// Add the forces, integrate, clear <- it is a loop frame per frame
	ClearForces();
}