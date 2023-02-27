#define _CRT_SECURE_NO_WARNINGS 1

#include "display.h"






xyz_structure cam = { 0,5,1 }, direct = { 1,0, };




GLvoid InitGL()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void draw_text(const char* str_for_character,int len) {
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str_for_character[i]);
}
void draw_text(const char* str_for_character) {
	draw_text(str_for_character, strlen(str_for_character));
}
void draw_symbols()
{
	glPushMatrix();
	glTranslated(0, 0, -0.1);
	glColor3f(0, 0, 0);
	glRasterPos3f(-0.0004, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '+');
	
	char str_for_character[128];

	sprintf(str_for_character, "x: %+5f y: %+5f z: %+5f", cam.x, cam.y, cam.z);
	glRasterPos3f(-0.03, 0.02, 0);
	draw_text("coord: ");
	draw_text(str_for_character, strlen(str_for_character));
	
	sprintf(str_for_character, "x: %+5f y: %+5f z: %+5f", direct.x, direct.y, direct.z);
	glRasterPos3f(-0.03, 0.025, 0);
	draw_text("look at: ");
	draw_text(str_for_character, strlen(str_for_character));

	
	glPopMatrix();
}

void draw_lines()
{
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3d(0, 0, 1);
	for (int i = -30; i < 30; i++)
		for (int j = -30; j < 30; j++)
			glVertex3f(i, -30, 0), glVertex3f(i, 30, 0), glVertex3f(-30, j, 0), glVertex3f(30, j, 0);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3d(0, 0.5, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0.5, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 0.5);
	glVertex3d(0, 0, 0);
	glEnd();
	glPopMatrix();
}

void Display(void) {
	glClearColor(0.3, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//очистить буфер цвета и глубины
	glLoadIdentity();// обнулить трансформацию
	draw_symbols();
	gluLookAt(cam.x, cam.y, cam.z,
		cam.x + direct.x, cam.y + direct.y, cam.z + direct.z,
		0, 0, 1);// установить камеру 
				 /*gluLookAt(cam.x, cam.y, cam.z,
				 cam.x + magnito[global_i-1].z, cam.y - magnito[global_i-1].y, cam.z + magnito[global_i-1].z,
				 0, 1, 0);*/



	glLineWidth(1);
	draw_lines();

	glutSwapBuffers();
}