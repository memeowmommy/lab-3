#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include<Windows.h>
using namespace std;

// áèíàðíîå äåðåâî
struct Tree
{
    int data;
    int level;  //Óðîâåíü óçëà äëÿ âûâîäà äåðåâà íà ýêðàí
    Tree* left;
    Tree* right;
    Tree* parent;
};

// ñîçäàíèå óçëà â äåðåâå
Tree* CreateRoot(int data, Tree* p) // óçåë èíèöèàëèçèðóåòñÿ ñ ïîìîùüþ ññûëêè íà ðîäèòåëÿ è äàííûõ, â í¸ì ñîäåðæàùèõñÿ
{
    // ñîçäàíèå íîâîé âåðøèíû äåðåâà
    Tree* q = new Tree;
    q->data = data;
    // èñïîëüçóåì òåðíàðíûé îïåðàòîð
    q->level = (p == nullptr ? 0 : p->level + 1);
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;

    return q;
}

// äîáàâëåíèå ýëåìåíòà (ïî äàííûì è óêàçàòåëþ íà óêàçàòåëü íóæíîãî êîðíÿ)
void AddElement(int data, Tree*& root)
{
    if (root == nullptr) // êîðåíü äåðåâà ïóñò => ñîçäà¸ì êîðåíü
    {
        root = CreateRoot(data, nullptr);
        return;
    }

    Tree* v = root;

    // ïîìåùàåì äàííûé ýëåìåíò â ëåâûé èëè ïðàâûé ïîòîìîê
    while (((data < v->data) && (v->left != nullptr)) || ((data > v->data) && (v->right != nullptr)))
    {
        if (data < v->data) { v = v->left; }
        else { v = v->right; }
    }

    // åñëè çíà÷åíèå ïîòîìêà ðàâíî çíà÷åíèþ ðîäèòåëÿ, áåçäåéñòâóåì
    if (data == v->data) { return; }

    // ñîçäàåì íîâóþ âåðøèíó
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

// äîáàâëåíèå ýëåìåíòà íà îñíîâå ñêîáî÷íîé çàïèñè
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

// çàïîëíåíèå áèíàðíîãî äåðåâà
void FillTree(string& str, int& i, Tree*& root)
{
    int value = 0;

    while (str[i] != '\0')
    {
        switch (str[i])
        {
        // '(' => äâèãàåìñÿ ïî äåðåâó âëåâî
        case '(':
        {
            i++;
            value = 0;
            while ((str[i] >= '0') && (str[i] <= '9'))                      // ÿâëÿåòñÿ ëè ýòîò ýëåìåíò öèôðîé?
            {
                value = value * 10 + str[i] - '0';
                i++;
            }

            if (value != 0)
            {
                AddBracketElement(value, root, true);                 // äîáàâëåíèå ýëåìåíòà
                if (str[i] == '(') { FillTree(str, i, root->left); }  // åñëè ïîñëå '(' ñòîèò '(' => ðåêóðñèâíî âûçûâàåì äàííóþ ôóíêöèþ
            }
            value = 0;
            break;
        }

        // ',' => äâèãàåìñÿ ïî äåðåâó âïðàâî
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

        // ')' îñòàíàâëèâàåò ïðåäûäóùóþ ðåêóðñèþ, ðàññìàòðèâàåòñÿ ñëåäóþùèé ýëåìåíò
        case ')':
        {
            i++;
            return;
        }
        default: {break; }
        }
    }
}

// ïðÿìîé îáõîä äåðåâà
void Pass(Tree* v)
{
    if (v == nullptr) { return; }
    Pass(v->left);
    cout << v->data << endl;
    Pass(v->right);
}

// ïîèñê ýëåìåíòà
Tree* SearchElement(int data, Tree* v)
{
    if (v == nullptr) { return v; }
    if (v->data == data) { return v; }
    if (data < v->data) { return SearchElement(data, v->left); }
    else { return SearchElement(data, v->right); }
}

// óäàëåíèå ýëåìåíòà
void DeleteElement(int data, Tree*& root)
{
    Tree* u = SearchElement(data, root);

    if (u == nullptr) { return; }

    if (u->left == nullptr && u->right == nullptr && u == root)    // ýëåìåíò — êîðåíü, çíà÷èò óäàëÿåì åãî
    {
        delete root;
        root = nullptr;
        return;
    }

    if (u->left == nullptr && u->right != nullptr && u == root)         // åñòü ïðàâûé ïîòîìîê => ìåíÿåì ýëåìåíò ñ ñàìûì ìàëåíüêèì ýëåìåíòîì, íàõîäÿùèìñÿ ñïðàâà
    {
        Tree* t = u->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right == nullptr && u == root)         // åñòü ëåâûé ïîòîìîê => ìåíÿåì ýëåìåíò ñ ñàìûì áîëüøèì èç ëåâîé ÷àñòè
    {
        Tree* t = u->left;
        while (t->right != nullptr)
        {
            t = t->right;
        }
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right != nullptr)                      // åñòü îáà ïîòîìêà => ìåíÿåì íàø ýëåìåíò ñ ñàìûì ìàëåíüêèì èç ïðàâîé ÷àñòè
    {
        Tree* t = u->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        u->data = t->data;
        u = t;
    }

    // óäàëåíèå ýëåìåíòà
    Tree* t;
    if (u->left == nullptr) { t = u->right; }
    else { t = u->left; }
    if (u->parent->left == u) { u->parent->left = t; }
    else { u->parent->right = t; }
    if (t != nullptr) { t->parent = u->parent; }
    delete u;
}

// î÷èñòêà äåðåâà
void ClearTree(Tree*& v)
{
    if (v == nullptr) { return; } // óäàëÿåì óçëû
    ClearTree(v->left);
    ClearTree(v->right);
    delete v;
    v = nullptr;
}

// âûâîä äåðåâà íà ýêðàí
void Print(Tree* root)
{
    if (root == nullptr)
    {
        cout << endl;
        return;
    }

    // âûâîäèì äåðåâà íà ýêðàí ñïðàâà íàëåâî (â êîíñîëè îíî áóäåò ëåæàòü íà ëåâîì áîêó)
    Print(root->right);

    for (int i = root->level; i > 0; i--)
    {
        cout << '\t';
    }
    cout << root->data << endl;

    Print(root->left);
}

void Menu(Tree* root)   //Ðåàëèçàöèÿ ìåíþ âûáîðà
{
    int input;
    bool flag = false;
    while (!flag)
    {
        cout << "Âûáåðèòå íîìåð îïåðàöèè:" << std::endl;
        cout << "Äîáàâèòü - 1, Óäàëèòü - 2, Íàéòè - 3, Âûõîä èç ïðîãðàììû - 4" << std::endl;
        cin >> input;
        switch (input)
        {
        case 1:
        {
            int value;
            cout << "Ââåäèòå çíà÷åíèå, êîòîðîå íàäî äîáàâèòü: ";
            cin >> value;
            AddElement(value, root);
            break;
        }
        case 2:
        {
            int value;
            cout << "Ââåäèòå çíà÷åíèå, êîòîðîå íàäî óäàëèòü: ";
            cin >> value;
            DeleteElement(value, root);
            break;
        }
        case 3:
        {
            int value;
            cout << "Ââåäèòå çíà÷åíèå, êîòîðîå íàäî íàéòè: ";
            cin >> value;

            Tree* element = nullptr;
            element = SearchElement(value, root);
            cout << "Ýëåìåíò " << (element == nullptr ? "íå íàéäåí!" : "íàéäåí.") << std::endl;
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
    cout << "Ââåäèòå âûðàæåíèå â ñêîáî÷íîì âèäå!" << endl;
    cin >> str;

    Tree* root = nullptr;

    int value = 0, i = 0;
    while ((str[i] >= '0') && (str[i] <= '9'))  //Åñëè â ñòðîêå ÷èñëî, ïèøåì åãî â çíà÷åíèå óçëà
    {
        value = value * 10 + str[i] - '0';
        i++;
    }
    AddElement(value, root);
    FillTree(str, i, root);
    Menu(root);
    ClearTree(root);
}
