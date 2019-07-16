import socket

client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
client.connect("/tmp/test")

client.send(b"hello_world")
client.recv(1024)
