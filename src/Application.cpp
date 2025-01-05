#include "Application.h"
#include "./Physics/Constants.h"

bool Application::IsRunning() {
    return running;
}

///////////////////////////////////////////////////////////////////////////////
// Setup function (executed once in the beginning of the simulation)
///////////////////////////////////////////////////////////////////////////////
void Application::Setup() {
    running = Graphics::OpenWindow();

    particle = new Particle(50, 100, 1.0f);
    particle->radius = 4;
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
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Update function (called several times per second to update objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Update() {
    // Get width and height
    static int screenWidth = Graphics::Width();
    static int screenHeight = Graphics::Height();

    // Wait some time until we reach the target frame time in milliseconds
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0) 
        SDL_Delay(timeToWait);
    // Calculate the deltaTime in sec
    float deltaTime = (SDL_GetTicks() - timePreviousFrame)/1000.0f;
    if (deltaTime > 0.016) 
           deltaTime = 0.016;

    // Set the time of the current frame to be used in the sext one
    timePreviousFrame = SDL_GetTicks();

    // Proceed to update the objects on the scene
    particle->acceleration = Vec2(6.0 * PIXELS_PER_METER, 9.8 * PIXELS_PER_METER);

    // Integrate accel & vel to find the new position
    particle->Integrate(deltaTime);

    // Check the particle position and try to limit it, put a constraint. Keep the particle inside the boundaries of the screen
    if (particle->position.x - particle->radius <= 0) {
        particle->position.x = particle->radius;
        particle->velocity.x *= -0.9;
    }
    else if (particle->position.x + particle->radius >= screenWidth) {
        particle->position.x = screenWidth - particle->radius;
        particle->velocity.x *= -0.9;
    }

    if (particle->position.y - particle->radius <= 0) {
        particle->position.y = particle->radius;
        particle->velocity.y *= -0.9;
    }
    else if (particle->position.y + particle->radius >= screenHeight) {
        particle->position.y = screenHeight - particle->radius;
        particle->velocity.y *= -0.9;
    }      

}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(particle->position.x, particle->position.y, particle->radius, 0xFFFFFFFF);
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    delete particle;

    Graphics::CloseWindow();
}