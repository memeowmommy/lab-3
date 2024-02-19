// хеш-таблица "с наложением"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class HashElement
{
private:
	int m_key;
	string m_data;

public:
	HashElement(int key, string data) : m_key(key), m_data(data) {};

	string getData() { return m_data; }

	int getKey() { return m_key; }
};


class HashTable
{
private:
	vector<HashElement> m_hash_table;
	unsigned int start_size = 12;

public:
	HashTable()
	{
		for (int i = 0; i < start_size; ++i)
		{
			m_hash_table.push_back(HashElement(i, ""));
		}
	};

	int GetStartSize() { return start_size; }

	int HashFunc(const string& str)
	{
		int hash = 0;

		for (int i = 0; i < str.size(); i++)
		{
			hash += (str[i] - '0');
		}
		return (hash / 23);
	}

	int GetSize() { return m_hash_table.size(); }

	string GetData(const string& str)
	{
		int key = HashFunc(str);

		for (int i = key; i < m_hash_table.size(); ++i)
		{
			if (m_hash_table[i].getData() == str) { return m_hash_table[i].getData(); }
		}
		return "No such data";
	}

	void HashTableInsert(const string data)
	{
		int key = HashFunc(data);

		if (key >= m_hash_table.size()) { m_hash_table.push_back(HashElement(key, data)); }
		else
		{
			int i = key;
			bool flag = false;

			while (m_hash_table[i].getData() != "") { i++; }

			if (m_hash_table.size() < i) { m_hash_table.push_back(HashElement(key, data)); }
			else { m_hash_table[i] = HashElement(key, data); }
		}
	}

	HashElement operator[] (int key) { return m_hash_table[key]; }
};

int main()
{
	HashTable table;
	string line;
	int n = 1;

	ifstream in("in.txt");
	ofstream out;

	if (in.is_open())
	{
		while (getline(in, line))
		{
			table.HashTableInsert(line);
			cout << n << " - " << table.GetData(line) << endl;
			n++;
		}
	}
	in.close();

	out.open("out.txt", ios::out | ios::trunc);
	out << "Index | Key | Element" << "\n";
	int i = 0;
	for (i; i < table.GetSize() - 1; i++)
	{
		out << i << "   -   " << table[i].getKey() << "   -   " << table[i].getData() << "\n";
	}

	out << i << "   -   " << table[i].getKey() << "   -   " << table[i].getData();
	out.close();
}