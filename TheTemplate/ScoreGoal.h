#pragma once
#include "Obstacle.h"
#include "UI.h"

class ScoreGoal :
    public Obstacle
{
private:
	int scoreIncrease;
	UI* theUI;
public:
	ScoreGoal(float x, float y, Tmpl8::Pixel c1, std::vector<vec2Equation>& edgeVectors, int scoreIncrease, UI* theUI);
	float GotHit();
};
