#include "user_head.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
using namespace std;

int main() {
  string filename, password, login;
  string choice;
  data(login, password);

  ofstream file("database.txt", ios::ate | ios::app);
  do {
    system("clear");
    users_files(login, password);
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
    cin.clear();
    getline(cin, choice);
    cout << endl;
    if (choice == "1") {
      create_file(login, password, filename);
    } else if (choice == "2") {
      encrypt(filename, password, login);
    } else if (choice == "3") {
      decrypt(filename, login, password);
    } else if (choice == "4") {
      printFile(login, password);
    } else if (choice == "5") {
      exit();
    } else {
      cout << "Invalid input!" << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
  } while (choice != "5");

  return 0;
}