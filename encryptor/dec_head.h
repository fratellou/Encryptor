#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void decrypt(string& filename, string& login, string& password);	//Дешифрование
string vig_cipher_decr(string& word, string& key, string& alphabet);   //Дешифровка Виженера
void vigenere_decr(string& login, string& password, string& filename);    	//Построчная дешифровка файла методом Виженера
void elgamal_decr(string& login, string& password, string& filename);     //Построчная шифровка файла методом Эль-Гамаля
char elgamal_cipher_decr(uint64_t& p, uint64_t& a, uint64_t& C1, uint64_t& C2);  //Дешифровка Эль-Гамаля
void atbash_decr(string& login, string& password, string& filename);    	//Построчная дешифровка файла методом Атбаш
string atbash_cipher_decr_eng(string& ciphertext);    //Дешифрока Атбаш для английского алфавита
string atbash_cipher_decr_rus(string& ciphertext);  //Дешифровка Атбаш для русского алфавита
