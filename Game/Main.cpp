#include "EvilSpaceGame.h"
#include <vector>
#include <map>
#include <memory>
#include <fstream>

int main()
{

    {
        // Read file
        std::ifstream file("Assets/Data/text.txt");
        if (file.is_open())
        {
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << "\n";
            }
            std::cout << "\n\t<Finished reading file.>\n";
        }
    }

    {
        // Write file
        std::ofstream file("Assets/Data/text.txt", std::ios::app);
        if (file.is_open())
        {
            file << "Example text, blah.\n";
        }
    }

    {
        // Read / write
        std::fstream file("Assets/Data/text.txt", std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open())
        {
            // Input
            file << "Add a line.\n";
            // Output
            file.seekg(0);
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << "\n";
            }
            std::cout << "\n\t<Finished reading file.>\n";
        }
    }

    {
        std::string name;
        int score;
        bool isAlive;

        bool save = false;

        // Save game data
        if (save)
        {
            name = "Jack";
            score = 12;
            isAlive = true;

            std::ofstream file("Assets/Data/game.txt");
            if (file.is_open())
            {
                file << name << "\n";
                file << score << "\n";
                file << isAlive << "\n";
            }
        }
        // Load game data
        bool load = true;

        if (load)
        {
            std::ifstream file("Assets/Data/game.txt");
            if (file.is_open())
            {
                std::getline(file, name);

                std::string str;
                std::getline(file, str);
                score = std::stoi(str);
                file >> isAlive;
            }
        }

        // Display game data
        std::cout << name << std::endl;
        std::cout << score << std::endl;
        std::cout << isAlive << std::endl;
    }

    return 0;

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
