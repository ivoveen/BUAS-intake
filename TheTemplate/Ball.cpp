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
        if (stop == false) {
            vec2 force = TotalForce(x, y, 0.0001f, deltaTime);
            vec2 forcePos = force + vec2(x, y);

            float xTemp = forcePos.x, yTemp = forcePos.y;


            GameObject* obstacle = CheckHitboxCollison();
            if (obstacle == NULL) {
                x = xTemp, y = yTemp;

            }
            else {
                vec2 pointOfImpact = PointOfImpact(obstacle, force);

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

    GameObject* Ball::CheckHitboxCollison() {

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
        // I got it from: https://www.youtube.com/watch?v=egmZJU-1zPU&ab_channel=Two-BitCoding
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



    vec2 Ball::PointOfImpact(GameObject* obstacle, vec2 force) {
        std::vector<vec2Equation> edgeVectors = obstacle->GetEdgeVectors();
        bool isCorner = false;
        float shortestDistance = NULL;
        vec2Equation closestEdgeVector;
        vec2 closestPoint;

        //select with which line of the object the ball has collided.
        for (const auto& edgeVector : edgeVectors) {
            vec2 p = vec2(x, y);
            vec2 a = edgeVector.position;
            vec2 b = edgeVector.direction + edgeVector.position;
            vec2 cp = ClosestPointOnSegment(p, a, b);

            float distance = (abs(sqrtf(powf(cp.x - p.x, 2) + powf(cp.y - p.y, 2))));

            if (shortestDistance == NULL || distance <= shortestDistance) {
                isCorner = (distance == shortestDistance);
                shortestDistance = distance;
                closestEdgeVector = edgeVector;
                closestPoint = cp;
            }
        }
        
        if (isCorner) {
            return CornerPointOfImpact(force, closestPoint);
        }
        else {
            return EdgePointOfImpact(force, closestEdgeVector);
        }
    }

    vec2 Ball::CornerPointOfImpact(vec2 force, vec2 corner) {
        // calculating the amount of deltatime elapsed until impact.
        // x(t) = x0 + fX * t
        // y(t) = y0 + fY * t
        // d(t) = sqrt((x(t) - x_c)^2 + (y(t) - y_c)^2)
        // d(t) = r
        // substitute x(t) and y(t) and solve for t
        // to solve this equation I used chatGPT4 to save time
        float xCircleCenter = x, yCircleCenter = y;
        float a = powf(force.x, 2) + powf(force.y, 2);
        float b = 2 * (xCircleCenter * force.x - corner.x * force.x + yCircleCenter * force.y - corner.y * force.y);
        float c = powf(xCircleCenter, 2) - 2 * xCircleCenter * corner.x + powf(corner.x, 2) + powf(yCircleCenter, 2) - 2 * yCircleCenter * corner.y + powf(corner.y, 2) - powf(r, 2);
        float d = powf(b, 2) - 4 * a * c;
        if (d < 0) {
            return vec2(0, 0);
        }
        float dT1 = (-b + sqrt(d)) / (2 * a);
        float dT2 = (-b - sqrt(d)) / (2 * a);
        float dT;

        //the smallest positive dT refers to the correct point of impact.
        if (dT1 <= dT2 && dT1 > 0) {
            dT = dT1;
        }
        else if (dT2 <= dT1 && dT1 > 0) {
            dT = dT2;
        }
        else {
            return vec2(0, 0);
        }
        vec2 impactCircleCenter = vec2(xCircleCenter, yCircleCenter) + force * dT; //the position of the center of the circle at the time of impact.
        vec2 cornerPointOfImpact = impactCircleCenter + force.normalized() * r; //the position of the point of impact 
        vec2 circleCollisionPoint = vec2(xCircleCenter, yCircleCenter) + force.normalized() * r; //the position of the point of impact before the impact happened.
        
        //check if the collision point on the line is within reach of the force of the ball.
        if (force.length() > sqrtf(powf(circleCollisionPoint.x - cornerPointOfImpact.x, 2) + powf(circleCollisionPoint.y - cornerPointOfImpact.y, 2))) {
            return impactCircleCenter;
        }
        else {
            return vec2(0, 0);
        }
    }

    vec2 Ball::EdgePointOfImpact(vec2 force, vec2Equation closestEdgeVector) {
        float nLine, nForce;
        float XLinePos = closestEdgeVector.position.x, YLinePos = closestEdgeVector.position.y;
        float xCircleCenter = x, yCircleCenter = y; 
        vec2 circleCollisionPoint; //the point of the circle that will hit the edge first.
        vec2 obstacleEdge = closestEdgeVector.direction;
        vec2 lineCollisionPoint; //the point the actual hit takes place.

        circleCollisionPoint = vec2(xCircleCenter, yCircleCenter) + obstacleEdge.clockwise().normalized() * r;
        
        //calculate the intersection between the line and the movement of the circleCollisionPoint.
        nLine = (circleCollisionPoint.y * force.x + XLinePos * force.y - circleCollisionPoint.x * force.y - YLinePos * force.x) / (obstacleEdge.y * force.x - obstacleEdge.x * force.y);
        nForce = (YLinePos * obstacleEdge.x + circleCollisionPoint.x * obstacleEdge.y - XLinePos * obstacleEdge.y - circleCollisionPoint.y * obstacleEdge.x) / (force.y * obstacleEdge.x - force.x * obstacleEdge.y);
        lineCollisionPoint = circleCollisionPoint + force * nForce;

        //check if this intersection is actually on the edge, and within reach of the velocity.
        if (nForce < 1 && nLine < 1 && nLine > 0) {
            return lineCollisionPoint + obstacleEdge.counterClockwise().normalized() * r;
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