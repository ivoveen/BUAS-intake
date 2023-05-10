#include "Flipper.h"
#include "windows.h"
#include "Game.h"
#include "ball.h"

#include <iostream>
using namespace Tmpl8;

Flipper::Flipper(float x, float y, Pixel c1, std::vector<vec2Equation>& edgeVectors, int flipperKey, Ball* theBall) :
	Obstacle(x, y, c1, edgeVectors)
{
	this->theBall = theBall;
	this->flipperKey = flipperKey;
	maxRotation = (flipperKey == VK_LEFT) ? -0.25f * PI : 0.25f * PI; //rotatian (in radians) in the direction corresponding to which side the flipper is on.
	standardRotation = (flipperKey == VK_LEFT) ? 0.0625f * PI : -0.0625f * PI;
	rotationSpeed = 0.016f;
	factor = 0;
	totalRotation = 0;
	maxBoost = 1.5;

}

void Flipper::Tick(float deltaTime) {
	Move(deltaTime);
	CheckForBallCollision(deltaTime);
}

void Flipper::CheckForBallCollision(float deltaTime) {
	std::vector<vec2Equation> edgeVectors = this->GetEdgeVectors();
	vec2 closestPoint;
	vec2 p = vec2(theBall->x, theBall->y);
	float shortestDistance = NULL;
	vec2Equation closestEdgeVector;
	//select with which line of the object the ball has collided.
	for (const auto& edgeVector : edgeVectors) {

		vec2 cp = theBall->ClosestPointOnSegment(p, edgeVector.position, edgeVector.position + edgeVector.direction);

		float distance = (abs(sqrtf(powf(cp.x - p.x, 2) + powf(cp.y - p.y, 2))));

		if (shortestDistance == NULL || distance <= shortestDistance) {
			shortestDistance = distance;
			closestEdgeVector = edgeVector;
			closestPoint = cp;
		}
	}

	float distance = closestPoint.distance(p);
	if (distance < theBall->r) {
		//std::cout << "distance: " << distance << "ball x:" << p.x << " , y: " << p.y << "| closestPoint x: " << closestPoint.x << ", y: " << closestPoint.y << "\n";
		Ball::Impact impact = theBall->EdgePointOfImpact(theBall->x, theBall->y, theBall->TotalPhysicsDisplacement(theBall->x, theBall->y, deltaTime), closestEdgeVector, -1000, 0, deltaTime);
		if (!impact.noImpact) {
			vec2 newDisplacement = theBall->Bounce(impact.normalOfImpactLine, impact.elapsedDeltaTime, deltaTime, this->GotHit(impact.pointOfImpact));
			theBall->x += newDisplacement.x, theBall->y += newDisplacement.y;
		}
		else {
			std::cout << "no impact";
		}
	}

}


void Flipper::Move(float deltaTime) {
	//I got the formula for rotating a vector from: https://homepages.uc.edu/~herronda/linear_algebra/beamers/RotationMatrix.pdf
	std::vector<vec2Equation> edgeVectors = this->GetEdgeVectors();
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
	vec2 positionVec2 = vec2(x, y);
	for (auto& edgeVector : edgeVectors) {
		edgeVector.direction = vec2(edgeVector.direction.x * (float)cos(rotationAdjustment) - edgeVector.direction.y * (float)sin(rotationAdjustment), edgeVector.direction.x * (float)sin(rotationAdjustment) + edgeVector.direction.y * (float)cos(rotationAdjustment));
		edgeVector.position = positionVec2;
		positionVec2 += edgeVector.direction;
	}
	Flipper::SetEdgeVectors(edgeVectors);
}

float Flipper::GotHit(vec2 pointOfImpact) {
	std::vector<vec2Equation> edgeVectors = this->GetEdgeVectors();
	float nLine = 0;
	//calculate which edge was hit
	for (auto& edgeVector : edgeVectors) {
		nLine = (pointOfImpact.x - edgeVector.position.x) / edgeVector.direction.x;
		if (nLine > 0 && nLine < 1) {
			break;
		}
	}
	//closer to the middle == more boost
	if (flipperKey == VK_RIGHT) nLine = abs(nLine - 1);
	if (totalRotation != maxRotation && totalRotation != standardRotation) {
		return 0.2f + nLine * 0.04f;
	}
	else {
		return 0;
	}
}