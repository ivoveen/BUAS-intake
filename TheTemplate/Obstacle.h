#pragma once
#include "GameObject.h"
#include "surface.h"
#include "template.h"
#include <vector>

namespace Tmpl8
{
    class Obstacle :
        public GameObject
    {
    private:
    std::vector<vec2Equation> edgeVectors; 
    
    public:
        float x1, y1, x2, y2;
        Pixel c1;

        Obstacle(float x1, float y1, float x2, float y2, Pixel c1, std::vector<vec2Equation>& i);
        void Tick(float deltaTime, Surface* screen);
        Hitbox GetHitbox();
        std::vector<vec2Equation> GetEdgeVectors();
        void Draw(Surface * screen);

    };

}