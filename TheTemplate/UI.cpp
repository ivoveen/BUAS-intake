#include "UI.h"
#include "surface.h"
#include "template.h"
using namespace Tmpl8;

UI::UI() : livesSprite{ Sprite(new Surface("assets/lives.tga"), 4) } {

	lives = 3;
	xLives = 600, yLives = 750;
}

void UI::Draw(Tmpl8::Surface* screen) {

	livesSprite.SetFrame(abs(3 - lives));
	livesSprite.Draw(screen, xLives, yLives); //x-r,y-r : changes from ballCenter to top left corner.

}

void UI::UpdateLife() {
	lives--;
}
