
#include "display.h"
#include "tcpclient.h"

std::unordered_set<unsigned char> key_set; //pressed keys ascii
std::unordered_set<int> key_special_set; //pressed keys special (arrows etc)

Camera main_camera = Camera({0.5f,5.f,1.f }, { 0.f,0.f, 0.f});
TCP_Client tcp_client;

void keyboard_char(unsigned char key, int x, int y) {
	key_set.insert(key);
}
void keyboard_char_up(unsigned char key, int x, int y) {
	key_set.erase(key);
}
void keyboard_int(int key, int xx, int yy) {
	key_special_set.insert(key);
}
void keyboard_int_up(int key, int x, int y) {
	key_special_set.erase(key);
}
//обработка всех кнопок управления с клавиатуры
void keyboardParse() {
	//вращение камеры вокруг своих локальных осей
	if (key_special_set.count(GLUT_KEY_LEFT))  main_camera.rotate_left();
	if (key_special_set.count(GLUT_KEY_RIGHT)) main_camera.rotate_right();
	if (key_special_set.count(GLUT_KEY_UP))    main_camera.rotate_up();
	if (key_special_set.count(GLUT_KEY_DOWN))  main_camera.rotate_down();

	//перемещение камеры
	if ( key_set.count('A') || key_set.count('a')) {
        main_camera.move_left();
    }
	if ( key_set.count('D') || key_set.count('d')) {
        main_camera.move_right();
    }

	//перемещение камеры
	if (key_set.count('W') || key_set.count('w')) {
        main_camera.move_forward();
    }
	if (key_set.count('S') || key_set.count('s')) {
        main_camera.move_back();    
    }

	//перемещение камеры вверх вниз 
	// if (keychar['e'] || keychar['E']) cam.z += deltaMove.z;
	// if (keychar['q'] || keychar['Q']) cam.z -= deltaMove.z;
}
//redraw cycle
void timef(int value) {
	keyboardParse();
    tcp_client.send_telem(&main_camera, &key_set, &key_special_set);
	glutPostRedisplay();  //redraw scene

	glutTimerFunc(40, timef, 0); // recursion(actually no)
}

void user_interface(){
    char input_char=0;
    std::cout<<"use the default address ("<<tcp_client.ip<<":"<<tcp_client.port << ")? y/n:";
    std::cin>>input_char;
    if(input_char=='n' or input_char=='N'){
        std::cout<<"enter ip address:";
        std::cin>>tcp_client.ip;
        std::cout<<"enter port:";
        std::cin>>tcp_client.port;
    }
    std::cout<<"use the default username ("<<tcp_client.username<<")? y/n:";
    std::cin>>input_char;
    if(input_char=='n' or input_char=='N'){
        std::cout<<"enter username:";
        std::cin>>tcp_client.username;
    }
}
int main(int argc, char** argv) {
    //glut init
    glutInit(&argc, argv);
	
    user_interface();

    if(tcp_client.socket_connect() != 0){
        return errno;
    }
    if(tcp_client.authorization()!= 0){
        return errno;
    }

    Render render(tcp_client.username.c_str(), &main_camera);
    
	glutTimerFunc(20, timef, 0);//timer cycle
	glutSpecialFunc(keyboard_int);//key down processing (arrows)
	glutSpecialUpFunc(keyboard_int_up);//key up processing (arrows)
	glutKeyboardFunc(keyboard_char);//key down processing (w,a,s,d)
	glutKeyboardUpFunc(keyboard_char_up);//key up processing  (w,a,s,d)
	glutMainLoop();
	
    return 0;
}