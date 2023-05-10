#pragma once
#include<vector>
#include "GameObject.h"
#include "surface.h"
#include "Ball.h"
namespace Tmpl8 {
	 class Game
	{
	public:
	    static std::vector<GameObject*> myGameObjects;
		Ball* theBall;

		void SetTarget(Tmpl8::Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void UpdateScreen();
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { mousex = x, mousey = y; }
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key) { /* implement if you want to handle keys */ }
	private:

		Tmpl8::Surface* screen;
		int mousex, mousey;
		unsigned int tickCounter = 0;
		bool start;
	};
}