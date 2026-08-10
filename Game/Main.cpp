#include "EvilSpaceGame.h"
#include <vector>
#include <map>
#include <memory>

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main()
{

    // INITIALIZATION
    nu::Engine::Get().Initialize();
    EvilSpaceGame game;
    game.Initialize();
    
    // MAIN LOOP
    bool quit = false;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // UPDATE
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // Engine
        nu::Engine::Get().Update();

        float dt = nu::Engine::Get().GetTime().GetDeltaTime();

        // Game
        game.Update(dt);

        // RENDER
        nu::Engine::Get().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
        nu::Engine::Get().GetRenderer().Clear(); // Clear the renderer

        game.Draw(nu::Engine::Get().GetRenderer());

        nu::Engine::Get().GetPS().Draw(nu::Engine::Get().GetRenderer());

        nu::Engine::Get().GetRenderer().RenderPresent();// Render the screen
    }

    // SHUTDOWN
    nu::Engine::Get().Quit();

    // Testing edits
    return 0;
}
