#include "game.h"
#include "Ball.h"
#include "Obstacle.h"
#include "Flipper.h"
#include "UI.h"
#include "ScoreGoal.h"
#include <vector>
#include <windows.h>
constexpr auto PARTICLES = 4096u;
using namespace Tmpl8;

std::vector<GameObject*> Game::myGameObjects;


void Game::Init()
{
	std::vector<vec2Equation> tubeInnerWallS1;
	tubeInnerWallS1.push_back({ { 0, 0 }, {35, 35} });
	tubeInnerWallS1.push_back({ {35, 35}, {0, 705} });
	tubeInnerWallS1.push_back({ {35, 555}, {50,0} });
	std::vector<vec2Equation> tubeInnerWallS2;
	tubeInnerWallS2.push_back({ { 0, 0 }, { 600, 0 } });
	std::vector<vec2Equation> tubeInnerWallS3;
	tubeInnerWallS3.push_back({ {-35, 35}, {35, -35} });
	tubeInnerWallS3.push_back({ {-35, 165 }, {0, -130} });
	tubeInnerWallS3.push_back({ {15, 245}, {-50, -80} });
	std::vector<vec2Equation> tubeOuterWallS1;
	tubeOuterWallS1.push_back({ { 35, 35 }, { -35, -35 } });
	tubeOuterWallS1.push_back({ {35, 792}, {0, -757} });
	std::vector<vec2Equation> tubeOuterWallS2;
	tubeOuterWallS2.push_back({ {715, 0}, {-715, 0} });
	std::vector<vec2Equation> tubeOuterWallS3;
	tubeOuterWallS3.push_back({ {0, 0}, {-35, 35} });
	tubeOuterWallS3.push_back({ {-35, 35}, {0, 250} });
	tubeOuterWallS3.push_back({ {-35, 285}, {50,96} });
	std::vector<vec2Equation> leftWall;
	leftWall.push_back({ {0, 16}, {-50, 100} });
	leftWall.push_back({ {-50, 116}, {0, 190} });
	std::vector<vec2Equation> bottomLeftWall;
	bottomLeftWall.push_back({ {0, 0}, {263, 71} });
	bottomLeftWall.push_back({ {263, 71}, {0, 50} });
	std::vector<vec2Equation> bottomRightWall;
	bottomRightWall.push_back({ {-263, 71}, {263, -71} });
	bottomRightWall.push_back({ {-263, 121}, {0, -50} });
	std::vector<vec2Equation> rightWall;
	rightWall.push_back({ {0,0}, {0, -350} });
	std::vector<vec2Equation> topRightWall;
	topRightWall.push_back({ {0, 0}, {-100, -50} });
	topRightWall.push_back({ {-100, -50},{50, -150} });
	//topRightWall.push_back({ {-50, -200}, {-50, -25} });
	topRightWall.push_back({ {-100, -225}, {-50, 150} });
	topRightWall.push_back({ {-150, -75}, {-67, -33} });
	std::vector<vec2Equation> topRightWallScoreGoal;
	topRightWallScoreGoal.push_back({ {-50, -200}, {-50, -25} });
	std::vector<vec2Equation> topWall;
	topWall.push_back({ {380, 0}, {-380, 0} });
	//topWall.push_back({ {415, 35}, {-35, -35} });
	std::vector<vec2Equation> topWallScoreGoal;
	topWallScoreGoal.push_back({ {415, 35}, {-35, -35} });
	std::vector<vec2Equation> topCenterWall;
	topCenterWall.push_back({ {-280, 160}, {93, -53} });
	topCenterWall.push_back({ {-93, 53}, {93, -53} });
	topCenterWall.push_back({ {-230, 185}, {-50, -25} });
	topCenterWall.push_back({ {-57, 86}, {-57, 33} });
	topCenterWall.push_back({ {-171, 152}, {-57, 33} });

	std::vector<vec2Equation> topCenterWallScoreGoalTop;
	topCenterWallScoreGoalTop.push_back({ {-187, 107}, {94, -54} });

	std::vector<vec2Equation> topCenterWallScoreGoalBottom;
	topCenterWallScoreGoalBottom.push_back({ {-114, 119}, {-57, 33} });


	std::vector<vec2Equation> topLeftWall;
	topLeftWall.push_back({ {50, 0}, {-50, 0} });
	topLeftWall.push_back({ {0, -80}, {50, 80} });
	topLeftWall.push_back({ {35, -205}, {-35, 35} });
	std::vector<vec2Equation> topLeftWallScoreGoal;
	topLeftWallScoreGoal.push_back({ {0, -170}, {0, 90 } });
	std::vector<vec2Equation> leftCatcher;
	leftCatcher.push_back({ {0, 13}, {0, -113} });
	leftCatcher.push_back({ {0, -100}, {40, -80} });
	leftCatcher.push_back({ {40, -180}, {12, 6} });
	leftCatcher.push_back({ {52, -174}, {-28, 86} });
	leftCatcher.push_back({ {24, -88}, {0, 80} });
	leftCatcher.push_back({ {24, -8}, {120, 30} });
	leftCatcher.push_back({ {137, 49}, {-137,-36} });
	leftCatcher.push_back({ {144, 22}, {-6, 27} });
	std::vector<vec2Equation> rightCatcher;
	rightCatcher.push_back({ {0, 13}, {-144, 35} });
	rightCatcher.push_back({ {-144, 48}, {-7, -25} });
	rightCatcher.push_back({ {-150, 22}, {117, -31} });
	rightCatcher.push_back({ {-32, -10}, {10, -170} });
	rightCatcher.push_back({ {-22, -180}, {12, 0} });
	rightCatcher.push_back({ {-10, -180}, {10, 193} });
	std::vector<vec2Equation> scoreGoal1;
	scoreGoal1.push_back({ {0, 0}, {100, 0} });
	scoreGoal1.push_back({ {100, 0}, {0, 25} });
	scoreGoal1.push_back({ {100, 25}, {-100, 0} });
	scoreGoal1.push_back({ {0, 25}, {0, -25} });
	std::vector<vec2Equation> leftFlipper;
	leftFlipper.push_back({ {0, 0}, {120, 6} });
	leftFlipper.push_back({ {120, 6}, {0, 20} });
	leftFlipper.push_back({ {120, 26}, {-120, 0} });
	leftFlipper.push_back({ {0, 26}, {0, -26} });
	std::vector<vec2Equation> rightFlipper;
	rightFlipper.push_back({ {0, -26}, {0, 26} });
	rightFlipper.push_back({ {0, 0}, {-120, 0} });
	rightFlipper.push_back({ { -120, 0 }, { 0, -20 } });
	rightFlipper.push_back({ {-120, -26}, {120, -6} });

	theUI = new UI();
	theBall = new Ball(770, 600, vec2(-0.0f, -1.0f), theUI);
	//myGameObjects.push_back(new ScoreGoal(300, 550, 0x00FF00, scoreGoal1, 1, theUI));
	myGameObjects.push_back(new ScoreGoal(734, 329, 0x00FF00, topRightWallScoreGoal, 20, theUI)); 
	myGameObjects.push_back(new ScoreGoal(158, 100, 0x00FF00, topWallScoreGoal, 7, theUI));
	myGameObjects.push_back(new ScoreGoal(123, 305, 0x00FF00, topLeftWallScoreGoal, 8, theUI)); 
	myGameObjects.push_back(new ScoreGoal(573, 135, 0x00FF00, topCenterWallScoreGoalTop, 9, theUI)); 
	myGameObjects.push_back(new ScoreGoal(573, 135, 0x00FF00, topCenterWallScoreGoalBottom, 8, theUI));
	myGameObjects.push_back(new Flipper(213, 623, 0xFF00FF, leftFlipper, VK_LEFT, theBall, theUI));
	myGameObjects.push_back(new Flipper(523, 623, 0xFF00FF, rightFlipper, VK_RIGHT, theBall, theUI));
	myGameObjects.push_back(new Obstacle(68, 600, 0xFFFFFF, leftCatcher));
	myGameObjects.push_back(new Obstacle(674, 600, 0xFFFFFF, rightCatcher));
	myGameObjects.push_back(new Obstacle(708, 60, 0xFFFFFF, tubeInnerWallS1));
	myGameObjects.push_back(new Obstacle(108, 60, 0xFFFFFF, tubeInnerWallS2));
	myGameObjects.push_back(new Obstacle(108, 60, 0xFFFFFF, tubeInnerWallS3));
	myGameObjects.push_back(new Obstacle(758, 8, 0xFFFFFF, tubeOuterWallS1));
	myGameObjects.push_back(new Obstacle(43, 8, 0xFFFFFF, tubeOuterWallS2));
	myGameObjects.push_back(new Obstacle(43, 8, 0xFFFFFF, tubeOuterWallS3));
	myGameObjects.push_back(new Obstacle(58, 373, 0xFFFFFF, leftWall));
	myGameObjects.push_back(new Obstacle(8, 679, 0xFFFFFF, bottomLeftWall));
	myGameObjects.push_back(new Obstacle(734, 679, 0xFFFFFF, bottomRightWall));
	myGameObjects.push_back(new Obstacle(734, 679, 0xFFFFFF, rightWall));
	myGameObjects.push_back(new Obstacle(734, 329, 0xFFFFFF, topRightWall));
	myGameObjects.push_back(new Obstacle(123, 305, 0xFFFFFF, topLeftWall));
	myGameObjects.push_back(new Obstacle(158, 100, 0xFFFFFF, topWall));
	myGameObjects.push_back(new Obstacle(573, 135, 0xFFFFFF, topCenterWall));

	start = false;
	gameOver = true;
}

void Game::Shutdown() {

}

void Game::Tick(float deltaTime)
{

	//screen->Clear(0);
	if (GetAsyncKeyState(VK_SPACE) && gameOver) {
		start = true;
		gameOver = false;
		theUI->Init();
	}
	if (start) {
		tickCounter++;

		
		if (!gameOver) {
			theBall->Tick(deltaTime);

			if (tickCounter % 2 == 0) {
				for (const auto& obj : myGameObjects) {
					obj->Tick(deltaTime);
				}
			}
		}



		if (tickCounter == 9) {
			tickCounter = 0;
			screen->Clear(0);
			for (const auto& obj : myGameObjects) {
				obj->Draw(screen);
				theBall->Draw(screen);
				if (gameOver) theUI->DrawGameOver(screen);
				else gameOver = theUI->DrawUI(screen);
			}

		}
	}
	else {
		theUI->DrawMenu(screen);
	}

}

