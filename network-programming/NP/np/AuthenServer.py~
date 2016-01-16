import socket
import sys
sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address=('localhost',12116)
sock.bind(server_address)
sock.listen(1)
while True:
	connection,client_address=sock.accept()
	try:
                    fo= open("Third.html","r")
                    htmlText=fo.read();
                    print htmlText
                    fo.close()
               
                    fim2 =open("L.jpg","r")
                    image2=fim2.read()
                    fim2.close()
		    print>>sys.stderr,'connection from', client_address
		    data=connection.recv(1000);
		    print>>sys.stderr,' recieved %s' % data
		    connection.sendall("HTTP/1.1 200 OK\r\nContent-length: "+str(len(htmlText))+"\r\n\r\n"+htmlText)
                    
                    connection.sendall("HTTP/1.1 200 OK\r\nContent-type: image/jpeg\r\n\r\n"+image2)
	finally:
		    connection.close()
        connection,client_address=sock.accept()
        try:
                    fim1 =open("a.jpg","r")
                    image1=fim1.read()
                    fim1.close()
                    print>>sys.stderr,'connection from', client_address
                    data=connection.recv(1000);
		    print>>sys.stderr,' recieved %s' % data
                    connection.sendall("HTTP/1.1 200 OK\r\nContent-type: image/jpeg\r\n\r\n"+image1)
        finally:
		    connection.close()
        connection,client_address=sock.accept()
        try:
                    fim2 =open("L.jpg","r")
                    image2=fim2.read()
                    fim2.close()
                    print>>sys.stderr,'connection from', client_address
                    data=connection.recv(1000);
		    print>>sys.stderr,' recieved %s' % data
                    connection.sendall("HTTP/1.1 200 OK\r\nContent-type: image/jpeg\r\n\r\n"+image2)
        finally:
		    connection.close()

