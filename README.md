# Encryptor

It is necessary to develop a program that should encrypt and decrypt the source data using one of the presented algorithms.
The program must perform the following basic actions:
- provide a procedure for verifying user data by logging in to the system;
- provide input of the source text from the keyboard or download data from a file;
- implement data encryption and demonstration of the results obtained;
- implement decryption (decryption) of data and demonstration of the results (console, file).

The program uses 3 encryption methods: Atbash, Vigener and El Gamal.

## Table of Contents

1. [The Atbash cipher](#the-atbash-cipher)
2. [The Vigener Cipher](#the-vigener-cipher)
3. [The El Gamal Cipher](#the-el-gamal-cipher)
4. [Program modules](#program-modules)

## The Atbash cipher

Encryption consists in replacing each letter of the source text with a letter of the alphabet that is "symmetrical" to it, that is, the first alphabet was replaced by the last and vice versa, the second letter by the penultimate and vice versa, etc. 

## The Vigener Cipher

Encryption happens like this. The key word is written under the letters of the encrypted text, repeating it many times. Then replace the letters of the source text with their sums with the letters of the key. When decrypting, you will have to perform subtraction instead of addition.

In the first row of the table, the alphabet can be arranged in a natural order or in an arbitrary order. The plaintext is written in a line without spaces, then to form the key we use the same plaintext with the addition of a random character to the beginning of the key, which both the recipient and the sender know. A pair of letters standing under each other in the plaintext and in the key (G and Q) indicated the number of the column and row, respectively, at the intersection of which the encrypted letter was located.

>Plaintext: GREENTEA
>
>Key: QGREENTE
>
>Ciphertext: WXVIRGXE

## The El Gamal Cipher

Participants in the information process choose a prime number p and an arbitrary integer q, which is the primitive root modulo p.
Side A generates the secret key k_a< p and calculates the public key: Y_a=q^(k_a) (mod p).

Side B selects the number k_b < p and uses it to encrypt the transmitted message M as follows: Y_b=q^(k_b) (mod p) and C=M⊕(Y_a^(k_b) (mod p))

The value M is a sequence of binary characters transmitted to the communication channel.

Side A, having received the message in the form of Y_b and C, restores it: M=(Y_b^(k_a) (mod p)) ⨁ C. 

In network messaging, sender A uses the public key of recipient B for encryption, since only B should be able to decrypt messages addressed to him. B must encrypt the response messages using the public key of A.

## Program modules

`Enc_head.h` is a header file that contains declarations of all functions for encrypting text using different methods;

`Dec_head.h` is a header file that contains declarations of all functions for decrypting text using different methods; 

`User_head.h` is a header file that contains declarations of all auxiliary functions for working with files and the user;

`Encryptors.cpp ` – the file contains the definition of the functions declared in the header file Enc_head.h:

- `void encrypt(string& filename, string& password, string& login)` -Encryption;

- `bool is_Prime(const int& n)` - Checking the number for simplicity; 

- `int isalpha_ru(const char& c)` - Checking whether a letter belongs to the Russian alphabet; 

- `uint64_t NOD(const uint64_t& a, const uint64_t& b)` - Euclid's algorithm for finding nodes of two numbers;

- `uint64_t mod_p(const uint64_t& a, const uint64_t& x, const uint64_t& p)` - Function for exponentiation modulo;

- `void password_encrypt(string& password)` - Password encryption function;

- `void login_encrypt(string& login)` - Login encryption function;

- `string vig_cipher(string& word, string& key, string& alphabet)` - Vigener encryption;

- `void vigenere_encr(string& login, string& password, string& filename)` -Line-by-line file encryption using the Vigener method;

- `string elgamal_cipher(uint64_t& p, uint64_t& g, uint64_t& a, string& message)` - Line-by-line file encryption using the El Gamal method;

- `void elgamal_encr(string& login, string& password, string& filename)` -El Gamal's encryption;

- `void atbash_encr(string& login, string& password, string& filename)` - Line-by-line file encryption using the Atbash method;

- `string atbash_cipher_rus(string& text)` - Atbash encryption for the Russian alphabet;

- `string atbash_cipher_eng(string& text)` - Atbash encryption for the English alphabet;

`Decryptors.cpp ` – the file contains the definition of the functions declared in the dec_head.h header file:

- `void decrypt(string& filename, string& login, string& password)` – Decryption;

- `string vig_cipher_decr(string& word, string& key, string& alphabet)` - Decryption of the Vigener;

- `void vigenere_decr(string& login, string& password, string& filename)` - Line-by-line decryption of the file by the Vigener method;

- `void elgamal_decr(string& login, string& password, string& filename)` - Line-by-line file encryption using the El Gamal method;

- `char elgamal_cipher_decr(uint64_t& p, uint64_t& a, uint64_t& C1, uint64_t& C2)` - Decryption of El Gamal;

- `void atbash_decr(string& login, string& password, string& filename)` - Line-by-line decryption of the file using the Atbash method;

- `string atbash_cipher_decr_eng(string& ciphertext)` - Atbash decryption for the English alphabet;

- `string atbash_cipher_decr_rus(string& ciphertext)` - Decryption of Atbash for the Russian alphabet;

`user.cpp ` – the file contains the definition of the functions declared in the header file user_head.h:

- `string word_search(string& line, const uint64_t& number_of_word)` is a function that returns the word required in order from a string;

- `bool username_check(string& login)` is a function that checks if the name is occupied when creating a new user;

- `void password_check(string& password, string& login)` - Password verification function;

- `void data(string& login, string& password)` - Creating a new user or logging into an existing account;

- `int users_files(string& login, string& password)` - Selecting a file from the user's existing ones or creating a new file;

- `void add_file(string& login, string& password, string& filename)` - Adding a file to the user's file list;

- `void create_file(string& login, string& password, string& filename)` - The function of creating a new file;

- `bool file_check(string& filename)` is a function that checks if a file with the same name exists;

- `void printFile(string& login, string& password)` - File output function;

- `void exit()` - Exit the program;

`encryptor.cpp ` - Contains the main function, which represents the functionality for entering a password, displaying the cipher selection menu, with the corresponding function call, and entering the necessary data.

>
>fratellou, 2023