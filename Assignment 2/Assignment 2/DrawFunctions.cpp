#include "AI.h"

void AI::GlutDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1, 1, 1);

	glPushMatrix();

	glTranslatef(0, -10, 0);

	DrawLineCube(25, 25, 80, 50);

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			DrawObject(go);
		}
		for (std::vector<GameObject *>::iterator it = bullet_list.begin(); it != bullet_list.end(); ++it)
		{
			GameObject *go = (GameObject *)*it;
			if (go->active)
			{
				DrawObject(go);
			}
		}
	}

	glPopMatrix();

	police_mb.DebugMessage.RenderMessageBoard(3,78,60,20);
	robber_mb.DebugMessage.RenderMessageBoard(67,78,60,20);
	glutSwapBuffers();
	glutPostRedisplay();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

}

void AI::DrawObject(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_ROBBER:
		glPushMatrix();
			if (go->CurrentState == GameObject::STATES::RUNNING_AWAY)
				glColor3f(1, 0, 1);
			else
				glColor3f(1, 0, 0);
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);
			glutSolidSphere(1, 10, 10);

			glTranslatef(0, 3, 0); //Bar Outline
			glColor3f(1, 0, 0);
			glBegin(GL_LINES);
				glVertex3f(-3, -1, 0);	glVertex3f(3, -1, 0);
				glVertex3f(3, 1, 0);	glVertex3f(-3, 1, 0);
				glVertex3f(3, -1, 0);	glVertex3f(3, 1, 0);
				glVertex3f(-3, -1, 0);	glVertex3f(-3, 1, 0);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(-3, 1, 0);
				glVertex3f(-3, -1, 0);
				glVertex3f(-3 + 0.06 * go->health, -1, 0);
				glVertex3f(-3 + 0.06 * go->health, 1, 0);
			glEnd();

			glTranslatef(0, -6, 0); //Bar Outline
			glColor3f(0, 1, 0);
			glBegin(GL_LINES);
				glVertex3f(-3, -1, 0);	glVertex3f(3, -1, 0);
				glVertex3f(3, 1, 0);	glVertex3f(-3, 1, 0);
				glVertex3f(3, -1, 0);	glVertex3f(3, 1, 0);
				glVertex3f(-3, -1, 0);	glVertex3f(-3, 1, 0);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(-3, 1, 0);
				glVertex3f(-3, -1, 0);
				glVertex3f(-3 + 0.06 * go->money, -1, 0);
				glVertex3f(-3 + 0.06 * go->money, 1, 0);
			glEnd();
		glPopMatrix();
		break;
	case GameObject::GO_LOOKOUT:
		glPushMatrix();
			if (go->CurrentState == GameObject::STATES::RUNNING_AWAY)
				glColor3f(1, 0, 1);
			else
				glColor3f(0.5, 0, 0);
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);

			glutSolidSphere(15, 20, 10);

			glutSolidSphere(1, 10, 10);

			glTranslatef(0, 3, 0); //Bar Outline
			glColor3f(1, 0, 0);
			glBegin(GL_LINES);
			glVertex3f(-3, -1, 0);	glVertex3f(3, -1, 0);
			glVertex3f(3, 1, 0);	glVertex3f(-3, 1, 0);
			glVertex3f(3, -1, 0);	glVertex3f(3, 1, 0);
			glVertex3f(-3, -1, 0);	glVertex3f(-3, 1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(-3, 1, 0);
			glVertex3f(-3, -1, 0);
			glVertex3f(-3 + 0.06 * go->health, -1, 0);
			glVertex3f(-3 + 0.06 * go->health, 1, 0);
			glEnd();

			glTranslatef(0, -6, 0); //Bar Outline
			glColor3f(0, 1, 0);
			glBegin(GL_LINES);
			glVertex3f(-3, -1, 0);	glVertex3f(3, -1, 0);
			glVertex3f(3, 1, 0);	glVertex3f(-3, 1, 0);
			glVertex3f(3, -1, 0);	glVertex3f(3, 1, 0);
			glVertex3f(-3, -1, 0);	glVertex3f(-3, 1, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(-3, 1, 0);
			glVertex3f(-3, -1, 0);
			glVertex3f(-3 + 0.06 * go->money, -1, 0);
			glVertex3f(-3 + 0.06 * go->money, 1, 0);
			glEnd();
		glPopMatrix();
		break;
	case GameObject::GO_POLICE:
		glPushMatrix();
			glColor3f(0, 0, 1);
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);
			glutSolidSphere(1, 10, 10);

			glTranslatef(0, 3, 0); //Bar Outline
			glColor3f(1, 0, 0);
			glBegin(GL_LINES);
				glVertex3f(-3, -1, 0);	glVertex3f(3, -1, 0);
				glVertex3f(3, 1, 0);	glVertex3f(-3, 1, 0);
				glVertex3f(3, -1, 0);	glVertex3f(3, 1, 0);
				glVertex3f(-3, -1, 0);	glVertex3f(-3, 1, 0);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(-3, 1, 0);
				glVertex3f(-3, -1, 0);
				glVertex3f(-3 + 0.06 * go->health, -1, 0);
				glVertex3f(-3 + 0.06 * go->health, 1, 0);
			glEnd();
		glPopMatrix();
		break;

	case GameObject::GO_CHIEF:
		glPushMatrix();
		glColor3f(0, 1, 1);
		glTranslatef(go->pos.x, go->pos.y, go->pos.z);
		glScalef(go->scale.x, go->scale.y, go->scale.z);
		glutSolidSphere(1, 10, 10);

		glTranslatef(0, 3, 0); //Bar Outline
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(-3, -1, 0);	glVertex3f(3, -1, 0);
		glVertex3f(3, 1, 0);	glVertex3f(-3, 1, 0);
		glVertex3f(3, -1, 0);	glVertex3f(3, 1, 0);
		glVertex3f(-3, -1, 0);	glVertex3f(-3, 1, 0);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-3, 1, 0);
		glVertex3f(-3, -1, 0);
		glVertex3f(-3 + 0.06 * go->health, -1, 0);
		glVertex3f(-3 + 0.06 * go->health, 1, 0);
		glEnd();
		glPopMatrix();
		break;
	case GameObject::GO_BULLET:
		glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);
			glutSolidSphere(0.2, 10, 10);
		glPopMatrix();
		break;
	case GameObject::GO_WAYPOINTS:
		glPushMatrix();
			glColor3f(1, 0, 1);
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);
			glutSolidCube(2);
		glPopMatrix();
		break;
	case GameObject::GO_EXIT:
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(go->pos.x, go->pos.y, go->pos.z);
		glScalef(go->scale.x, go->scale.y, go->scale.z);
		glutSolidCube(2);
		glPopMatrix();
		break;
	case GameObject::GO_MONEY:
		glPushMatrix();
		glColor3f(0, 0.5, 0);
		glTranslatef(go->pos.x, go->pos.y, go->pos.z);
		glScalef(go->scale.x, go->scale.y, go->scale.z);
		//glBindTexture(GL_TEXTURE_2D, textures[GameObject::GAMEOBJECT_TYPE::GO_MONEY].texID);
		DrawSquare(10);
		glPopMatrix();
		break;
	}
}
