//
// Created by Арсений Волынец on 05.12.2020.
//
#include <vector>
#include <string>
using namespace std;

#ifndef DM_LAB2_SOURCE_H
#define DM_LAB2_SOURCE_H
void findSDNF();
void findSKNF();
bool calcOnSDNF(int);
std::vector<char> tableOnSDNF();
void findJEGAL();
void checkCorrect(const std::vector<char>& vv);

struct Node{
    Node* l_child, *r_child;
    bool val;
    Node(): l_child(nullptr), r_child(nullptr), val(false){}
    Node(Node* l, Node* r, bool v = false): l_child(l), r_child(r), val(v){}
};
struct BinaryDiagram{
    const int N = 9;// число вершин графа
    std::vector<Node*> nodes;
    Node* root;
public:
    BinaryDiagram(): root(nullptr), nodes(N, nullptr){
        for (int i = 0; i < N; i++){
            nodes[i] = new Node;
        }
        setChildren(0, 1, 2);
        setChildren(1, 6, 8);
        setChildren(8, 4, 4);
        setChildren(2, 3, 7);
        setChildren(3, 5, 4);
        setChildren(4, 6, 7);
        setChildren(5, 7, 6);
        nodes[6]->val = false;
        nodes[7]->val = true;
    }
    void setChildren(int i, int l, int r){
        nodes[i]->l_child = nodes[l];
        nodes[i]->r_child = nodes[r];
    }
    bool calc(int i);
    std::vector<char> tableOnBdr();
};

string tobin(u_int num);
long long takeNum(u_int min, u_int max, string& buf, const char* message);
long long takeNum(u_int min, u_int max, string& ss, int start = 0, u_int* stop = 0);
void printMenu();
void setNewFunc();
#endif //DM_LAB2_SOURCE_H
