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
            Impact() {
                pointOfImpact = vec2(NULL, NULL);
                circleCenter = vec2(NULL, NULL);
                elapsedDeltaTime = NULL;
            }
            Impact(vec2 pointOfImpact, vec2 circleCenter, float elapsedDeltaTime) {
                this->pointOfImpact = pointOfImpact;
                this->circleCenter = circleCenter;
                this->elapsedDeltaTime = elapsedDeltaTime;
            }
            vec2 pointOfImpact;
            vec2 circleCenter;
            float elapsedDeltaTime;
        };

        Surface* sprite;
        Sprite ballSprite;
        float x, y, r, b, mass;
        Pixel c1, c2;
        bool stop;
    public:
        Ball(float x, float y, Surface* ballSprite, vec2 v);
        void Tick(float deltaTime, Surface* screen);
        void Move(float deltaTime, Surface* screen);
        vec2 Ball::CalculateBounce(float xCircleCenter, float yCircleCenter,float deltaTime, vec2 displacemnt);
        std::vector<GameObject*> CheckBoundingBoxCollison();
        Impact PointOfImpact(float xCircleCenter, float yCircleCenter, GameObject* obj, vec2 force);
        vec2 ClosestPointOnSegment(vec2 p, vec2 a, vec2 b);
        Impact CornerPointOfImpact(float xCircleCenter, float yCircleCenter, vec2 force, vec2 closestPoint);
        Impact EdgePointOfImpact(float xCircleCenter, float yCircleCenter, vec2 force, vec2Equation closestEdgeVector);
        void Draw(Surface* screen);
        BoundingBox GetBoundingBox();
    };

}