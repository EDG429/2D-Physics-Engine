#include "Body.h"
#include <iostream>
#include <math.h>

Body::Body(const Shape& shape, float x, float y, float mass) {
    this->shape = shape.Clone();
    this->position = Vec2(x, y);
    this->velocity = Vec2(0, 0);
    this->acceleration = Vec2(0, 0);
    this->rotation = 0.0;
    this->angularVelocity = 0.0;
    this->angularAcceleration = 0.0;
    this->sumForces = Vec2(0, 0);
    this->sumTorque = 0.0;
    this->restitution = 1.0;
    this->mass = mass;
    if (mass != 0.0) {
        this->invMass = 1.0 / mass;
    } else {
        this->invMass = 0.0; // Object of infinite mass / static object not going to be affected by gravity and/or wind
    }
    I = shape.GetMomentOfInertia() * mass;
    if (I != 0.0) {
        this->invI = 1.0 / I;
    }
    else {
        this->invI = 0.0;
    }
    std::cout << "Body constructor called!" << std::endl;
}

Body::~Body() {
    delete shape;
    std::cout << "Body destructor called!" << std::endl;
}

void Body::AddForce(const Vec2& force) {
    sumForces += force;
}

void Body::AddTorque(float torque) {
    sumTorque += torque;
}

void Body::ClearForces() {
    sumForces = Vec2(0.0, 0.0);
}

void Body::ClearTorque() {
    sumTorque = 0.0;
}

void Body::IntegrateLinear(float dt) {
    // If the body that I am trying to integrate is static I return from this function
    if (IsStatic()) 
        return;

    // Find the acceleration based on the forces that are being applied and the mass
    acceleration = sumForces * invMass;

    // Integrate the acceleration to find the new velocity
    velocity += acceleration * dt;

    // Integrate the velocity to find the acceleration
    position += velocity * dt;

    ClearForces();
}

void Body::IntegrateAngular(float dt) {
    // If the body that I am trying to integrate is static I return from this function
    if (IsStatic())
        return;

    // Find the angular acceleration based on the torque that is being applied and the moment of inertia
    angularAcceleration = sumTorque * invI;

    // Integrate the angular acceleration to find the new angular velocity
    angularVelocity += angularAcceleration * dt;

    // Integrate the angular velocity to find the new rotation angle
    rotation += angularVelocity * dt;
    
    // Clear the torque for the next step
    ClearTorque();
}

void Body::Update(float dt) {
    IntegrateLinear(dt);
    IntegrateAngular(dt);
    bool isPolygon = shape->GetType() == POLYGON || shape->GetType() == BOX;
    if (isPolygon) {
        PolygonShape* polygonShape = (PolygonShape*) shape;
        polygonShape->UpdateVertices(rotation, position);
    }
}

bool Body::IsStatic() const {
    const float epsilon = 0.005f;
    return fabs(invMass - 0.0) < epsilon; 
    // if the inverse of the mass minus 0.0 is less than epsilon, we consider that the body is static/has infinite mass
    // we use this trick because floating point numbers can harly equal 0.0;

}

void Body::ApplyImpulse(const Vec2& j) {
    if (IsStatic())
        return;
    velocity += j * invMass;
}