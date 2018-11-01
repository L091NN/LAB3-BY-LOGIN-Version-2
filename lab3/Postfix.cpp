#include"Postfix.h"

Postfix::Postfix(string PRF1)
{
	PRF = PRF1;
	fill_OP_ex1();
	fill_OP_ex2();
}

Postfix::~Postfix()
{

}

void Postfix::fill_OP_ex1()
{
	OP_ex1.push_back("("); //0
	OP_ex1.push_back(")"); //1
	OP_ex1.push_back("+"); //2
	OP_ex1.push_back("-"); //3
	OP_ex1.push_back("*"); //4
	OP_ex1.push_back("/"); //5
	OP_ex1.push_back("%"); //6
	OP_ex1.push_back("^"); //7
}

void Postfix::fill_OP_ex2()
{
	OP_ex2.push_back("sin"); //0
	OP_ex2.push_back("cos"); //1
	OP_ex2.push_back("tg"); //2
	OP_ex2.push_back("ctg"); //3
	OP_ex2.push_back("exp"); //4
	OP_ex2.push_back("abs"); //5
	OP_ex2.push_back("sign"); //6
	OP_ex2.push_back("ln"); //7

}


void Postfix::set_prf(string PRF1)
{

}

void Postfix::disassemble(string PRF1)
{
	string tmp = "";
	for (int x = 0; x < PRF1.size(); x++)
	{
		if (PRF1[x] == '(')
		{
			if (tmp == "")
			{
				OP_prf.push_back("(");
				continue;
			}
			else
			{
				for (int i = 0; i < OP_ex2.size(); i++)
				{
					if (OP_ex2[i] == tmp)
					{
						OP_prf.push_back(tmp);
						tmp = "";
						break;
					}
				}
				if (tmp != "") throw ("Incorrect input!");
				continue;
			}
		}

		for (int y = 0; y < OP_ex1.size(); y++) //
		{
			
			if (PRF1[x] == OP_ex1[y][0])
			{
				if (tmp == "")
				{
					throw("Incorrect input!");
				}
				else
				{
					operand.push_back(tmp);
					tmp = "////";
					OP_prf.push_back(OP_ex1[y]);
					break;
				}
			}
		}
		if (tmp == "////") tmp = "";
		else tmp += PRF1[x];
		for (int i = 0; i < OP_prf.size(); i++)
			cout << OP_prf[i][0] << endl;
	}
		
}

vector<string> Postfix::GetOP_prf()
{
	return OP_prf;
}