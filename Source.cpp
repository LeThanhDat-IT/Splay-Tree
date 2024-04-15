#include "Header.h"
void init(STree& root) {
    root = NULL;
}
NODE makeNode(int x)
{
    NODE p = new node;
    p->data = x;
    p->left = p->right = NULL;
    return p;
}

NODE rotateRight(NODE p)
{
    NODE q = p->left;
    p->left = q->right;
    q->right = p;
    return q;
}

NODE rotateLeft(NODE p)
{
    NODE q = p->right;
    p->right = q->left;
    q->left = p;
    return q;
}

NODE splaying(STree root, int x)
{
    if (root == NULL || root->data == x)
        return root;
    if (root->data > x)
    {
        if (root->left == NULL) return root;
        if (root->left->data > x)
        {
            root->left->left = splaying(root->left->left, x);

            root = rotateRight(root);
        }
        else if (root->left->data < x)
        {
            root->left->right = splaying(root->left->right, x);

            if (root->left->right != NULL)
                root->left = rotateLeft(root->left);
        }

        return (root->left == NULL) ? root : rotateRight(root);
    }
    else
    {
        if (root->right == NULL) return root;
        if (root->right->data > x)
        {
            root->right->left = splaying(root->right->left, x);
            if (root->right->left != NULL)
                root->right = rotateRight(root->right);
        }
        else if (root->right->data < x)
        {
            root->right->right = splaying(root->right->right, x);
            root = rotateLeft(root);
        }
        return (root->right == NULL) ? root : rotateLeft(root);
    }
}

NODE findX(STree root, int data)
{
    return splaying(root, data);
}

NODE insertNode(STree& root, int k)
{
    // Simple Case: If tree is empty
    if (root == NULL) return makeNode(k);

    // Bring the closest leaf node to root
    root = splaying(root, k);

    // If key is already present, then return
    if (root->data == k) return root;

    // Otherwise allocate memory for new node
    NODE newnode = makeNode(k);

    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    if (root->data > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }

    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode; // newnode becomes new root
}

//NODE insertNode(STree &root, int x)
//{
//    if (root == NULL) 
//        return  makeNode(x);
//    root = splaying(root, x);
//    if (root->data == x) return root;
//    NODE p = makeNode(x);
//    if (root->data > x)
//    {
//        p->right = root;
//        p->left = root->left;
//        root->left = NULL;
//    }
//    else
//    {
//        p->left = root;
//        p->right = root->right;
//        root->right = NULL;
//    }
//    return p;
//}
void deleteX(STree& root, int x) {
    if (!root)	throw "The Splay tree is empty";
    if (root->data > x)	return deleteX(root->left, x);
    if (root->data < x)	return deleteX(root->right, x);
    else {
        NODE p = root;
        if (!root->left)
            root = root->right;
        else
            if (!root->right)
                root = root->left;
            else
                searchFor(p, root->right);

        delete p;
    }
}
void searchFor(NODE& p, NODE& q) {
    if (q->left)
        searchFor(p, q->left);
    else {
        p->data = q->data;
        p = q;
        q = q->right;
    }
}
//NODE deleteX(STree root, int data) {
//    NODE q;
//    if (!root)
//        return NULL;
//    root = splaying(root, data);
//    if (data != root->data)
//        return root;
//    if (!root->left)
//    {
//        q = root;
//        root = root->right;
//    }
//    else
//    {
//        q = root;
//        root = splaying(root->left, data);
//        root->right = q->right;
//    }
//    delete(q);
//    return root;
//}

void levelTraverse(STree root, int k) {
    if (!root)
        return;
    if (k == 0) {
        cout << root->data << "\t";
        return;
    }
    levelTraverse(root->left, k - 1);
    levelTraverse(root->right, k - 1);
}
void LNR(STree t) {
    if (t)
    {
        LNR(t->left);
        cout << t->data << "\t";
        LNR(t->right);
    }
}

void NLR(STree t) {
    if (t) {
        cout << t->data << "\t";
        NLR(t->left);
        NLR(t->right);
    }
}

