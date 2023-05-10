#pragma once
#include "GameObject.h"
#include "surface.h"
#include "template.h"
#include <vector>


class Obstacle :
	public GameObject
{
private:
	std::vector<vec2Equation> edgeVectors;
	BoundingBox myBoundingBox;
	float boundingBoxBuffer;

public:
	float x, y;
	Tmpl8::Pixel c1;
	Obstacle(float x, float y, Tmpl8::Pixel c1, std::vector<vec2Equation>& i);
	BoundingBox GetBoundingBox();
	std::vector<vec2Equation> GetEdgeVectors();
	void SetEdgeVectors(std::vector<vec2Equation> edgeVectors);
	void Draw(Tmpl8::Surface* screen);

};

