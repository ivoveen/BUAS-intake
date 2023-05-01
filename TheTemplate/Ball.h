#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "surface.h"

namespace Tmpl8 {

    class Ball :
        private Physics,
        public GameObject
    {
    public:
        float x, y, r, b, mass;
        Pixel c1, c2;

        Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v);
        void Tick(float deltaTime, Surface* screen);
        void Move(float deltaTime, Surface* screen);
        bool CheckCollison();
        void Draw(Surface* screen);
        Hitbox GetHitbox();
    };

}