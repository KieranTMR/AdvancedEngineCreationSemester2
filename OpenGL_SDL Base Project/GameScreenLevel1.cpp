#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <string>
#include <sstream>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include "Texture.h"
#include "object3DS.h"
#include "Camera.h"


using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f,aspect,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Vertex3D startPosition;
	startPosition.x = 0.0f;
	startPosition.y = 0.0f;
	startPosition.z = 0.0f;

	Clock = new Object3DS(startPosition, "Clock.3ds"); // This is where you change the object



	Hourhand = new Object3DS(startPosition, "Hourhand.3ds");
	Hourhand->setHandSpeed(0.00000016f);

	Minutehand = new Object3DS(startPosition, "Minutehand.3ds");
	Minutehand->setHandSpeed(0.0025f);

	Secondhand = new Object3DS(startPosition, "Secondhand.3ds");
	Secondhand->setHandSpeed(0.10f);

	//Vector3D forward = { 0.0f, 0.0f, 0.0f };
	Vector3D up = { 1.0f, 0.0f, 0.0f };
	Vector3D to = { 0.0f, -30.0f, 0.0f }; //tilt
	Vector3D eye = { 0.0f, 10.0f, 0.0f }; //pan

	camInstance = new Camera;
	camInstance->SetPos(eye, to, up);
	//camInstance->SetForward(forward);
	
	

	



	
	Texture2D* penguins = new Texture2D();
	penguins->Load("Penguins.raw", 512, 512);
	
	Texture2D* stars = new Texture2D();
	stars->Load("ClockFace.raw", 512, 512);

	
	
	


}

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::OutputLine(float x, float y, string text)
{
	glRasterPos2f(x, y); // this is where we start drawning
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}
}

void GameScreenLevel1::SetLight(){
	lighting light = {
		{1.0f,1.0f,1.0f,1.0f},
		{0.7f,0.7f,0.7f,1.0f},
		{0.5f, 0.5f,0.5f,1.0f}
	};
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

}

void GameScreenLevel1::SetMaterial(){
	material material = {
		{ 1.00f, 1.00f, 1.00f, 1.0f },
		{ 1.00f, 1.00f, 1.00f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		0.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specualr);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}



void GameScreenLevel1::Render()
{

	
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 1);// texture stuff
	
	glScalef(0.5f, 0.5f, 0.5f);
	Hourhand->render();
	Minutehand->render();
	Secondhand->render();
	
	glBindTexture(GL_TEXTURE_2D, 2);// texture stuff
	
	Clock->render();

	
	stringstream ss;
	ss << "Seconds Passed:" << timeSec << endl;
	stringstream ss2;
	ss2 << "Minutes Passed:" << timeMin << endl;
	stringstream ss3;
	ss3 << "Hours Passed:" << timeHour << endl;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(5, 95, "Use the W and S keys to zoom in and out and the A and D keys to move the camera Left and right.");
	OutputLine(5, 85, ss.str());
	OutputLine(5, 75, ss2.str());
	OutputLine(5, 65, ss3.str());
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	SetLight();
	SetMaterial();
	
	camInstance->Render();

	




}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	
	mCurrentTime += deltaTime;

	timeSec += deltaTime;

	if (timeSec >= 60)
	{
		timeSec = 0;
		timeMin += 1;
	}

	if (timeMin >= 60)
	{
		timeMin = 0;
		timeHour += 1;
	}
	
	

	Hourhand->update(deltaTime);
	Minutehand->update(deltaTime);
	Secondhand->update(deltaTime);

	Clock->update(deltaTime);
	
	camInstance->Update(deltaTime, e);


	
}

//--------------------------------------------------------------------------------------------------
