#include <iostream>
#include <fstream>
#include <string>
#include "windows.h"
#include "user_head.h"
#include "enc_head.h"
using namespace std;

string word_search(string& line, const uint64_t& number_of_word)     //�������, ������� ���������� ����������� �� ������� ����� �� ������
{

    int count_of_spaces = 1;        //������� �������� � ������
    string word = "";   //������� �� ����� ����� � ������
    for (char symb : line)  //������� ���� �������� ������
    {
        if (symb == ' ')    //��� ���������� �������
        {
            count_of_spaces++;  //���������� �������� �������� 
        }
        else if (count_of_spaces == number_of_word)     //���� ��������� ����������� ������� ��������, �� ������� ������� �� ����� �����
        {
            word.push_back(symb);
        }
    }
    return word;        //����������� �������� �� ����� �����
}

bool username_check(string& login)       //�������, ������� ���������, ������ �� ��� ��� �������� ������ ������������
{
    string line;
    ifstream check;      //�������� ������ ��� ������ �����
    check.open("database.txt");
    cout << "Create your username (without spaces): ";
    getline(cin, login);
    while (getline(check, line))        //������� ���� ����� �����
    {

        if (word_search(line, 1) == login)
        {
            cout << "That username is already taken. Enter a different username.\n";
            username_check(login);
        }
        if (login == "" && login != " ")
        {
            cout << "Username shouldn't be empty. Enter a different username.\n";
            username_check(login);
        }
    }
    check.close();      //�������� ������
    return true;        //���� �� ������� ������� �������� � ����� � ����� �� ������, �� ������� true
}

void password_check(string& password, string& login)    //������� �������� ������
{
    string line;
    ifstream check;      //�������� ������ ��� ������ �����
    check.open("database.txt");

    while (getline(check, line))        //������� ���� ����� �����
    {
        if (word_search(line, 1) == login)
        {
            while (true)
            {
                cout << "Enter the password: ";
                getline(cin, password);
                password_encrypt(password);
                if (word_search(line, 2) == password)
                {
                    check.close();
                    break;    //���� ������ ������ �����, �� ����������� ������ �������
                }
                else
                {
                    cout << "Incorrect password. Try again.\n";
                }
            }
        }
    }
    check.close();      //�������� ������
}

void data(string& login, string& password)  //�������� ������ ������������ ��� ���� � ������� �������������
{
    cout << " ________________________________________________________" << endl;
    cout << "|                          Hello!                        |" << endl;
    cout << "|________________________________________________________|\n\n";
    cout << "Are you a new user? (Y/N): ";
    string question_answer;
    getline(cin, question_answer);

    if (question_answer == "n" || question_answer == "no" || question_answer == "N" || question_answer == "No")
    {
        cout << "Enter your username: ";
        getline(cin, login);
        login_encrypt(login);
        string line;
        bool flag = false;
        ifstream app("database.txt");  //�������� ������ ��� ������ ����� � ������
        if (app.is_open())
        {
            while (getline(app, line))       //������� ���� ����� �����
            {
                if (word_search(line, 1) == login)
                {
                    password_check(password, login);
                    flag = true;
                    break;
                }
            }
            if (flag == true)
            {
                app.close();

            }
            else if (flag == false)
            {
                cout << "The user wasn't found.\n";
                Sleep(2000);
                system("cls");
                data(login, password);
            }
        }
        app.close();      //�������� ������ ��� ������ �����    
    }

    else if (question_answer == "y" || question_answer == "yes" || question_answer == "Y" || question_answer == "Yes")      //����� ������������
    {
        fstream in_file;
        in_file.open("database.txt", ios::app | ios::ate);      //�������� ������ ��� ������ � ����
        if (username_check(login) == true)      //���� ����� �� �����
        {
            login_encrypt(login);
            in_file << endl << login << " ";   //���������� ������ ������ � ���� ������
            cout << "Create a password: ";
            getline(cin, password);
            password_encrypt(password);
            in_file << password << " ";
            in_file.close();
        }
    }
    else
    {
        cout << "Answer error. Please enter the correct answer to the question!\n";      //������ ������ �� ������
        Sleep(2000);
        system("cls");
        data(login, password);
    }
}

int users_files(string& login, string& password)     //����� ����� �� ��������� � ������������ ��� �������� ������ �����
{
    string line;
    ifstream file;
    file.open("database.txt");     //�������� ������ ��� ������ ����� ���� ������
    if (file.is_open())     
    {
        while (getline(file, line))
        {
            if (word_search(line, 1) == login && word_search(line, 2) == password)      //���� ������ 2 ����� � ������ ��������� � ������� � �������
            {
                int words_in_line = 0;  //������� ���������� ���� � ������ 
                for (char c : line)
                {
                    if (c == ' ') words_in_line++;
                }
                cout << " ________________________________________________________" << endl;
                cout << "|                       Your files                       |" << endl;
                cout << "|________________________________________________________|\n\n";
                if (words_in_line >= 3)
                {
                    for (int i = 3; i <= words_in_line; i++)
                    {
                            cout << i - 2 << '.' << word_search(line, i) << " ";
                    }
                    cout << endl << endl;
                    file.close();
                    return 1;       //����������� �������, ���� � ������������ ���� �����
                }
                else
                {
                    cout << "Empty..." << endl << endl;
                    file.close();
                    return 0;   //����������� ����, ���� � ������������ ��� ������
                }
            }
        }
        file.close();
    }
    return 0;
}

