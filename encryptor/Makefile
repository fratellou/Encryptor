СС=gcc
CFLAGS=-Wall -Wextra -Werror

all:build

build: decryptors.o encryptor.o encryptors.o user.o
	$(CC) $(CFLAGS) decryptors.o encryptor.o encryptors.o user.o -o encryptor

decryptors.o: dec_head.h user_head.h enc_head.h decryptors.cpp user.cpp encryptors.cpp 
	$(CC) $(CFLAGS) -c decryptors.cpp

encryptor.o: encryptor.cpp user_head.h user.cpp
	$(CC) $(CFLAGS) -c encryptor.cpp

encryptors.o: enc_head.h user_head.h encryptors.cpp user.cpp
	$(CC) $(CFLAGS) -c encryptors.cpp

user.o: user_head.h enc_head.h user.cpp user.cpp encryptors.cpp 
	$(CC) $(CFLAGS) -c user.cpp

clean: 
	rm -rf *.o encryptor

rebuild:clean all