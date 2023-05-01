#include "Obstacle.h"
#include "GameObject.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{

        Obstacle::Obstacle(float x1, float y1, float x2, float y2, Pixel c1) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->c1 = c1;
        }

        void Obstacle::Tick(float deltaTime, Surface* screen) {
            Draw(screen);
        }

        Hitbox Obstacle::GetHitbox() {
            return Hitbox(x1, y1, x2, y2);
        }

        void Obstacle::Draw(Surface * screen) {
            screen->FBox(x1, y1, x2, y2, c1);
        }

   
}
