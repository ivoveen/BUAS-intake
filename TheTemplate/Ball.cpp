#include "Ball.h"
#include "template.h"
#include "surface.h"
#include "Physics.h"
#include "GameObject.h"


namespace Tmpl8
{
    Ball::Ball(float x, float y, float r, float b, float mass, Pixel c1, Pixel c2, vec2 v) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->b = b;
        this->mass = mass;
        this->c1 = c1;
        this->c2 = c2;
        this->v = v;
    }

    void Ball::move(float deltaTime, Surface* screen) {
        vec2 force = gravity(x, y, 0, deltaTime);
        x = force.x, y = force.y;

        draw(screen);
    }

    void Ball::draw(Surface* screen) {
        screen->FCircle(x, y, r, b, c1, c2);
    }

    Hitbox Ball::GetHitbox() {
        return Hitbox(x - r, y - r, x + r, y + r);
    }
}