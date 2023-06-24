#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "windows.h"
#include "enc_head.h"
#include "user_head.h"
using namespace std;

int isalpha_ru(const char& c)  //Проверка, принадлежит ли буква русскому алфавиту 
{
    if ((uint8_t)c > 191 && (uint8_t)c < 224) return 1;  //Возвращение 1, если буква находится в диапазоне заглавных букв
    else if ((uint8_t)c > 223 && (uint8_t)c <= 255) return 2; //Возвращение 2, если буква находится в диапазоне строчных букв
    else return 0;       //Возвращение 0, если буква не входит в алфавит русских букв
}

bool is_Prime(const int& n)    //Проверка числа на простоту 
{

    int square_root = sqrt(n);  //Квадратичный корень числа
    int toggle = 1;
    for (int i = 2; i <= square_root; i++)      //Проверка чисел от 2 до корня числа
    {
        if (n % i == 0)     //Если исходное число делится на число из диапазона
        {
            toggle = 0;     //Переменная флаг 0
            break;
        }
    }
    if (toggle)
        return true;        //Возвращение true при простоте числа
    else
        return false;   //Возвращение false в ином случае
}

uint64_t NOD(const uint64_t& a, const uint64_t& b)   // Алгоритм Евклида для нахождения НОД двух чисел
{
    uint64_t r = a % b;
    uint64_t k = a / b;
    if (r != 0)
    {
        NOD(b, r);      //Рекурсивное вычисление по алгоритму Евклида для измененных переменных
    }
    else    //Иначе найден НОД
    {
        return b;
    }
}

uint64_t mod_p(const uint64_t& a, const uint64_t& x, const uint64_t& p)      // Функция для возведения в степень по модулю
{
    uint64_t res = 1;
    for (uint64_t i = 1; i <= x; i++)
    {
        res = res * a;
        res = res % p;
    }
    return res;
}

string atbash_cipher_eng(string& message)        //Шифровка Атбаш для английского алфавита
{
    string ciphered_text = "";     //Зашифрованное сообщение
    for (char c : message)      //Посимвольный перебор текста
    {
        if (isalpha(c))     //Если символ входит в алфавит
        {
            if (isupper(c)) //Если буква заглавная
            {
                ciphered_text += char('Z' - (c - 'A'));  //Вычисляем зеркальную букву
            }
            else        //Если буква строчная 
            {
                ciphered_text += char('z' - (c - 'a'));  //Вычисляем зеркальную букву
            }
        }
        else    //Иначе если символ не принадлежит алфавиту, то добавление в текст без шифровки 
        {
            ciphered_text += c;
        }
    }
    return ciphered_text;   //Возвращение зашифрованного текста
}


string atbash_cipher_rus(string& message)        //Шифровка Атбаш для русского алфавита
{
    string ciphered_text = "";     //Зашифрованное сообщение
    for (char c : message)      //Посимвольный перебор текста
    {
        int result = isalpha_ru(c);
        if (result != 0)     //Если символ входит в алфавит
        {
            if (result == 1) //Если буква заглавная и принадлежит русскому алфавиту
            {
                ciphered_text += char('Я' - (c - 'А'));  //Вычисляем зеркальную букву
            }
            else if (result == 2)   //Если буква строчная и принадлежит русскому алфавиту
            {
                ciphered_text += char('я' - (c - 'а'));  //Вычисляем зеркальную букву
            }
        }
        else    //Иначе если символ не принадлежит алфавиту, то добавление в текст без шифровки 
        {
            ciphered_text += c;
        }
    }
    return ciphered_text;   //Возвращение зашифрованного текста
}

