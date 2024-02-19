// внешняя многофазная
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream in, in1, in2;
	ofstream out, out1, out2;
	int el, el2, count1, count2, count, size = 0;
	bool is_1full, is_2full, flag = 1;

	in.open("in.txt");
	out.open("out.txt");

	while (in >> el)
	{
		out << el << " ";
		size++;
	}

	in.close();
	out.close();

	for (int part_size = 1; part_size < size; part_size *= 2)
	{
		in.open("out.txt");
		out1.open("1.txt");
		out2.open("2.txt");
		count = 0;
		while (in >> el)
		{
			count++;
			if (flag) { out1 << el << " "; }
			else { out2 << el << " "; }
		
			if (count == part_size)
			{
				count = 0;
				flag = !flag;
			}
		}
		in.close();
		out1.close();
		out2.close();

		in1.open("1.txt");
		in2.open("2.txt");
		out.open("out.txt");

		if (in1 >> el) { is_1full = true; }
		else { is_1full = false; }
		if (in2 >> el2) { is_2full = true; }
		else { is_2full = false; }

		for (int i = 0; i < size; i += 2 * part_size)
		{
			count1 = 0; count2 = 0;
			while (count1 < part_size && is_1full && count2 < part_size && is_2full)
				if (el < el2)
				{
					out << el << " ";
					if (in1 >> el) { is_1full = true; }
					else { is_1full = false; }
					count1++;
				}
				else
				{
					out << el2 << " ";
					if (in2 >> el2) { is_2full = true; }
					else { is_2full = false; }
					count2++;
				}

			while (count1 < part_size && is_1full)
			{
				out << el << " ";
				if (in1 >> el) { is_1full = true; }
				else { is_1full = false; }
				count1++;
			}

			while (count2 < part_size && is_2full)
			{
				out << el2 << " ";
				if (in2 >> el2) { is_2full = true; }
				else { is_2full = false; }
				count2++;
			}
		}
		in1.close();
		in2.close();
		out.close();
		remove("1.txt");
		remove("2.txt");
	}
}