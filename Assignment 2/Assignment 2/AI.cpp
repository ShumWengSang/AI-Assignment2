#include "AI.h"

void AI::Init()
{
	LoadTGA(&textures[GameObject::GAMEOBJECT_TYPE::GO_MONEY], "images/money.tga");

	srand(time(NULL));
	GameObject * go;
	Math::InitRNG();

	WayPoints[0] = Vector3(80, 70, 0);
	WayPoints[1] = Vector3(100, 70, 0);
	WayPoints[2] = Vector3(100, 40, 0);
	WayPoints[3] = Vector3(80, 40, 0);
	WayPoints[4] = Vector3(50, 50, 0);

	for (int i = 0; i < 5; i++)
	{
		go = FetchGO();
		go->type = GameObject::GO_WAYPOINTS;
		go->pos.Set(WayPoints[i]);
	}

	Alarm = false;

	money = FetchGO();
	money->type = GameObject::GO_MONEY;
	money->pos.Set(30, 30, 0);
	money->scale.Set(1, 1, 1);



	go = FetchGO();
	go->type = GameObject::GO_ROBBER;
	go->pos.Set(70, 20, 0);
	go->CurrentState = GameObject::STATES::STEALING;

	go = FetchGO();
	go->type = GameObject::GO_ROBBER;
	go->pos.Set(70, 40, 0);
	go->CurrentState = GameObject::STATES::STEALING;

	go = FetchGO();
	go->type = GameObject::GO_ROBBER;
	go->pos.Set(70, 60, 0);
	go->CurrentState = GameObject::STATES::STEALING;
	go = FetchGO();

	go = FetchGO();
	go->type = GameObject::GO_ROBBER;
	go->pos.Set(70, 80, 0);
	go->CurrentState = GameObject::STATES::STEALING;
	




	go = FetchGO();
	go->type = GameObject::GO_POLICE;
	go->pos.Set(80, 70, 0);
	//go->vel.Set(0, 15, 0);
	go->CurrentState = GameObject::STATES::PATROLLING;
	go->TargetLocked = false;

	go = FetchGO();
	go->type = GameObject::GO_POLICE;
	go->pos.Set(80, 60, 0);
	//go->vel.Set(0, 15, 0);
	go->CurrentState = GameObject::STATES::PATROLLING;
	go->TargetLocked = false;

	go = FetchGO();
	go->type = GameObject::GO_POLICE;
	go->pos.Set(80, 50, 0);
	//go->vel.Set(0, 15, 0);
	go->CurrentState = GameObject::STATES::PATROLLING;
	go->TargetLocked = false;

	go = FetchGO();
	go->type = GameObject::GO_POLICE;
	go->pos.Set(80, 40, 0);
	//go->vel.Set(0, 15, 0);
	go->CurrentState = GameObject::STATES::PATROLLING;
	go->TargetLocked = false;

	exit = FetchGO();
	exit->type = GameObject::GO_EXIT;
	exit->pos.Set(20, 60, 0);

	for (std::vector<GameObject *>::iterator iter2 = m_goList.begin(); iter2 != m_goList.end(); ++iter2)
	{
		if ((*iter2)->type == GameObject::GO_ROBBER) {
			//cout << robber_list.size();
			//(*iter2)->vecPos = robber_list.size();
			robber_list.push_back((*iter2));

		}
		else if ((*iter2)->type == GameObject::GO_CHIEF || (*iter2)->type == GameObject::GO_POLICE)
			police_list.push_back((*iter2));
	}

	police_list[0]->type = GameObject::GO_CHIEF;

	//cout << robber_list.size() << " " << police_list.size();

	//go = FetchGO();
	//go->type = GameObject::GO_ROBBER;
	//go->pos.Set(70, 50, 0);
	//go->scale.Set(1, 1, 1);
	//go->CurrentState = GameObject::STATES::STEALING;
	//go->vel.Set(0, 5, 0);



	//exit = FetchGO();
	//exit->type = GameObject::GO_EXIT;
	//exit->pos.Set(20, 60, 0);
	//exit->scale.Set(1, 1, 1);
}


