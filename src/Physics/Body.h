#ifndef BODY_H
#define BODY_H

#include "Vec2.h"
#include "shape.h"

struct Body {
    // Collision detection
    bool isColliding = false;

    // Linear motion
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    // Angular motion
    float rotation;
    float angularVelocity;
    float angularAcceleration;

    // Forces and torque
    Vec2 sumForces;
    float sumTorque;

    // Mass and Moment of inertia
    float mass;
    float invMass;
    float I;
    float invI;

    // Pointer to the body shape of this rigid body
    Shape* shape = nullptr;

    Body(const Shape& shape, float x, float y, float mass);
    ~Body();

    void AddForce(const Vec2& force);
    void AddTorque(float torque);
    void ClearForces();
    void ClearTorque();

    void IntegrateLinear(float dt);
    void IntegrateAngular(float dt);

    void Update(float dt);
};

#endif
