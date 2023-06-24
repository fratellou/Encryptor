#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include "user_head.h"
#include "enc_head.h"
#include "dec_head.h"
using namespace std;

string word_search(string& line, const uint64_t& number_of_word);     //Функция, которая возвращает необходимое по порядку слово из строки
bool username_check(string& login);       //Функция, которая проверяет, занято ли имя при создании нового пользователя
void password_check(string& password, string& login);    //Функция проверки пароля
void data(string& login, string& password);  //Создание нового пользователя или вход в аккаунт существующего
int users_files(string& login, string& password);	  //Выбор файла из имеющихся у пользователя или создание нового файла
void add_file(string& login, string& password, string& filename);    //Добавление файла к списку файлов пользователя
void create_file(string& login, string& password, string& filename);		//Функция создания нового файла
bool file_check(string& filename);  //Функция, которая проверяет, существует ли файл с таким именем
void printFile(string& login, string& password);		//Функция вывода файла
void exit();     //Выход из программы