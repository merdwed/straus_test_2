#define _CRT_SECURE_NO_WARNINGS 1
#define JUMP_FOR_DYNAMIC_ARRAY_OF_POINTS 1000;
#define EXTRA_LINE_LENGTH 64
#include <GL/glut.h>

#include <stdio.h>
#include <thread>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

struct xyz_structure {
	float x;
	float y;
	float z;
};
struct quaternion {
	float x;
	float y;
	float z;
	float w;
};
extern xyz_structure cam, direct;
GLvoid InitGL();
void draw_symbols();
void draw_lines();
void Display(void);