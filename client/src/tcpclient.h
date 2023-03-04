#include <iostream>
#include <string.h>
#include <sstream> 
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unordered_set>
#include "camera.h"
using namespace std;
class TCP_Client{
public:
    string ip;
    int port;
    string username;
private:
    int client_fd; //socket
    struct sockaddr_in serv_addr;
    static const int BUFFER_SIZE = 1024; 
    char buffer[BUFFER_SIZE] = { 0 };
    stringstream data_to_json(Camera *camera, unordered_set<unsigned char> *key_pressed, unordered_set<int> *key_pressed_special);
public:
    TCP_Client();
    TCP_Client(string ip, int port, string username);
    int send_telem(Camera *camera, unordered_set<unsigned char> *key_pressed, unordered_set<int> *key_pressed_special);
    int socket_connect();
    int authorization();
};