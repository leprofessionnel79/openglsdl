#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>

#include "functions.h"

using namespace std;

float angle=0.0;

int cube;
objloader obj;  //create an instance of the objloader
void init()
{
	glClearColor(0.5,0.5,0.5,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	cube=obj.load("cubemat.obj");  //load it
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	float col[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float pos[]={-1.5,2.0,-2.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glTranslatef(-1.3,-1.3,-7.0);
	glRotatef(angle,-1.0,-1.0,-1.0);
	glCallList(cube);   //and display it
}


int main(int argc,char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	bool running=true;
	Uint32 start;
	SDL_Event event;
	init();
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				running=false;
				break;
			}
		}
		display();
		SDL_GL_SwapBuffers();
		angle+=0.5;
		if(angle>360)
			angle-=360;
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;   
}