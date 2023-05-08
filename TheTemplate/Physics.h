#pragma once
#include "template.h"


namespace Tmpl8 {

	class Physics
	{
	public:
		float g;
		vec2 v, normalVelocity; 
		
		Physics();
		vec2 Gravity(float x, float y, float deltaTime);
		vec2 Resistance(vec2 F, float airResistance, float deltaTime);
		vec2 TotalPhysicsDisplacement(float x, float y, float airResistance, float deltaTime);
		void NormalVelocity(vec2 pointOfImpact, vec2 circleCenter);
		vec2 Bounce(vec2 pointOfImpact, vec2 circleCenter, float elapsedDeltaTime, float totalDeltaTime);
		
		
		
	};

}