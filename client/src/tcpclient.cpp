#include "tcpclient.h"
stringstream TCP_Client::data_to_json(Camera *camera, unordered_set<unsigned char> *key_pressed, unordered_set<int> *key_pressed_special){
    //convert data to json
    stringstream json_ss;
    json_ss << "{";
    json_ss << "\"time\":" << time(NULL) << ",";
    json_ss << "\"pose\":{";
    json_ss << "\"position\":[" << camera->position.x << "," << camera->position.y << "," << camera->position.z << "],";
    json_ss << "\"orientation\":[" << camera->rotation.x << "," << camera->rotation.y << "," << camera->rotation.z << "]},";
    json_ss << " \"pressed\":[";
    //all pressed char
    for(char c :*key_pressed){
        if(c != *key_pressed->begin())
            json_ss << ",";
        json_ss << "\"" << c << "\"";
    }
    json_ss << "],";
    json_ss << "\"pressed_special\":[";
    //all pressed special symbols
    for(int i : *key_pressed_special){
        if(i != *key_pressed_special->begin())
            json_ss << ",";
        json_ss << i;
    }
    json_ss << "]}";
    return json_ss;
}
TCP_Client::TCP_Client(){
    this->ip = "127.0.0.1";
    this->port = 15243;
    this->username = "user";
}
TCP_Client::TCP_Client(string ip, int port, string username){
    this->ip = ip;
    this->port = port;
    this->username = username;
}
int TCP_Client::send_telem(Camera *camera, unordered_set<unsigned char> *key_pressed, unordered_set<int> *key_pressed_special){
    string json_str = this->data_to_json(camera, key_pressed, key_pressed_special).str();
    ssize_t status = send(this->client_fd, json_str.c_str(), json_str.size() , MSG_NOSIGNAL);
    if(status<0){
        cout<<"Send data error! closed connection"<<endl;
        close(this->client_fd);
        exit(errno);
    }
    return 0;
}

int TCP_Client::socket_connect(){
    if ((this->client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout<<"Socket creation error"<<endl;
        return errno;
    }
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_port = htons(this->port);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, ip.c_str(), &this->serv_addr.sin_addr)
        <= 0) {
        cout<<"Invalid address/ Address not supported"<<endl;
        return errno;
    }

    if ((connect(this->client_fd, (struct sockaddr*)&this->serv_addr,
                   sizeof(this->serv_addr)))
        < 0) {
        cout<<"Connection Failed"<<endl;
        return errno;
    }
    return 0;
}

int TCP_Client::authorization(){
    string json_hello_msg = "{\"username\":\"" + username + "\"}";
    int status = send(this->client_fd, json_hello_msg.c_str(), json_hello_msg.size(), MSG_NOSIGNAL);
    if(status<0){
        cout<<"\n Authorization error!"<<endl;
        close(this->client_fd);
        return errno;
    }
    status = recv(this->client_fd, this->buffer, this->BUFFER_SIZE,MSG_NOSIGNAL);
    cout<<buffer<<endl;
    if(status < 0){
        cout<<"\n Authorization error!"<<endl;
        close(this->client_fd);
        return errno;
    }
    return 0;
}