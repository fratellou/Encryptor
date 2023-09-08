#include "enc_head.h"
#include "user_head.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
using namespace std;

string word_search(const string &line, const uint64_t &number_of_word) {

  uint64_t count_of_spaces = 1;
  string word = "";
  for (char symb : line) {
    if (symb == ' ') {
      count_of_spaces++;
    } else if (count_of_spaces == number_of_word) {
      word.push_back(symb);
    }
  }
  return word;
}

bool username_check(string &login) {
  string line;
  ifstream check;
  check.open("database.txt");
  cout << "Create your username (without spaces): ";
  getline(cin, login);
  while (getline(check, line)) {

    if (word_search(line, 1) == login) {
      cout << "That username is already taken. Enter a different username.\n";
      username_check(login);
    }
  }
  check.close();
  return true;
}

void password_check(string &password, const string &login) {
  string line;
  ifstream check;
  check.open("database.txt");

  while (getline(check, line)) {
    if (word_search(line, 1) == login) {
      while (true) {
        cout << "Enter the password: ";
        getline(cin, password);
        password_encrypt(password);
        if (word_search(line, 2) == password) {
          check.close();
          break;
        } else {
          cout << "Incorrect password. Try again.\n";
        }
      }
    }
  }
  check.close();
}

void data(string &login, string &password) {
  cout << " ________________________________________________________" << endl;
  cout << "|                          Hello!                        |" << endl;
  cout << "|________________________________________________________|\n\n";
  cout << "Are you a new user? (Y/N): ";
  string question_answer;
  getline(cin, question_answer);

  if (question_answer == "n" || question_answer == "no" ||
      question_answer == "N" || question_answer == "No") {
    cout << "Enter your username: ";
    getline(cin, login);
    login_encrypt(login);
    string line;

    ifstream app("database.txt");
    if (app.is_open()) {
      bool flag = false;
      while (getline(app, line)) {
        if (word_search(line, 1) == login) {
          password_check(password, login);
          flag = true;
          break;
        }
      }
      if (flag == true) {
        app.close();

      } else if (flag == false) {
        cout << "The user wasn't found.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        system("clear");
        data(login, password);
      }
    }
    app.close();
  }

  else if (question_answer == "y" || question_answer == "yes" ||
           question_answer == "Y" || question_answer == "Yes") {
    fstream in_file;
    in_file.open("database.txt", ios::app | ios::ate);
    if (username_check(login) == true) {
      login_encrypt(login);
      in_file << endl << login << " ";
      cout << "Create a password: ";
      getline(cin, password);
      password_encrypt(password);
      in_file << password << " ";
      in_file.close();
    }
  } else {
    cout << "Answer error. Please enter the correct answer to the question!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("clear");
    data(login, password);
  }
}

int users_files(const string &login, const string &password) {
  string line;
  ifstream file;
  file.open("database.txt");
  if (file.is_open()) {
    while (getline(file, line)) {
      if (word_search(line, 1) == login && word_search(line, 2) == password) {
        int words_in_line = 0;
        for (char c : line) {
          if (c == ' ')
            words_in_line++;
        }
        cout << " ________________________________________________________"
             << endl;
        cout << "|                       Your files                       |"
             << endl;
        cout
            << "|________________________________________________________|\n\n";
        if (words_in_line >= 3) {
          for (int i = 3; i <= words_in_line; i++) {
            cout << i - 2 << '.' << word_search(line, i) << " ";
          }
          cout << endl << endl;
          file.close();
          return 1;
        } else {
          cout << "Empty..." << endl << endl;
          file.close();
          return 0;
        }
      }
    }
    file.close();
  }
  return 0;
}

