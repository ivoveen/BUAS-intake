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
    BoundingBox myBoundingBox;
    float boundingBoxBuffer;

    public:
        float x, y;
        Pixel c1;

        Obstacle(float x, float y, Pixel c1, std::vector<vec2Equation>& i);
        void Tick(float deltaTime, Surface* screen);
        BoundingBox GetBoundingBox();
        std::vector<vec2Equation> GetEdgeVectors();
        void Draw(Surface * screen);

    };

}