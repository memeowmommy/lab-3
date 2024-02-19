// поразрядная сортировка
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>
#include<queue>
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
    int max_el = *max_element(v.begin(), v.end());
    string str_max = to_string(max_el);
    int max = str_max.length();

    int base = 10;
    vector<vector<int>> bins(base, vector<int>());
    queue<int> q;

    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < v.size(); j++)
        {
            int digit = (v[j] / static_cast<int>(pow(base, i))) % base; 
            bins[digit].push_back(v[j]);
        }

        v.clear();

        for (const auto& q : bins)
        {
            v.insert(v.end(), q.begin(), q.end());
        }

        cout << "Sorting:" << endl;
        Output(v);

        bins.assign(base, vector<int>());
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