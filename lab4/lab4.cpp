#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

int main()
{
    // Устанавливаем кодировку консоли на Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Устанавливаем локаль для wcin и wcout
    locale loc(".1251");
    wcin.imbue(loc);
    wcout.imbue(loc);

    // Карты для соответствия русских букв и их индексов
    map<wchar_t, int> bukvi;
    map<int, wchar_t> bukvi1;

    // Инициализация карт
    wchar_t letters[] = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    int n = wcslen(letters);

    for (int i = 0; i < n; i++) {
        bukvi[letters[i]] = i;
        bukvi1[i] = letters[i];
    }

    // Пути к файлам
    const wstring PATH = L"D:\\СИБСТРИН ИНФА\\семестр6\\2324, Теория информации, данные, знания, 12 (экзамен, заоч. (5, 6 сем.) (310а-з, 310з гр.) )\\Лабораторная работа №4\\";
    const wstring INPUT = L"Вариант 17.txt";

    wstring pathin = PATH + INPUT;
    wstring pathout = PATH + INPUT + L"_output.txt";
    wstring pathout2 = PATH + INPUT + L"_recovery.txt";

    // Открытие файлов
    wifstream fin(pathin);
    wofstream fout(pathout);
    wofstream fout2(pathout2);

    // Устанавливаем кодировку для файлов
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    fout2.imbue(locale(fout2.getloc(), new codecvt_utf8<wchar_t>));

    if (!fin.is_open() || !fout.is_open()) {
        wcerr << L"Не удалось открыть файл" << endl;
        return 1;
    }

    vector<wchar_t> t_in;
    wchar_t ch;

    wcout << L"Исходный текст:\n";

    // Чтение входного файла
    while (fin.get(ch)) {
        t_in.push_back(ch);
        wcout << ch;
    }

    // Ввод ключевого слова (гаммы)
    wcout << L"\nВведите ключевое слово (гамму): ";
    wstring str1;
    wcin >> str1;

    map<int, wchar_t> key;
    int kol_el = str1.length();

    for (int i = 0; i < kol_el; i++) {
        key[i] = str1[i];
    }

    vector<wchar_t> t_out;
    int j = 0;

    for (int i = 0; i < t_in.size(); i++) {
        bool a = t_in[i] >= L'А';
        bool b = t_in[i] <= L'Я';
        bool c = t_in[i] == L'Ё';
        if ((a && b) || c) {
            wchar_t ind = bukvi1[(bukvi[t_in[i]] + bukvi[key[j]]) % 33];
            t_out.push_back(ind);
            if (j == kol_el - 1) {
                j = 0;
            }
            else {
                j++;
            }
        }
        else {
            t_out.push_back(t_in[i]);
        }
    }

    wcout << L"\nЗашифрованный текст:\n";
    // Вывод результатов
    for (int i = 0; i < t_out.size(); i++) {
        wcout << t_out[i];
        fout << t_out[i];
    }

    vector<wchar_t> t_out2;
    j = 0;

    wcout << L"\nВновь расшифрованный текст:\n";
    for (int i = 0; i < t_out.size(); i++) {
        bool a = t_out[i] >= L'А';
        bool b = t_out[i] <= L'Я';
        bool c = t_out[i] == L'Ё';
        if ((a && b) || c) {
            wchar_t ind = bukvi1[(bukvi[t_out[i]] - bukvi[key[j]] + 33) % 33];
            t_out2.push_back(ind);
            if (j == kol_el - 1) {
                j = 0;
            }
            else {
                j++;
            }
        }
        else {
            t_out2.push_back(t_out[i]);
        }
    }

    for (int i = 0; i < t_out2.size(); i++) {
        wcout << t_out2[i];
        fout2 << t_out2[i];
    }

    return 0;
}