void AI::GotoLocation(Vector3 theNewPos, GameObject * go, float speed)
{
	Vector3 TheDirection(theNewPos - go->pos);
	TheDirection.Normalize();
	TheDirection *= speed;
	go->vel = TheDirection;
}


bool AI::ReachedLocation(Vector3 thePosReached, GameObject * go)
{
	return 1 > (thePosReached - go->pos).Length();
}

void AI::GlutKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'h':
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *go = (GameObject *)*it;
			if (go->active)
			{
				go->health = 100;
			}
		}
		break;

	case ' ':
		Alarm = true;
		for (std::vector<GameObject *>::iterator iter = robber_list.begin(); iter != robber_list.end(); ++iter)
		{
			GameObject *go = (GameObject *) *iter;
			go->TargetShoot = police_list[rand() % police_list.size()];
			
			go->CurrentState = GameObject::STATES::SHOOTING;

			//FireBullet(go);

			//go->CurrentState = GameObject::STATES::RUNNING_AWAY;
			
			
			/*int runaway = rand() % 2;
			if (runaway)
				go->CurrentState = GameObject::STATES::RUNNING_AWAY;
			else
				go->CurrentState = GameObject::STATES::SHOOTING;*/
		}

		for (std::vector<GameObject *>::iterator iter = police_list.begin(); iter != police_list.end(); ++iter)
		{
			GameObject *go = (GameObject *)*iter;
			go->CurrentState = GameObject::STATES::SHOOTING;
		}
		break;
	}
}

