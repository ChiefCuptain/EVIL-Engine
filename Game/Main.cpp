#include "EvilSpaceGame.h"
#include <vector>
#include <map>
#include <memory>

//class Object
//{
//public:
//    Object() { std::cout << "Constructor\n"; }
//    ~Object() { std::cout << "Destructor\n"; }
//
//    Object(const Object& object) { std::cout << "Copy constructor\n"; }
//    Object& operator = (const Object& object) { std::cout << "Assignment operator \n"; return *this; }
//
//};

int main()
{

    //std::cout << "===============Object===============\n";
    //{
    //    Object objectA;
    //    Object objectB = objectA;
    //    Object objectC;
    //    objectC = objectA;
    //}

    //std::cout << "===============Raw Pointers===============\n";
    //{
    //    Object* objectA = new Object();
    //    std::cout << objectA << "\n";
    //    Object* objectB = new Object(*objectA);
    //    std::cout << objectB << "\n";

    //    Object* objectC = nullptr;
    //    objectC = objectA;
    //    std::cout << objectC << "\n";

    //    delete objectA;
    //    delete objectB;
    //    //delete objectC;
    //}

    //std::cout << "===============Unique Pointers===============\n";
    //{
    //    std::unique_ptr<Object> objectA = std::make_unique<Object>();
    //    std::cout << objectA.get() << "\n";
    //    std::unique_ptr<Object> objectB;
    //    objectB = std::move(objectA);
    //    //std::cout << objectA.get() << "\n";
    //    std::cout << objectB.get() << "\n";


    //}

    //std::cout << "===============Shared Pointers===============\n";
    //std::shared_ptr<Object> objectC;
    //{
    //    auto objectA = std::make_shared<Object>();
    //    std::cout << objectA.get() << "\n";
    //    std::cout << objectA.use_count() << "\n";
    //    auto objectB = objectA;
    //    std::cout << objectB.get() << "\n";
    //    std::cout << objectB.use_count() << "\n";
    //    objectC = objectA;
    //    std::cout << objectC.get() << "\n";
    //    std::cout << objectC.use_count() << "\n";
    //}
    //std::cout << objectC.use_count() << "\n";


    //return 0;

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


        nu::Engine::Get().GetRenderer().DrawTexture(*nu::Resources().Get<nu::Texture>("Assets/Textures/spr_player.png", nu::Engine::Get().GetRenderer()), 30, 30);


        nu::Engine::Get().GetPS().Draw(nu::Engine::Get().GetRenderer());

        nu::Engine::Get().GetRenderer().RenderPresent();// Render the screen
    }

    // SHUTDOWN
    nu::Engine::Get().Quit();

    // Testing edits
    return 0;
}
