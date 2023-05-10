#pragma once
#include "Obstacle.h"
#include "Ball.h"

class Flipper :
	public Obstacle
{
private:
	int flipperKey;
	float factor, totalRotation;
	float maxRotation, standardRotation, rotationSpeed, maxBoost;
	Ball* theBall;
	UI* theUI;
public:
	

	Flipper(float x, float y, Tmpl8::Pixel c1, std::vector<vec2Equation>& edgeVectors, int flipperKey, Ball* theBall, UI* theUI);
	//Flipper(float x, float y);
	void Tick(float deltaTime);
	void CheckForBallCollision(float deltaTime);
	void Move(float deltaTime);
	float GotHit();
};



