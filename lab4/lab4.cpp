#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

int main()
{
    //    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    map <char, int> bukvi;
    map <int, char> bukvi1;

    for (int i = 0; i < 6; i++) {
        bukvi[char(int('А') + i)] = i;
        bukvi1[i] = char(int('А') + i);
    }
    bukvi['Ё'] = 6;
    bukvi1[6] = 'Ё';
    for (int i = 7; i < 33; i++) {
        bukvi[char(int('Ж') + i - 7)] = i;
        bukvi1[i] = char(int('Ж') + i - 7);
    }
    //for (auto b : bukvi) {
    //    cout << b.first << " " << b.second << endl;
    //}

    const string PATH = "D:\\СИБСТРИН ИНФА\\семестр6\\2324, Теория информации, данные, знания, 12 (экзамен, заоч. (5, 6 сем.) (310а-з, 310з гр.) )\\Лабораторная работа №4\\";
    const string INPUT = "Вариант 17_.txt";

    string pathin = PATH + INPUT;
    string pathout = PATH + INPUT + "_output.txt";
    string pathout2 = PATH + INPUT + "_recovery.txt";

    ifstream fin;
    ofstream fout;
    ofstream fout2(pathout2);

    fin.open(pathin);
    fout.open(pathout);

    cout << "Исходный текст:\n";
    vector<char> t_in;
    char ch;

    while (fin.get(ch)) {
        t_in.push_back(ch);
        cout << ch;
    }

    while (fin.get(ch))
    {
        t_in.push_back(ch);
    }

    cout << "Введите ключевое слово (гамму)  ";
    string str1;

    cin >> str1;

    map <int, char> key;
    int kol_el = str1.length();

    for (int i = 0; i < kol_el; i++)
    {
        key[i] = str1[i];
    }

    vector <char> t_out;

    int j = 0;

    cout << "\nЗашифрованный текст:\n";
    for (int i = 0; i < t_in.size(); i++)
    {
        bool a = t_in[i] >= 'А';
        bool b = t_in[i] <= 'Я';
        bool c = t_in[i] == 'Ё';
        if ((a and b) or c)
        {
            char ind = bukvi1[(bukvi[t_in[i]] + bukvi[key[j]]) % 33];
            t_out.push_back(ind);
            if (j == kol_el - 1) { j = 0; }
            else { j++; }
        }
        else
        {
            t_out.push_back(t_in[i]);
        }

    }

    for (int i = 0; i < t_out.size(); i++)
    {
        fout << t_out[i];
        cout << t_out[i];
    }

    vector<char> t_out2;
    j = 0;

    cout << "\nВновь расшифрованный текст:\n";
    for (int i = 0; i < t_out.size(); i++) {
        bool a = (t_out[i] >= 'А' && t_out[i] <= 'Я');
        bool b = (t_out[i] == 'Ё');
        if (a || b) {
            char ind = bukvi1[(bukvi[t_out[i]] - bukvi[str1[j]] + 33) % 33];
            t_out2.push_back(ind);
            j = (j + 1) % kol_el;
        }
        else {
            t_out2.push_back(t_out[i]);
        }
    }

    for (int i = 0; i < t_out2.size(); i++) {
        cout << t_out2[i];
        fout2 << t_out2[i];
    }

}
