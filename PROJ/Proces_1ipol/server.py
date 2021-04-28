import socket
import sys
import xmlrpc.client

#sock.listen(1)

def sned(msg):
    sock1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address1 = ('localhost', 12343)
    sock1.connect(server_address1)

    try:
        sock1.send(msg)

    finally:
        sock1.close()

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 12344)
sock.bind(server_address)

while True:
    #connection, client_address = sock.accept()
    
    try:
        data = sock.recv(1024)
        data = data 
        print(data)
        sned(data)
        #connection.sendall(data + ' echoed from server')
            
    finally:
        pass
