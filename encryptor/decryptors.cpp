#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> 
#include "windows.h"
#include "dec_head.h"
#include "user_head.h"
#include "enc_head.h"
using namespace std;


string atbash_cipher_decr_eng(string& message)        //��������� ����� ��� ����������� ��������
{
    string text = "";     //�������������� ���������
    for (char c : message)      //������������ ������� ������
    {
        if (isalpha(c))     //���� ������ ������ � �������
        {
            if (isupper(c)) //���� ����� ���������
            {
                text += char('Z' - (c - 'A'));  //��������� ���������� �����
            }
            else        //���� ����� �������� 
            {
                text += char('z' - (c - 'a'));  //��������� ���������� �����
            }
        }
        else    //����� ���� ������ �� ����������� ��������, �� ���������� � ����� ��� ���������� 
        {
            text += c;
        }
    }
    return text;   //����������� ��������������� ������
}

string atbash_cipher_decr_rus(string& message)        //���������� ����� ��� �������� ��������
{
    string ciphered_text = "";     //�������������� ���������
    for (char c : message)      //������������ ������� ������
    {
        if (isalpha_ru(c))     //���� ������ ������ � �������
        {
            if (isalpha_ru(c) == 1) //���� ����� ��������� � ����������� �������� ��������
            {
                ciphered_text += char('�' - (c - '�'));  //��������� ���������� �����
            }
            else if (isalpha_ru(c) == 2)   //���� ����� �������� � ����������� �������� ��������
            {
                ciphered_text += char('�' - (c - '�'));  //��������� ���������� �����
            }
            else {   //����� ������ �� ����������� �������� �������� � ���������� � ����� ��� �������� 
                ciphered_text += c;
            }
        }
        else    //����� ���� ������ �� ����������� ��������, �� ���������� � ����� ��� �������� 
        {
            ciphered_text += c;
        }
    }
    return ciphered_text;   //����������� �������������� ������
}

