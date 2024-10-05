CC = gcc
CFLAGS = -Wall -Wextra

TARGET = Webserver

All: Util Http Server
	$(CC) $(CFLAGS) Main.c *.o -o $(TARGET)
	rm *.o

Util: Source/Util/*.c
	$(CC) -c $(CFLAGS) Source/Util/*.c 

Http: Source/Http/*.c
	$(CC) -c $(CFLAGS) Source/Http/*.c 

Server: Source/Server/*.c
	$(CC) -c $(CFLAGS) Source/Server/*.c
