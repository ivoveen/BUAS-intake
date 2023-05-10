#include "GameObject.h"
#include "surface.h"



void GameObject::Tick(float deltaTime) {

}

BoundingBox GameObject::GetBoundingBox() {
	return BoundingBox(0, 0, 0, 0);;
}


