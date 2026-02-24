#include "functions.h"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    using namespace std;
    system("chcp 65001");
    int choice;
    do {
        cout << "1. File10\n";
        cout << "2. File30 \n";
        cout << "3. File52 \n";
        cout << "4. Recur17\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";
        cin >> choice;

        switch (choice) {
            case 1: tF10(); break;
            case 2: tF30(); break;
            case 3: tF52(); break;
            case 4: tR17(); break;
            case 0: cout << "конец.\n"; break;
            default: cout << "нет\n";
        }
    } while (choice != 0);

    return 0;
}
