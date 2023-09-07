#include "enc_head.h"
#include "user_head.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;

bool is_Prime(const int &n) //�������� ����� �� ��������
{

  int square_root = sqrt(n); //������������ ������ �����
  int toggle = 1;
  for (int i = 2; i <= square_root; i++) //�������� ����� �� 2 �� ����� �����
  {
    if (n % i == 0) //���� �������� ����� ������� �� ����� �� ���������
    {
      toggle = 0; //���������� ���� 0
      break;
    }
  }
  if (toggle)
    return true; //����������� true ��� �������� �����
  else
    return false; //����������� false � ���� ������
}

uint64_t NOD(const uint64_t &a, const uint64_t &b) {
  uint64_t r = a % b;
  if (r != 0) {
    NOD(b, r);
  } else {
    return b;
  }
  return 0;
}

uint64_t mod_p(const uint64_t &a, const uint64_t &x,
               const uint64_t &p) // ������� ��� ���������� � ������� �� ������
{
  uint64_t res = 1;
  for (uint64_t i = 1; i <= x; i++) {
    res = res * a;
    res = res % p;
  }
  return res;
}

string
atbash_cipher(const string &message) //�������� ����� ��� ����������� ��������
{
  string ciphered_text = ""; //������������� ���������
  for (char c : message) //������������ ������� ������
  {
    if (isalpha(c)) //���� ������ ������ � �������
    {
      if (isupper(c)) //���� ����� ���������
      {
        ciphered_text += char('Z' - (c - 'A')); //��������� ���������� �����
      } else //���� ����� ��������
      {
        ciphered_text += char('z' - (c - 'a')); //��������� ���������� �����
      }
    } else //����� ���� ������ �� ����������� ��������, �� ���������� � �����
           //��� ��������
    {
      ciphered_text += c;
    }
  }
  return ciphered_text; //����������� �������������� ������
}

void atbash_encr(string &login, string &password,
                 string &filename) //���������� �������� ����� ������� �����
{

  string new_file = "atb_encr_" + filename;
  add_file(login, password, new_file);
  new_file += ".txt";
  filename += ".txt";
  ofstream second_file; //����� ��� ������ �����
  second_file.open(new_file);

  ifstream first_file; //����� ��� ������ �����
  first_file.open(filename);

  string line;

  if (first_file.is_open() && second_file.is_open()) {
    while (getline(first_file, line)) {
      string word = atbash_cipher(line);
      second_file << word;
    }
    first_file.close();
    second_file.close();
  }
}

string elgamal_cipher(uint64_t &p, uint64_t &g, uint64_t &h,
                      string &message) //�������� ��� ������
{
  string encr_message;

  for (char i : message) //����������� ���������� ������
  {
    uint64_t m =
        (uint8_t)i; //�������������� ������� � �������� �� ������� ASCII
    uint64_t k = 2; // ��������� ����� �����, 1 < k < p-1 � ���(k, p-1) = 1
    while (NOD(k, p - 1) != 1) {
      k++;
    }
    uint64_t C1 = mod_p(g, k, p); // ���������� ������ ���������� ����� C
    uint64_t C2 =
        (mod_p(h, k, p) * m) % p; // ���������� ������ ���������� ����� C
    encr_message += to_string(C1) + " " + to_string(C2) + "\n";
  }
  return encr_message;
}

void elgamal_encr(
    string &login, string &password,
    string &filename) //���������� �������� ����� ������� ���-������
{

  string new_file = "elgam_encr_" + filename; //�������� ������ �����
  add_file(login, password, new_file);
  new_file += ".txt";
  filename += ".txt";
  ofstream second_file; //����� ��� ������ �����
  second_file.open(new_file);

  uint64_t p, g, a;

  while (true) //���� ����� p
  {
    cout << "Enter a simple number p: ";
    cin >> p;
    if (is_Prime(p) == true)
      break;
    else
      cout << "The entered number is incorrect." << endl;
  }
  second_file << p << " ";

  while (true) //���� ����� g
  {
    cout << "Enter a integer g (g < p and gcd(g, p) = 1): ";
    cin >> g;
    if (NOD(p, g) == 1 && g < p)
      break;
    else
      cout << "The entered number is incorrect." << endl;
  }

  while (true) {
    cout << "Enter a integer a (1 < a < p-1): ";
    cin >> a;
    if ((1 < a && a < (p - 1)) == 1)
      break;
    else
      cout << "The entered number is incorrect." << endl;
  }
  second_file << a << endl;

  uint64_t h = mod_p(g, a, p); // ���������� ��������� ����� h

  string line;
  ifstream app; //�������� ������ ��� ������ �����
  app.open(filename);
  if (app.is_open()) {
    while (getline(app, line)) {
      string word = elgamal_cipher(p, g, h, line); //������������� ������
      second_file << word;
    }
    second_file.close();
    app.close();
  }
}

