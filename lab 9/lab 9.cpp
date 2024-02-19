//heap
#include <iostream>
#include <vector>
using namespace std;

void Output(vector <int> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void Heapify(vector <int>& v, int size, int i)
{
	int max = i;
	int lef_kid = 2 * i + 1;
	int rig_kid = 2 * i + 2;

	if (lef_kid < size && v[lef_kid] > v[max]) { max = lef_kid; }
	if (rig_kid < size && v[rig_kid] > v[max]) { max = rig_kid; }

	if (max != i)
	{
		swap(v[i], v[max]);
		Heapify(v, size, max);
	}
}

void Sorting(vector <int>& v, int size)
{
	int cur_size = size;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < cur_size; x++)
		{
			Heapify(v, cur_size, cur_size - 1 - x);
		}
		cout << "Sorting: " << endl;
		Output(v);
		if (cur_size != 1) { swap(v[0], v[cur_size - 1]); }
		cur_size--;
	}
}

int main()
{
	int size = 0;
	vector <int> v;
	cout << "Enter the size: " << endl;
	cin >> size;
	cout << "Input elements:" << endl;
	for (int i = 0; i < size; i++)
	{
		int el = 0;
		cin >> el;
		v.push_back(el);
	}

	Sorting(v, size);
	cout << "Sorted: " << endl;
	Output(v);
}