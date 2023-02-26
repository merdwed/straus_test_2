from _thread import *
import threading
import socket
import json

HOST = "0.0.0.0"  
PORT = 15243  
def threaded_recv(conn,addr):
    with conn:
        while True:
            data = conn.recv(1024)
            if not data:
                print(f'{addr[0]}:{addr[1]} disconnected')
                break
            print(f'{addr[0]}:{addr[1]} {data}')
            
def Main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        # a forever loop until client wants to exit
        while True:
        
            # establish connection with client
            conn, addr = s.accept()
    
            # lock acquired by client
            # print_lock.acquire()
            print(f'{addr[0]}:{addr[1]} connected')
            # Start a new thread
            start_new_thread(threaded_recv, (conn,addr))
        conn, addr = s.accept()
        
if __name__ == '__main__':
    Main()