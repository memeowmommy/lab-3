// сортировка прочёсыванием
//сложность - лучшее время O(n*logn)
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
    int step = v.size() - 1;

    while (step >= 1)
    {
        for (int i = 0; i < v.size() - step; i++)
        {
            if (v[i] > v[i + step]) { swap(v[i], v[i + step]); }
        }
        step--;
       
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
