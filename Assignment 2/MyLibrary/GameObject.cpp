#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
			: type(typeValue),
			scale(1, 1, 1),
			active(false),
			color(1, 1, 1),
			health(100),
			money(0),
			TargetShoot(NULL),
			TargetLocked(false)
{
}

GameObject::~GameObject()
{
}