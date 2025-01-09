#include "Application.h"
#include "./Physics/Constants.h"
#include "./Physics/Force.h"

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    Body* body = new Body(Graphics::Width() / 2.0, Graphics::Height() / 2.0, 1.0);
    body->radius = 4;
    bodies.push_back(body);
}

///////////////////////////////////////////////////////////////////////////////
// Input processing
///////////////////////////////////////////////////////////////////////////////
void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            // ...
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {
    // Wait some time until the reach the target frame time in milliseconds
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    // Calculate the deltatime in seconds
    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
    if (deltaTime > 0.016)
        deltaTime = 0.016;

    // Set the time of the current frame to be used in the next one
    timePreviousFrame = SDL_GetTicks();

    // Apply forces to the bodies
    for (auto body : bodies) {
        // Apply the weight force
        Vec2 weight = Vec2(0.0, body->mass * 9.8 * PIXELS_PER_METER);
        body->AddForce(weight);
    }

    // Integrate the acceleration and velocity to estimate the new position
    for (auto body : bodies) {
        body->Integrate(deltaTime);
    }

    // Check the boundaries of the window applying a hardcoded bounce flip in velocity
    for (auto body : bodies) {
        if (body->position.x - body->radius <= 0) {
            body->position.x = body->radius;
            body->velocity.x *= -0.9;
        }
        else if (body->position.x + body->radius >= Graphics::Width()) {
            body->position.x = Graphics::Width() - body->radius;
            body->velocity.x *= -0.9;
        }
        if (body->position.y - body->radius <= 0) {
            body->position.y = body->radius;
            body->velocity.y *= -0.9;
        }
        else if (body->position.y + body->radius >= Graphics::Height()) {
            body->position.y = Graphics::Height() - body->radius;
            body->velocity.y *= -0.9;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF0F0721);

    // Draw all bodies
    for (auto body : bodies) {
        Graphics::DrawFillCircle(body->position.x, body->position.y, body->radius, 0xFFFFFFFF);
    }

    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    for (auto body : bodies) {
        delete body;
    }
    Graphics::CloseWindow();
}