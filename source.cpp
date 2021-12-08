#include <cmath>
#include <iostream>
#include <algorithm>
#include "source.h"
using namespace std;
vector<char> func{0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1};
string ids{"xyzkqwertuiop"};
size_t len = 4;
string sdnf, sknf, jegal;
const int BAD_INPUT = -1;
static size_t countCallsCOS = 0;

void findSDNF(){
    sdnf.clear();
    countCallsCOS = 0;
    bool d = false, c = false, isZero = true;
    for (int i = 0; i < func.size(); i++) {
        int tmp;
        tmp++;
        if (func[i] == 1) {
            isZero = false;
            if (d)
                sdnf += "V ";
            else
                d = true;
            c = false;
            for (int j = 1; j < len + 1; j++) {
                if (!c)
                    c = true;
                char x = (i / (int) pow(2, len - j)) % 2;
                if (x == 0) {
                    sdnf += "(!";
                    sdnf += ids[j - 1];
                    sdnf += ')';
                } else
                    sdnf += ids[j - 1];
            }
            sdnf += " ";
        }
    }
}

void findSKNF(){
    sknf.clear();
    bool d = false, c = false;
    for (int i = 0; i < func.size(); i++){
        if (func[i] == 0){
            sknf += "(";
            c = false;
            for (int j = 1; j < len+1; j++){
                if (c)
                    sknf += "V";
                else
                    c = true;
                char x = (i/(int)pow(2, len-j)) % 2;
                if (x == 1){
                    sknf += "(!";
                    sknf += ids[j-1];
                    sknf += ')';
                } else
                    sknf += ids[j-1];
            }
            sknf += ")";
        }
    }

}

vector<char> toBin(int i){
    vector<char> value(len, 0);
    for (int k = 0; k < len; k++){
        value[len-k-1] = (bool)(i & (1 << k));
    }
    return value;
}


bool calcOnSDNF(int i){
    static vector<vector<char>> table;
    if (sdnf.empty()){
        return false;
    }
    if (countCallsCOS == 0){
        table.clear();
        int term = -1;
        for (int k = 0; k < sdnf.size(); k++) {
            if (sdnf[k] == ids[0]) {
                table.emplace_back();
                if (k > 0 and sdnf[k - 1] == '!')
                    table[++term].push_back(0);
                else
                    table[++term].push_back(1);
            }
            else if (find(ids.begin(), ids.end(), sdnf[k]) != ids.end()){
                if (k > 0 and sdnf[k - 1] == '!')
                    table[term].push_back(0);
                else
                    table[term].push_back(1);
            }
        }
        countCallsCOS++;
    }
    vector<char> value(toBin(i));
    bool res = true;
    for (int k = 0; k < table.size(); k++){
        res = true;
        for (int j = 0; j < len; j++){
            if (table[k][j] != value[j]){
                res = false;
                break;
            }
        }
        if (res) return true;
    }
    return res;
}


bool BinaryDiagram::calc(int i){
    vector<char> value(toBin(i));
    Node* p = nodes[0];
    for (int k = 0; k < value.size(); k++){
        if (p->r_child == nullptr and p->l_child == nullptr)
            return p->val;
        else if (value[k] == 0)
            p = p->l_child;
        else
            p = p->r_child;
    }
    return p->val;
}


void findJEGAL(){
    jegal.clear();
    vector<char> triangle(func.size(), 0);
    for (int i = 0; i < triangle.size(); i++)
        triangle[i] = func[i];
    bool f = false;
    for (int i = 0; i < (int)pow(2, len); i++){
        if (i != 0) {
            for (int j = 0; j < (int) pow(2, len) - i; j++) {
                triangle[j] ^= triangle[j + 1];
            }
        }
        if (triangle[0] == 1){
            if (f)
                jegal += " + ";
            else
                f = true;
            vector<char> value(toBin(i));
            if (i == 0)
                jegal += "1";
            else{
                for (int k = 0; k < len; k++) {
                    if (value[k])
                        jegal += ids[k];
                }
            }
        }
    }
}

vector<char> BinaryDiagram::tableOnBdr() {
    vector<char> res(func.size(), 0);
    for (int i = 0; i < (int)pow(2, len); i++) {
        bool x = calcOnSDNF(i);
        cout << x;
        res[i] = x;
    }
    cout << endl;
    return res;
}


vector<char> tableOnSDNF(){
    vector<char> res(func.size(), 0);
    for (int i = 0; i < (int)pow(2, len); i++) {
        bool x = calcOnSDNF(i);
        cout << x;
        res[i] = x;
    }
    cout << endl;
    return res;
}


void checkCorrect(const vector<char>& vv){
    for(int i = 0; i < min(vv.size(), func.size()); i++) {
        if (vv[i] != func[i]) {
            cout << "Не совпадает с таблицей истинности." << endl;
            return;
        }
    }
    cout << "Совпадает с таблицей истинности." << endl;
}


unsigned long long ipow(int base, int exp)
{
    unsigned long long result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}


long long takeNum(u_int min, u_int max, string& ss, int start, u_int* stop){
    //return a min <= number <= max, from ss, that is between ss[start] and ss.size(), update stop
    int i = start;
    for (; i < ss.size(); i++){
        if (!isdigit(ss[i])) {
            if (ss[i] != ' ') {
                cout << ss[i] << " is not a digit!" << endl;
                return BAD_INPUT;
            }
            break;
        }
    }

    if (stop) *stop = i+1;
    i--;
    u_int res = 0;
    for (int j = 0, x = i-start; j <= x; j++, i--)
        res += (ss[i]-'0')*ipow(10, j);

    if (res > max) {
        cout << "Incorrect number: " << res << ". The number must be not greater than " << max << endl;
        return BAD_INPUT;
    }
    if (res < min) {
        cout << "Incorrect number: " << res << ". The number must be at least " << min << endl;
        return BAD_INPUT;
    }

    return res;
}

void takeInput(string& buf){
    buf.clear();
    while (buf.empty()) {
        cin >> ws;
        getline(cin, buf);
    }
}


long long takeNum(u_int min, u_int max, string& buf, const char* message){
    long long num = BAD_INPUT;
    do {
        cout << message;
        takeInput(buf);
        num = takeNum(min, max, buf);
    } while (num == BAD_INPUT);

    return num;
}


string tobin(u_int num){
    string s(len, '0');
    for (int i= len-1; i>=0; --i)
    {
        s[len-1-i] = '0' + ((num>>i)&1);
    }
    return s;
}

void printMenu(){
    cout << "To print information about fuction (i)\n";
    cout << "To print menu (m)\n";
    cout << "To calc value on given argument (c)\n";
    cout << "To set new function (f)\n";
    cout << "To quit (q)\n";
}


void setNewFunc(){
    string buf;
    auto mes = "Введите количество переменных: ";
    len = takeNum(1, 5, buf, mes);
    while (true) {
        cout << "Введите вектор значений: ";
        cin >> buf;
        vector<char> tmp;
        tmp.reserve(pow(2, len));
        bool correct = true;
        for (int i = 0; i < pow(2, len); i++) {
            if (buf[i] == '0') {
                tmp.push_back(0);
            } else if (buf[i] == '1') {
                tmp.push_back(1);
            } else {
                cout << "Неправильный ввод, попробуйте еще раз." << endl;
                correct = false;
                break;
            }
        }
        if (correct) {
            func = tmp;
            break;
        }
    }
}
