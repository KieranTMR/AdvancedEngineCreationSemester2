#include "Texture.h"
#include <iostream>
#include <fstream>
using namespace::std;

Texture2D::Texture2D()
{
	
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char*tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg (0, ios::end); //Seek to end of file
	fileSize = (int)inFile.tellg();//Get current position in file - The End, this gives us the total file size

	tempTextureData = new char [fileSize]; // Creates a new array to store the file data
	inFile.seekg(0, ios::beg); //Seek back to the beginning of the file
	inFile.read(tempTextureData, fileSize); // Read all the data in one
	inFile.close(); //close the file

	cout << path << " Loaded." << endl;

	glGenTextures(1, &_ID); //Get next Texture ID
	glBindTexture(GL_TEXTURE_2D,_ID); //Bind the Texture to the ID
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData; //Clear up the data - We don't need this any more
	return true;

}