#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include<Windows.h>
using namespace std;

// �������� ������
struct Tree
{
    int data;
    int level;  //������� ���� ��� ������ ������ �� �����
    Tree* left;
    Tree* right;
    Tree* parent;
};

// �������� ���� � ������
Tree* CreateRoot(int data, Tree* p) // ���� ���������������� � ������� ������ �� �������� � ������, � �� ������������
{
    // �������� ����� ������� ������
    Tree* q = new Tree;
    q->data = data;
    // ���������� ��������� ��������
    q->level = (p == nullptr ? 0 : p->level + 1);
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;

    return q;
}

// ���������� �������� (�� ������ � ��������� �� ��������� ������� �����)
void AddElement(int data, Tree*& root)
{
    if (root == nullptr) // ������ ������ ���� => ������ ������
    {
        root = CreateRoot(data, nullptr);
        return;
    }

    Tree* v = root;

    // �������� ������ ������� � ����� ��� ������ �������
    while (((data < v->data) && (v->left != nullptr)) || ((data > v->data) && (v->right != nullptr)))
    {
        if (data < v->data) { v = v->left; }
        else { v = v->right; }
    }

    // ���� �������� ������� ����� �������� ��������, ������������
    if (data == v->data) { return; }

    // ������� ����� �������
    Tree* u = CreateRoot(data, v);
    if (data < v->data)
    {
        v->left = u;
    }
    else
    {
        v->right = u;
    }
}

// ���������� �������� �� ������ ��������� ������
void AddBracketElement(int data, Tree*& root, bool is_left)
{
    Tree* v = root;
    Tree* u = CreateRoot(data, v);
    if (is_left)
    {
        v->left = u;
    }
    else
    {
        v->right = u;
    }
}

// ���������� ��������� ������
void FillTree(string& str, int& i, Tree*& root)
{
    int value = 0;

    while (str[i] != '\0')
    {
        switch (str[i])
        {
        // '(' => ��������� �� ������ �����
        case '(':
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))                      // �������� �� ���� ������� ������?
            {
                value = value * 10 + str[i] - '0';
                i++;
            }

            if (value != 0)
            {
                AddBracketElement(value, root, true);                 // ���������� ��������
                if (str[i] == '(') { FillTree(str, i, root->left); }  // ���� ����� '(' ����� '(' => ���������� �������� ������ �������
            }
            value = 0;
            break;
        }

        // ',' => ��������� �� ������ ������
        case ',':
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))
            {
                value = value * 10 + str[i] - '0';
                i++;
            }

            if (value != 0)
            {
                AddBracketElement(value, root, false);
                if (str[i] == '(') { FillTree(str, i, root->right); }
            }
            value = 0;
            break;
        }

        // ')' ������������� ���������� ��������, ��������������� ��������� �������
        case ')':
        {
            i++;
            return;
        }
        default: {break; }
        }
    }
}

// ������ ����� ������
void Pass(Tree* v)
{
    if (v == nullptr) { return; }
    Pass(v->left);
    cout << v->data << endl;
    Pass(v->right);
}

// ����� ��������
Tree* SearchElement(int data, Tree* v)
{
    if (v == nullptr) { return v; }
    if (v->data == data) { return v; }
    if (data < v->data) { return SearchElement(data, v->left); }
    else { return SearchElement(data, v->right); }
}

// �������� ��������
void DeleteElement(int data, Tree*& root)
{
    Tree* u = SearchElement(data, root);

    if (u == nullptr) { return; }

    if (u->left == nullptr && u->right == nullptr && u == root)    // ������� � ������, ������ ������� ���
    {
        delete root;
        root = nullptr;
        return;
    }

    if (u->left == nullptr && u->right != nullptr && u == root)         // ���� ������ ������� => ������ ������� � ����� ��������� ���������, ����������� ������
    {
        Tree* t = u->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right == nullptr && u == root)         // ���� ����� ������� => ������ ������� � ����� ������� �� ����� �����
    {
        Tree* t = u->left;
        while (t->right != nullptr)
        {
            t = t->right;
        }
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right != nullptr)                      // ���� ��� ������� => ������ ��� ������� � ����� ��������� �� ������ �����
    {
        Tree* t = u->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        u->data = t->data;
        u = t;
    }

    // �������� ��������
    Tree* t;
    if (u->left == nullptr) { t = u->right; }
    else { t = u->left; }
    if (u->parent->left == u) { u->parent->left = t; }
    else { u->parent->right = t; }
    if (t != nullptr) { t->parent = u->parent; }
    delete u;
}

// ������� ������
void ClearTree(Tree*& v)
{
    if (v == nullptr) { return; } // ������� ����
    ClearTree(v->left);
    ClearTree(v->right);
    delete v;
    v = nullptr;
}

// ����� ������ �� �����
void Print(Tree* root)
{
    if (root == nullptr)
    {
        cout << endl;
        return;
    }

    // ������� ������ �� ����� ������ ������ (� ������� ��� ����� ������ �� ����� ����)
    Print(root->right);

    for (int i = root->level; i > 0; i--)
    {
        cout << '\t';
    }
    cout << root->data << endl;

    Print(root->left);
}

void Menu(Tree* root)   //���������� ���� ������
{
    int input;
    bool flag = false;
    while (!flag)
    {
        cout << "�������� ����� ��������:" << std::endl;
        cout << "�������� - 1, ������� - 2, ����� - 3, ����� �� ��������� - 4" << std::endl;
        cin >> input;
        switch (input)
        {
        case 1:
        {
            int value;
            cout << "������� ��������, ������� ���� ��������: ";
            cin >> value;
            AddElement(value, root);
            break;
        }
        case 2:
        {
            int value;
            cout << "������� ��������, ������� ���� �������: ";
            cin >> value;
            DeleteElement(value, root);
            break;
        }
        case 3:
        {
            int value;
            cout << "������� ��������, ������� ���� �����: ";
            cin >> value;

            Tree* element = nullptr;
            element = SearchElement(value, root);
            cout << "������� " << (element == nullptr ? "�� ������!" : "������.") << std::endl;
            break;
        }
        case 4:
            flag = true;
            break;
        default:
            break;
        }
    }
    Print(root);
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    string str;
    cout << "������� ��������� � ��������� ����!" << endl;
    cin >> str;

    Tree* root = nullptr;

    int value = 0, i = 0;
    while ((str[i] >= '0') && (str[i] <= '9'))  //���� � ������ �����, ����� ��� � �������� ����
    {
        value = value * 10 + str[i] - '0';
        i++;
    }
    AddElement(value, root);
    FillTree(str, i, root);
    Menu(root);
    ClearTree(root);
}

//8(3(1,6(4,7)),10(,14(13,)))