void atbash_decr(string& login, string& password, string& filename)    	//���������� ���������� ����� ������� �����
{

    cout << "Alphabet: 1.Eng 2.Ru" << endl;
    cout << "Enter the alphabet number: ";
    string alph_num;
    cin >> alph_num;
    while (true)
    {
        if (alph_num == "1")
        {
            string new_file = filename + "_decrypted";
            add_file(login, password, new_file);
            new_file += ".txt";
            filename += ".txt";
            ofstream second_file;    //����� ��� ������ �����
            second_file.open(new_file);

            ifstream first_file;        //����� ��� ������ �����
            first_file.open(filename);

            string line;

            if (first_file.is_open() && second_file.is_open())
            {
                while (getline(first_file, line))
                {
                    string word = atbash_cipher_decr_eng(line);
                    second_file << word;
                }
                first_file.close();
                second_file.close();
            }
            break;
        }
        else if (alph_num == "2")
        {
            string new_file = filename + "_decrypted";
            add_file(login, password, new_file);
            new_file += ".txt";
            filename += ".txt";
            ofstream second_file;    //����� ��� ������ �����
            second_file.open(new_file);

            ifstream first_file;        //����� ��� ������ �����
            first_file.open(filename);

            string line;

            if (first_file.is_open() && second_file.is_open())
            {
                while (getline(first_file, line))
                {
                    string word = atbash_cipher_decr_rus(line);
                    second_file << word;
                }
                first_file.close();
                second_file.close();
            }
            break;
        }
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
}


char elgamal_cipher_decr(uint64_t& p, uint64_t& a, uint64_t& C1, uint64_t& C2)  //���������� ���-������
{
    uint64_t M = mod_p(C1, p - 1 - a, p);
    M *= C2;
    M %= p;
    char letter = M;
    return letter;
}

void elgamal_decr(string& login, string& password, string& filename)     //���������� �������� ����� ������� ���-������
{

    string new_file = filename + "_decrypted";     //�������� ������ �����
    add_file(login, password, new_file);
    new_file += ".txt";
    filename += ".txt";
    ofstream second_file;    //����� ��� ������ �����
    second_file.open(new_file);

    string line;
    fstream app;       //�������� ������ ��� ������ �����
    string keys;
    
    app.open(filename);
    if (app.is_open())
    {
        getline(app, keys);

        string p_str = word_search(keys, 1);
        string a_str = word_search(keys, 2);

        char* end;
        uint64_t p = strtoull(p_str.c_str(), &end, 10);
        uint64_t a = strtoull(a_str.c_str(), &end, 10);



        while (getline(app, line))
        {
            if (line != keys)
            {
                string c1_str = word_search(line, 1);
                string c2_str = word_search(line, 2);
                
                uint64_t C1 = strtoull(c1_str.c_str(), &end, 10);
                uint64_t C2 = strtoull(c2_str.c_str(), &end, 10);
                
                char word = elgamal_cipher_decr(p, a, C1, C2);        //������������� ������
                second_file << word;
            }
        }
        second_file.close();
        app.close();
    }
    users_files(login, password);
}

string vig_cipher_decr(string& word, string& key, string& alphabet)   //���������� ��������
{
    string new_key;   //������ ������������ ����� �� ����� �����
    if (word.size() >= key.size())      //���� ����� ��������� ����� ������, ���� ����� ����� �����
    {
        for (int i = 0; i < (word.size() / key.size()); i++)     //���������� ����� ���������� �����. ���������� ���� �� ����� �����.
        {
            new_key = new_key + key;
        }
        for (int j = 0; j < (word.size() % key.size()); j++)     //���������� ���������� ����� �� �����
        {
            new_key = new_key + key[j];
        }
    }

    else  //����� ���� ���� ������� �����
    {
        for (int s = 0; s < word.size(); s++)       //����������� ���� �� ����� �����
        {
            new_key = new_key + key[s];
        }
    }

    vector<int> A;
    vector<int> B;
    for (int k = 0; k < word.size(); k++)
    {
        for (int n = 0; n < alphabet.size(); n++)   //���� ����������� ����
        {
            if (word[k] == alphabet[n])
            {
                A.push_back(n);
            }

            if (new_key[k] == alphabet[n])
            {
                B.push_back(n);
            }
        }
    }

    int e = 0; //��� ����� ������� ��������. ����� ��� ���������� ���������� ���� ����, ��������� ��� �� �����, ������� � ������� ������
    for (int u = 0; u < word.size(); u++)
    {
        e = ((A[u] + B[u]) % alphabet.size());
        word[u] = alphabet[e];
    }
    return word;
}


void vigenere_decr(string& login, string& password, string& filename)    	//���������� ���������� ����� ������� ��������
{

    string new_file = filename + "_decrypted";
    add_file(login, password, new_file);
    new_file += ".txt";
    filename += ".txt";
    ofstream second_file;    //����� ��� ������ � ����
    second_file.open(new_file);

    ifstream first_file;     //����� ��� ������ �����
    first_file.open(filename);
    string key_word;    //�������� �����, ������� ��������� �� ������ ������ �������������� �����
    getline(first_file, key_word);

    string alphabet = "abcdefghijklmnopqrstuvwxyz ��������������������������������.,!<>:';][{}+=_-)(*&^%$#@!1234567890QWERTYUIOPLKJHGFDSAZXCVBNM��������������������������������";
    string line;

    
    if (first_file.is_open())
    {
        while (getline(first_file, line))
        {
            if (line != key_word)
            {
                string word = vig_cipher_decr(line, key_word, alphabet);
                second_file << word;
            }
        }
        second_file.close();
        first_file.close();
    }
    users_files(login, password);
}

void decrypt(string& filename, string& login, string& password) 
{
    string re_password;
    cout << "Re-enter the password: ";
    getline(cin, re_password);
    password_encrypt(re_password);
    if (password == re_password)
    {
        system("cls");
        if (users_files(login, password) == 1)
        {
            cout << " ________________________________________________________\n";
            cout << "|                       Decryption                       |\n";
            cout << "|________________________________________________________|\n\n";
            cout << "1. The Vigenere cipher\n";
            cout << "2. ElGamal encryption\n";
            cout << "3. Atbash cipher\n";
            cout << "4. Return\n";
            cout << "Enter the decryption number: ";
            string number_of_decryption;
            getline(cin, number_of_decryption);

            if (number_of_decryption == "1")
            {
                cout << "Enter the file number to decrypt: ";
                int number_of_file;
                cin >> number_of_file;
                ifstream stream;
                string line;
                stream.open("database.txt");
                if (stream.is_open())
                {
                    while (getline(stream, line))
                    {
                        if (word_search(line, 1) == login && word_search(line, 2) == password)
                        {
                            filename = word_search(line, number_of_file + 2);
                            break;
                        }
                    }
                }
                stream.close();
                vigenere_decr(login, password, filename);
            }

            else if (number_of_decryption == "2")
            {
                cout << "Enter the file number to decrypt: ";
                int number_of_file;
                cin >> number_of_file;
                ifstream stream;
                string line;
                stream.open("database.txt");
                if (stream.is_open())
                {
                    while (getline(stream, line))
                    {
                        if (word_search(line, 1) == login && word_search(line, 2) == password)
                        {
                            filename = word_search(line, number_of_file + 2);
                            break;
                        }
                    }
                }
                stream.close();
                elgamal_decr(login, password, filename);
            }

            else if (number_of_decryption == "3")
            {
                cout << "Enter the file number to decrypt: ";
                int number_of_file;
                cin >> number_of_file;
                ifstream stream;
                string line;
                stream.open("database.txt");
                if (stream.is_open())
                {
                    while (getline(stream, line))
                    {
                        if (word_search(line, 1) == login && word_search(line, 2) == password)
                        {
                            filename = word_search(line, number_of_file + 2);
                            break;
                        }
                    }
                }
                stream.close();
                atbash_decr(login, password, filename);
            }

            else if (number_of_decryption == "4")
            {
                system("cls");
                cout << " ________________________________________________________\n";
                cout << "|                        Returning                       |\n";
                cout << "|________________________________________________________|\n\n";
                Sleep(300);
                cout << "                        ";
                for (int i = 0; i < 10; i++)
                {
                    cout << '.';
                    Sleep(200);
                }
            }

            
        }

        else
        {
            cout << "You don't have any files to decrypt. First create a file." << endl;
            Sleep(2000);
        }
    }
    else
    {
        cout << "Wrong password!" << endl;
        Sleep(2000);
    }
}