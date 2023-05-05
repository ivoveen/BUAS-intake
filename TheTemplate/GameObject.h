#pragma once
#include "surface.h"
#include "template.h"
#include <vector>

namespace Tmpl8
{
    struct BoundingBox {
        BoundingBox() {}
        BoundingBox(float x1, float y1, float x2, float y2) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
        }
        float x1, y1, x2, y2;
    };

    struct vec2Equation {
        vec2Equation() {}
        vec2Equation(vec2 position, vec2 direction) {
            this->position = position;
            this->direction = direction;
        }
        vec2 position, direction;
    };

	
	class GameObject
	{
    public:
        virtual void Tick(float deltaTime, Surface* screen);
        virtual BoundingBox GetBoundingBox();
        virtual std::vector<vec2Equation> GetEdgeVectors(){
            std::vector<vec2Equation> emptyVector;
            return emptyVector;
        }
	};
}

