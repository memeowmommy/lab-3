// хеш-таблица "со списками"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class HashTable
{
private:
    int m_size;
    vector<vector<string>> m_table;

public:
    HashTable(int s) : m_size(s)
    {
        for (int i = 0; i < m_size; i++)
        {
            m_table.push_back({});
        }
    }

    void fillWithLists(const string& str)
    {
        int ind = hash(str);
        m_table[ind].push_back(str);
    }

    int hash(const string& s)
    {
        int hashValue = 0;
        for (char ch : s)
        {
            hashValue += static_cast<int>(ch);
        }
        return hashValue % m_size;
    }

    int getSize() const { return m_size; }
    const vector<string>& operator[](int i) const { return m_table[i]; }
};

int main()
{
    ifstream in;
    in.open("in.txt");

    string el;
    int size = 0;

    while (in >> el)
    {
        size++;
    }

    in.close();
    in.open("in.txt");

    string current;

    HashTable table(size);

    while (in >> current)
    {
        table.fillWithLists(current);
    }

    in.close();

    ofstream out;
    out.open("out.txt");

    out << "Key | Value" << endl;

    for (int i = 0; i < table.getSize(); i++)
    {
        out << i << "\t";

        for (const auto& value : table[i])
        {
            out << value << "    ";
        }
        out << "\n";
    }
    out.close();
}