/*
���� �1 "������ � �������"
(������ ������� �� ���� �������, �� �� ������ �� �������� � ������ ����� ������)
�� ���� ������� ������, ��������� �� ������. ��������� ������ ���������� ������������ ��������� ���������� 
���������. ������ ������, ��� ��������� ������ �������� �� ������� �����: 
"������� ������", "������ �� ����������", "������ ����������" � �.�.
����� 1: � ������ ����� ������ ������ ������ ����: ��� "()" , ��� "{}", ��� "[]"
����� 2: � ������ ����� ��� ��� ���� ������
��� �������� ����� ���� ��� ������ ��������� ������ ��������� ��������� (����� ������� ��������� ��������� �� 
������ �����)

������ �����:
()[({}())]
*/

#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	string str;

	bool existence = 1;

	while (str != ".")
	{
		cout << "������� ������: " << endl;
		cin >> str;

		vector<char> stack;

		for (int i = 0; i < str.length(); i++)
		{
			if ((str[i] == '(') or (str[i] == '[') or (str[i] == '{'))	{stack.push_back(str[i]);}
			else if ((str[i] == ')') or (str[i] == ']') or (str[i] == '}'))
			{
				if (stack.empty() == 1)
				{
					existence = 0;
					break;
				}
				else
				{
					if (int(str[i] - stack.back()) <= 2)
					{
						stack.pop_back();
						existence = 1;
					}
				}
			}
		}

		if ((stack.empty() == 1) and (existence == 1)) {cout << "c����� ���������� !!" << endl;}
		else {cout << "c����� �� ���������� :((" << endl;}
	}
}