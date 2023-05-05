#include "Physics.h"
#include "template.h"
#include "surface.h"
#include <iostream>

namespace Tmpl8
{

    Physics::Physics() {
        g = 0.000981f;

    }

    vec2 Physics::Gravity(float x, float y, float deltaTime) {
        vec2 Fz = vec2(0, 0);
        vec2 v0 = v;
        vec2 a = vec2(0, g);

        v = v0 + a * deltaTime;
        Fz = v * deltaTime + a * 0.5f * powf(deltaTime, 2);
        std::cout << "Fz: " << Fz.x << ", " << Fz.y << "\n";
        return Fz;
        
    }


    vec2 Physics::AirResistance(vec2 F, float airResistance, float deltaTime) {
        if (F == vec2(0, 0)) {
            return F;
        }
        vec2 Ftot = F - (F.normalized() * airResistance * deltaTime);
        return Ftot;
    }
    
    vec2 Physics::TotalDisplacement(float x, float y, float airResistance, float deltaTime) {
        v = AirResistance(v, airResistance, deltaTime); 
        vec2 displacement = Gravity(x, y, deltaTime);
        
        std::cout << "v: " << v.x << ", " << v.y << "\n";
        return displacement;
    }

    vec2 Physics::Bounce(vec2 pointOfImpact, vec2 circleCenter, float elapsedDeltaTime, float totalDeltaTime) {
        //the formula I use to calculate the bounce r = d -2*(d * n) * n.
        //I got it from: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector

        vec2 n = circleCenter - pointOfImpact;
        n = n.normalized();
        vec2 d = v * -1;
        vec2 r = n * d.dot(n) * 2 - d;
        v = r;
        return v * (totalDeltaTime - elapsedDeltaTime);
    }
    
}