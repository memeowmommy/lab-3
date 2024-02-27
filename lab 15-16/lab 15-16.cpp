#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

struct Tree //бинарное дерево
{
    int data;
    Tree* left;
    Tree* right;
    Tree* parent;
};

Tree* RootMaker(int data, Tree* p)
{
    Tree* temp = new Tree;
    temp->data = data;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = p;
    return temp;
}

//добавление элемента (по данным и указателю на указатель нужного корня)
void AddEl(int data, Tree*& root)
{
    //при пустом корне - создаём его
    if (root == nullptr) { root = RootMaker(data, nullptr); return; } 

    Tree* child = root;

    //помещаем элемент в левый или правый потомок
    while (((data < child->data) && (child->left != nullptr)) || ((data > child->data) && (child->right != nullptr)))
    {
        if (data < child->data) { child = child->left; }
        else { child = child->right; }
    }

    //при дубле значения родителя ничего не делаем
    if (data == child->data) { return; }  

    //новая вершина 
    Tree* new_v = RootMaker(data, child);
    if (data < child->data) { child->left = new_v; }
    else { child->right = new_v; }
}

// добавлениe элемента по скобочной записи
void AddBracEl(int data, Tree*& root, bool left_flag) 
{
    Tree* a = root;
    Tree* b = RootMaker(data, a);
    if (left_flag) { a->left = b; }
    else { a->right = b; }
}

// заполнения бинарного дерева 
void TreeFiller(string& str, int& i, Tree*& root)
{
    int value = 0;
    while (str[i] != '\0')
    {
        switch (str[i])
            //Разбираем введённую запись на разные случаи
        {
        case ',':                       //, => вправо по дереву
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
                AddBracEl(value, root, false);
                if (str[i] == '(')
                {
                    TreeFiller(str, i, root->right);
                }
            }
            value = 0;
            break;
        }

        case '(':                   //( =>  влево по дереву
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))  // проверка на цифру
            {
                value = value * 10 + str[i] - '0'; i++;
            }

            if (value != 0)
            {
                AddBracEl(value, root, true);     //добавляем элемент
                if (str[i] == '(')      //если после скобки стоит еще одна то рекурсивно вызываем данную функцию
                {
                    TreeFiller(str, i, root->left);
                }
            }
            value = 0;
            break;
        }


        case ')':
            i++;
            return;
        default:
            break;
        }
    }
}

void Pass(Tree* v)   //Обход дерева (ПРЯМОЙ)
{
    if (v == nullptr) { return; } // nullptr check
    Pass(v->left);
    cout << v->data << endl;
    Pass(v->right);
}

Tree* TreeSearch(int data, Tree* tree)  // El search
{
    if (tree == nullptr) { return tree; }
    if (tree->data == data) { return tree; }
    if (data < tree->data) { return TreeSearch(data, tree->left); }
    else { return TreeSearch(data, tree->right); }
}

void ElDelete(int data, Tree*& root)
{
    Tree* tr = TreeSearch(data, root);
    if (tr == nullptr) { return; }

    // элемент — корень, значит удаляем его
    if (tr->left == nullptr && tr->right == nullptr && tr == root) 
    {
        delete root;
        root = nullptr;
        return;
    }

    //существуют правый потомoк => меняем этот элемент с самым маленьким элементом справа
    if (tr->left == nullptr && tr->right != nullptr && tr == root) 
    {
        Tree* t = tr->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        tr->data = t->data;
        tr = t;
    }

    //существуют левый потомoк =>  то меняем этот элемент с самым большим элементом слева
    if (tr->left != nullptr && tr->right == nullptr && tr == root) 
    {
        Tree* t = tr->left;
        while (t->right != nullptr)
        {
            t = t->right;
        }
        tr->data = t->data;
        tr = t;
    }

    //существуют оба потомка => меняем этот элемент с самым маленьким элементом  справа
    if (tr->left != nullptr && tr->right != nullptr) 
    {
        Tree* t = tr->right;
        while (t->left != nullptr) { t = t->left; }
        tr->data = t->data;
        tr = t;
    }
    Tree* t;                    // удаление элемента
    if (tr->left == nullptr) { t = tr->right; }
    else { t = tr->left; }
    if (tr->parent->left == tr) { tr->parent->left = t; }
    else { tr->parent->right = t; }
    if (t != nullptr) { t->parent = tr->parent; }
    delete tr;
}

void TreeClear(Tree*& tree)           //Очистка дерева
{
    if (tree == nullptr) { return; }  //Удаление узлов
    TreeClear(tree->left);
    TreeClear(tree->right);
    delete tree;
    tree = nullptr;
}

void Preorder(Tree* root) // прямой обход дерева (рекурс ф)
{
    if (root == nullptr) { return; } //случай пустого корня
    cout << root->data << endl; // данные текущего узла
    Preorder(root->left);   //Обход левого поддерева
    Preorder(root->right);  //Обход правого поддерева
}

void Inorder(Tree* root) // центральный обход дерева (рекурс ф)
{
    if (root == nullptr) { return; }
    Inorder(root->left);                  //Обход левого поддерева
    cout << root->data << endl; // данные текущего узла
    Inorder(root->right);                 //Обход правого поддерева
}

void Postorder(Tree* root) //обход в обратном порядке (рекурс ф)
{
    if (root == nullptr) { return; }
    Postorder(root->left); // Обход левого поддерева
    Postorder(root->right); // Обход правого поддерева
    cout << root->data << endl; // данные текущего узла

}

void ItOrder(Tree* root)  //обход в обратном порядке ( НЕ рекурс ф)
{
    stack<Tree*> stack; //корневой узел => пустой стек
    stack.push(root);

    while (!stack.empty()) // обход до тех пор, пока стек не опустеет
    {
        Tree* unit = stack.top();
        stack.pop();
        cout << unit->data << endl;

        if (unit->left != nullptr) { stack.push(unit->left); }
        if (unit->right != nullptr) { stack.push(unit->right); }
    }
}


int main()
{
    string str;
    cout << "Enter the expression in bracket form!" << endl;
    cin >> str;
    //
    Tree* root = nullptr;
    int value = 0;
    int x = 0;
    //
    while ((str[x] >= '0') && (str[x] <= '9'))  //Если в строке число, пишем его в значение узла
    {
        value = value * 10 + str[x] - '0'; x++;
    }

    AddEl(value, root);
    TreeFiller(str, x, root);

    Preorder(root);
    cout << "========================" << endl;
    Inorder(root);
    cout << "========================" << endl;
    Postorder(root);
    cout << "========================" << endl;
    ItOrder(root);
    cout << "========================" << endl;
    TreeClear(root);
    return 0;
}
