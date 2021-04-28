import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 12345)
sock.bind(server_address)

sock.listen(1)

while True:
    connection, client_address = sock.accept()
    
    try:
        data = connection.recv(1024)
        print(' '.join([hex(ord(i))[2:] for i in str(data)[2:-1]]))
        connection.sendall(data)
            
    finally:
        connection.close()
