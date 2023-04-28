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
        screen->FLine(35,23,240,250, 0xff0000);
        screen->Line(25, 23, 230, 250, 0xff0000);
    }
};