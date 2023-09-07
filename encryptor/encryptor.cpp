#include "user_head.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

int main() {
  string filename, password, login;
  string choice;
  data(login, password); //Проверка пользователя или регистрация

  ofstream file("database.txt",
                ios::ate | ios::app); //Открытие потока для чтения файла
  do {
    system("clear");              //Очистка консоли
    users_files(login, password); //Вывод файлов пользователя
    cout << " ________________________________________________________" << endl;
    cout << "|                          Menu                          |"
         << endl;
    cout << "|________________________________________________________|\n\n";
    cout << "1. Create new file\n";
    cout << "2. Encrypt file\n";
    cout << "3. Decrypt file\n";
    cout << "4. Print file\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
    getline(cin, choice); //Выбор действия
    cout << endl;
    if (choice == "1") {
      create_file(login, password, filename); //Создание нового файла
    } else if (choice == "2") {
      encrypt(filename, password, login); //Шифровка файла
    } else if (choice == "3") {
      decrypt(filename, login, password); //Дешифровка файла
    } else if (choice == "4") {
      printFile(login, password); //Вывод содержимого файла в консоль
    } else if (choice == "5") {
      exit(); //Завершение работы кода
    } else    //Ошибка ввода выбора действия
    {
      cout << "Invalid input!" << endl;
      sleep(2000);
    }
  } while (choice !=
           "5"); //Работа программы, пока пользователем не будет совершен выход

  return 0;
}