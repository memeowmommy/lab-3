//сортировка Шелла
#include<iostream>
#include<vector>
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
    for (int step = v.size() / 2; step > 0; step /= 2)
    {
        for (int i = step; i < v.size(); i++)
        {
            int tmp = v[i];
            int j;
            for (j = i; (j >= step) and (v[j - step] > tmp); j -= step)
            {
                v[j] = v[j - step];
            }
            v[j] = tmp;
        }

        cout << "Step: " << step << endl;
        cout << "Sorting:" << endl;
        Output(v);
    }
}

int main()
{
    int size = 0;

    vector<int> v;

    cout << "Enter the size: " << endl;
    cin >> size;
    cout << "Enter elements: " << endl;

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
