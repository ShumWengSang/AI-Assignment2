#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Vector3.h"
#include "GameObject.h"
#include "MessageBoard.h";
#include "freeglut.h"

using namespace std;

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	frameNumbers;									// Number of frames in the texture
} TextureImage;												// Structure Name

struct WayPoint
{
	Vector3 thePoint;
	WayPoint * nextPoint;
};

class AI
{
public:

	static AI* GetInstance()
	{
		static AI s_instance;
		return &s_instance;
	}
	void Init();
	void Exit();

	void SetupRenderContext();
	void GlutReshape(GLsizei w, GLsizei h);
	void GlutMouseClick(int button, int state, int x, int y);
	void GlutMouseMove(int x, int y);
	void GlutKeyboard(unsigned char key, int x, int y);
	void GlutIdle();
	void GlutDisplay();
	void GlutSpecialKey(int key, int x, int y);
	void DrawObject(GameObject *go);
	void RenderStringOnScreen(float x, float y, const char* quote);

private:
	AI();
	~AI();

	

	float m_fps;
	float m_speed;
	float m_worldSizeX;
	float m_worldSizeY;
	Vector3 m_force;


	GameObject* FetchGO();
	void FireBullet(GameObject* go);
	GameObject* money;
	GameObject* exit;
	//Vector3 WayPoints[5];
	WayPoint thePoints[5];

	std::vector<GameObject *> m_goList;
	std::vector<GameObject *> robber_list;
	std::vector<GameObject *> police_list;
	std::vector<GameObject *> bullet_list;
	//std::vector<GameObject *> robbers;


	void DrawLineCube(int x, int y, int width, int height);
	void DrawCubeTextured(int x, int y, int size);

	void DrawSquare(int length);
	void DrawBackground(int, int);
	bool Alarm;
	void AlarmRing();
	bool firstChiefDead;
	void GotoLocation(Vector3 theNewPos, GameObject * go, float speed);
	bool ReachedLocation(Vector3 thePosReached, GameObject * go);

	bool LoadTGA(TextureImage *texture, char *filename);
	TextureImage textures[GameObject::GAMEOBJECT_TYPE::GO_TOTAL];

	MessageBoard police_mb;
	MessageBoard robber_mb;
};