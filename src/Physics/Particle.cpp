#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass) {
	this->position = Vec2(x, y);
	this->mass = mass;
	std::cout << "Particle constructor called!\n";
}

Particle::~Particle() {
	std::cout << "Particle destructor called!\n";
}

void Particle::Integrate(float dT) {
	velocity += acceleration * dT;
	position += velocity * dT;
}