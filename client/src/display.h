#pragma once
#define JUMP_FOR_DYNAMIC_ARRAY_OF_POINTS 1000;
#define EXTRA_LINE_LENGTH 64
#include <GL/glut.h>

#include <stdio.h>
#include <iostream>
#include <thread>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "camera.h"
struct xyz_structure {
	float x;
	float y;
	float z;
};
extern Camera *display_camera;
void set_camera(Camera *camera);
// extern xyz_structure cam, direct;
GLvoid InitGL();
void draw_text(const char* str_for_character,int len);
void draw_text(const char* str_for_character);
void draw_game_data();
void draw_lines();
void reshape(int w, int h);
void display(void);
void authorization_display(void);
