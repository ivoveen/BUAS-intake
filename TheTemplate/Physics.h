#pragma once
#include "template.h"


namespace Tmpl8 {

	class Physics
	{
	public:
		float g;
		vec2 v; 
		
		Physics();
		vec2 gravity(float x, float y, float mass, float deltaTime);
		vec2 airResistance(); 
		vec2 bounce(vec2 F);
		vec2 totalForce();
		
		
	};

}