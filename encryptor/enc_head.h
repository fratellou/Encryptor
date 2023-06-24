#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void encrypt(string& filename, string& password, string& login);	//����������
bool is_Prime(const int& n);    //�������� ����� �� �������� 
int isalpha_ru(const char& c);  //��������, ����������� �� ����� �������� �������� 
uint64_t NOD(const uint64_t& a, const uint64_t& b);   // �������� ������� ��� ���������� ��� ���� �����
uint64_t mod_p(const uint64_t& a, const uint64_t& x, const uint64_t& p);      // ������� ��� ���������� � ������� �� ������
void password_encrypt(string& password);	//������� �������� ������
void login_encrypt(string& login);       //������� �������� ������
string vig_cipher(string& word, string& key, string& alphabet);	 //�������� ��������
void vigenere_encr(string& login, string& password, string& filename);	//���������� �������� ����� ������� ��������
string elgamal_cipher(uint64_t& p, uint64_t& g, uint64_t& a, string& message);	  //���������� �������� ����� ������� ���-������
void elgamal_encr(string& login, string& password, string& filename);	//�������� ��� ������
void atbash_encr(string& login, string& password, string& filename);    	//���������� �������� ����� ������� �����
string atbash_cipher_rus(string& text); //�������� ����� ��� �������� ��������
string atbash_cipher_eng(string& text);  //�������� ����� ��� ����������� ��������