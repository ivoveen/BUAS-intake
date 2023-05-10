#include "UI.h"
#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"
using namespace Tmpl8;

UI::UI() :
	livesSprite(Sprite(new Surface("assets/lives.tga"), 4)),
	mainMenu(Sprite(new Surface("assets/mainMenu.tga"), 1)),
	gameOver(Sprite(new Surface("assets/gameOver.tga"), 1))
{
	startUp = true;
	lives = 3;
}

void UI::Init() {
	startUp = false;
	drawGameOver = true;
	lives = 3;
	xLives = 600, yLives = 750;
}

void UI::DrawMenu(Surface* screen) {
	mainMenu.Draw(screen, 0, 0);
}


bool UI::DrawUI(Surface* screen) {

	if (lives != 0 && drawGameOver) {
		livesSprite.SetFrame(abs(3 - lives));
		livesSprite.Draw(screen, xLives, yLives); //x-r,y-r : changes from ballCenter to top left corner.
		return false;
	}
	return true;
}

void UI::DrawGameOver(Surface* screen) {
	gameOver.Draw(screen, 0, 0);
}


void UI::UpdateLife() {
	if (lives != 0) lives--;
}