void LRN(STree t) {
    if (t) {
        LRN(t->left);
        LRN(t->right);
        cout << t->data << "\t";
    }
}

int heightTree(STree t) {
    if (!t)
        return 0;
    return 1 + max(heightTree(t->left), heightTree(t->right));
}

void removeTree(STree& root) {
    if (root) {
        removeTree(root->left);
        removeTree(root->right);
        delete(root);
    }
}

void createSTree(STree& t) {
    int x;
    do {
        cout << "\nNhap gia tri (0 thoat) x = ";
        cin >> x;
        if (x == 0)	break;
        t = insertNode(t, x); 
    } while (true);
}
void read(STree& t, ifstream& ifs) {
    int x, n;
    ifs >> n;
    for (int i = 0; i < n; i++)
    {
        ifs >> x;
        insertNode(t, x);
    }
}

void write(STree t, ofstream& ofs) {
    if (!t)
        return;
    else {
        ofs << t->data << "\t";
        write(t->left, ofs);
        write(t->right, ofs);
    }
}
void menu(STree root) {
    int chon, x, k;
    char ch;
    do {
        cout << "\n0.Thoat";
        cout << "\n1.Tao cay Splay Tree";
        cout << "\n2.Them mot nut vao cay Splay Tree";
        cout << "\n3.Xoa mot nut trong cay Splay Tree";
        cout << "\n4.Duyet cay LNR";
        cout << "\n5.Duyet cay NLR";
        cout << "\n6.Duyet cay LRN";
        cout << "\n7.Duyet theo tang";
        cout << "\n8.Duyet theo tang toan bo cay Splay Tree";
        cout << "\n9.Tim kiem mot nut trong cay Splay Tree";
        cout << "\n10.Chieu cao cua cay";
        cout << "\n11.Xoa toan bo cay Splay Tree";
        cout << "\n12.Ghi File Splay Tree";
        cout << "\n13.Doc File Splay Tree";
        cout << "\n==> Vui long chon chuc nang ";
        cin >> chon;
        if (chon == 0)   break;
        switch (chon)
        {
        case 1:
            createSTree(root);
            cout << "\n-->Da tao cay thanh cong, vui long xem lai ";
            break;
        case 2:
            cout << "\nVui long nhap gia tri can them ";
            cin >> x;
            insertNode(root, x);
            cout << "\n-->Da them thanh cong, vui long xem lai ";
            break;
        case 3:
            cout << "\nVui long nhap nut can xoa";
            cin >> x;
            root = splaying(root, x);
            deleteX(root, x);
            cout << "\n-->Da xoa thanh cong, vui long xem lai ";
            break;
        case 4:
            cout << "\nDuyet cay LNR\n";
            LNR(root);
            break;
        case 5:
            cout << "\nDuyet cay NLR\n";
            NLR(root);
            break;
        case 6:
            cout << "\nDuyet cay LRN\n";
            LRN(root);
            break;
        case 7:
            cout << "\nVui long nhap tang can xuat ra ";
            cin >> k;
            cout << "\n";
            levelTraverse(root, k);
            break;
        case 8:
            cout << "\nToan bo cay Splay Tree xuat theo tang\n";
            for (int i = 0; i < heightTree(root); i++)
            {
                levelTraverse(root, i);
                cout << endl;
            }
            break;
        case 9:
            cout << "\nVui long nhap gia tri can tim ";
            cin >> x;
            root = findX(root, x);
            if (x == root->data)
                cout << "\nCo";
            else
                cout << "\nKhong co";
            break;
        case 10:
            cout << "\nChieu cao cua cay STree";
            cout << heightTree(root);
            break;
        case 11:
            cout << "\nBan co chac xoa toan bo cay STree (Y/N)";
            cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                removeTree(root);
                cout << "\nDa xoa toan bo cac nut trong cay";
            }
            break;
        case 12:
            cout << "\nGhi File cay STree";
            cout << heightTree(root);
            break;
        case 13:
            cout << "\nDoc File cay STree";
            cout << heightTree(root);
            break;
        default:
            break;
        }
    } while (true);
}