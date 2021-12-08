#include <iostream>
#include "source.h"
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cctype>
using namespace std;


extern string sdnf, sknf, jegal;
extern vector<char> func;
extern size_t len;
int main() {
    bool isNewFunc = false;
    string buf;
    buf = 'i';
    int arg = 0;
    printMenu();
    while (1){
        switch (buf[0]){
            case 'i':{
                cout << "Source function: (";
                for(auto i: func)
                    cout << (char)(i+'0');
                cout << ")" << endl;
                cout << "Вычисленная по таблице истинности СДНФ: " << endl;
                findSDNF();
                if (sdnf.size())
                    cout << sdnf << endl;
                else
                    cout << "Не существует" << endl;
                cout << "Вычисленная по таблице истинности СКНФ: " << endl;
                findSKNF();
                if (sknf.size())
                    cout << sknf << endl;
                else
                    cout << "Не существует" << endl;
                cout << "Значения функции вычисленные по СДНФ: " << endl;
                auto res = tableOnSDNF();
                checkCorrect(res);
                if (!isNewFunc) {
                    BinaryDiagram bdr;
                    cout << "Значения функции вычисленные по БДР: " << endl;
                    res = bdr.tableOnBdr();
                    checkCorrect(res);
                }
                cout << "Полином Жегалкина: " << endl;
                findJEGAL();
                if (jegal.size())
                    cout << jegal << endl;
                else
                    cout << "Не существует." << endl;
                break;
            }
            case 'f':{
                setNewFunc();
                isNewFunc = true;
                break;
            }
            case 'c':{
                string buf;
                cout << "Чтобы выйти из режима вычисления значения функции, введите 'q'." << endl;
                while (true){
                    cout << "Введите аргумент функции: ";
                    buf.clear();
                    cin >> buf;
                    arg = 0;
                    if (buf[0] == 'q')
                        break;
                    for (int i = 0; i < 4; i++){
                        if (buf[i] == '0')
                            continue;
                        else if (buf[i] == '1')
                            arg += pow(2, 3-i);
                        else{
                            arg = 0;
                            break;
                        }
                    }
                    if (buf.size() < 4){
                        int l = min(2, (int)buf.size());
                        bool c = true;
                        for (int i = 0; i < min(2, (int)buf.size()); i++){
                            if (isdigit(buf[i])){
                                arg += (buf[i]-'0')*pow(10, l-1-i);
                            }
                            else{
                                cout << "Неправильный ввод, попробуйте еще раз. " << endl;
                                c = false;
                                break;
                            }
                        }
                        if (!c)
                            continue;;
                    }
                    if (arg > (int)pow(2, len)-1){
                        cout << "Неправильный ввод, попробуйте еще раз. " << endl;
                        continue;
                    }
                    cout << "Значение функции в данной точке (" << tobin(arg) <<  "): " << calcOnSDNF(arg) << endl;
                }
                break;
            }
            case 'm':{
                printMenu();
                break;
            }
            case 'q':{
                return 0;
            }
            default:{
                cout << "Unknown command, to print menu of commands type in 'm'" << endl;
            }
        }
        cout << "command: ";
        buf.clear();
        cin >> buf;
    }
    return 0;
}
