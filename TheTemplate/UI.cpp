#include "UI.h"
#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"
#include <sstream>

#include <SDL.h>
using namespace Tmpl8;

UI::UI() :
	livesSprite(Sprite(new Surface("assets/lives.tga"), 4)),
	mainMenu(Sprite(new Surface("assets/mainMenu.tga"), 1)),
	gameOver(Sprite(new Surface("assets/gameOver.tga"), 1)),
	ScoreNumbers(Sprite(new Surface("assets/scoreNumbers.tga"), 10))
{
	startUp = true;
	lives = 3;
	score = 55;
}

void UI::Init() {
	startUp = false;
	drawGameOver = true;
	lives = 3;
	xLives = 600, yLives = 750;
	xScore = 100, yScore = 750;
	score = 0;
}

void UI::DrawMenu(Surface* screen) {
	mainMenu.Draw(screen, 0, 0);
}


bool UI::DrawUI(Surface* screen) {
	if (lives != 0 && drawGameOver) {
		livesSprite.SetFrame(abs(3 - lives));
		livesSprite.Draw(screen, xLives, yLives); //x-r,y-r : changes from ballCenter to top left corner.
		
		//print score
		ScoreNumbers.SetFrame(score % 10);
		ScoreNumbers.Draw(screen, xScore, yScore);
		ScoreNumbers.SetFrame(static_cast<int> (floor((score% 100 ) / 10)) );
		ScoreNumbers.Draw(screen, xScore - 40, yScore);
		ScoreNumbers.SetFrame(static_cast<int> (floor(score / 100)));
		ScoreNumbers.Draw(screen, xScore - 80, yScore);
		return false;
	}

	

	return true;
}

void UI::DrawGameOver(Surface* screen) {
	gameOver.Draw(screen, 0, 0);
	xScore = 410, yScore = 450;
	//print score
	ScoreNumbers.SetFrame(score % 10);
	ScoreNumbers.Draw(screen, xScore, yScore);
	ScoreNumbers.SetFrame(static_cast<int> (floor((score % 100) / 10)));
	ScoreNumbers.Draw(screen, xScore - 40, yScore);
	ScoreNumbers.SetFrame(static_cast<int> (floor(score / 100)));
	ScoreNumbers.Draw(screen, xScore - 80, yScore);

}


void UI::UpdateLife() {
	if (lives != 0) lives--;
}

void UI::UpdateScore(int scoreIncrease) {
	score += scoreIncrease;
}