void atbash_encr(string& login, string& password, string& filename)    	//Построчная шифровка файла методом Атбаш
{
    string alph_num;
    cout << "Alphabet: 1.Eng 2.Ru" << endl;
    cout << "Enter the alphabet number: ";
    cin >> alph_num;
    do
    {
        if (alph_num == "1")
        {
            string new_file = "atb_encr_" + filename;
            add_file(login, password, new_file);
            new_file += ".txt";
            filename += ".txt";
            ofstream second_file;    //Поток для записи файла
            second_file.open(new_file);

            ifstream first_file;        //Поток для чтения файла
            first_file.open(filename);

            string line;

            if (first_file.is_open() && second_file.is_open())
            {
                while (getline(first_file, line))
                {
                    string word = atbash_cipher_eng(line);
                    second_file << word;
                }
                first_file.close();
                second_file.close();
            }
            break;
        }
        else if (alph_num == "2")
        {
            string new_file = "atb_encr_" + filename;
            add_file(login, password, new_file);
            new_file += ".txt";
            filename += ".txt";
            ofstream second_file;    //Поток для записи файла
            second_file.open(new_file);

            ifstream first_file;        //Поток для чтения файла
            first_file.open(filename);

            string line;

            if (first_file.is_open() && second_file.is_open())
            {
                while (getline(first_file, line))
                {
                    string word = atbash_cipher_rus(line);
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
    } while (true);
}

string elgamal_cipher(uint64_t& p, uint64_t& g, uint64_t& h, string& message)    //Шифровка эль гамаля
{
    string encr_message;

    for (char i : message)  //Побуквенное шифрование строки
    {
        uint64_t m = (uint8_t)i;     //Преобразование символа в значение по таблице ASCII
        uint64_t k = 2;  // Случайное целое число, 1 < k < p-1 и НОД(k, p-1) = 1
        while (NOD(k, p - 1) != 1)
        {
            k++;
        }
        uint64_t C1 = mod_p(g, k, p); // вычисление первой координаты точки C
        uint64_t C2 = (mod_p(h, k, p) * m) % p; // вычисление второй координаты точки C
        encr_message += to_string(C1) + " " + to_string(C2) + "\n";
    }
    return encr_message;
}

void elgamal_encr(string& login, string& password, string& filename)     //Построчная шифровка файла методом Эль-Гамаля
{

    string new_file = "elgam_encr_" + filename;     //Создание нового файла
    add_file(login, password, new_file);
    new_file += ".txt";
    filename += ".txt";
    ofstream second_file;    //Поток для записи файла
    second_file.open(new_file);


    uint64_t p, g, a;

    while (true)        //Ввод числа p
    {
        cout << "Enter a simple number p: ";
        cin >> p;
        if (is_Prime(p) == true) break;
        else cout << "The entered number is incorrect." << endl;
    }
    second_file << p << " ";

    while (true)        //Ввод числа g
    {
        cout << "Enter a integer g (g < p and gcd(g, p) = 1): ";
        cin >> g;
        if (NOD(p, g) == 1 && g < p) break;
        else cout << "The entered number is incorrect." << endl;
    }

    while (true)    //Ввод числа a
    {
        cout << "Enter a integer a (1 < a < p-1): ";
        cin >> a;
        if (1 < a && a < p - 1 == 1) break;
        else cout << "The entered number is incorrect." << endl;
    }
    second_file << a << endl;

    uint64_t h = mod_p(g, a, p);     // вычисление открытого ключа h

    string line;
    ifstream app;       //Открытие потока для чтения файла
    app.open(filename);
    if (app.is_open())
    {
        while (getline(app, line))  
        {
            string word = elgamal_cipher(p, g, h, line);        //Зашифрованная строка
            second_file << word;
        }
        second_file.close();
        app.close();
    }

}


string vig_cipher(string& word, string& key, string& alphabet)   //Шифровка Виженера
{
    string new_key;   //Строка растягивания ключа по длине слова
    if (word.size() >= key.size())      //Если длина вводимого слова больше, либо равна длине ключа
    {
        for (int i = 0; i < (word.size() / key.size()); i++)     //Записываем целое количество ключа. Растягивая ключ по длине слова.
        {
            new_key = new_key + key;
        }
        for (int j = 0; j < (word.size() % key.size()); j++)     //Записываем остаточные буквы от ключа
        {
            new_key = new_key + key[j];
        }
    }

    else  //Иначе если ключ длиннее слова
    {
        for (int s = 0; s < word.size(); s++)       //Укорачиваем ключ до длины слова
        {
            new_key = new_key + key[s];
        }
    }

    vector<int> A;
    vector<int> B;
    for (int k = 0; k < word.size(); k++)
    {
        for (int n = 0; n < alphabet.size(); n++)   //Ищем пересечение букв
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

    int e = 0; //Для суммы номеров символов. Чтобы при достижении количества всех букв, программа шла по кругу, начиная с первого номера
    for (int u = 0; u < word.size(); u++)
    {
        e = ((A[u] - B[u]));
        if (e < 0)
            e += alphabet.size();
        word[u] = alphabet[e];
    }
    return word;
}

void vigenere_encr(string& login, string& password, string& filename)    	//Построчная шифровка файла методом Виженера
{
  
    string new_file = "vig_encr_" + filename;
    add_file(login, password, new_file);
    new_file += ".txt";
    filename += ".txt";
    ofstream second_file;    //Поток для записи файла
    second_file.open(new_file);

    string key_word;
    cout << "Enter a key word: ";
    cin >> key_word;
    second_file << key_word << endl;

    string alphabet = "abcdefghijklmnopqrstuvwxyz йцукенгшщзхъфывапролджэячсмитьбю.,!<>:';][{}+=_-)(*&^%$#@!1234567890QWERTYUIOPLKJHGFDSAZXCVBNMЙЦУКЕНГШЩЗХЪЭЖДЛОРПАВЫФЯЧСМИТЬБЮ";
    string line;

    ifstream app;
    app.open(filename);
    if (app.is_open())
    {
        while (getline(app, line))
        {
            string word = vig_cipher(line, key_word, alphabet);
            second_file << word;
        }
        second_file.close();
        app.close();
    }
    
}

void encrypt(string& filename, string& password, string& login)
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
            cout << "|                       Encryption                       |\n";
            cout << "|________________________________________________________|\n\n";
            cout << "1. The Vigenere cipher\n";
            cout << "2. ElGamal encryption\n";
            cout << "3. Atbash cipher\n";
            cout << "4. Return\n";
            cout << "Enter the encryption number: ";
            string number_of_encryption;
            getline(cin, number_of_encryption);
           

            if (number_of_encryption == "1")
            {
                cout << "Enter the file number to encrypt: ";
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
                vigenere_encr(login, password, filename);
            }

            else if (number_of_encryption == "2")
            {
                cout << "Enter the file number to encrypt: ";
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
                elgamal_encr(login, password, filename);
            }

            else if (number_of_encryption == "3")
            {
                cout << "Enter the file number to encrypt: ";
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
                atbash_encr(login, password, filename);
            }

            else if (number_of_encryption == "4")
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

            else
            {
                cout << "Invalid input" << endl;
                Sleep(2000);
            }
        }

        else
        {
            cout << "You don't have any files to encrypt. First create a file." << endl;
            Sleep(2000);

        }
    }
    else
    {
        cout << "Wrong password!";
        Sleep(2000);
    }
}


void password_encrypt(string& password)     //Функция шифровки пароля
{
    string encrypted_password;
    for (char c : password)
    {
        int encr_char = (int(c) + 10);
        encrypted_password.push_back(static_cast<char>(encr_char));
    }
    password = encrypted_password;
}

void login_encrypt(string& login)       //Функция шифровки логина
{
    string encrypted_password;
    for (char c : login)
    {
        int encr_char = (int(c) - 10);
        encrypted_password.push_back(static_cast<char>(encr_char));
    }
    login = encrypted_password;
}