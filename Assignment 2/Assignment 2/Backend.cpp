#include "AI.h"

AI::AI()
	: m_fps(30)
	, m_speed(1)
	, m_worldSizeY(100)
	, m_worldSizeX(m_worldSizeY)
{
}

AI::~AI()
{
	Exit();
}

void AI::SetupRenderContext()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);	// set background colour to black
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void AI::GlutReshape(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	float ratio = (float)w / h;
	m_worldSizeX = m_worldSizeY * ratio;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, m_worldSizeX, 0, m_worldSizeY);
	glMatrixMode(GL_MODELVIEW);
}

void AI::GlutMouseClick(int button, int state, int x, int y)
{
}

void AI::GlutMouseMove(int x, int y)
{
}

void AI::GlutSpecialKey(int key, int x, int y)
{
	//Exercise 5: update m_force with the following keys
	switch (key)
	{
	case GLUT_KEY_LEFT:
		exit->pos.x -= 5;
		break;
	case GLUT_KEY_UP:
		exit->pos.y += 5;
		break;
	case GLUT_KEY_RIGHT:
		exit->pos.x += 5;
		break;
	case GLUT_KEY_DOWN:
		exit->pos.y -= 5;
		break;
	}
}


void AI::Exit()
{
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}

GameObject* AI::FetchGO()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = *it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}
	GameObject *go = new GameObject(GameObject::GO_NONE);
	go->active = true;
	m_goList.push_back(go);
	return go;
}

void AI::FireBullet(GameObject* go)
{
	GameObject * bullet = new GameObject(GameObject::GO_NONE);
	bullet->active = true;
	bullet->type = GameObject::GO_BULLET;
	bullet->vel = (go->TargetShoot->pos - go->pos).Normalize() * 30;
	bullet->pos = go->pos + (go->TargetShoot->pos - go->pos).Normalize() * 3;
	bullet_list.push_back(bullet);
}

void AI::RenderStringOnScreen(float x, float y, const char* quote)
{
	int length = strlen(quote);
	glRasterPos2f(x, y);

	for (int i = 0; i < length; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, quote[i]);
	}
}

bool AI::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{
	GLubyte		TGAheader[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type = GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if (file == NULL ||										// Does File Even Exist?
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
		fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

	if (texture->width <= 0 ||								// Is The Width Less Than Or Equal To Zero
		texture->height <= 0 ||								// Is The Height Less Than Or Equal To Zero
		(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel = texture->bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize = texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if (texture->imageData == NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if (texture->imageData != NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp = texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose(file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

	if (texture[0].bpp == 24)									// Was The TGA 24 Bits
	{
		type = GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	texture->frameNumbers = texture->width / texture->height;

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}
