#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "object3DS.h"
#include "Camera.h"


class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void SetLight();
	void SetMaterial();
	void OutputLine(float x, float y, string text);
	float timeSec = 0.0f;
	int timeMin = 0;
	int timeHour = 0;


//--------------------------------------------------------------------------------------------------
private:


	float mCurrentTime;
	float rotation;
	Object3DS* Clock;
	Object3DS* Hourhand;
	Object3DS* Minutehand;
	Object3DS* Secondhand;
	Camera* camInstance;
	

};


#endif //_GAMESCREENLEVEL1_H