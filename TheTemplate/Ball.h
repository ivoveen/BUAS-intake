#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "surface.h"


class Ball :
	public Physics,
	public GameObject
{
private:
	

	Tmpl8::Surface* sprite;
	Tmpl8::Sprite ballSprite;
	float b, mass;
	Tmpl8::Pixel c1, c2;
	bool stop;
public:
	struct Impact
	{
		Impact() {
			pointOfImpact = Tmpl8::vec2(NULL, NULL);
			circleCenter = Tmpl8::vec2(NULL, NULL);
			elapsedDeltaTime = NULL;
			elapsedDeltaTime = NULL;
			normalOfImpactLine = NULL;
			noImpact = true;
		}
		Impact(Tmpl8::vec2 pointOfImpact, Tmpl8::vec2 circleCenter, float elapsedDeltaTime, Tmpl8::vec2 normalOfImpactLine, bool noImpact) {
			this->pointOfImpact = pointOfImpact;
			this->circleCenter = circleCenter;
			this->elapsedDeltaTime = elapsedDeltaTime;
			this->noImpact = noImpact;
			this->normalOfImpactLine = normalOfImpactLine;
		}
		Tmpl8::vec2 pointOfImpact;
		Tmpl8::vec2 circleCenter;
		float elapsedDeltaTime;
		Tmpl8::vec2 normalOfImpactLine;
		bool noImpact;
	};

	float x, y, r;
	Ball(float x, float y, Tmpl8::Surface* ballSprite, Tmpl8::vec2 v);
	void Tick(float deltaTime);
	void Move(float deltaTime);
	Tmpl8::vec2 Ball::CalculateBounce(float xCircleCenter, float yCircleCenter, float deltaTime, Tmpl8::vec2 displacemnt);
	std::vector<GameObject*> CheckBoundingBoxCollison();
	Impact PointOfImpact(float xCircleCenter, float yCircleCenter, GameObject* obj, Tmpl8::vec2 force, float deltaTime);
	Tmpl8::vec2 ClosestPointOnSegment(Tmpl8::vec2 p, Tmpl8::vec2 a, Tmpl8::vec2 b);
	Impact CornerPointOfImpact(float xCircleCenter, float yCircleCenter, Tmpl8::vec2 force, Tmpl8::vec2 closestPoint, float deltaTime);
	Impact EdgePointOfImpact(float xCircleCenter, float yCircleCenter, Tmpl8::vec2 force, vec2Equation closestEdgeVector, float minNDisplacement, float maxNDisplacement, float deltaTime);
	void Draw(Tmpl8::Surface* screen);
	BoundingBox GetBoundingBox();
};
