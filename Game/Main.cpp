#include "EvilSpaceGame.h"
#include "Player.h"
#include <vector>
#include <map>
#include <memory>

using namespace nu;

    int main()
    {
        // don't move this
        SetWorkingDirectory("Assets");
        // don't move this

        auto actor = Factory::Instance().Create<Actor>("Actor");
        std::cout << actor->IsActive() << "\n";

        return 0;
        // INITIALIZATION
        Engine::Get().Initialize();
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
            Engine::Get().Update();

            float dt = Engine::Get().GetTime().GetDeltaTime();

            // Game
            game.Update(dt);

            // RENDER
            Engine::Get().GetRenderer().SetColor(0, 0, 0); // Set render draw color to black
            Engine::Get().GetRenderer().Clear(); // Clear the renderer

            game.Draw(Engine::Get().GetRenderer());

            Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

            Engine::Get().GetRenderer().RenderPresent();// Render the screen
        }

        // SHUTDOWN
        Engine::Get().Quit();

        // Testing edits
        return 0;
    }