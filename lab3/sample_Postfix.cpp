#include <iostream>
#include <locale>
#include "Postfix.h"
//---------------------------------------------------------------------------

void main()
{
	setlocale(LC_ALL, "ru");
	Postfix p;
	string s = "";

	while (1)
	{
		system("cls");
		cout << "Доступные операции:" << endl;

		for (int i = 2; i < p.Get_OP_ex1().size(); ++i)
		{
			cout << p.Get_OP_ex1()[i] << ',';
		}
		for (int i = 0; i < p.Get_OP_ex2().size(); ++i)
		{
			if (i == p.Get_OP_ex2().size() - 1)
				cout << p.Get_OP_ex2()[i] + "()";
			else
				cout << p.Get_OP_ex2()[i] + "()" << ',';
		}
		cout << endl << endl;

		cout << "Введите выражение:";
		getline(cin, s);
		p.Set_prf(s);
		cout << "Постфиксный вид : " << p.Get_Postfix();

		cout << endl << endl;

		while (p.there_is_unknow_value())
		{
			cout << p.Get_unknow_value()[0] << '=';
			cin >> s;
			vector<string> vs;
			vs.push_back(s);
			p.Set_unknow_operand(vs);
		}

		system("cls");

		cout << "Введённая строка: " << p.Get_PRF();
		cout << endl << endl;
		cout << "Постфиксный вид: " << p.Get_Postfix();
		cout << endl << endl;
		cout << "Ответ: " << p.calc();
		cout << endl << endl;
		cout << "Ввести новую строку? ";
		
		system("pause");
	}
}
//---------------------------------------------------------------------------