void AI::GlutIdle()
{
	static int frame = 0;
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	++frame;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float dt = (time - lastTime) / 1000.f;
	lastTime = time;

	static int lastFPSTime = glutGet(GLUT_ELAPSED_TIME);
	if (time - lastFPSTime > 1000)
	{
		m_fps = frame * 1000.f / (time - lastFPSTime);
		lastFPSTime = time;
		frame = 0;
	}

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			go->pos += go->vel * dt * m_speed;

			GameObject *nearest = NULL;

			//Check bullet collision
			

			switch (go->type)
			{
			case GameObject::GO_BULLET:
				break;

			case GameObject::GO_CHIEF:
				switch (go->CurrentState)
				{
				case GameObject::STATES::SHOOTING:
					if (frame == 0)
					{
						if (go->TargetShoot == NULL || go->TargetShoot->active == false)
						{
							if (robber_list.size() > 0)
							{
								go->TargetShoot = robber_list[rand() % robber_list.size()];
								for (std::vector<GameObject *>::iterator it = police_list.begin(); it != police_list.end(); ++it) {
									GameObject * police = (GameObject*)*it;
									police->TargetShoot = go->TargetShoot;
								}
							}
							FireBullet(go);
						}
						else
						{
							FireBullet(go);
						}
					}
					break;
				}
				break;

			case GameObject::GO_POLICE:
				switch (go->CurrentState)
				{
				case GameObject::STATES::CHASING:
					/*
					if (go->TargetLocked)
					{
						//if (!(robbers[go->Target]->pos == go->TargetPos))
						if (!(robbers[go->Target]->active))
						{

							go->TargetLocked = false;
							std::cout << "Target change" << std::endl;
						}
					}

					if (!go->TargetLocked)
					{
						go->Target = rand() % robbers.size();
						go->TargetLocked = true;
					}
					GotoLocation(robbers[go->Target]->pos, go, 15);
					go->TargetPos = robbers[go->Target]->pos/* + robbers[go->Target]->vel;
					*/
					break;
				case GameObject::STATES::SHOOTING:
					if (frame == 0)
					{
						FireBullet(go);
					}
					break;
				}
				break;

			case GameObject::GO_ROBBER:
				if (!Alarm) 
				{
					if (go->money < 100)
						go->CurrentState = GameObject::STATES::STEALING;
					else
						go->CurrentState = GameObject::STATES::DEPOSITING;
				}


				switch (go->CurrentState) //Robber States
				{
				case GameObject::STATES::STEALING:
					GotoLocation(money->pos, go, 15);
					if (ReachedLocation(money->pos, go))
					{
						go->vel.SetZero();
						if (go->money < 100)
							go->money++;
					}
					break;
				case GameObject::STATES::DEPOSITING:
					GotoLocation(exit->pos, go, 15);
					if (ReachedLocation(exit->pos, go))
						go->money = 0;
					break;
				case GameObject::STATES::RUNNING_AWAY:
					GotoLocation(exit->pos, go, 15);
					if (ReachedLocation(exit->pos, go))
						go->active = false;
					break;
				case GameObject::STATES::SHOOTING:
					go->vel.SetZero();
					if (frame == 0)
					{
						go->TargetShoot = police_list[rand() % police_list.size()];
						FireBullet(go);
					}
					//GotoLocation(go->TargetShoot->pos, go, 15);
					/*GameObject * bullet = FetchGO();
					bullet->type = GameObject::GO_BULLET;
					bullet->pos = go->pos;
					bullet->vel = (go->pos - go->TargetShoot->pos).Normalized();*/
					break;
				}
				break;
			}
		}

		if (go->type == GameObject::GO_POLICE || go->type == GameObject::GO_ROBBER || go->type == GameObject::GO_CHIEF)
		{
			for (std::vector<GameObject *>::iterator it2 = bullet_list.begin(); it2 != bullet_list.end(); ++it2)
			{
				GameObject *other = (GameObject *)*it2;
				if (other->active && other->type == GameObject::GO_BULLET)
				{
					if (ReachedLocation(go->pos, other))
					{
						go->health -= 10;
						other->active = false;
						///*
						if (go->health <= 0) {
							go->active = false;
							if (go->type == GameObject::GO_ROBBER) {
								//robber_list.erase[go->vecPos];
								//m_goList.erase(go);
								//robber_list.erase(go);
								//robber_list.erase(std::remove(robber_list.begin(), robber_list.end(), go), robber_list.end());
							}
							else if (go->type == GameObject::GO_CHIEF) {

							}
						}
						//*/
					}
				}
			}
		}


	}

	for (std::vector<GameObject *>::iterator it = bullet_list.begin(); it != bullet_list.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			//if (go->pos.x < 0 || go->pos.x > m_worldSizeX || go->pos.y < 0 || go->pos.y > m_worldSizeY)
			//	go->active = false;
			go->pos += go->vel * dt * m_speed;
		}
	}

	std::vector<GameObject *>::iterator it = robber_list.begin();
	while (it != robber_list.end()) {
		GameObject *go = (GameObject *)*it;
		if (go->active == false) {
			it = robber_list.erase(it);
		}
		else
		{
			it++;
		}
	}

}

void AI::DrawSquare(int length)
{
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);		glVertex2f(-length * 0.5, -length * 0.5);
	glTexCoord2f(1, 0);		glVertex2f(length * 0.5, -length * 0.5);
	glTexCoord2f(1, 1);		glVertex2f(length * 0.5, length * 0.5);
	glTexCoord2f(0, 1);		glVertex2f(-length * 0.5, length * 0.5);
	//glTexCoord2f(0, 1);		glVertex2f(0, 0);
	//glTexCoord2f(0, 0);		glVertex2f(0, 10);
	//glTexCoord2f(1, 0);		glVertex2f(10, 10);
	//glTexCoord2f(1, 1);		glVertex2f(10, 0);


	//glutSolidCube(1);
	glEnd();
	//glutSolidCube(10);
}



void AI::DrawLineCube(int x, int y, int width, int height)
{
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	{

		glColor3f(1, 1, 1);
		glVertex2f(x, y);
		glVertex2f(x, y + height);
		glVertex2f(x + width, y + height);
		glVertex2f(x + width, y);
		glVertex2f(x, y);
		//glLineWidth(1);
	}
	glEnd();
	glLineWidth(1);
}