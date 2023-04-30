#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "template.h"

constexpr auto PARTICLES = 4096u;


namespace Tmpl8
{
    class physics {
    public:
        physics() {
            g = 0.00081f;
        
        }
        float g;
        vec2 v;
        
        vec2 gravity(float x, float y, float mass, float deltaTime) {
            vec2 Fz = vec2(0, 0);
            vec2 y0 = vec2(x, y);
            vec2 v0 = v;
            vec2 a = vec2(0, g);

            v = v0 + a * deltaTime;
            Fz = y0 + v * deltaTime +  a * 0.5f * powf(deltaTime, 2);

            return Fz;
        }

        
        vec2 airResistance();
        vec2 bounce(vec2 F) {
            F *= -1;
            return F;
        }
        vec2 totalForce();


    };

    struct Hitbox {
        Hitbox(float x1, float y1, float x2, float y2) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
        }
        float x1, y1, x2, y2;
    };


    class Obstacle {
    public:
        Obstacle(float x1, float y1, float x2, float y2, Pixel c1 ) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
        }
        float x1, y1, x2, y2;
        Pixel c1;

        Hitbox GetHitbox() {
            return Hitbox(x1, y1, x2, y2);
        }

        void draw(Surface* screen) {
            screen->FBox(x1, y1, x2, y2, c1);
        }

    };

    

    class Ball: private physics{
    public: 
        Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v) {
            this->x = x;
            this->y = y;
            this->r = r;
            this->b = b;
            this->mass = mass;
            this->c1 = c1;
            this->c2 = c2;
            this->v = v;
        }
        float x, y, r, b, mass;
        Pixel c1, c2;

        void move(float deltaTime, Surface* screen) {
            vec2 force = gravity(x, y, 0, deltaTime);
            x = force.x, y = force.y;

            draw(screen);
        }

        void draw(Surface* screen) {
            screen->FCircle(x, y, r, b, c1, c2);
        }

        Hitbox GetHitbox() {
            return Hitbox(x-r, y-r, x+r, y+r);
        }

    };
    


    Ball* myBall = new Ball(200,500,50,2,100,0xFFFFFF,0x00FF00, vec2(0.2,-1));
    Ball* myBall2 = new Ball(400, 50, 100, 4, 100, 0xFFFFFF, 0x00FF00, vec2(0.1f,0.1f));


    Obstacle* box = new Obstacle(50,500,750,510, 0xFFFFFF);
    void Game::Init()
    {
       
    }

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
       

        myBall->move(deltaTime, screen);
        myBall2->move(deltaTime, screen);
        
        box->draw(screen);



    }
};