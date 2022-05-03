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

float angle = 0.0;
const int triangle = 1; // this is the id used in glnewlist function and it couldnt be = 0

int cube;
int monk;
void Init(){

	glClearColor(0.5,0.5,0.5,1.0); //change background color into grey color to show the fog on mesh
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640/480,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,1.0);
	glFogf(GL_FOG_END,7.1);
	float fogColor[]={0.5,0.5,0.5,1.0};
	glFogfv(GL_FOG_COLOR,fogColor);

	float dif[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);

	float amb[]={0.2,0.2,0.2,1.0};
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb);


	monk = loadObject("monk.obj"); // object loaded here by this function declared in functions.cpp
	cube = loadObject("cube.obj");
	

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float pos[]={-1.5,2.0,-2.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glPushMatrix();
		glTranslatef(1.2,0.0,-7.0);
		glRotatef(angle,-1.0,-1.0,0.0);
		glCallList(monk);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0,0.0,-7.0);
		glRotatef(angle,1.0,1.0,0.0);
		glCallList(monk);
	glPopMatrix();
	
	/*glBegin(GL_TRIANGLES);

	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0,2.0,0.0);

	glColor3f(0.0,1.0,0.0);
	glVertex3f(-2.0,-2.0,0.0);

	glColor3f(0.0,0.0,0.0);
	glVertex3f(2.0,-2.0,1.0);

	glEnd();*/

}




int main(int argc , char** argv){

	cout<<"hi ahmad"<<endl;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Surface* screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	bool running = true;
	Uint32 start;
	SDL_Event event;
	Init();
	while(running){
		start = SDL_GetTicks();

		while(SDL_PollEvent(&event)){
			switch(event.type){

			case SDL_QUIT:
				running = false;
				break;
			}
		}

		display();
		SDL_GL_SwapBuffers();
		angle+=0.05;
		if(angle>360)
			angle-=360;
		if(1000/30>(SDL_GetTicks()-start))
		{
			SDL_Delay(1000/30>(SDL_GetTicks()-start));

		}
	}


	SDL_Quit();
	return 0;
}