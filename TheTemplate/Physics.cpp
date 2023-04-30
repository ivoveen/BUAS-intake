#include "Physics.h"
#include "template.h"
#include "surface.h"

namespace Tmpl8
{

    Physics::Physics() {
        g = 0.00081f;

    }

    vec2 Physics::Gravity(float x, float y, float mass, float deltaTime) {
        vec2 Fz = vec2(0, 0);
        vec2 y0 = vec2(x, y);
        vec2 v0 = v;
        vec2 a = vec2(0, g);

        v = v0 + a * deltaTime;
        Fz = y0 + v * deltaTime + a * 0.5f * powf(deltaTime, 2);

        return Fz;
    }


    vec2 Physics::AirResistance() {
        return NULL;
    }
    vec2 Physics::Bounce(vec2 F) {
        F *= -1;
        return F;
    }
    vec2 Physics::TotalForce() {
        return NULL;
    }
}