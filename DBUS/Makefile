
all: client server

client: client.cpp
	gcc -ldbus-1 -I/usr/include/dbus-1.0 -o $@ $< 

server: server.cpp
	gcc  -ldbus-1 -I/usr/include/dbus-1.0  -o $@ $< 

clean:
	rm client server
