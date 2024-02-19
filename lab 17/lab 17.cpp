#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include<Windows.h>
using namespace std;

// бинарное дерево
struct Tree
{
    int data;
    int level;  //Уровень узла для вывода дерева на экран
    Tree* left;
    Tree* right;
    Tree* parent;
};

// создание узла в дереве
Tree* CreateRoot(int data, Tree* p) // узел инициализируется с помощью ссылки на родителя и данных, в нём содержащихся
{
    // создание новой вершины дерева
    Tree* q = new Tree;
    q->data = data;
    // используем тернарный оператор
    q->level = (p == nullptr ? 0 : p->level + 1);
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;

    return q;
}

// добавление элемента (по данным и указателю на указатель нужного корня)
void AddElement(int data, Tree*& root)
{
    if (root == nullptr) // корень дерева пуст => создаём корень
    {
        root = CreateRoot(data, nullptr);
        return;
    }

    Tree* v = root;

    // помещаем данный элемент в левый или правый потомок
    while (((data < v->data) && (v->left != nullptr)) || ((data > v->data) && (v->right != nullptr)))
    {
        if (data < v->data) { v = v->left; }
        else { v = v->right; }
    }

    // если значение потомка равно значению родителя, бездействуем
    if (data == v->data) { return; }

    // создаем новую вершину
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

// добавление элемента на основе скобочной записи
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

// заполнение бинарного дерева
void FillTree(string& str, int& i, Tree*& root)
{
    int value = 0;

    while (str[i] != '\0')
    {
        switch (str[i])
        {
        // '(' => двигаемся по дереву влево
        case '(':
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))                      // является ли этот элемент цифрой?
            {
                value = value * 10 + str[i] - '0';
                i++;
            }

            if (value != 0)
            {
                AddBracketElement(value, root, true);                 // добавление элемента
                if (str[i] == '(') { FillTree(str, i, root->left); }  // если после '(' стоит '(' => рекурсивно вызываем данную функцию
            }
            value = 0;
            break;
        }

        // ',' => двигаемся по дереву вправо
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

        // ')' останавливает предыдущую рекурсию, рассматривается следующий элемент
        case ')':
        {
            i++;
            return;
        }
        default: {break; }
        }
    }
}

// прямой обход дерева
void Pass(Tree* v)
{
    if (v == nullptr) { return; }
    Pass(v->left);
    cout << v->data << endl;
    Pass(v->right);
}

// поиск элемента
Tree* SearchElement(int data, Tree* v)
{
    if (v == nullptr) { return v; }
    if (v->data == data) { return v; }
    if (data < v->data) { return SearchElement(data, v->left); }
    else { return SearchElement(data, v->right); }
}

// удаление элемента
void DeleteElement(int data, Tree*& root)
{
    Tree* u = SearchElement(data, root);

    if (u == nullptr) { return; }

    if (u->left == nullptr && u->right == nullptr && u == root)    // элемент — корень, значит удаляем его
    {
        delete root;
        root = nullptr;
        return;
    }

    if (u->left == nullptr && u->right != nullptr && u == root)         // есть правый потомок => меняем элемент с самым маленьким элементом, находящимся справа
    {
        Tree* t = u->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right == nullptr && u == root)         // есть левый потомок => меняем элемент с самым большим из левой части
    {
        Tree* t = u->left;
        while (t->right != nullptr)
        {
            t = t->right;
        }
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right != nullptr)                      // есть оба потомка => меняем наш элемент с самым маленьким из правой части
    {
        Tree* t = u->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        u->data = t->data;
        u = t;
    }

    // удаление элемента
    Tree* t;
    if (u->left == nullptr) { t = u->right; }
    else { t = u->left; }
    if (u->parent->left == u) { u->parent->left = t; }
    else { u->parent->right = t; }
    if (t != nullptr) { t->parent = u->parent; }
    delete u;
}

// очистка дерева
void ClearTree(Tree*& v)
{
    if (v == nullptr) { return; } // удаляем узлы
    ClearTree(v->left);
    ClearTree(v->right);
    delete v;
    v = nullptr;
}

// вывод дерева на экран
void Print(Tree* root)
{
    if (root == nullptr)
    {
        cout << endl;
        return;
    }

    // выводим дерева на экран справа налево (в консоли оно будет лежать на левом боку)
    Print(root->right);

    for (int i = root->level; i > 0; i--)
    {
        cout << '\t';
    }
    cout << root->data << endl;

    Print(root->left);
}

void Menu(Tree* root)   //Реализация меню выбора
{
    int input;
    bool flag = false;
    while (!flag)
    {
        cout << "Выберите номер операции:" << std::endl;
        cout << "Добавить - 1, Удалить - 2, Найти - 3, Выход из программы - 4" << std::endl;
        cin >> input;
        switch (input)
        {
        case 1:
        {
            int value;
            cout << "Введите значение, которое надо добавить: ";
            cin >> value;
            AddElement(value, root);
            break;
        }
        case 2:
        {
            int value;
            cout << "Введите значение, которое надо удалить: ";
            cin >> value;
            DeleteElement(value, root);
            break;
        }
        case 3:
        {
            int value;
            cout << "Введите значение, которое надо найти: ";
            cin >> value;

            Tree* element = nullptr;
            element = SearchElement(value, root);
            cout << "Элемент " << (element == nullptr ? "не найден!" : "найден.") << std::endl;
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
    cout << "Введите выражение в скобочном виде!" << endl;
    cin >> str;

    Tree* root = nullptr;

    int value = 0, i = 0;
    while ((str[i] >= '0') && (str[i] <= '9'))  //Если в строке число, пишем его в значение узла
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