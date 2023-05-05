#pragma once
#include "template.h"


namespace Tmpl8 {

	class Physics
	{
	public:
		float g;
		vec2 v; 
		
		Physics();
		vec2 Gravity(float x, float y, float deltaTime);
		vec2 AirResistance(vec2 F, float airResistance, float deltaTime);
		vec2 TotalDisplacement(float x, float y, float airResistance, float deltaTime);
		vec2 Bounce(vec2 pointOfImpact, vec2 circleCenter, float elapsedDeltaTime, float totalDeltaTime);
	
		
		
	};

}