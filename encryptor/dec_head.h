#ifndef DEC_HEAD_H
#define DEC_HEAD_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void decrypt(string &filename, string &login, string &password);
string vig_cipher_decr(string &word, const string &key, const string &alphabet);
void vigenere_decr(string &login, string &password, string &filename);
void elgamal_decr(string &login, string &password, string &filename);
char elgamal_cipher_decr(const uint64_t &p, const uint64_t &a,
                         const uint64_t &C1, const uint64_t &C2);
void atbash_decr(string &login, string &password, string &filename);
string atbash_cipher_decr(const string &ciphertext);

#endif