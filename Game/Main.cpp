#include "EvilSpaceGame.h"
#include <vector>
#include <map>
#include <memory>

int main()
{




    // load the json data from a file
    std::string buffer;
    if (nu::ReadTextFile("Assets/Data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (nu::json::Load("Assets/Data/data.json", document))
        {
            std::string name;
            int age;
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);


            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
    }

    return 0;

    // INITIALIZATION
    nu::Engine::Get().Initialize();
    nu::EvilSpaceGame game;
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
