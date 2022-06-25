CC = g++
#CC = x86_64-w64-mingw32-g++

CFLAGS = -g -Wall

TARGET = main.exe

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

main.exe: main.o sha256.o miner.o util.o
	$(CC) $(CFLAGS) -o main main.o sha256.o miner.o util.o

main.o: main.cpp sha256.h miner.h util.h
	$(CC) $(CFLAGS) -c main.cpp

miner.o: miner.cpp sha256.h miner.h util.h
	$(CC) $(CFLAGS) -c miner.cpp

sha256.o: miner.cpp sha256.h
	$(CC) $(CFLAGS) -c sha256.cpp

util.o: miner.cpp util.h
	$(CC) $(CFLAGS) -c util.cpp