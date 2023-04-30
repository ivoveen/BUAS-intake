#pragma once
#include "GameObject.h"
#include "surface.h"
#include "template.h"


namespace Tmpl8
{
    class Obstacle :
        public GameObject
    {
    public:
        float x1, y1, x2, y2;
        Pixel c1;

        Obstacle(float x1, float y1, float x2, float y2, Pixel c1);
        void Tick(float deltaTime, Surface* screen);
        Hitbox GetHitbox();
        void Draw(Surface * screen);
    };

}