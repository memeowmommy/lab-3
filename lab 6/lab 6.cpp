// сортировака выбором
#include <iostream>
#include <vector>
using namespace std;

void Output(vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

void Sorting(vector<int>& v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j] < v[min]) { min = j; } 
        }
        if (min != i) { swap(v[i], v[min]); }
        cout << "Sorting:" << endl;
        Output(v);
    }
}

int main()
{
    int size = 0;
    vector<int> v;

    cout << "Enter the size:" << endl;
    cin >> size;
    cout << "Enter elements:" << endl;

    for (int i = 0; i < size; i++)
    {
        int el = 0;
        cin >> el;
        v.push_back(el);
    }

    Sorting(v);
    cout << "Sorted: " << endl;
    Output(v);
}
