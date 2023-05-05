#include "GameObject.h"
#include "surface.h"


namespace Tmpl8
{

	void GameObject::Tick(float deltaTime, Surface* screen) {

	}

	BoundingBox GameObject::GetBoundingBox() {
		return BoundingBox(0, 0, 0, 0);;
	}

}

