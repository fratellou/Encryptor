#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void decrypt(string& filename, string& login, string& password);	//������������
string vig_cipher_decr(string& word, string& key, string& alphabet);   //���������� ��������
void vigenere_decr(string& login, string& password, string& filename);    	//���������� ���������� ����� ������� ��������
void elgamal_decr(string& login, string& password, string& filename);     //���������� �������� ����� ������� ���-������
char elgamal_cipher_decr(uint64_t& p, uint64_t& a, uint64_t& C1, uint64_t& C2);  //���������� ���-������
void atbash_decr(string& login, string& password, string& filename);    	//���������� ���������� ����� ������� �����
string atbash_cipher_decr_eng(string& ciphertext);    //��������� ����� ��� ����������� ��������
string atbash_cipher_decr_rus(string& ciphertext);  //���������� ����� ��� �������� ��������
