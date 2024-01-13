# Encryptor

Необходимо разработать программу, которая должна шифровать и дешифровать исходные данные одним из представленных алгоритмов.
Программа должна выполнять следующие основные действия:
- обеспечить процедуру проверки пользовательских данных путем авторизации в системе;
- предусмотреть ввод исходного текста с клавиатуры или загрузку данных из файла;
- реализовать шифрование данных и демонстрацию полученных результатов;
- реализовать дешифрование (расшифрование) данных и демонстрацию полученных результатов (консоль, файл).

В программе используется 3 метода шифрования: Атбаша, Виженера и Эль-Гамаля.

## Оглавление

1. [Шифр Атбаша](#шифр-атбаша)
2. [Шифр Виженера](#шифр-виженера)
3. [Шифр Эль-Гамаля](#шифр-эль-гамаля)
4. [Модули программы](#модули-программы)

## Шифр Атбаша

Шифрование заключается в замене каждой буквы исходного текста на «симметричную» ей букву алфавита, то есть первая алфавита заменялась на последнюю и наоборот, вторая буква – на предпоследнюю и наоборот и т.д. 

## Шифр Виженера

Шифрование происходит так. Под буквами шифруемого текста записывают слово-ключ, многократно его повторяя. Затем заменяют буквы исходного текста их суммами с буквами ключа. При расшифровке же вместо сложения придётся выполнять вычитание.

В первой строке таблицы алфавит может быть расположение в естественном порядке или в произвольном. Открытый текст записывается в строчку без пробелов, затем для формирования ключа используем этот же открытый текст с добавлением к началу ключа случайного символа, который знают и получатель и отправитель. Пара букв стоящих друг под другом в открытом тексте и в ключе (G и Q), указывали номер столбца и строки, соответственно, на пересечении которых находилась зашифрованная буква.

>Открытый текст: GREENTEA 
>
>Ключ: QGREENTE 
>
>Шифротекст: WXVIRGXE

## Шифр Эль-Гамаля

Участники информационного процесса выбирают простое число p и произвольное целое число q, являющееся первообразным корнем по модулю p.
Сторона А генерирует секретный ключ k_a< p и вычисляет открытый ключ: Y_a=q^(k_a ) (mod p).

Сторона В выбирает число k_b < p и с его помощью зашифровывает передаваемое сообщение М следующим образом: Y_b=q^(k_b) (mod p)  и C=M⊕(Y_a^(k_b) (mod p))

Величина М представляет собой последовательность двоичных символов, передаваемых в канал связи.

Сторона А, получив сообщение в виде Y_b  и C, восстанавливает его: M=(Y_b^(k_a) (mod p)) ⨁ C. 

При сетевом обмене сообщениями отправитель A использует для шифрования открытый ключ получателя B, поскольку только B должен иметь возможность расшифровывать адресованные ему послания. Ответные сообщения B должен шифровать, используя открытый ключ A.

## Модули программы

`Enc_head.h`- заголовочный файл, содержит объявления всех функций для шифровки текста разными методами;

`Dec_head.h` – заголовочный файл, содержит объявления всех функций для дешифровки текста разными методами; 

`User_head.h` – заголовочный файл, содержит объявления всех вспомогательных функций для работы с файлами и пользователем;

`Encryptors.cpp` – файл содержит определение функций, объявленных в заголовочном файле Enc_head.h:

- `void encrypt(string& filename, string& password, string& login)` -Шифрование;

- `bool is_Prime(const int& n)` - Проверка числа на простоту; 

- `int isalpha_ru(const char& c)` - Проверка, принадлежит ли буква русскому алфавиту; 

- `uint64_t NOD(const uint64_t& a, const uint64_t& b)` - Алгоритм Евклида для нахождения НОД двух чисел;

- `uint64_t mod_p(const uint64_t& a, const uint64_t& x, const uint64_t& p)` - Функция для возведения в степень по модулю;

- `void password_encrypt(string& password)` - Функция шифровки пароля;

- `void login_encrypt(string& login)` - Функция шифровки логина;

- `string vig_cipher(string& word, string& key, string& alphabet)` - Шифровка Виженера;

- `void vigenere_encr(string& login, string& password, string& filename)` -Построчная шифровка файла методом Виженера;

- `string elgamal_cipher(uint64_t& p, uint64_t& g, uint64_t& a, string& message)` - Построчная шифровка файла методом Эль-Гамаля;

- `void elgamal_encr(string& login, string& password, string& filename)` -Шифровка эль гамаля;

- `void atbash_encr(string& login, string& password, string& filename)` - Построчная шифровка файла методом Атбаш;

- `string atbash_cipher_rus(string& text)` - Шифровка Атбаш для русского алфавита;

- `string atbash_cipher_eng(string& text)` - Шифровка Атбаш для английского алфавита;

`Decryptors.cpp` – файл содержит определение функций, объявленных в заголовочном файле dec_head.h:

- `void decrypt(string& filename, string& login, string& password)` – Дешифрование;

- `string vig_cipher_decr(string& word, string& key, string& alphabet)` - Дешифровка Виженера;

- `void vigenere_decr(string& login, string& password, string& filename)` - Построчная дешифровка файла методом Виженера;

- `void elgamal_decr(string& login, string& password, string& filename)` - Построчная шифровка файла методом Эль-Гамаля;

- `char elgamal_cipher_decr(uint64_t& p, uint64_t& a, uint64_t& C1, uint64_t& C2)` - Дешифровка Эль-Гамаля;

- `void atbash_decr(string& login, string& password, string& filename)` - Построчная дешифровка файла методом Атбаш;

- `string atbash_cipher_decr_eng(string& ciphertext)` - Дешифрока Атбаш для английского алфавита;

- `string atbash_cipher_decr_rus(string& ciphertext)` - Дешифровка Атбаш для русского алфавита;

`user.cpp` – файл содержит определение функций, объявленных в заголовочном файле user_head.h:

- `string word_search(string& line, const uint64_t& number_of_word)` - Функция, которая возвращает необходимое по порядку слово из строки;

- `bool username_check(string& login)` - Функция, которая проверяет, занято ли имя при создании нового пользователя;

- `void password_check(string& password, string& login)` - Функция проверки пароля;

- `void data(string& login, string& password)` - Создание нового пользователя или вход в аккаунт существующего;

- `int users_files(string& login, string& password)` - Выбор файла из имеющихся у пользователя или создание нового файла;

- `void add_file(string& login, string& password, string& filename)` - Добавление файла к списку файлов пользователя;

- `void create_file(string& login, string& password, string& filename)` - Функция создания нового файла;

- `bool file_check(string& filename)` - Функция, которая проверяет, существует ли файл с таким именем;

- `void printFile(string& login, string& password)` - Функция вывода файла;

- `void exit()` - Выход из программы;

`encryptor.cpp` - Содержит функцию main, представляющую функционал по вводу пароля, выводу меню выбора шифров, с соответствующим вызовом функций, и вводом необходимых данных. 

>
>fratellou, 2023