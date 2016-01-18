#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>
#include "Commons.h"
#include "3dsLoader.h"


long filelength(int f)
{
	struct stat buf;

	fstat(f, &buf);

	return(buf.st_size);
}


char Load3DS(obj_type_ptr p_object, char *p_filename)
{
	int i; //Index var
	FILE *inFile; // File Pointer

	unsigned short chunkId, s_temp; // Chunk Id Unsigned
	int chunkLength; // Chunk Length
	unsigned char name; // Name var
	unsigned short size; // number of elements in each Chunk 

	unsigned short faceFlag; //Flag that stores some face information

	if ((inFile = fopen(p_filename, "rb")) == NULL)
		return 0; //Open File

	while (ftell(inFile) < filelength(fileno(inFile))) // scan the whole file 
	{
		fread(&chunkId, 2, 1, inFile); // Read the header 
		fread(&chunkLength, 4, 1, inFile); // Reaf the chunk length 
		//getchar(); // Debug will wait for keypress for each reading

		switch (chunkId)
		{
			//Main3DS
			//Description: Main chunk, contains all the other chunks
			//Chunk ID: 4d4d
			//Chunk Length: 0 + sub Chunks

		case 0x4d4d:
			break;

			//Edit 3DS
			//Description: 3D editor chunk, objects layout info
			//Chunk ID: 3d3d (hex)
			//Chunk Length 0 + sub Chunks

		case 0x3d3d:
			break;

			//Edit Object
			//Description: Object block, info for each object 
			//Chunk ID: 4000 (hex)
			//Chunk Length: len(object name) + sub chunks

		case 0x4000:
			i = 0;
			do
			{
				fread(&name, 1, 1, inFile);
				p_object->name[i] = name;
				i++;
			} while (name != '\0' && i < 20);
			break;

			//OBJ_Trimesh
			//Description: Triangular mesh, contains chunks for 3D mesh info
			//Chunk ID : 4100 (hex)
			//Chunk Length: 0 + sub chunks

		case 0x4100:
			break;

			//TRI Vertexl
			//Description: Vertices list
			//Chunk ID: 4110 (hex)
			//Chunk Length: 1 x unsigned short (number of vertices)
			//				+ 3 x float (vertex coordinates) x (number of vertices) 
			//				+ sub chunks

		case 0x4110:
			fread(&size, sizeof(unsigned short), 1, inFile);
			p_object->verticies_qty = size;

			for (i = 0; i < size; i++)
			{
				fread(&p_object->vertex[i].x, sizeof(float), 1, inFile);
				fread(&p_object->vertex[i].y, sizeof(float), 1, inFile);
				fread(&p_object->vertex[i].z, sizeof(float), 1, inFile);
			}

			break;

			// Tri Facel1
			// Description: triangles (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk LengtH: 1 x unsigned short (number of triangles)
			//				+ 3 x unsigned short (triangle points) x (number of triangles)
			//				+ sub chunks

		case 0x4120:
			fread(&size, sizeof(unsigned short), 1, inFile);
			p_object->triangle_qty = size;

			for (i = 0; i < size; i++)
			{
				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->triangle[i].a = s_temp;

				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->triangle[i].b = s_temp;

				fread(&s_temp, sizeof(unsigned short), 1, inFile);
				p_object->triangle[i].c = s_temp;

				fread(&faceFlag, sizeof(unsigned short), 1, inFile);
			}
			break;

			// Tri MappingCoords
			//Description: Vertices lise
			//Chunk ID: 4410 (hex)
			//Chunk Length: 1 x unsigned short (number of mapping points)
			//				+ 2 x float (mapping coords) x (number of mapping points)
			//				+ sub chunks

		case 0x4140:
			fread(&size, sizeof(unsigned short), 1, inFile);
					for (i = 0; i < size; i++)
			{
				fread(&p_object->texcoord[i].u, sizeof(float), 1, inFile);

				fread(&p_object->texcoord[i].v, sizeof(float), 1, inFile);
			}
			break;

			//Skip uknown chunks
			//We need to skip all the chunks that we don't currently use
			// we use the chunk length info to set the file pointer
			// to the same level next chunk 

		default: 
			fseek(inFile, chunkLength - 6, SEEK_CUR);
		}
	}
	fclose(inFile);		//Close the file.
	return(1);


}