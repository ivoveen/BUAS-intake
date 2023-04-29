#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"

constexpr auto PARTICLES = 4096u;


namespace Tmpl8
{

    


    void Game::Init()
    {
    
    }

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        screen->FCircle( 200,  200,  100, 4,  0xFFFFFF,  0xFF0000);
        screen->Circle(420, 200, 100, 4, 0xFFFFFF, 0xFF0000);

    }
};