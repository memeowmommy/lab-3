/* Лаба №3 "Задача о простых множителях"
На вход дается одно число х, нужно вывести все числа от 1 до х, удовлетворяющие условию :
3 ^ K * 5 ^ L * 7 ^ M = x_i

где K, L, M - натуральные числа или могут быть равны 0.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	double print = 0;
	int X = 0;
	int add = 1;
	bool flag = false;
	cout << "Enter x:  ";
	cin >> print;

	int k_range = pow(print, 1 / 3.0) + 2;
	int l_range = pow(print, 1 / 5.0) + 2;
	int m_range = pow(print, 1 / 7.0) + 2;

	for (int k = 0; k < k_range; k++)
	{
		for (int l = 0; l < l_range; l++)
		{
			for (int m = 0; m < m_range; m++)
			{
				X = pow(3, k) * pow(5, l) * pow(7, m);

				if (X <= print)
				{
					cout << X << ":  K = " << k << " L = " << l << " M = " << m << endl;
					add++;
				}
			}
		}
	}
}
