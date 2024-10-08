CC = gcc
CFLAGS = -Wall -Iinclude

all: banking_management

banking_management: src/main.o src/account.o src/fileManagement.o
	$(CC) -o banking_management src/main.o src/account.o src/fileManagement.o

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

src/account.o: src/account.c
	$(CC) $(CFLAGS) -c src/account.c

src/fileManagement.o: src/fileManagement.c
	$(CC) $(CFLAGS) -c src/fileManagement.c

clean:
	rm -f src/*.o banking_management
