#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_

#include "Commons.h"
#include <string>
using std::string;

class Object3DS

{
public:
	Object3DS(Vertex3D startPosition, string modelFileName);
	
	~Object3DS(){}

	void update(float deltaTime);
	void render();

	void initValues();

	

	//Load 3ds file
	void loadModel();

	void setHandSpeed(float speed);
	
	

	//Load texture for this model.
	void loadTexture();
	Vertex3D mPosition;
private:
	

	char filename[20];
	char textureName[20];

	obj_type object;

	bool reached = false;

	float posX;		//clock position
	float posY;
	float posZ;

	float posRotX;		// clock rotation to postion
	float posRotY;
	float posRotZ;

	float posRotAngleX;
	float posRotAngleY;
	float posRotAngleZ;

	float handRotationspeed;		//Hand rotation
	float handRotaion;

};
#endif //_OBJECT3DS_H_