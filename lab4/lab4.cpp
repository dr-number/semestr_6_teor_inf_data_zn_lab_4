#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;

int main()
{
    //setlocale(LC_ALL, "RUS");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    map <char, int> bukvi;
    map <int, char> bukvi1;

    for (int i = 0; i < 6; i++) {
        bukvi[char(int('�') + i)] = i;
        bukvi1[i] = char(int('�') + i);
    }
    bukvi['�'] = 6;
    bukvi1[6] = '�';
    for (int i = 7; i < 33; i++) {
        bukvi[char(int('�') + i - 7)] = i;
        bukvi1[i] = char(int('�') + i - 7);
    }
    //for (auto b : bukvi) {
    //    cout << b.first << " " << b.second << endl;
    //}

    const string PATH = "D:\\�������� ����\\�������6\\2324, ������ ����������, ������, ������, 12 (�������, ����. (5, 6 ���.) (310�-�, 310� ��.) )\\������������ ������ �4\\";
    const string INPUT = "������� 17_.txt";

    string pathin = PATH + INPUT;
    string pathout = PATH + INPUT + "_output.txt";
    string pathout2 = PATH + INPUT + "_recovery.txt";

    // �������� ������
    ifstream fin(pathin);
    ofstream fout(pathout);
    ofstream fout2(pathout2);

    //fin.open(pathin);
    //fout.open(pathout);
    //fout2.open(pathout2);

    cout << "�������� ����� : \n";
    vector <char> t_in;
    char ch;

    while (fin.get(ch))
    {
        t_in.push_back(ch);
        cout << ch;
    }

    cout << "������� �������� ����� (�����)  ";
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

    for (int i = 0; i < t_in.size(); i++)
    {
        bool a = t_in[i] >= '�';
        bool b = t_in[i] <= '�';
        bool c = t_in[i] == '�';
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
        cout << t_out[i];
        fout << t_out[i];
    }

    cout << "\n������������� �����:\n";
    // ����� �����������
    for (int i = 0; i < t_out.size(); i++) {
        cout << t_out[i];
        fout << t_out[i];
    }

    vector<char> t_out2;
    j = 0;

    cout << "\n����� �������������� �����:\n";
    for (int i = 0; i < t_out.size(); i++) {
        bool a = t_out[i] >= '�';
        bool b = t_out[i] <= '�';
        bool c = t_out[i] == '�';
        if ((a && b) || c) {
            char ind = bukvi1[(bukvi[t_out[i]] - bukvi[key[j]] + 33) % 33];
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
        cout << t_out2[i];
        fout2 << t_out2[i];
    }

}