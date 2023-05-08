#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"
#include "Ball.h"
#include "Obstacle.h"
#include "Flipper.h"
#include <vector>
#include <windows.h>
constexpr auto PARTICLES = 4096u;


namespace Tmpl8
{
   std::vector<GameObject*> Game::myGameObjects;
   Surface* ballSprite = new Surface("assets/ball.tga");

   void Game::Init()
   {
       
       std::vector<vec2Equation> tubeInnerWallS1;
       tubeInnerWallS1.push_back(vec2Equation(vec2(0, 0), vec2(35, 35)));
       tubeInnerWallS1.push_back(vec2Equation(vec2(35, 35), vec2(0, 700))); 
       std::vector<vec2Equation> tubeInnerWallS2;
       tubeInnerWallS2.push_back(vec2Equation(vec2(0, 0), vec2(600, 0)));
       std::vector<vec2Equation> tubeInnerWallS3;
       tubeInnerWallS3.push_back(vec2Equation(vec2(-35, 35), vec2(35, -35)));
       tubeInnerWallS3.push_back(vec2Equation(vec2(-35, 165 ), vec2(0, -130)));
       tubeInnerWallS3.push_back(vec2Equation(vec2(15, 245), vec2(-50, -80)));
       std::vector<vec2Equation> tubeOuterWallS1;
       tubeOuterWallS1.push_back(vec2Equation(vec2(35, 35), vec2(-35, -35)));
       tubeOuterWallS1.push_back(vec2Equation(vec2(35, 635), vec2(0, -600)));
       std::vector<vec2Equation> tubeOuterWallS2;
       tubeOuterWallS2.push_back(vec2Equation(vec2(715, 0), vec2(-715, 0)));
       std::vector<vec2Equation> tubeOuterWallS3;
       tubeOuterWallS3.push_back(vec2Equation(vec2(0, 0), vec2(-35, 35)));
       tubeOuterWallS3.push_back(vec2Equation(vec2(-35, 35), vec2(0, 250)));
       tubeOuterWallS3.push_back(vec2Equation(vec2(-35, 285), vec2(50,80)));
       std::vector<vec2Equation> leftWall;
       leftWall.push_back(vec2Equation(vec2(0, 0), vec2(-50, 100)));
       leftWall.push_back(vec2Equation(vec2(-50, 100), vec2(0, 206)));
       std::vector<vec2Equation> bottomLeftWall;
       bottomLeftWall.push_back(vec2Equation(vec2(0, 0), vec2(263, 71)));
       bottomLeftWall.push_back(vec2Equation(vec2(263, 71), vec2(0, 50)));
       std::vector<vec2Equation> bottomRightWall;
       bottomRightWall.push_back(vec2Equation(vec2(-263, 71), vec2(263, -71)));
       bottomRightWall.push_back(vec2Equation(vec2(-263, 121), vec2(0, -50)));
       std::vector<vec2Equation> rightWall;
       rightWall.push_back(vec2Equation(vec2(0,0), vec2(0, -350)));
       std::vector<vec2Equation> topRightWall;
       topRightWall.push_back(vec2Equation(vec2(0, 0), vec2(-100, -50)));
       topRightWall.push_back(vec2Equation(vec2(-100, -50), vec2(50, -150)));
       topRightWall.push_back(vec2Equation(vec2(-50, -200), vec2(-50, -25)));
       topRightWall.push_back(vec2Equation(vec2(-100, -225), vec2(-50, 150)));
       topRightWall.push_back(vec2Equation(vec2(-150, -75), vec2(-67, -33)));
       std::vector<vec2Equation> topWall;
       topWall.push_back(vec2Equation(vec2(380, 0), vec2(-380, 0)));
       topWall.push_back(vec2Equation(vec2(415, 35), vec2(-35, -35)));
       std::vector<vec2Equation> topCenterWall;
       topCenterWall.push_back(vec2Equation(vec2(-280, 160), vec2(280, -160)));
       topCenterWall.push_back(vec2Equation(vec2(-230, 185), vec2(-50, -25)));
       topCenterWall.push_back(vec2Equation(vec2(-57, 86), vec2(-173, 99)));
       std::vector<vec2Equation> topLeftWall;
       topLeftWall.push_back(vec2Equation(vec2(50, 0), vec2(-50, 0)));
       topLeftWall.push_back(vec2Equation(vec2(0, -80), vec2(50, 80)));
       topLeftWall.push_back(vec2Equation(vec2(0, -170), vec2(0, 90)));
       topLeftWall.push_back(vec2Equation(vec2(35, -205), vec2(-35, 35)));
       std::vector<vec2Equation> leftCatcher;
       leftCatcher.push_back(vec2Equation(vec2(0, 13), vec2(0, -113)));
       leftCatcher.push_back(vec2Equation(vec2(0, -100), vec2(40, -80)));
       leftCatcher.push_back(vec2Equation(vec2(40, -180), vec2(12, 6))); 
       leftCatcher.push_back(vec2Equation(vec2(52, -174), vec2(-28, 86))); 
       leftCatcher.push_back(vec2Equation(vec2(24, -88), vec2(0, 80)));
       leftCatcher.push_back(vec2Equation(vec2(24, -8), vec2(120, 30)));
       leftCatcher.push_back(vec2Equation(vec2(137, 49), vec2(-137,-36)));
       leftCatcher.push_back(vec2Equation(vec2(144, 22), vec2(-6, 27)));
       std::vector<vec2Equation> rightCatcher;
       rightCatcher.push_back(vec2Equation(vec2(0, 13), vec2(-144, 35)));
       rightCatcher.push_back(vec2Equation(vec2(-144, 48), vec2(-7, -25)));
       rightCatcher.push_back(vec2Equation(vec2(-150, 22), vec2(117, -31)));
       rightCatcher.push_back(vec2Equation(vec2(-32, -10), vec2(10, -170)));
       rightCatcher.push_back(vec2Equation(vec2(-22, -180), vec2(12, 0)));
       rightCatcher.push_back(vec2Equation(vec2(-10, -180), vec2(10, 193)));
       std::vector<vec2Equation> leftFlipper;
       leftFlipper.push_back(vec2Equation(vec2(0, 0), vec2(150, 20))); 
       leftFlipper.push_back(vec2Equation(vec2(150, 20), vec2(0, 6)));
       leftFlipper.push_back(vec2Equation(vec2(150, 26), vec2(-150, 0)));
       leftFlipper.push_back(vec2Equation(vec2(0, 26), vec2(0, -26)));
       std::vector<vec2Equation> rightFlipper;
       rightFlipper.push_back(vec2Equation(vec2(0, -26), vec2(0, 26)));
       rightFlipper.push_back(vec2Equation(vec2(0, 0), vec2(-150, 0)));
       rightFlipper.push_back(vec2Equation(vec2(-150, 0), vec2(0, -6)));
       rightFlipper.push_back(vec2Equation(vec2(-150, -6), vec2(150, -20)));

        myGameObjects.push_back(new Flipper(213, 623, 0xFF00FF, leftFlipper, VK_LEFT));
        myGameObjects.push_back(new Flipper(523, 623, 0xFF00FF, rightFlipper, VK_RIGHT));
        
        myGameObjects.push_back(new Ball(760, 600, ballSprite, vec2(0.0f, -1.0f)));    
        myGameObjects.push_back(new Ball(400, 630, ballSprite, vec2(-0.0f, -0.0f)));
        myGameObjects.push_back(new Ball(600, 250, ballSprite, vec2(-0.0f, -0.0f)));

        myGameObjects.push_back(new Obstacle(68, 600, 0xFFFFFF, leftCatcher));
        myGameObjects.push_back(new Obstacle(674, 600, 0xFFFFFF, rightCatcher));
        myGameObjects.push_back(new Obstacle(708, 60, 0xFFFFFF, tubeInnerWallS1));
        myGameObjects.push_back(new Obstacle(108, 60, 0xFFFFFF, tubeInnerWallS2));
        myGameObjects.push_back(new Obstacle(108, 60, 0xFFFFFF, tubeInnerWallS3));
        myGameObjects.push_back(new Obstacle(758, 8, 0xFFFFFF, tubeOuterWallS1));
        myGameObjects.push_back(new Obstacle(43, 8, 0xFFFFFF, tubeOuterWallS2));
        myGameObjects.push_back(new Obstacle(43, 8, 0xFFFFFF, tubeOuterWallS3));
        myGameObjects.push_back(new Obstacle(58, 373, 0xFFFFFF, leftWall));
        myGameObjects.push_back(new Obstacle(8, 679, 0xFFFFFF, bottomLeftWall));
        myGameObjects.push_back(new Obstacle(734, 679, 0xFFFFFF, bottomRightWall));
        myGameObjects.push_back(new Obstacle(734, 679, 0xFFFFFF, rightWall));
        myGameObjects.push_back(new Obstacle(734, 329, 0xFFFFFF, topRightWall));
        myGameObjects.push_back(new Obstacle(123, 305, 0xFFFFFF, topLeftWall));
        myGameObjects.push_back(new Obstacle(158, 100, 0xFFFFFF, topWall));
        myGameObjects.push_back(new Obstacle(573, 135, 0xFFFFFF, topCenterWall));
               /*
        std::vector<vec2Equation> box2;
        box2.push_back(vec2Equation(vec2(0, 0), vec2(300, 0)));
        box2.push_back(vec2Equation(vec2(300, 0), vec2(0, 110)));
        box2.push_back(vec2Equation(vec2(300, 110), vec2(-300, 0)));
        box2.push_back(vec2Equation(vec2(0, 110), vec2(0, -110)));

        myGameObjects.push_back(new Ball(400, 225, ballSprite, vec2(-0.0f, -0.0f)));

        myGameObjects.push_back(new Obstacle(300, 650, 0xFFFFFF, box2));*/

       // myGameObjects.push_back(new Ball(200, 400, ballSprite, vec2(0, 0)));
       // myGameObjects.push_back(new Ball(400, 800, 20, 2, 100, 0xFFFFFF, 0x00FFF0, vec2(0.2f, -0.6f)));
       // myGameObjects.push_back(new Ball(500, 300, 20, 2, 100, 0xFFFFFF, 0x00FFF0, vec2(0.2f, 0.3f)));
        start = false;
    }

    void Game::Shutdown() {
       
    }
    //Sprite theSprite(new Surface("assets/ball.png"), 1);

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        //ballSprite.Draw(screen, 0, 0);

        if (GetAsyncKeyState(VK_UP)) start = true;

        if (start) {
            
            for (const auto& obj : myGameObjects) {
                obj->Tick(deltaTime, screen);
             //   BoundingBox boundingBox =obj->GetBoundingBox();
             //   screen->Box(boundingBox.x1, boundingBox.y1, boundingBox.x2, boundingBox.y2, 0xFF0000);
            }
        }    

    }


};
