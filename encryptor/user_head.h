#ifndef USER_HEAD_H
#define USER_HEAD_H

#include "dec_head.h"
#include "enc_head.h"
#include "user_head.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

string word_search(const string &line, const uint64_t &number_of_word);
bool username_check(string &login);
void password_check(string &password, const string &login);
void data(string &login, string &password);
int users_files(const string &login, const string &password);
void add_file(const string &login, const string &password,
              const string &filename);
void create_file(const string &login, const string &password, string &filename);
bool file_check(const string &filename);
void printFile(const string &login, const string &password);
void exit();

#endif