#include "Obstacle.h"
#include "GameObject.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{

        Obstacle::Obstacle(float x, float y, Pixel c1, std::vector<vec2Equation>& i){
            this->x = x;
            this->y = y;
            this->c1 = c1;
            this->edgeVectors = i;

            for (auto& edgeVector : edgeVectors) {
                edgeVector.position = edgeVector.position + vec2(x, y);
            }

            float lowestX = NULL, highestX = NULL, lowestY = NULL, highestY = NULL;
            for (auto& edgeVector : edgeVectors) {
                lowestX = (lowestX == NULL || edgeVector.position.x < lowestX ) ? edgeVector.position.x : lowestX;
                lowestY = (lowestY == NULL || edgeVector.position.y < lowestY) ? edgeVector.position.y : lowestY;
                highestX = (highestX == NULL || edgeVector.position.x > highestX) ? edgeVector.position.x : highestX;
                highestY = (highestY == NULL || edgeVector.position.y > highestY) ? edgeVector.position.y : highestY;
                lowestX = (lowestX == NULL || edgeVector.direction.x + edgeVector.position.x < lowestX) ? edgeVector.direction.x + edgeVector.position.x : lowestX;
                lowestY = (lowestY == NULL || edgeVector.direction.y + edgeVector.position.y < lowestY) ? edgeVector.direction.y + edgeVector.position.y : lowestY;
                highestX = (highestX == NULL || edgeVector.direction.x + edgeVector.position.x > highestX) ? edgeVector.direction.x + edgeVector.position.x : highestX;
                highestY = (highestY == NULL || edgeVector.direction.y + edgeVector.position.y > highestY) ? edgeVector.direction.y + edgeVector.position.y : highestY;
            }
            boundingBoxBuffer = 50;
            myBoundingBox = BoundingBox(lowestX - boundingBoxBuffer, lowestY - boundingBoxBuffer, highestX + boundingBoxBuffer, highestY + boundingBoxBuffer);
        }

        void Obstacle::Tick(float deltaTime, Surface* screen) {
            Draw(screen);
        }

        void Obstacle::Draw(Surface* screen) {
            //screen->FBox(x1, y1, x2, y2, c1);
            for (const auto& edgeVector : edgeVectors) {
                screen->Line(edgeVector.position.x, edgeVector.position.y, edgeVector.direction.x + edgeVector.position.x, edgeVector.direction.y + edgeVector.position.y, c1);
            }
        }

        BoundingBox Obstacle::GetBoundingBox() {
            return myBoundingBox;
        }

        std::vector<vec2Equation> Obstacle::GetEdgeVectors() {
            return edgeVectors;
        }


   
}
