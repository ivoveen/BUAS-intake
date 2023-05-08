#include "Flipper.h"
#include "windows.h"

#include <iostream>
namespace Tmpl8
{
	Flipper::Flipper(float x, float y, Pixel c1, std::vector<vec2Equation>& edgeVectors, int flipperKey) : 
		Obstacle( x,y,c1,edgeVectors )
	{
		this->flipperKey = flipperKey;
		maxRotation = (flipperKey == VK_LEFT) ? -0.25f * PI : 0.25f * PI; //rotatian (in radians) in the direction corresponding to which side the flipper is on.
		standardRotation = (flipperKey == VK_LEFT) ? 0.0625f * PI : -0.0625f * PI;
		rotationSpeed = 0.008f;
		factor = 0;
		totalRotation = 0;
	}

	void Flipper::Tick(float deltaTime, Surface* screen) {
		Move(deltaTime);
		Draw(screen);
	}

	void Flipper::Move(float deltaTime) {
		//I got the formula for rotating a vector from: https://homepages.uc.edu/~herronda/linear_algebra/beamers/RotationMatrix.pdf
		std::vector<vec2Equation> edgeVectors = Flipper::GetEdgeVectors();
		float rotationAdjustment = 0;
		float oldRotation = totalRotation;
		if (GetAsyncKeyState(flipperKey)) {
			factor = factor + rotationSpeed * deltaTime;
			if (factor > 1) factor = 1;
		} 
		else if (factor > 0) {
			factor = factor - rotationSpeed * deltaTime;
			if (factor < 0) factor = 0;
		}
		totalRotation = standardRotation + factor * (maxRotation - standardRotation);
		rotationAdjustment = totalRotation - oldRotation;
		vec2 positionVec2 = vec2(x,y);
		for (auto& edgeVector : edgeVectors) {
			edgeVector.direction = vec2(edgeVector.direction.x * (float)cos(rotationAdjustment) - edgeVector.direction.y * (float)sin(rotationAdjustment), edgeVector.direction.x * (float)sin(rotationAdjustment) + edgeVector.direction.y * (float)cos(rotationAdjustment));
			edgeVector.position = positionVec2;
			positionVec2 += edgeVector.direction;
		}
		Flipper::SetEdgeVectors(edgeVectors);
	}
}