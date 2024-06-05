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
    // ������������� ��������� ������� �� Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ������������� ������ ��� wcin � wcout
    locale loc(".1251");
    wcin.imbue(loc);
    wcout.imbue(loc);

    // ����� ��� ������������ ������� ���� � �� ��������
    map<wchar_t, int> bukvi;
    map<int, wchar_t> bukvi1;

    // ������������� ����
    wchar_t letters[] = L"�����Ũ��������������������������";
    int n = wcslen(letters);

    for (int i = 0; i < n; i++) {
        bukvi[letters[i]] = i;
        bukvi1[i] = letters[i];
    }

    // ���� � ������
    const wstring PATH = L"D:\\�������� ����\\�������6\\2324, ������ ����������, ������, ������, 12 (�������, ����. (5, 6 ���.) (310�-�, 310� ��.) )\\������������ ������ �4\\";
    const wstring INPUT = L"������� 17.txt";

    wstring pathin = PATH + INPUT;
    wstring pathout = PATH + INPUT + L"_output.txt";
    wstring pathout2 = PATH + INPUT + L"_recovery.txt";

    // �������� ������
    wifstream fin(pathin);
    wofstream fout(pathout);
    wofstream fout2(pathout2);

    // ������������� ��������� ��� ������
    fin.imbue(locale(fin.getloc(), new codecvt_utf8<wchar_t>));
    fout.imbue(locale(fout.getloc(), new codecvt_utf8<wchar_t>));
    fout2.imbue(locale(fout2.getloc(), new codecvt_utf8<wchar_t>));

    if (!fin.is_open() || !fout.is_open()) {
        wcerr << L"�� ������� ������� ����" << endl;
        return 1;
    }

    vector<wchar_t> t_in;
    wchar_t ch;

    wcout << L"�������� �����:\n";

    // ������ �������� �����
    while (fin.get(ch)) {
        t_in.push_back(ch);
        wcout << ch;
    }

    // ���� ��������� ����� (�����)
    wcout << L"\n������� �������� ����� (�����): ";
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
        bool a = t_in[i] >= L'�';
        bool b = t_in[i] <= L'�';
        bool c = t_in[i] == L'�';
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

    wcout << L"\n������������� �����:\n";
    // ����� �����������
    for (int i = 0; i < t_out.size(); i++) {
        wcout << t_out[i];
        fout << t_out[i];
    }

    vector<wchar_t> t_out2;
    j = 0;

    wcout << L"\n����� �������������� �����:\n";
    for (int i = 0; i < t_out.size(); i++) {
        bool a = t_out[i] >= L'�';
        bool b = t_out[i] <= L'�';
        bool c = t_out[i] == L'�';
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
