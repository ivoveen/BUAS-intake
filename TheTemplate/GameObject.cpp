#include "GameObject.h"
#include "surface.h"


namespace Tmpl8
{

	void GameObject::Tick(float deltaTime, Surface* screen) {

	}

	Hitbox GameObject::GetHitbox() {
		return Hitbox(0, 0, 0, 0);;
	}

}