void create_file(string& login, string& password, string& filename)
{
    while (true)
    {
        system("cls");
        cout << " ________________________________________________________" << endl;
        cout << "|                        Creating                        |" << endl;
        cout << "|________________________________________________________|\n\n";

        cout << "Enter filename: ";
        cin >> filename;
        if (file_check(filename) == true)
        {
            string true_filename = filename + ".txt";
            {
                ofstream file(true_filename);    //����� ��� ������ �����
                string text;
                cout << "Enter text: ";

                cin.ignore();
                getline(cin, text);
                file << text;
                file.close();
            }
            add_file(login, password, filename);
            break;
        }
        else
        {
            cout << "This filename is already taken!";
            Sleep(2000);
        }
    }
    

}

bool file_check(string& filename)  //�������, ������� ���������, ���������� �� ���� � ����� ������
{
    string line;
    ifstream file("database.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            int words_count = 1;
            for (char symb : line)  //������� ���� �������� ������
            {
                if (symb == ' ')    //��� ���������� �������
                {
                    words_count++;  //���������� �������� ����
                }
            }
            for (int i = 3; i <= words_count; i++)
            {
                if (word_search(line, i) == filename)
                {
                    file.close();
                    return false;
                }
            }
        }
        file.close();
        return true;
    }
}

void add_file(string& login, string& password, string& filename)    //���������� ����� � ������ ������ ������������
{
  
    string line;
    ifstream file_in("database.txt");  //�������� ������ ��� ������ �� �����
    ofstream file_out("temp.txt");    //�������� ���������� ������ ��� ������ � ����
    if (file_in.is_open() && file_out.is_open())
    {
        while (getline(file_in, line))
        {
            if (word_search(line, 1) == login && word_search(line, 2) == password)
            {
                file_out << line << filename << " " << endl;   //������ ������ � ��������� �����
            }
            else
            {
                file_out << line << endl;   //������ �������� ������ ��� ���������
            }
        }
        file_in.close();
        file_out.close();
    }

    string new_line;
    ifstream ini_file{ "temp.txt" }; 
    ofstream out_file{ "database.txt" };
    if (ini_file && out_file) {

        while (getline(ini_file, new_line)) {
            out_file << new_line << "\n";
        }

    }
    ini_file.close();
    out_file.close();

    remove("temp.txt");     //�������� ��������� �����
}


void printFile(string& login, string& password) 
{
    system("cls");

    if (users_files(login, password) == 1)
    {
        cout << " ________________________________________________________" << endl;
        cout << "|                        Printing                        |" << endl;
        cout << "|________________________________________________________|\n\n";
        int number_of_file;
        string line;
        string filename;
        cout << "Enter the number of file: ";
        cin >> number_of_file;
        cout << endl;
        ifstream file("database.txt");
        if (file.is_open())
        {
            while (getline(file, line))
            {
                if (word_search(line, 1) == login && word_search(line, 2) == password)
                {
                    filename = word_search(line, number_of_file + 2);
                    break;
                }
            }
            file.close();
        }

        ifstream file_to_read(filename + ".txt");
        if (file_to_read.is_open())
        {
            while (!file_to_read.eof())
            {
                getline(file_to_read, line);
                for (char c : line)
                {
                    cout << c;
                    Sleep(100);
                }
                cout << endl;
            }
            file_to_read.close();
        }
        Sleep(3000);
    }
    else
    {
        cout << " ________________________________________________________" << endl;
        cout << "|                        Printing                        |" << endl;
        cout << "|________________________________________________________|\n\n";
        cout << "You don't have any files to print. First create a file.";
        Sleep(2000);
    }
}

void exit()     //����� �� ���������
{
    system("cls");
    cout << " ________________________________________________________" << endl;
    cout << "|                     Exiting program                    |" << endl;
    cout << "|________________________________________________________|\n\n";
    Sleep(300);
    cout << "                        ";
    for (int i = 0; i < 10; i++)
    {
        cout << '.';
        Sleep(200);
    }

    system("cls");
    cout << " ________________________________________________________" << endl;
    cout << "|                     Exiting program                    |" << endl;
    cout << "|________________________________________________________|\n\n";
    ifstream cat("cat.txt");
    string line;
    if (cat.is_open())
    {
        while (!cat.eof())
        {
            getline(cat, line);
            cout << "\t\t\t\t";
            for (char c : line)
            {
                cout << c;
                Sleep(20);
            }
            cout << endl;
            
        }
        cat.close();
    }
    Sleep(500);

    system("cls");
    cout << " ________________________________________________________" << endl;
    cout << "|                     Exiting program                    |" << endl;
    cout << "|________________________________________________________|\n\n";
    Sleep(300);

    ifstream cat2("cat.txt");
    if (cat2.is_open())
    {
        while (!cat2.eof())
        {
            getline(cat2, line);
            cout << "\t\t\t\t" << line << endl;
            
        }
        cat2.close();
    }
    Sleep(500);
    system("cls");
    cout << " ________________________________________________________" << endl;
    cout << "|                     Exiting program                    |" << endl;
    cout << "|________________________________________________________|\n\n";
    Sleep(300);

    ifstream cat3("cat.txt");
    if (cat3.is_open())
    {
        while (!cat3.eof())
        {
            getline(cat3, line);
            cout << "\t\t\t\t" << line << endl;
            
        }
        cat3.close();
    }
    cout << endl;
    Sleep(500);
    cout << " ________________________________________________________" << endl;
    cout << "|                            Bye!                        |" << endl;
    cout << "|________________________________________________________|\n\n";
    Sleep(500);
}