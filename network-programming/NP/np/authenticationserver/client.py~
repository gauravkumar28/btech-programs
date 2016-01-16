import socket
import sys

sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address=('localhost',12116)
sock.connect(server_address)
print sock.recv(100000)


sock.close()

