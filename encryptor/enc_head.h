#ifndef ENC_HEAD_H
#define ENC_HEAD_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void encrypt(string &filename, const string &password, const string &login);
bool is_Prime(const int &n);
uint64_t NOD(const uint64_t &a, const uint64_t &b);
uint64_t mod_p(const uint64_t &a, const uint64_t &x, const uint64_t &p);
void password_encrypt(string &password);
void login_encrypt(string &login);
string vig_cipher(string &word, const string &key, const string &alphabet);
void vigenere_encr(const string &login, const string &password,
                   string &filename);
string elgamal_cipher(uint64_t &p, uint64_t &g, uint64_t &a, string &message);
void atbash_encr(const string &login, const string &password, string &filename);
string atbash_cipher(const string &text);
void elgamal_encr(const string &login, const string &password,
                  string &filename);

#endif