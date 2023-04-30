#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "surface.h"

namespace Tmpl8 {

    class Ball :
        private Physics
    {
    public:
        float x, y, r, b, mass;
        Pixel c1, c2;

        Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v);
        void move(float deltaTime, Surface* screen);
        void draw(Surface* screen);
        Hitbox GetHitbox();
    };

}