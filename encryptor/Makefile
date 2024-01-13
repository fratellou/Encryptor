CFLAGS=-Wall -Wextra -Werror

all:build

build: decryptors.o encryptor.o encryptors.o user.o
	g++ $(CFLAGS) decryptors.o encryptor.o encryptors.o user.o -o encryptor

decryptors.o: 
	g++ $(CFLAGS) -c decryptors.cpp

encryptor.o: 
	g++ $(CFLAGS) -c encryptor.cpp

encryptors.o: 
	g++ $(CFLAGS) -c encryptors.cpp

user.o: 
	g++ $(CFLAGS) -c user.cpp

clean: 
	rm -rf *.o encryptor

rebuild:clean all