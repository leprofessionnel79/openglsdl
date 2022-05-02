#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#ifndef FUNCTION_H
#define FUNCTION_H

struct Coordinate{
	float x,y,z;
	Coordinate(float a, float b, float c);
};

struct face{
	int facenum;
	bool four;
	int faces[4];
	face(int facen, int f1, int f2, int f3);
	face(int facen, int f1, int f2, int f3, int f4);
};

int loadObject(const char* filename);
void drawCube(float size);

#endif