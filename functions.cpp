#include "functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// F10
void binfile(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cout << "Нет" << filename << endl;
        return;
    }

    in.seekg(0, ios::end);
    streampos size = in.tellg();
    in.seekg(0, ios::beg);

    int count = size / sizeof(int);

    if (count > 0) {
        vector<int> data(count);
        in.read(reinterpret_cast<char*>(data.data()), size);

        cout << "Содержимое файла \"";
        for (int i = 0; i < count; ++i) {
            cout << data[i];
            if (i < count - 1) cout << " ";
        }
        cout << endl;
    } else {
        cout << "нет\n";
    }
}
void tF10() {
    string inputFile, outputFile;
    cout << "Имя исходного файла: ";
    cin >> inputFile;
    cout << "Имя нового файла: ";
    cin >> outputFile;

    ifstream in(inputFile, ios::binary);
    if (!in) {
        cout << "нету\n";
        return;
    }

    in.seekg(0, ios::end);
    streampos size = in.tellg();
    int count = size / sizeof(int);
    in.seekg(0, ios::beg);

    vector<int> data(count);
    in.read(reinterpret_cast<char*>(data.data()), size);
    in.close();

    ofstream out(outputFile, ios::binary);
    if (!out) {
        cout << "нет\n";
        return;
    }

    for (int i = count - 1; i >= 0; --i) {
        out.write(reinterpret_cast<char*>(&data[i]), sizeof(int));
    }

    out.close();
    cout << "все\n";
    binfile(inputFile);
    binfile(outputFile);
}

//F30
void tF30() {
    string filename;
    cout << "Имя файла: ";
    cin >> filename;
    binfile(filename);
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "нет\n";
        return;
    }

    file.seekg(0, ios::end);
    streampos size = file.tellg();
    int count = size / sizeof(int);

    if (count % 2 != 0) {
        cout << "нет\n";
        return;
    }

    int newSize = count / 2;
    file.seekg(0, ios::beg);

    vector<int> firstHalf(newSize);
    file.read(reinterpret_cast<char*>(firstHalf.data()), newSize * sizeof(int));
    file.close();

    // Перезаписываем файл
    ofstream out(filename, ios::binary | ios::trunc);
    out.write(reinterpret_cast<char*>(firstHalf.data()), newSize * sizeof(int));
    out.close();
    binfile(filename);
}

// F52
void tF52() {
    string s0;
    int n;
    cout << "Имя архивного файла: ";
    cin >> s0;
    cout << "Количество файлов (1-4): ";
    cin >> n;

    if (n > 4 || n <= 0) {
        cout << "условие не то\n";
        return;
    }

    vector<string> filenames(n);
    for (int i = 0; i < n; ++i) {
        cout << "Введите имя файла " << i + 1 << ": ";
        cin >> filenames[i];
    }

    vector<int> sizes(n);
    vector<vector<int>> allData(n);

    // Чтение данных из файлов
    for (int i = 0; i < n; ++i) {
        ifstream in(filenames[i], ios::binary);
        if (!in) {
            cout << "нет " << filenames[i] << endl;
            return;
        }

        in.seekg(0, ios::end);
        streampos size = in.tellg();
        sizes[i] = size / sizeof(int);
        in.seekg(0, ios::beg);

        allData[i].resize(sizes[i]);
        in.read(reinterpret_cast<char*>(allData[i].data()), size);
        in.close();
    }

    // архив
    ofstream out(s0, ios::binary);
    if (!out) {
        cout << "нет\n";
        return;
    }

    out.write(reinterpret_cast<char*>(&n), sizeof(int));
    out.write(reinterpret_cast<char*>(sizes.data()), n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        out.write(reinterpret_cast<char*>(allData[i].data()), sizes[i] * sizeof(int));
    }
    out.close();
    binfile(s0);
}

//R17
int readNumber(const string& s, int& pos) {
    if (pos >= s.length() || !isdigit(s[pos])) {
        return 0;
    }
    int digit = s[pos] - '0';
    pos++;

    if (pos < s.length() && isdigit(s[pos])) {
        return digit * 10 + readNumber(s, pos);
    }

    return digit;
}



int perec(const string& s, int& pos) {
    if (pos >= s.length()) return 0;

    if (isdigit(s[pos])) {
        int number = 0;
        while (pos < s.length() && isdigit(s[pos])) {
            number = number * 10 + (s[pos] - '0');
            pos++;
        }
        return number;
    }

    if (s[pos] == '(') {
        pos++;

        int left = perec(s, pos);
        int op = s[pos++];
        int right = perec(s, pos);
        if (op == '+') return left + right;
        if (op == '-') return left - right;
        if (op == '*') return left * right;

        cout << "Нtn\n";
        return 0;
    }

    return 0;
}
void tR17() {
    string s;
    cout << "Выражение: ";
    cin.ignore();
    getline(cin, s);

    int pos = 0;
    int result = perec(s, pos);
    cout << "Результат: " << result << endl;
    if (pos < s.length()) {
        cout << s.substr(pos) << "\n";
    }
}
