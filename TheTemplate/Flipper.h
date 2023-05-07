#pragma once
#include "Obstacle.h"

namespace Tmpl8
{
    class Flipper :
        public Obstacle
    {
    private:

    public:
        int flipperKey;
        float factor, totalRotation;
        float maxRotation, standardRotation, rotationSpeed;
        Pixel c1;

        Flipper(float x, float y, Pixel c1, std::vector<vec2Equation>& edgeVectors, int flipperKey);
        //Flipper(float x, float y);
        void Tick(float deltaTime, Surface* screen);
        void Move(float deltaTime);
    };

}

