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
   std::vector<GameObject*> Game::myGameObjects;


    void Game::Init()
    {
        std::vector<vec2Equation> line;
        line.push_back(vec2Equation(vec2(0, 0), vec2(700, 0)));


        //myGameObjects.push_back(new Ball(200, 400, 50, 2, 100, 0xFFFFFF, 0x00FF00, vec2(0.05f, -1.0f)));
        myGameObjects.push_back(new Obstacle(50, 700, 750, 710, 0xFFFFFF, line)); 
        myGameObjects.push_back(new Ball(400, 50, 100, 4, 100, 0xFFFFFF, 0x00FF00, vec2(0.2f, 0.2f)));
       
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