void create_file(const string &login, const string &password,
                 string &filename) {
  while (true) {
    system("clear");
    cout << " ________________________________________________________" << endl;
    cout << "|                        Creating                        |"
         << endl;
    cout << "|________________________________________________________|\n\n";

    cout << "Enter filename: ";
    cin >> filename;
    if (file_check(filename) == true) {
      string true_filename = filename + ".txt";
      {
        ofstream file(true_filename);
        string text;
        cout << "Enter text: ";

        cin.ignore();
        getline(cin, text);
        file << text;
        file.close();
      }
      add_file(login, password, filename);
      break;
    } else {
      cout << "This filename is already taken!";
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
  }
}

bool file_check(const string &filename) {
  string line;
  ifstream file("database.txt");
  if (file.is_open()) {
    while (getline(file, line)) {
      int words_count = 1;
      for (char symb : line) {
        if (symb == ' ') {
          words_count++;
        }
      }
      for (int i = 3; i <= words_count; i++) {
        if (word_search(line, i) == filename) {
          file.close();
          return false;
        }
      }
    }
    file.close();
    return true;
  }
  return false;
}

void add_file(const string &login, const string &password,
              const string &filename) {

  string line;
  ifstream file_in("database.txt");
  ofstream file_out("temp.txt");
  if (file_in.is_open() && file_out.is_open()) {
    while (getline(file_in, line)) {
      if (word_search(line, 1) == login && word_search(line, 2) == password) {
        file_out << line << filename << " " << endl;
      } else {
        file_out << line << endl;
      }
    }
    file_in.close();
    file_out.close();
  }

  string new_line;
  ifstream ini_file{"temp.txt"};
  ofstream out_file{"database.txt"};
  if (ini_file && out_file) {

    while (getline(ini_file, new_line)) {
      out_file << new_line << "\n";
    }
  }
  ini_file.close();
  out_file.close();

  remove("temp.txt");
}

void printFile(const string &login, const string &password) {
  system("clear");

  if (users_files(login, password) == 1) {
    cout << " ________________________________________________________" << endl;
    cout << "|                        Printing                        |"
         << endl;
    cout << "|________________________________________________________|\n\n";
    int number_of_file;
    string line;
    string filename;
    cout << "Enter the number of file: ";
    cin >> number_of_file;
    cout << endl;
    ifstream file("database.txt");
    if (file.is_open()) {
      while (getline(file, line)) {
        if (word_search(line, 1) == login && word_search(line, 2) == password) {
          filename = word_search(line, number_of_file + 2);
          break;
        }
      }
      file.close();
    }

    ifstream file_to_read(filename + ".txt");
    if (file_to_read.is_open()) {
      while (!file_to_read.eof()) {
        getline(file_to_read, line);
        for (char c : line) {
          cout << c;
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        cout << endl;
      }
      file_to_read.close();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  } else {
    cout << " ________________________________________________________" << endl;
    cout << "|                        Printing                        |"
         << endl;
    cout << "|________________________________________________________|\n\n";
    cout << "You don't have any files to print. First create a file.";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
}

void exit() {
  system("clear");
  cout << " ________________________________________________________" << endl;
  cout << "|                     Exiting program                    |" << endl;
  cout << "|________________________________________________________|\n\n";

  system("clear");
  cout << " ________________________________________________________" << endl;
  cout << "|                     Exiting program                    |" << endl;
  cout << "|________________________________________________________|\n\n";
  ifstream cat("cat.txt");
  string line;
  if (cat.is_open()) {
    while (!cat.eof()) {
      getline(cat, line);
      cout << "\t\t\t\t";
      for (char c : line) {
        cout << c;
      }
      cout << endl;
    }
    cat.close();
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  system("clear");
  cout << " ________________________________________________________" << endl;
  cout << "|                     Exiting program                    |" << endl;
  cout << "|________________________________________________________|\n\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  ifstream cat2("cat.txt");
  if (cat2.is_open()) {
    while (!cat2.eof()) {
      getline(cat2, line);
      cout << "\t\t\t\t" << line << endl;
    }
    cat2.close();
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(600));
  system("clear");
  cout << " ________________________________________________________" << endl;
  cout << "|                     Exiting program                    |" << endl;
  cout << "|________________________________________________________|\n\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  ifstream cat3("cat.txt");
  if (cat3.is_open()) {
    while (!cat3.eof()) {
      getline(cat3, line);
      cout << "\t\t\t\t" << line << endl;
    }
    cat3.close();
  }
  cout << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(600));
  cout << " ________________________________________________________" << endl;
  cout << "|                            Bye!                        |" << endl;
  cout << "|________________________________________________________|\n\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(600));
}