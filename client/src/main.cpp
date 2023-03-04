#include "display.h"

bool keychar[256];
bool keyint[256];
int client_fd; //socket
char host[32] = "127.0.0.1";
int port = 5628;
char username[32]="user";
struct sockaddr_in serv_addr;
char buffer[1024] = { 0 };
Camera main_camera = Camera({0.5f,5.f,1.f }, { 0.f,0.f, 0.f});

int send_telem(){
    //convert data to json
    sprintf(buffer,"{\"time\":%ld,\"pose\":{\"position\":[%f,%f,%f],\"orientation\":[%f,%f,%f]}, \"pressed\":[",
        time(NULL), main_camera.position.x, main_camera.look_vector.y, main_camera.look_vector.z, main_camera.rotation.x, main_camera.rotation.y, main_camera.rotation.z);
    int count = 0;
    //all pressed char
    for(int i = 0;i<256;++i)
        if(keychar[i]){
            sprintf(buffer+strlen(buffer),"\"%c\",",i);
            ++count;
        }
    if(count > 0){
        buffer[strlen(buffer)-1]=0;//erase comma
    }
    sprintf(buffer+strlen(buffer), "],\"pressed_special\":[");
    count = 0;
    //all pressed special symbols
    for(int i = 0;i<256;++i)
        if(keyint[i]){
            sprintf(buffer+strlen(buffer),"%d,",i);
            ++count;
        }
    if(count > 0){
        buffer[strlen(buffer)-1]=0;//erase comma
    }
    sprintf(buffer+strlen(buffer), "]}");
    ssize_t status = send(client_fd, buffer, strlen(buffer), MSG_NOSIGNAL);
    if(status<0){
        std::cout<<"Send data error! closed connection"<<std::endl;
        close(client_fd);
        exit(-1);
    }
    return 0;
}
int socket_connect(){
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout<<"Socket creation error"<<std::endl;
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(15243);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        std::cout<<"Invalid address/ Address not supported"<<std::endl;
        return -1;
    }
  
    if ((connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        std::cout<<"Connection Failed"<<std::endl;
        return -1;
    }
    return 0;
}
int authorization(){
    sprintf(buffer,"{\"username\":\"%s\"}",username);
    int status = send(client_fd, buffer, strlen(buffer), MSG_NOSIGNAL);
    if(status<0){
        std::cout<<"\n Authorization error!"<<std::endl;
        close(client_fd);
        return -1;
    }
    status = recv(client_fd, buffer, 1024,MSG_NOSIGNAL);
    std::cout<<buffer<<std::endl;
    
    if(status<0){
        std::cout<<"\n Authorization error!"<<std::endl;
        close(client_fd);
        return -1;
    }
    return 0;
}


void keyboard_char(unsigned char key, int x, int y) {
	keychar[key] = true;
}
void keyboard_char_up(unsigned char key, int x, int y) {
	keychar[key] = false;
}
void keyboard_int(int key, int xx, int yy) {
	keyint[key] = true;
}
void keyboard_int_up(int key, int x, int y) {
	keyint[key] = false;
}
//обработка всех кнопок управления с клавиатуры
void keyboardParse() {
	//вращение камеры вокруг своих локальных осей
	if (keyint[GLUT_KEY_LEFT])  main_camera.rotate_left();
	if (keyint[GLUT_KEY_RIGHT]) main_camera.rotate_right();
	if (keyint[GLUT_KEY_UP])    main_camera.rotate_up();
	if (keyint[GLUT_KEY_DOWN])  main_camera.rotate_down();

	//перемещение камеры
	if ( keychar['A'] || keychar['a']) {
        main_camera.move_left();
    }
	if ( keychar['D'] || keychar['d']) {
        main_camera.move_right();
    }

	//перемещение камеры
	if (keychar['W'] || keychar['w']) {
        main_camera.move_forward();
    }
	if (keychar['S'] || keychar['s']) {
        main_camera.move_back();    
    }

	//перемещение камеры вверх вниз 
	// if (keychar['e'] || keychar['E']) cam.z += deltaMove.z;
	// if (keychar['q'] || keychar['Q']) cam.z -= deltaMove.z;
}
//redraw cycle
void timef(int value) {
	keyboardParse();
    send_telem();
	glutPostRedisplay();  //redraw scene

	glutTimerFunc(40, timef, 0); // recursion(actually no)
}


int main(int argc, char** argv) {
	char input_char=0;
    std::cout<<"use the default address (127.0.0.1:15243)? y/n:";
    std::cin>>input_char;
    if(input_char=='n' or input_char=='N'){
        std::cout<<"enter ip address:";
        std::cin>>host;
        std::cout<<"enter port:";
        std::cin>>port;
    }
    std::cout<<"use the default username (username)? y/n:";
    std::cin>>input_char;
    if(input_char=='n' or input_char=='N'){
        std::cout<<"enter username:";
        std::cin>>username;
    }
    if(socket_connect() < 0){
        return -1;
    }
    authorization();
    set_camera(&main_camera);

    // инициализация GLUT и создание окон
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow(username);
    glutPositionWindow(520,20);
	glutReshapeFunc(reshape);
    glutDisplayFunc(display);//main draw function
	InitGL();
	glutTimerFunc(20, timef, 0);
	glutSpecialFunc(keyboard_int);//key down processing (arrows)
	glutSpecialUpFunc(keyboard_int_up);//key up processing (arrows)
	glutKeyboardFunc(keyboard_char);//key down processing (w,a,s,d)
	glutKeyboardUpFunc(keyboard_char_up);//key up processing  (w,a,s,d)
	

	
	srand(time(0));


	glutMainLoop();
	return 0;
}