string vig_cipher(string &word, const string &key,
                  const string &alphabet) //�������� ��������
{
  string new_key;
  int word_size = word.size();
  int key_size = key.size();
  if (word_size >=
      key_size) //���� ����� ��������� ����� ������, ���� ����� ����� �����
  {
    for (int i = 0; i < (word_size / key_size);
         i++) //���������� ����� ���������� �����. ���������� ���� �� �����
              //�����.
    {
      new_key = new_key + key;
    }
    for (int j = 0; j < (word_size % key_size);
         j++) //���������� ���������� ����� �� �����
    {
      new_key = new_key + key[j];
    }
  }

  else //����� ���� ���� ������� �����
  {
    for (int s = 0; s < word_size; s++) //����������� ���� �� ����� �����
    {
      new_key = new_key + key[s];
    }
  }

  vector<int> A;
  vector<int> B;
  int alph_size = alphabet.size();
  for (int k = 0; k < word_size; k++) {
    for (int n = 0; n < alph_size; n++) //���� ����������� ����
    {
      if (word[k] == alphabet[n]) {
        A.push_back(n);
      }

      if (new_key[k] == alphabet[n]) {
        B.push_back(n);
      }
    }
  }

  for (int u = 0; u < word_size; u++) {
    int e = ((A[u] - B[u]));
    if (e < 0)
      e += alph_size;
    word[u] = alphabet[e];
  }
  return word;
}

void vigenere_encr(
    string &login, string &password,
    string &filename) //���������� �������� ����� ������� ��������
{

  string new_file = "vig_encr_" + filename;
  add_file(login, password, new_file);
  new_file += ".txt";
  filename += ".txt";
  ofstream second_file; //����� ��� ������ �����
  second_file.open(new_file);

  string key_word;
  cout << "Enter a key word: ";
  cin >> key_word;
  second_file << key_word << endl;

  string alphabet =
      "abcdefghijklmnopqrstuvwxyz "
      "��������������������������������.,!<>:';][{}+=_-)(*&^%$#@!"
      "1234567890QWERTYUIOPLKJHGFDSAZXCVBNM��������������������������������";
  string line;

  ifstream app;
  app.open(filename);
  if (app.is_open()) {
    while (getline(app, line)) {
      string word = vig_cipher(line, key_word, alphabet);
      second_file << word;
    }
    second_file.close();
    app.close();
  }
}

void encrypt(string &filename, string &password, string &login) {
  string re_password;
  cout << "Re-enter the password: ";
  getline(cin, re_password);
  password_encrypt(re_password);
  if (password == re_password) {
    system("clear");
    if (users_files(login, password) == 1) {
      cout << " ________________________________________________________\n";
      cout << "|                       Encryption                       |\n";
      cout << "|________________________________________________________|\n\n";
      cout << "1. The Vigenere cipher\n";
      cout << "2. ElGamal encryption\n";
      cout << "3. Atbash cipher\n";
      cout << "4. Return\n";
      cout << "Enter the encryption number: ";
      string number_of_encryption;
      getline(cin, number_of_encryption);

      if (number_of_encryption == "1") {
        cout << "Enter the file number to encrypt: ";
        int number_of_file;
        cin >> number_of_file;
        ifstream stream;
        string line;
        stream.open("database.txt");
        if (stream.is_open()) {
          while (getline(stream, line)) {
            if (word_search(line, 1) == login &&
                word_search(line, 2) == password) {
              filename = word_search(line, number_of_file + 2);
              break;
            }
          }
        }
        stream.close();
        vigenere_encr(login, password, filename);
      }

      else if (number_of_encryption == "2") {
        cout << "Enter the file number to encrypt: ";
        int number_of_file;
        cin >> number_of_file;
        ifstream stream;
        string line;
        stream.open("database.txt");
        if (stream.is_open()) {
          while (getline(stream, line)) {
            if (word_search(line, 1) == login &&
                word_search(line, 2) == password) {
              filename = word_search(line, number_of_file + 2);
              break;
            }
          }
        }
        stream.close();
        elgamal_encr(login, password, filename);
      }

      else if (number_of_encryption == "3") {
        cout << "Enter the file number to encrypt: ";
        int number_of_file;
        cin >> number_of_file;
        ifstream stream;
        string line;
        stream.open("database.txt");
        if (stream.is_open()) {
          while (getline(stream, line)) {
            if (word_search(line, 1) == login &&
                word_search(line, 2) == password) {
              filename = word_search(line, number_of_file + 2);
              break;
            }
          }
        }
        stream.close();
        atbash_encr(login, password, filename);
      }

      else if (number_of_encryption == "4") {
        system("clear");
        cout << " ________________________________________________________\n";
        cout << "|                        Returning                       |\n";
        cout
            << "|________________________________________________________|\n\n";
        sleep(300);
        cout << "                        ";
        for (int i = 0; i < 10; i++) {
          cout << '.';
          sleep(200);
        }
      }

      else {
        cout << "Invalid input" << endl;
        sleep(2000);
      }
    }

    else {
      cout << "You don't have any files to encrypt. First create a file."
           << endl;
      sleep(2000);
    }
  } else {
    cout << "Wrong password!";
    sleep(2000);
  }
}

void password_encrypt(string &password) //������� �������� ������
{
  string encrypted_password;
  for (char c : password) {
    int encr_char = (int(c) + 10);
    encrypted_password.push_back(static_cast<char>(encr_char));
  }
  password = encrypted_password;
}

void login_encrypt(string &login) //������� �������� ������
{
  string encrypted_password;
  for (char c : login) {
    int encr_char = (int(c) - 10);
    encrypted_password.push_back(static_cast<char>(encr_char));
  }
  login = encrypted_password;
}