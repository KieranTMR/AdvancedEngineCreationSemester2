#include "Spinner.h"
#include "../gl/glut.h"
#include "3dsLoader.h"
#include "GameScreenLevel1.h"
#include "Texture.h"
#include "Commons.h"
#include "Constants.h"

Object3DS::Object3DS(Vertex3D startPosition, string modelFileName)
{
	//start position.
	mPosition = startPosition;

	//3ds file to load
	std::strcpy(filename, modelFileName.c_str());
	loadModel();

}


void Object3DS::loadModel()
{

	if (filename[0] != '---')
		Load3DS(&object, filename);
}

void Object3DS::loadTexture()
{
	Texture2D* texture = new Texture2D();
	texture->Load("stars.raw", 512, 512);
	glBindTexture(GL_TEXTURE_2D, texture->GetID());
}

void Object3DS::render()
{

	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);



	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (Triangles)

	for (int l_index = 0; l_index < object.triangle_qty; l_index++)
	{


		//Texture coordinates of the first vertex
		glTexCoord2f(object.texcoord[object.triangle[l_index].a].u,
			object.texcoord[object.triangle[l_index].a].v);


		glVertex3f(object.vertex[object.triangle[l_index].a].x,
			object.vertex[object.triangle[l_index].a].y,
			object.vertex[object.triangle[l_index].a].z); // Vertex Definition



		//Texture coordinates of the first vertex
		glTexCoord2f(object.texcoord[object.triangle[l_index].b].u,
			object.texcoord[object.triangle[l_index].b].v);


		glVertex3f(object.vertex[object.triangle[l_index].b].x,
			object.vertex[object.triangle[l_index].b].y,
			object.vertex[object.triangle[l_index].b].z);



		//Texture coordinates of the first vertex
		glTexCoord2f(object.texcoord[object.triangle[l_index].c].u,
			object.texcoord[object.triangle[l_index].c].v);


		glVertex3f(object.vertex[object.triangle[l_index].c].x,
			object.vertex[object.triangle[l_index].c].y,
			object.vertex[object.triangle[l_index].c].z);
	}
	glEnd();

	glPopMatrix();

}

void Object3DS::update(float deltaTime)
{

	if (reached == false)
	{
		mPosition.x += 0.009f;

		if (mPosition.x >= 10.0)
		{
			reached = true;
		}
	}

	if (reached == true)

	{
		mPosition.x -= 0.06f;

		if (mPosition.x <= -10.0)
		{
			reached = false;
		}
	}



	glTranslatef(mPosition.x, mPosition.y, mPosition.z);


	glRotatef(0.0f, 1.0f, 1.0f, 1.0f);
}