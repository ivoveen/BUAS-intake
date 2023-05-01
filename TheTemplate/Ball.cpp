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

    void Ball::Tick(float deltaTime, Surface* screen) {
        Move(deltaTime, screen);
        Draw(screen);
    }

    void Ball::Move(float deltaTime, Surface* screen) {
        vec2 force = TotalForce(x, y, 0.0001f, deltaTime);
        x = force.x, y = force.y;

       ;
    }

    void Ball::Draw(Surface* screen) {
        screen->FCircle(x, y, r, b, c1, c2);
    }

    Hitbox Ball::GetHitbox() {
        return Hitbox(x - r, y - r, x + r, y + r);
    }
}