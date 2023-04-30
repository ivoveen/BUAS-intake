#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "Ball.h"
#include "Obstacle.h"
#include <vector>

constexpr auto PARTICLES = 4096u;


namespace Tmpl8
{
   


    void Game::Init()
    {
       // Ball* myBall = new Ball(200, 500, 50, 2, 100, 0xFFFFFF, 0x00FF00, vec2(0.2, -1));
        //Ball* myBall2 = new Ball(400, 50, 100, 4, 100, 0xFFFFFF, 0x00FF00, vec2(0.1f, 0.1f));

        // Obstacle* box = new Obstacle(50, 500, 750, 510, 0xFFFFFF);

        myGameObjects.push_back(new Ball(200, 500, 50, 2, 100, 0xFFFFFF, 0x00FF00, vec2(0.2, -1)));
        myGameObjects.push_back(new Ball(400, 50, 100, 4, 100, 0xFFFFFF, 0x00FF00, vec2(0.1f, 0.1f)));
        myGameObjects.push_back(new Obstacle(50, 500, 750, 510, 0xFFFFFF));
    }

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);

        for (const auto &obj : myGameObjects) {
            obj->Tick(deltaTime, screen);
        }       

    }
};