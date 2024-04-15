#include <iostream>
#include <fstream>
using namespace std;

struct node
{
    int data;
    node* left, * right;
};
typedef node* NODE;
typedef NODE STree;
void init(STree& root);
NODE makeNode(int x);
//NODE right_rotation(NODE x);
//NODE left_rotation(NODE x);
NODE splaying(STree root, int data);
NODE findX(STree root, int data);
//NODE insertNode(STree &root, int x);
NODE insertNode(STree& root, int k);
//NODE deleteX(STree root, int data)
void deleteX(STree &root, int data);
void searchFor(NODE& p, NODE& q);
void createSTree(STree& t);
void NLR(STree root);
void LNR(STree root);
void LRN(STree root);
void menu(STree root);
void read(STree& t, ifstream& ifs);
void write(STree t, ofstream& ofs);