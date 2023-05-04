#include "Obstacle.h"
#include "GameObject.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{

        Obstacle::Obstacle(float x1, float y1, float x2, float y2, Pixel c1, std::vector<vec2Equation>& i){
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->c1 = c1;
            this->edgeVectors = i;

            for (auto& edgeVector : edgeVectors) {
                edgeVector.position = edgeVector.position + vec2(x1, y1);
            }
        }

        void Obstacle::Tick(float deltaTime, Surface* screen) {
            Draw(screen);
        }

        void Obstacle::Draw(Surface* screen) {
            screen->FBox(x1, y1, x2, y2, c1);
        }

        Hitbox Obstacle::GetHitbox() {
            return Hitbox(x1, y1, x2, y2);
        }

        std::vector<vec2Equation> Obstacle::GetEdgeVectors() {

           
            
            return edgeVectors;
        }


   
}
