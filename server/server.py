from _thread import *
import threading
import socket
import json
from typing import Dict


class User:
    username=''
    online = False
    telemetry_history=[]
    def __init__(self, username):
        self.username = username   
    def __enter__(self):
        print(f'{self.username} online')
        self.online=True
        return self
    def __exit__(self, type, value, traceback):
        print(f'{self.username} offline')
        self.online=False
             
user_dict:Dict[str,User]= dict()
HOST = "0.0.0.0"  
PORT = 15243  
def authorization(conn) -> User:
    data = conn.recv(1024)
    print(data)
    auth = json.loads(data)
    if not 'username' in auth:
        conn.sendall(b'"message":"bad authorization request"')
        return None
    username:str=auth['username']
    if not (username in user_dict):
        user_dict[username]=User(username)
    if user_dict[username].online == True:
        conn.sendall(b'"message":"this user is already online"')
        return None
    conn.sendall(b'"message":"authorization OK"')
    return user_dict[username]
    
def threaded_recv(conn,addr):
    with conn:
        user = authorization(conn)
        if user == None:
            return
        with user: #correct online status
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                telem=json.loads(data)
                user.telemetry_history.append(telem)
                print(f'{addr[0]}:{addr[1]} {telem}')
    print(f'{addr[0]}:{addr[1]} disconnected')
def Main():
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