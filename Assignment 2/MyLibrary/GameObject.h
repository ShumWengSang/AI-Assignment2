#pragma once
#include "Vector3.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_POLICE,
		GO_CHIEF,
		GO_ROBBER,
		GO_LOOKOUT,
		GO_BULLET,
		GO_WAYPOINTS,
		GO_WALL,
		GO_EXIT,
		GO_MONEY,
		GO_TOTAL //must be last
	};

	enum STATES
	{
		IDLE = 0,
		ALARMED,
		CHASING,
		PATROLLING,
		
		SHOOTING,

		STEALING,
		DEPOSITING,
		RUNNING_AWAY,
		CAUGHT,
		ESCAPED
	};

	STATES CurrentState;
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	bool active;
	int health;
	int money;
	Vector3 color;
	Vector3 normal;

	GameObject* Target;
	//int Target;
	bool TargetLocked;
	Vector3 TargetPos;

	GameObject* TargetShoot;

	int vecPos;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_NONE);
	~GameObject();
};