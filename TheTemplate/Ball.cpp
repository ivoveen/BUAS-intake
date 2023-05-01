#include "Ball.h"
#include "template.h"
#include "Game.h"
#include "surface.h"
#include "Physics.h"
#include "GameObject.h"


namespace Tmpl8
{
    Ball::Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->b = b;
        this->mass = mass;
        this->c1 = c1;
        this->c2 = c2;
        this->v = v;
    }

    void Ball::Tick(float deltaTime, Surface* screen) {
        Move(deltaTime, screen);
        Draw(screen);
    }

    void Ball::Move(float deltaTime, Surface* screen) {
        vec2 force = TotalForce(x, y, 0.0001f, deltaTime);
        float xTemp = force.x, yTemp = force.y;


        if (!CheckCollison()) {
            x = xTemp, y = yTemp;

        }
        

        
       
    }
    
    bool Ball::CheckCollison(){
      
        for (const auto& obj : Game::myGameObjects)
        {
            Hitbox myHitbox = GetHitbox();
            Hitbox checkHitbox = obj->GetHitbox();
           
            //check if the checkHitbox isn't your own Hitbox
            if (myHitbox.x1 != checkHitbox.x1 && myHitbox.y1 != checkHitbox.y1 && myHitbox.x2 != checkHitbox.x2 && myHitbox.y2 != checkHitbox.y2) {

                // do the hitboxes collide?
                if (myHitbox.x1 <= checkHitbox.x2 && myHitbox.x2 >= checkHitbox.x1 && myHitbox.y1 <= checkHitbox.y2 && myHitbox.y2 >= checkHitbox.y1) {
                    return true; 
                }
            }
        }

        return false;
    }


    Hitbox Ball::GetHitbox() {
        return Hitbox(x - r, y - r, x + r, y + r);
    }

    void Ball::Draw(Surface* screen) {
        screen->FCircle(x, y, r, b, c1, c2);
    }

   
}