from _thread import *
import os
import socket
import json
from typing import Dict


class User:
    username=''
    online = False
    telemetry_history=[]
    def __init__(self, username):
        self.username = username  
        self.telemetry_history=[] 
        self.online=False
    def __enter__(self):
        print(f'{self.username} online')
        self.online=True
        return self
    def __exit__(self, type, value, traceback):
        print(f'{self.username} offline')
        self.online=False
    def __str__(self):
        return f"username: {self.username}; elements of history:{len(self.telemetry_history)} {' online' if self.online else ''}"
             
user_dict:Dict[str,User]= dict()
HOST = "0.0.0.0"  
PORT = 15243  
echo_username = ''
def set_echo_username(username):
    global echo_username
    echo_username=username
commands ={
    'users': lambda arg: print(*user_dict.values(), sep='\n'),
    'history': lambda username: print(*user_dict[username].telemetry_history, sep='\n'),
    'echo': set_echo_username,
    'q': lambda arg:set_echo_username(''),
    'exit': lambda arg: os._exit(0),
    'help': lambda arg: print('allowed commands:\n\
        users (print list of users with status)\n\
        history <user> (print telemetry history of specific user)\n\
        echo <user> (print all new telemetry data from a specific user. To stop use \'q\' or \'echo\' (without arguments))\n\
        q (stop echo)\n\
        exit (shutdown server program)')
}
def threaded_cli():
    while True:
        text=input().split(' ',maxsplit=1)
        if(text[0]==''):
            continue
        if(not text[0] in commands):
            print('unknown command. try \'help\'')
            continue
        command = text[0]
        arg = text[1] if len(text)>1 else ''
        commands[command](arg)
        
def authorization(conn) -> User:
    data = conn.recv(1024)
    auth = json.loads(data)
    if not 'username' in auth:
        conn.sendall(b'"{message":"bad authorization request}"')
        return None
    username:str=auth['username']
    if not (username in user_dict):
        user_dict[username]=User(username)
    if user_dict[username].online == True:
        conn.sendall(b'"{message":"this user is already online}"')
        return None
    conn.sendall(b'"{message":"authorization OK}"')
    return user_dict[username]

def threaded_recv(conn,addr):
    with conn:
        user = authorization(conn)
        if user != None:
            with user: #correct online status
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    telem=json.loads(data)
                    user.telemetry_history.append(telem)
                    if echo_username == user.username:
                        print(telem)
    print(f'{addr[0]}:{addr[1]} disconnected')
def Main():
    print('try \'help\' to see allowed command')
    start_new_thread(threaded_cli, ())
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        while True:
            # establish connection with client
            conn, addr = s.accept()
    
            print(f'{addr[0]}:{addr[1]} connected')
            # Start a new thread
            start_new_thread(threaded_recv, (conn,addr))
        
if __name__ == '__main__':
    Main()