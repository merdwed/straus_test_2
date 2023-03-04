#pragma once
#define JUMP_FOR_DYNAMIC_ARRAY_OF_POINTS 1000;
#define EXTRA_LINE_LENGTH 64
#include <GL/glut.h>

#include <stdio.h>
#include <iostream>
#include <thread>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "camera.h"

class Render{
	static Camera *main_camera;
public:
	Render();
	Render(const char* title_name);
	Render(Camera *camera);
	Render(const char* title_name, Camera* camera);
	static void set_camera(Camera *camera);
	static void draw_text(const char* str_for_character,int len) ;
	static void draw_text(const char* str_for_character) ;
	static void draw_game_data();
	static void draw_lines();

	static void reshape(int w, int h);
	static void display(void);
};