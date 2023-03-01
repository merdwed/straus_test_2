import socket
import json
import time
HOST = "127.0.0.1" 
PORT = 15243  
send_text=b"Hello, world"
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while (True):
        time.sleep(1)
        send_text= json.dumps(
            {
                'time':time.time(), 
                'pose': {'position':[0,0,0], 'orientation':[0,0,0,1]},
                'pressed':['w'],
            }
        ).encode()
        s.sendall(send_text)
        