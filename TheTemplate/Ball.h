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
        bool stop;

        Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v);
        void Tick(float deltaTime, Surface* screen);
        void Move(float deltaTime, Surface* screen);
        GameObject* CheckHitboxCollison();
        vec2 PointOfImpact(GameObject* obj, vec2 force);
        vec2 ClosestPointOnSegment(vec2 p, vec2 a, vec2 b);
        vec2 CornerPointOfImpact(vec2 force, vec2 closestPoint);
        vec2 EdgePointOfImpact(vec2 force, vec2Equation closestEdgeVector);
        void Draw(Surface* screen);
        Hitbox GetHitbox();
    };

}