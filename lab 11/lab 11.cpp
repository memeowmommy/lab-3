// быстрая сортировка
//лучшее время - O(n^2), худшее время - O(n log n)
#include <iostream>
#include <vector>
using namespace std;

void Output(std::vector<int>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int Split(vector<int>& v, int start, int end)
{
    // Выбираем крайний правый элемент в качестве опорного элемента массива
    int reference = v[end];

    // элементы, меньшие точки поворота, будут перемещены влево от `ref_ind`
    // элементы больше, чем точка поворота, будут сдвинуты вправо от `ref_ind`
    // равные элементы могут идти в любом направлении
    int ref_ind = start;

    // каждый раз, когда мы находим элемент, меньший или равный опорному, `ref_ind`
    // увеличивается, и этот элемент будет помещен перед опорной точкой.
    for (int i = start; i < end; i++)
    {
        if (v[i] <= reference)
        {
            swap(v[i], v[ref_ind]);
            ref_ind++;
        }
    }
    swap(v[ref_ind], v[end]);

    cout << "Referenced: " << endl;
    cout << v[ref_ind] << endl;
    return ref_ind;
}

void Sorting(vector<int>& v, int start, int end)
{
    if (start >= end) { return; }

    cout << "Sorting: " << endl;
    Output(v);

    // переставить элементы по оси
    int reference = Split(v, start, end);

    // повторяем подмассив, содержащий элементы, меньшие опорной точки
    Sorting(v, start, reference - 1);

    // повторяем подмассив, содержащий элементы, превышающие точку опоры
    Sorting(v, reference + 1, end);
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

    Sorting(v, 0, size - 1);

    cout << "Sorted: " << endl;
    Output(v);
}
