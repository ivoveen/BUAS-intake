#include "ScoreGoal.h"
#include"template.h"
#include"surface.h"
#include"UI.h"

using namespace Tmpl8;

ScoreGoal::ScoreGoal(float x, float y, Pixel c1, std::vector<vec2Equation>& edgeVectors, int scoreIncrease, UI* theUI) :
	Obstacle(x, y, c1, edgeVectors)
{
	this->scoreIncrease = scoreIncrease;
	this->theUI = theUI;
}

float ScoreGoal::GotHit() {
	theUI->UpdateScore(scoreIncrease);

	return 0;
}