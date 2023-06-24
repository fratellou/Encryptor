#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include "user_head.h"
#include "enc_head.h"
#include "dec_head.h"
using namespace std;

string word_search(string& line, const uint64_t& number_of_word);     //�������, ������� ���������� ����������� �� ������� ����� �� ������
bool username_check(string& login);       //�������, ������� ���������, ������ �� ��� ��� �������� ������ ������������
void password_check(string& password, string& login);    //������� �������� ������
void data(string& login, string& password);  //�������� ������ ������������ ��� ���� � ������� �������������
int users_files(string& login, string& password);	  //����� ����� �� ��������� � ������������ ��� �������� ������ �����
void add_file(string& login, string& password, string& filename);    //���������� ����� � ������ ������ ������������
void create_file(string& login, string& password, string& filename);		//������� �������� ������ �����
bool file_check(string& filename);  //�������, ������� ���������, ���������� �� ���� � ����� ������
void printFile(string& login, string& password);		//������� ������ �����
void exit();     //����� �� ���������