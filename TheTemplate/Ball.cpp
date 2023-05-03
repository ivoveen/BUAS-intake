#include "Ball.h"
#include "template.h"
#include "Game.h"
#include "surface.h"
#include "Physics.h"
#include "GameObject.h"
#include <vector>


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
        stop = false;
    }

    void Ball::Tick(float deltaTime, Surface* screen) {
        Move(deltaTime, screen);
        Draw(screen);
    }

    void Ball::Move(float deltaTime, Surface* screen) {
        if(stop == false){
        vec2 force = TotalForce(x, y, 0.0001f, deltaTime);
        vec2 forcePos = force + vec2(x, y);
        
        float xTemp = forcePos.x, yTemp = forcePos.y;


        GameObject* object = CheckCollison();
        if (object == NULL) {
            x = xTemp, y = yTemp;

        }
        else {
            vec2 pointOfImpact = PointOfImpact( object, force);
            if (pointOfImpact == vec2(0, 0)) {
                x = xTemp, y = yTemp;
            }
            else {
                x = pointOfImpact.x, y = pointOfImpact.y;
                stop = true;
                v = vec2(0, 0);

            }
            
        }
        //delete(object);
        }
    }
    
    GameObject* Ball::CheckCollison(){
      
        for (const auto& obj : Game::myGameObjects)
        {
            Hitbox myHitbox = GetHitbox();
            Hitbox checkHitbox = obj->GetHitbox();
           
            //check if the checkHitbox isn't your own Hitbox
            if (myHitbox.x1 != checkHitbox.x1 && myHitbox.y1 != checkHitbox.y1 && myHitbox.x2 != checkHitbox.x2 && myHitbox.y2 != checkHitbox.y2) {

                // do the hitboxes collide?
                if (myHitbox.x1 <= checkHitbox.x2 && myHitbox.x2 >= checkHitbox.x1 && myHitbox.y1 <= checkHitbox.y2 && myHitbox.y2 >= checkHitbox.y1) {
                    //yes there is a collision
                    return obj;
                }
            }
        }

        return NULL;
    }

    vec2 Ball::PointOfImpact(GameObject* obj, vec2 force) {
        //get the vector equation of the line the ball collided with
        std::vector<vec2Equation> edgeVectors = obj->GetEdgeVectors();
        
        
        
        //calculate the point (D) on the old circle that will hit the ground first.
        float nLine;
        float nForce;
        float XLinePos = edgeVectors[0].position.x, YLinePos = edgeVectors[0].position.y;
        vec2 d;
        vec2 obstacleEdge = edgeVectors[0].direction;
        d = vec2(x, y) + obstacleEdge.clockwise().normalized() * r;

        //calculate intersection between de movement of point d and the vector of the object edge
        float Xd = d.x, Yd = d.y;

        float XForce = force.x, YForce = force.y;
        float XLine = obstacleEdge.x, YLine = obstacleEdge.y;
        //nLine = (Yd * XForce + XLinePos * YForce - Xd * YForce - YLinePos * XForce) / (YLine * XForce - XLine * YForce);
        nForce = (YLinePos * XLine + Xd * YLine - XLinePos * YLine - Yd * XLine) / (YForce * XLine - XForce * YLine);


        //get the intersection location
        //vec2 dl = vec2(XLinePos, YLinePos) + obstacleEdge * nLine;
        vec2 dl = vec2(Xd, Yd) + force * nForce;

        //check if the ball should be at this location this tick, or the next. 
        //return dl;
        //go back to circle pos
        if(nForce < 1){
            return dl + obstacleEdge.counterClockwise().normalized() * r;
        }
        else {
            return vec2(0, 0);
        }
        

    }



    Hitbox Ball::GetHitbox() {
        return Hitbox(x - r, y - r, x + r, y + r);
    }

    void Ball::Draw(Surface* screen) {
        screen->FCircle(x, y, r, b, c1, c2);
    }

   
}