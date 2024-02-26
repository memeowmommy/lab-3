// сортировка слиянием  O(n log n)
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

void Sorting(vector<int>& v, int ind, int size)
{
    if (size == ind) { return; }

    int middle = (size + ind) / 2;

    Sorting(v, ind, middle);
    Sorting(v, middle + 1, size);

    int i = ind;
    int j = middle + 1;

    vector<int> tmp(size - ind + 1, 0);

    for (int k = 0; k < size - ind + 1; k++)
    {
        if ((j > size) || ((i <= middle) && (v[i] < v[j])))
        {
            tmp[k] = v[i];
            i++;
        }
        else
        {
            tmp[k] = v[j];
            j++;
        }
    }

    for (int k = 0; k < size - ind + 1; k++)
    {
        v[ind + k] = tmp[k];
    }
    cout << "Sorting:" << endl;
    Output(v);
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

    Sorting(v, 0, v.size() - 1);

    cout << "Sorted: " << endl;
    Output(v);
}
