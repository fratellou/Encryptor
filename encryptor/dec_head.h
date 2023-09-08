#ifndef DEC_HEAD_H
#define DEC_HEAD_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string atbash_cipher_decr(const string &ciphertext);
void atbash_decr(const string &login, const string &password, string &filename);
char elgamal_cipher_decr(const uint64_t &p, const uint64_t &a,
                         const uint64_t &C1, const uint64_t &C2);
void elgamal_decr(const string &login, const string &password,
                  string &filename);
string vig_cipher_decr(string &word, const string &key, const string &alphabet);
void vigenere_decr(const string &login, const string &password,
                   string &filename);
void decrypt(string &filename, const string &login, const string &password);

#endif