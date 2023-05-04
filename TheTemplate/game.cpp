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
        line.push_back(vec2Equation(vec2(0, 0), vec2(300, 0)));
        line.push_back(vec2Equation(vec2(300, 0), vec2(0, 110)));
        line.push_back(vec2Equation(vec2(300, 110), vec2(-300, 0)));
        line.push_back(vec2Equation(vec2(0, 110), vec2(0, -110)));


        myGameObjects.push_back(new Ball(800, 400, 50, 2, 100, 0xFFFFFF, 0x00FF00, vec2(-0.5f, 0.0f)));
        myGameObjects.push_back(new Obstacle(150, 600, 450, 710, 0xFFFFFF, line)); 
        myGameObjects.push_back(new Ball(200, 50, 10, 2, 100, 0xFFFFFF, 0x00FF00, vec2(0.2f, 0.2f)));
        myGameObjects.push_back(new Ball(400, 1000, 10, 2, 100, 0xFFFFFF, 0x00FFF0, vec2(0.2f, -0.9f)));
        myGameObjects.push_back(new Ball(0, 300, 10, 2, 100, 0xFFFFFF, 0x00FFF0, vec2(0.2f, 0.0f)));
       
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