// сортировака вставками
// сложность O(n²)
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
    for (int j = 1; j < v.size(); j++)
    {
        int key = v[j];
        int i = j - 1;
        while ((i >= 0) and (v[i] > key))
        {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = key;

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
