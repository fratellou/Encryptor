#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void encrypt(string& filename, string& password, string& login);	//Шифрование
bool is_Prime(const int& n);    //Проверка числа на простоту 
int isalpha_ru(const char& c);  //Проверка, принадлежит ли буква русскому алфавиту 
uint64_t NOD(const uint64_t& a, const uint64_t& b);   // Алгоритм Евклида для нахождения НОД двух чисел
uint64_t mod_p(const uint64_t& a, const uint64_t& x, const uint64_t& p);      // Функция для возведения в степень по модулю
void password_encrypt(string& password);	//Функция шифровки пароля
void login_encrypt(string& login);       //Функция шифровки логина
string vig_cipher(string& word, string& key, string& alphabet);	 //Шифровка Виженера
void vigenere_encr(string& login, string& password, string& filename);	//Построчная шифровка файла методом Виженера
string elgamal_cipher(uint64_t& p, uint64_t& g, uint64_t& a, string& message);	  //Построчная шифровка файла методом Эль-Гамаля
void elgamal_encr(string& login, string& password, string& filename);	//Шифровка эль гамаля
void atbash_encr(string& login, string& password, string& filename);    	//Построчная шифровка файла методом Атбаш
string atbash_cipher_rus(string& text); //Шифровка Атбаш для русского алфавита
string atbash_cipher_eng(string& text);  //Шифровка Атбаш для английского алфавита