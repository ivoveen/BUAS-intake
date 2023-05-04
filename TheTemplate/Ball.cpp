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



    vec2 Ball::ClosestPointOnSegment(vec2 p, vec2 a, vec2 b) {
    //This function calculates the distance between a point and a line segment. I did not make this myself,
    // i got it from: https://www.youtube.com/watch?v=egmZJU-1zPU&ab_channel=Two-BitCoding
    
        vec2 ab = b - a;
        vec2 ap = p - a;
        vec2 cp;

        float proj = ap.dot(ab);
        float abLenSq = powf(ab.length(), 2);
        float d = proj / abLenSq;

        if (d <= 0) {
            cp = a;
        }
        else if (d >= 1) {
            cp = b;
        }
        else {
            cp = a + ab * d;
        }
  
        return cp;
    }



    vec2 Ball::PointOfImpact(GameObject* obj, vec2 force) {
        std::vector<vec2Equation> edgeVectors = obj->GetEdgeVectors();
        
        //select with which line of the object the ball has collided.
        bool isCorner = false; 
        float shortestDistance = NULL;
        vec2Equation closestEdgeVector;
        vec2 closestPoint;


        for (const auto& obj : edgeVectors) {
            vec2 p = vec2(x,y);
            vec2 a = obj.position;
            vec2 b = obj.direction + obj.position;
            vec2 cp = ClosestPointOnSegment(p, a, b);

            float distance = (abs(sqrtf(powf(cp.x - p.x, 2) + powf(cp.y - p.y, 2))));
            
            if (shortestDistance == NULL || distance <= shortestDistance) {
                isCorner = (distance == shortestDistance);
                shortestDistance = distance;
                closestEdgeVector = obj;
                closestPoint = cp;
            }
        }
        
        
        
        //calculate the point (D) on the old circle that will hit the ground first.
       
        

        if (isCorner) {
            //this collision happens with a corner
            // x(t) = x0 + fX * t
            // y(t) = y0 + fY * t
            // d(t) = sqrt((x(t) - x_c)^2 + (y(t) - y_c)^2)
            // d(t) = r
            // substitute x(t) and y(t) and solve for t
            // to solve this eqaution I used chatGPT4 to save time
            float fX = force.x, fY = force.y;
            float xCorner = closestPoint.x, yCorner = closestPoint.y;
            float xCenter = x, yCenter = y;

            float a = powf(fX, 2) + powf(fY, 2);
            float b = 2 * (xCenter * fX - xCorner * fX + yCenter * fY - yCorner * fY);
            float c = powf(xCenter, 2) - 2 * xCenter * xCorner + powf(xCorner, 2) + powf(yCenter, 2) - 2 * yCenter * yCorner + powf(yCorner, 2) - powf(r, 2);

            float d = powf(b, 2) - 4 * a * c;

            if (d < 0) {
                return vec2(0, 0);
            }

            float t1 = (-b + sqrt(d)) / (2 * a);
            float t2 = (-b - sqrt(d)) / (2 * a);

            //the smallest positive t is the one we need.
            float t ;
            if (t1 <= t2 && t1 > 0) {
                t = t1;
            }
            else if (t2 <= t1 && t1 > 0) {
                t = t2;
            }
            else {
                return vec2(0, 0);
            }

            vec2 collisionCircleCenter = vec2(xCenter, yCenter) + force * t;
            vec2 cornerCollisionPoint = collisionCircleCenter + force.normalized() * r;

            //check if the collision point on the line is within reach of the force of the ball.
            vec2 circleCollisionPoint = vec2(xCenter, yCenter) + force.normalized() * r;
            float test = sqrtf(powf(circleCollisionPoint.x - cornerCollisionPoint.x, 2) + powf(circleCollisionPoint.y - cornerCollisionPoint.y, 2));
            
            if (force.length() < test) {
                return vec2(0, 0);
            }
            else {
                return collisionCircleCenter;
            }
        }

        else {
            //this collision happens with an edge
            float nLine;
            float nForce;
            float XLinePos = closestEdgeVector.position.x, YLinePos = closestEdgeVector.position.y;
            vec2 circleCollisionPoint;
            vec2 obstacleEdge = closestEdgeVector.direction;
            vec2 lineCollisionPoint;


            circleCollisionPoint = vec2(x, y) + obstacleEdge.clockwise().normalized() * r;

            //calculate intersection between de movement of point d and the vector of the object edge
            float Xd = circleCollisionPoint.x, Yd = circleCollisionPoint.y;

            float XForce = force.x, YForce = force.y;
            float XLine = obstacleEdge.x, YLine = obstacleEdge.y;

            nLine = (Yd * XForce + XLinePos * YForce - Xd * YForce - YLinePos * XForce) / (YLine * XForce - XLine * YForce);
            nForce = (YLinePos * XLine + Xd * YLine - XLinePos * YLine - Yd * XLine) / (YForce * XLine - XForce * YLine);


            //get the intersection location
            lineCollisionPoint = vec2(Xd, Yd) + force * nForce;

            //check if this intersection is actually on the edge, and not too far away
            if (nForce < 1 && nLine < 1 && nLine > 0) {
                return lineCollisionPoint + obstacleEdge.counterClockwise().normalized() * r;
            }
            else {
                return vec2(0, 0);
            }


        }

    }

    //calculate the distance between the center of the circle and the line


    Hitbox Ball::GetHitbox() {
        return Hitbox(x - r, y - r, x + r, y + r);
    }

    void Ball::Draw(Surface* screen) {
        screen->FCircle(x, y, r, b, c1, c2);
    }

   
}