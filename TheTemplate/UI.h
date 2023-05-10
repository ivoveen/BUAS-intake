#pragma once
#include "surface.h"
#include "template.h"

class UI
{
private:
	int lives;
	int xLives, yLives;
	bool startUp, drawGameOver;
	Tmpl8::Sprite livesSprite;
	Tmpl8::Sprite mainMenu;
	Tmpl8::Sprite gameOver;

public:
	UI(); 
	void Init();
	void DrawMenu(Tmpl8::Surface* screen);
	bool DrawUI(Tmpl8::Surface* screen);
	void DrawGameOver(Tmpl8::Surface* screen);
	void UpdateLife();

};

