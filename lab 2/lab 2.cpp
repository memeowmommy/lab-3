/*Лаба №2 "Задача об арифметическом выражении"
На вход подаётся математическое выражение. Элементы - числа. Операции - "+ - * /". Также есть скобочки. 
Окончанием выражения служит "=". Программа должна вывести результат выражения

Пример ввода:
2+7*(3/9)-5=

Замечание:
Программа также должна делать "проверку на дурака": нет деления на 0, все скобки стоят верно (см лабу №1) и т.п.
*/

#include <iostream>
#include<vector>
#include<string>
#include<Windows.h>

#include <stdio.h>
#include <stdlib.h>
using namespace std;


string TokenFormer(string exmpl, string ex_mas[], int& leng)
{
	string tempo = "";
	int counter = 0;
	bool len_fl = false;
	for (int x = 0; x <= exmpl.length(); x++)
	{
		bool flag = ((exmpl[x] != '+') and (exmpl[x] != '-') and (exmpl[x] != '*') and (exmpl[x] != '/') and (exmpl[x] != '(') and (exmpl[x] != ')'));

		if ((x == exmpl.length()) and (exmpl[x] == '\0'))
		{
			bool len_fl = true;
			if (tempo != "") { ex_mas[counter] = tempo; leng++; }
		}

		if ((x == exmpl.length()) and (exmpl[x] != '\0'))
		{
			tempo += exmpl[x];
			ex_mas[counter] = tempo;
			leng++;
			bool len_fl = true;
		}

		if (flag == true) { tempo += exmpl[x]; }

		else if (flag == false)
		{
			if (tempo != "")
			{
				ex_mas[counter] = tempo;
				leng++;
				tempo = "";
				counter += 1;
			}

			if (len_fl != true)
			{
				tempo += exmpl[x];
				ex_mas[counter] = tempo;
				leng++;
				tempo = "";
				counter += 1;
			}

		}
	}

	return exmpl;
}

int CheckLenght(string str)
{
	int oper_check = 0;
	for (int x = 0; x < str.length(); x++)
	{
		if ((str[x] == '+') or (str[x] == '-') or (str[x] == '*') or (str[x] == '/') or (str[x] == '(') or (str[x] == ')')) { oper_check += 1; }
	}
	return (oper_check * 2 + 1);
}

double ApllyOperation(double num_1, double num_2, string oper)
{
	if (oper[0] == '+') { return (num_1 + num_2); }
	if (oper[0] == '-') { return (num_1 - num_2); }
	if (oper[0] == '*') { return (num_1 * num_2); }
	if (oper[0] == '/')
	{
		if (num_2 == 0)
		{
			cout << "Критическая ошибка! Деление на 0!" << endl;
			exit(0);
		}
		return (num_1 / num_2);
	}
}

int GetPriority(string obj)
{
	if ((obj[0] == '+') or (obj[0] == '-')) { return 1; }
	if ((obj[0] == '*') or (obj[0] == '/')) { return 2; }
	if ((obj[0] == '(') or (obj[0] == ')')) { return -1; }
	return 0;
}

double MathCalc(string tok_mas[], int leng)
{
	vector<double> num_mas;
	vector<string> oper_mas;

	for (int x = 0; x < leng; x++)
	{
		if (GetPriority(tok_mas[x]) == 0) { num_mas.push_back(stod(tok_mas[x])); }

		else if ((GetPriority(tok_mas[x]) != 0))
		{
			if (oper_mas.empty()) { oper_mas.push_back(tok_mas[x]); }

			else if ((GetPriority(tok_mas[x]) == -1))
			{
				if (tok_mas[x][0] == '(') { oper_mas.push_back(tok_mas[x]); }
				else if (tok_mas[x][0] == ')')
				{
					while (oper_mas.back()[0] != '(')
					{
						if (oper_mas.empty() == true) { break; }
						else if (oper_mas.empty() != true)
						{
							string oper_c = oper_mas.back();
							oper_mas.pop_back();
							double num_2_c = num_mas.back();
							num_mas.pop_back();
							double num_1_c = num_mas.back();
							num_mas.pop_back();
							num_mas.push_back(ApllyOperation(num_1_c, num_2_c, oper_c));
						}
					}
					if (oper_mas.empty() != true) { oper_mas.pop_back(); }
					else if (oper_mas.empty() == true) { break; }
				}
			}

			else if ((GetPriority(tok_mas[x]) == 1) or (GetPriority(tok_mas[x]) == 2))
			{
				if (GetPriority(tok_mas[x]) > GetPriority(oper_mas.back())) { oper_mas.push_back(tok_mas[x]); }
				else if (GetPriority(tok_mas[x]) == GetPriority(oper_mas.back()))
				{
					double num_2 = num_mas.back();
					num_mas.pop_back();
					double num_1 = num_mas.back();
					num_mas.pop_back();
					string oper = oper_mas.back();
					oper_mas.pop_back();
					num_mas.push_back(ApllyOperation(num_1, num_2, oper));
					oper_mas.push_back(tok_mas[x]);
				}

				else if (GetPriority(tok_mas[x]) < GetPriority(oper_mas.back()))
				{
					double num_2 = num_mas.back();
					num_mas.pop_back();
					double num_1 = num_mas.back();
					num_mas.pop_back();
					string oper = oper_mas.back();
					oper_mas.pop_back();
					num_mas.push_back(ApllyOperation(num_1, num_2, oper));
					oper_mas.push_back(tok_mas[x]);

				}
			}
		}
	}

	while (oper_mas.empty() == false)
	{
		if (num_mas.empty() == true) { cout << "Критическая ошибка! Проверьте входные данные." << endl; exit(0); }
		double num_2_e = num_mas.back();
		num_mas.pop_back();
		if (num_mas.empty() == true) { cout << "Критическая ошибка! Проверьте входные данные." << endl; exit(0); }
		double num_1_e = num_mas.back();
		num_mas.pop_back();
		string oper_e = oper_mas.back();
		oper_mas.pop_back();
		num_mas.push_back(ApllyOperation(num_1_e, num_2_e, oper_e));
	}

	if (oper_mas.empty()) { return (num_mas.back()); }
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	string example;
	cout << "Введите выражение: ";
	cin >> example;
	if (!example.empty()) { example.erase(prev(example.end())); }

	int leng = CheckLenght(example);
	int act_leng = 0;

	string* token_mas = new string[leng];

	TokenFormer(example, token_mas, act_leng);
	cout << "act_leng: " << act_leng << endl;

	cout << "Ответ: " << MathCalc(token_mas, act_leng) << endl;

	delete[] token_mas;
}