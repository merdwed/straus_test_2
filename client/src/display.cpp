#include "display.h"

Camera * Render::main_camera;
Render::Render(){
	// инициализация GLUT и создание окон
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("game");
	glutPositionWindow(520,20);
	glutReshapeFunc(this->reshape);
	glutDisplayFunc(this->display);//main draw function
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}
Render::Render(const char* title_name):Render::Render(){
	glutSetWindowTitle(title_name);
}
Render::Render(Camera *camera):Render::Render(){
	Render::main_camera = camera;
}
Render::Render(const char* title_name, Camera* camera):Render::Render(title_name){
	Render::main_camera = camera;
}
void Render::set_camera(Camera *camera){
	Render::main_camera = camera;
}	
void Render::draw_text(const char* str_for_character,int len) {
for (int i = 0; i < len; i++)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str_for_character[i]);
}
void Render::draw_text(const char* str_for_character) {
	draw_text(str_for_character, strlen(str_for_character));
}
void Render::draw_game_data(){
	glPushMatrix();
	glTranslated(0, 0, -0.1);
	glColor3f(0, 0, 0);
	glRasterPos3f(-0.0004, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '+');
	char str_for_character[128];
	sprintf(str_for_character, "x: %+5f y: %+5f z: %+5f", Render::main_camera->look_vector.x, Render::main_camera->look_vector.y, Render::main_camera->look_vector.z);
	glRasterPos3f(-0.03, 0.03, 0);
	draw_text("look at: ");
	draw_text(str_for_character, strlen(str_for_character));
	sprintf(str_for_character, "x: %+5f y: %+5f z: %+5f", Render::main_camera->rotation.x, Render::main_camera->rotation.y, Render::main_camera->rotation.z);
	glRasterPos3f(-0.03, 0.025, 0);
	draw_text("euler angle: ");
	draw_text(str_for_character, strlen(str_for_character));
	sprintf(str_for_character, "x: %+5f y: %+5f z: %+5f", Render::main_camera->position.x, Render::main_camera->position.y, Render::main_camera->position.z);
	glRasterPos3f(-0.03, 0.02, 0);
	draw_text("coord: ");
	draw_text(str_for_character, strlen(str_for_character));
	glPopMatrix();
}
void Render::draw_lines(){
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
void Render::reshape(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	//float ratio = w * 1 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	//glViewport(-(1000 - w) / 2, -(1000 - h) / 2, w / h * 1000, 1000);
	glViewport(0, 0, w, h);
	// установить параметры вьюпорта
	// установить корректную перспективу
	gluPerspective(45, 1, 0.1, 100); 
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}
void Render::display(void) {
	glClearColor(0.3, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//очистить буфер цвета и глубины
	glLoadIdentity();// обнулить трансформацию
	draw_game_data();
	Point3D pos = Render::main_camera->position;
	Point3D look_pos = Render::main_camera->position + Render::main_camera->look_vector;
	gluLookAt(pos.x, pos.y, pos.z,
		look_pos.x, look_pos.y, look_pos.z,
		0, 0, 1);// установить камеру 
	glLineWidth(1);
	draw_lines();
	glutSwapBuffers();
}
