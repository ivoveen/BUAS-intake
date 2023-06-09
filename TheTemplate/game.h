#pragma once
#include<vector>
#include "GameObject.h"
#include "surface.h"
#include "Ball.h"
#include "UI.h"
namespace Tmpl8 {
	 class Game
	{
	public:
	    static std::vector<GameObject*> myGameObjects;
		
		
		
		void SetTarget(Tmpl8::Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
	private:
		bool start, gameOver;
		Tmpl8::Surface* screen;
		int mousex, mousey;
		unsigned int tickCounter = 0;
		Ball* theBall;
		UI* theUI;
		
	};
}