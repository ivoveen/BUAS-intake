#include "Physics.h"
#include "template.h"
#include "surface.h"
#include <iostream>

namespace Tmpl8
{

    Physics::Physics() {
        g = 0.001f;
        normalVelocity = 0;
        v = 0;

    }

    vec2 Physics::Gravity(float x, float y, float deltaTime) {
        vec2 gravityDisplacement = vec2(0, 0);
        vec2 v0 = v;
        vec2 a = vec2(0, g);

        v = v0 + a * deltaTime;
        v += normalVelocity;
        normalVelocity = 0;


        gravityDisplacement = v * deltaTime + a * 0.5f * powf(deltaTime, 2);
        //std::cout << "Fz: " << Fz.x << ", " << Fz.y << "\n";
        return gravityDisplacement;
        
    }


    vec2 Physics::Resistance(vec2 F, float resistance, float deltaTime) {
        if (F == vec2(0, 0)) {
            return F;
        }
        vec2 Ftot = F - (F.normalized() * resistance * deltaTime);
        return Ftot;
    }
    
    vec2 Physics::TotalPhysicsDisplacement(float x, float y, float airResistance, float deltaTime) {
       /* v += normalVelocity;
        normalVelocity = 0;*/
        v = Resistance(v, airResistance, deltaTime); 
        return Gravity(x, y, deltaTime) + v * deltaTime;
        

        ////std::cout << "v: " << v.x << ", " << v.y << "\n";
        //return displacement;
    }

    void Physics::NormalVelocity(vec2 pointOfImpact, vec2 circleCenter) {
        vec2 hitEdge = (circleCenter - pointOfImpact).clockwise();
        float edgeDegree = (hitEdge.dot(vec2(1, 0))) / (hitEdge.length() * vec2(1, 0).length());
        normalVelocity = (v * cos(edgeDegree)) * -1;
        //make the friction less
        normalVelocity *= 0.1f;

    }
    vec2 Physics::Bounce(vec2 pointOfImpact, vec2 circleCenter, float elapsedDeltaTime, float totalDeltaTime) {
        //the formula I use to calculate the bounce r = d -2*(d * n) * n.
        //I got it from: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector

        vec2 n = circleCenter - pointOfImpact;
        n = n.normalized();
        vec2 d = v * -1;
        vec2 r = n * d.dot(n) * 2 - d;
        
        v = Resistance(r, 0.0005f, (totalDeltaTime - elapsedDeltaTime));

        return v * (totalDeltaTime - elapsedDeltaTime);
    }
    
}