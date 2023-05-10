#pragma once
#include "template.h"

constexpr float GRAVITY = 0.000981f/2;
constexpr float AIRRESISTANCE = 0.0001f;

class Physics
{
public:	
	Tmpl8::vec2 v, normalVelocity;

	Physics();
	void Init();
	Tmpl8::vec2 Gravity(float x, float y, float deltaTime);
	Tmpl8::vec2 Resistance(Tmpl8::vec2 F, float resistance, float deltaTime);
	Tmpl8::vec2 TotalPhysicsDisplacement(float x, float y,float deltaTime);
	void NormalVelocity(Tmpl8::vec2 pointOfImpact, Tmpl8::vec2 circleCenter);
	Tmpl8::vec2 Bounce(Tmpl8::vec2 normal, float elapsedDeltaTime, float totalDeltaTime, float velocityPercentage);



};

