#pragma once
#include "surface.h"
#include "template.h"

class UI
{
private:
	int lives;
	float xLives, yLives;
	Tmpl8::Sprite livesSprite;
	

public:
	UI(); 
	void Draw(Tmpl8::Surface* screen);
	void UpdateLife();

};

