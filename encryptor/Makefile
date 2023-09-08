CFLAGS=-Wall -Wextra -Werror

all:build

build: decryptors.o encryptor.o encryptors.o user.o
	g++ $(CFLAGS) decryptors.o encryptor.o encryptors.o user.o -o encryptor

decryptors.o: dec_head.h user_head.h enc_head.h decryptors.cpp user.cpp encryptors.cpp 
	g++ $(CFLAGS) -c decryptors.cpp

encryptor.o: encryptor.cpp user_head.h user.cpp
	g++ $(CFLAGS) -c encryptor.cpp

encryptors.o: enc_head.h user_head.h encryptors.cpp user.cpp
	g++ $(CFLAGS) -c encryptors.cpp

user.o: user_head.h enc_head.h user.cpp user.cpp encryptors.cpp 
	g++ $(CFLAGS) -c user.cpp

clean: 
	rm -rf *.o encryptor

rebuild:clean all