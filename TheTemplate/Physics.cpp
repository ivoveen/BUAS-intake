#include "Physics.h"
#include "template.h"
#include "surface.h"
#include <iostream>

using namespace Tmpl8;

Physics::Physics() {
	Init();
}

void Physics::Init() {
	normalVelocity = 0;
	v = 0;
}

vec2 Physics::Gravity(float x, float y, float deltaTime) {
	vec2 gravityDisplacement = vec2(0, 0);
	vec2 v0 = v;
	vec2 a = vec2(0, GRAVITY);

	v = v0 + a * deltaTime;
	v += normalVelocity;
	normalVelocity = 0;

	gravityDisplacement = v * deltaTime + a * 0.5f * powf(deltaTime, 2);

	return gravityDisplacement;
}


vec2 Physics::Resistance(vec2 velocity, float resistance, float deltaTime) {
	if (velocity == vec2(0, 0)) {
		return velocity;
	}
	vec2 Ftot = velocity - (velocity.normalized() * resistance * deltaTime);
	return Ftot;
}

vec2 Physics::TotalPhysicsDisplacement(float x, float y,  float deltaTime) {

	v = Resistance(v, AIRRESISTANCE, deltaTime);
	return Gravity(x, y, deltaTime);

}

void Physics::NormalVelocity(vec2 pointOfImpact, vec2 circleCenter) {
	vec2 hitEdge = (circleCenter - pointOfImpact).clockwise();
	float edgeDegree = acos((hitEdge.dot(vec2(1, 0))) / (hitEdge.length() * vec2(1, 0).length()));
	normalVelocity = (v * cos(edgeDegree)) * -1;
	//make the friction less
	normalVelocity *= 0.05f;

}
vec2 Physics::Bounce(vec2 normal, float elapsedDeltaTime, float totalDeltaTime, float velocityPercentage) {
	//the formula I use to calculate the bounce r = d -2*(d * n) * n.
	//I got it from: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector

	vec2 n = normal;
	n = n.normalized();
	vec2 d = v * -1;
	vec2 r = n * d.dot(n) * 2 - d;
	std::cout << "n: " << n.toString() << " d: " << d.toString() << " r: " << r.toString() << "\n";
	if (velocityPercentage == NULL) velocityPercentage = 0;

	r += r.normalized() * velocityPercentage;
	v = Resistance(r, 0.001f, (totalDeltaTime - elapsedDeltaTime));
	//v = r;
	vec2 bounceDisplacement = v * (totalDeltaTime - elapsedDeltaTime) + v.normalized() * velocityPercentage * (totalDeltaTime - elapsedDeltaTime);
	std::cout << (totalDeltaTime - elapsedDeltaTime) << ": DELTA TIME ||" << bounceDisplacement.toString() << " BOUNCE DISPLACE \n";
	return bounceDisplacement;
}

