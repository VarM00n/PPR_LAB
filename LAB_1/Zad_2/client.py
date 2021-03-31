import socket
import sys
import os

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 12347)
sock.connect(server_address)

try:
    message = input("What you want to send - ")
    print(str(os.getpid()) + message)
    sock.sendall(str.encode(str(os.getpid()) + message))

finally:
    sock.close()
