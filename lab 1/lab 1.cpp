/*
Лаба №1 "Задача о скобках"
(Задача состоит из двух пунктов, но вы можете не париться и делать сразу второй)
На вход подаётся строка, состоящая из скобок. Программа должна определить правильность введённого скобочного 
выражения. Савкин сказал, что программа должна работать на русском языке: 
"Введите строку", "Строка не существует", "Строка существует" и т.п.
Пункт 1: В строке будут скобки только одного типа: или "()" , или "{}", или "[]"
Пункт 2: В строке будут все три вида скобок
Для успешной сдачи лабы оба пункта программа должна выполнять корректно (можно сделать отдельные программы на 
каждый пункт)

Пример входа:
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
		cout << "введите строку: " << endl;
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

		if ((stack.empty() == 1) and (existence == 1)) {cout << "cтрока существует !!" << endl;}
		else {cout << "cтрока не существует :((" << endl;}
	}
}