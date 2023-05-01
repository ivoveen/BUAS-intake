#pragma once
#include "surface.h"

namespace Tmpl8
{
    struct Hitbox {
        Hitbox(float x1, float y1, float x2, float y2) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
        }
        float x1, y1, x2, y2;
    };
	
	class GameObject
	{
    public:
        virtual void Tick(float deltaTime, Surface* screen);
        virtual Hitbox GetHitbox();

	};
}

