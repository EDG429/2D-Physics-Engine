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
    /*
    Particle* smallBall = new Particle(50, 100, 1.0);
    smallBall->radius = 4;
    particles.push_back(smallBall);

    Particle* bigBall = new Particle(200, 100, 3.0);
    bigBall->radius = 12;
    particles.push_back(bigBall);*/

    liquid.x = 0;
    liquid.y = Graphics::Height() * 0.5;
    liquid.w = Graphics::Width();
    liquid.h = Graphics::Height() * 0.5;
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
            if (event.key.keysym.sym == SDLK_UP)
                pushForce.y = -50 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_RIGHT)
                pushForce.x = 50 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_DOWN)
                pushForce.y = 50 * PIXELS_PER_METER;
            if (event.key.keysym.sym == SDLK_LEFT)
                pushForce.x = -50 * PIXELS_PER_METER;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP)
                pushForce.y = 0;
            if (event.key.keysym.sym == SDLK_RIGHT)
                pushForce.x = 0;
            if (event.key.keysym.sym == SDLK_DOWN)
                pushForce.y = 0;
            if (event.key.keysym.sym == SDLK_LEFT)
                pushForce.x = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                Particle* particle = new Particle(x, y, 1.0);
                particle->radius = 5;
                particles.push_back(particle);
            }
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

    // Apply forces to the particles
    for (auto particle : particles) {
        // Apply wind force to the particle if we are in the upper part of the screen
        if (particle->position.y < liquid.y) {
            Vec2 wind = Vec2(1.0 * PIXELS_PER_METER, 0.0);
            particle->AddForce(wind);   
        }         
    
        // Apply weight force to the particle    
        Vec2 weight = Vec2(0.0,particle->mass * 9.8 * PIXELS_PER_METER);
        particle->AddForce(weight);    

        // Apply push force to the particle           
        particle->AddForce(pushForce);

        // Apply friction force        


        // Apply a drag force if particles are inside the liquid
        if (particle->position.y >= liquid.y) {
            Vec2 drag = Force::GenerateDragForce(*particle, 0.01);
            particle->AddForce(drag);
        }
    }

    // Integrate accel & vel to find the new position
    for (auto particle : particles)
    {
        particle->Integrate(deltaTime);
    }

    // Check the particle position vs boundaries and try to limit it, put a constraint. Keep the particle inside the boundaries of the screen
    for (auto particle : particles) {
        if (particle->position.x - particle->radius <= 0) {
            particle->position.x = particle->radius;
            particle->velocity.x *= -1;
        }
        else if (particle->position.x + particle->radius >= screenWidth) {
            particle->position.x = screenWidth - particle->radius;
            particle->velocity.x *= -1;
        }

        if (particle->position.y - particle->radius <= 0) {
            particle->position.y = particle->radius;
            particle->velocity.y *= -1;
        }
        else if (particle->position.y + particle->radius >= screenHeight) {
            particle->position.y = screenHeight - particle->radius;
            particle->velocity.y *= -1;
        }      
    }
}

///////////////////////////////////////////////////////////////////////////////
// Render function (called several times per second to draw objects)
///////////////////////////////////////////////////////////////////////////////
void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    // Draw liquid in the screen
    Graphics::DrawFillRect(liquid.x + liquid.w * 0.5, liquid.y + liquid.h * 0.5, liquid.w, liquid.h, 0xFF6E3713);

    // Draw particles
    for (auto particle : particles)
    {
        Graphics::DrawFillCircle(particle->position.x, particle->position.y, particle->radius, 0xFFFFFFFF);
    }
    Graphics::RenderFrame();
}

///////////////////////////////////////////////////////////////////////////////
// Destroy function to delete objects and close the window
///////////////////////////////////////////////////////////////////////////////
void Application::Destroy() {
    for (auto particle : particles)
    {
       delete particle;
    }

    Graphics::CloseWindow();
}