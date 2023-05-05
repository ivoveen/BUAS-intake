#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "surface.h"

namespace Tmpl8 {

    class Ball :
        private Physics,
        public GameObject
    {
    private:
        struct Impact
        {
            Impact(vec2 pointOfImpact, vec2 circleCenter, float elapsedDeltaTime) {
                this->pointOfImpact = pointOfImpact;
                this->circleCenter = circleCenter;
                this->elapsedDeltaTime = elapsedDeltaTime;
            }
            vec2 pointOfImpact;
            vec2 circleCenter;
            float elapsedDeltaTime;
        };
    public:
        float x, y, r, b, mass;
        Pixel c1, c2;
        bool stop;

        Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v);
        void Tick(float deltaTime, Surface* screen);
        void Move(float deltaTime, Surface* screen);
        std::vector<GameObject*> CheckBoundingBoxCollison();
        Impact PointOfImpact(GameObject* obj, vec2 force);
        vec2 ClosestPointOnSegment(vec2 p, vec2 a, vec2 b);
        Impact CornerPointOfImpact(vec2 force, vec2 closestPoint);
        Impact EdgePointOfImpact(vec2 force, vec2Equation closestEdgeVector);
        void Draw(Surface* screen);
        BoundingBox GetBoundingBox();
    };

}