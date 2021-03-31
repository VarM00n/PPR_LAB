import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 12346)
sock.connect(server_address)

try:
    message = input("What you want to send - ")
    print(message)
    sock.sendall(str.encode(message))

finally:
    sock.close()