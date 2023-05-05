#include "Physics.h"
#include "template.h"
#include "surface.h"

namespace Tmpl8
{

    Physics::Physics() {
        g = 0.00081f;

    }

    vec2 Physics::Gravity(float x, float y, float deltaTime) {
        vec2 Fz = vec2(0, 0);
        vec2 v0 = v;
        vec2 a = vec2(0, g);

        v = v0 + a * deltaTime;
        Fz = v * deltaTime + a * 0.5f * powf(deltaTime, 2);
        return Fz;
    }


    vec2 Physics::AirResistance(vec2 F, float airResistance, float deltaTime) {
        vec2 Ftot = F + (F.normalized() * -1 * airResistance * deltaTime);
        return Ftot;
    }
    
    vec2 Physics::TotalVelocity(float x, float y, float airResistance, float deltaTime) {
        vec2 totalVelocity = Gravity(x, y, deltaTime);
        totalVelocity = AirResistance(totalVelocity, airResistance, deltaTime);
        
        return totalVelocity;
    }

    vec2 Physics::Bounce(vec2 F) {
        F *= -1;
        return F;
    }
    
}