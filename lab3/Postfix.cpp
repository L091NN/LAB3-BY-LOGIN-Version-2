#include"Postfix.h"

Postfix::Postfix(string PRF1)
{
	fill_OP_ex1();
	fill_OP_ex2();
	Set_prf(PRF1);
}

Postfix::Postfix(const Postfix &P)
{
	PRF = P.PRF;
	OP_ex1 = P.OP_ex1;
	OP_ex2 = P.OP_ex2;
	OP_prf = P.OP_prf;
	PSTF = P.PSTF;
	PSTF_str = P.PSTF_str;
}

Postfix::~Postfix()
{

}

void Postfix::fill_OP_ex1()
{
	OP_ex1.push_back("("); //0 ������ !�����������! � 0 1 ���������
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

string Postfix::erase_gap(string STR1)
{
	string STR2(STR1);
	int ind_ch = 0;
	for (int i = 0; i < STR2.size(); i++)
	{
		if (STR2[i] == ' ')
		{
			STR2.erase(i, 1);
			--i;
		}
	}

	return STR2;
}

void Postfix::Set_prf(string PRF1)
{
	PRF = PRF1;
	if (PRF != "")
	{
		PRF = erase_gap(PRF);
		disassemble(PRF);
		Make_Postfix();
		Make_PSTF_str();
	}
}

void Postfix::Set_unknow_operand(TStack<string> Ts)
{
	TStack<string> temp = Get_unknow_value();

	vector <string> S = {};
	for (int i = 0; !temp.is_empty(); ++i)
	{
		S.push_back(temp.pop());
	}


}

bool Postfix::disassemble(const string PRF1)
{
	string tmp=""; // �����
	int bkt_pot = 0; // ���������� ���������� ������ : ���� ��������� ( , �� +1 , ���� ��������� ) , �� -1
	bool ind = 0; //���������� ���������� ������ � ������� (- ... : ����� ����� 1, ���� �� ��������� )
	for (int x = 0; x < PRF1.size()+1; x++)
	{
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (x == PRF1.size())    // ����� �� ����������� �� �����
		{
			if (tmp == "")
			{
				if (OP_prf[OP_prf.size() - 1] != ")")
				{
					throw("The last simbol incorrect!");
				}
			}
			else
			{
				operand.push_back(tmp);
				tmp = "";
			} 
			//cout << x << ' ';
			//for (int i = 0; i < OP_prf.size(); i++)
			//{
			//	for (int j = 0; j < OP_prf[i].size(); j++)
			//		cout << OP_prf[i][j];
			//	cout << " ";
			//}

			//cout << " operand: ";
			//for (int i = 0; i < operand.size(); i++)
			//	cout << '|' << operand[i][0];
			//cout << endl;

			break;
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (PRF1[x] == '(') // ���� ��������� ( , ��...
		{
			if (ind == 1) throw("Incorrect input!");  // ����� (- �������� ������� � ) , � ��������� ( , => ������

			if (x == PRF1.size() - 1) throw("The last simbol incorrect!");// ���� ���  ��������� ������ � �������, �� ��� ������

			if (OP_prf.size() != 0)  // ���� ��� �� ������ ��������, ��...
			{
				if (OP_prf[OP_prf.size() - 1] == ")") throw("Incorrect input");  // ���� ��������� �������� ) , �� ��� ������
			}

			++bkt_pot;    // ���������� � ���������� ������ 1

			for (int y = 0; y < OP_ex2.size(); y++)   // ��������� �������� �� ���������� ��������������� ��������
			{
				if (tmp == OP_ex2[y])              // ���� ����� �������� ������� , �� ...
				{
					OP_prf.push_back(OP_ex2[y]);   // ��������� �������� � ������ OP_prf
					tmp = "////";  // ����������� ������ //// 
					break;    // ������� �� ����� ������ ��������������� ��������

				}
			}

			if (PRF1[x + 1] == '-') // ���� ��������� ������ - , �� ...
			{
				if (tmp != "////")
				{
					ind = 1; // ���������� ������������� �������
					OP_prf.push_back("(-"); // ��������� � ���������� ������� -
					++x; // �������� ����� � ���� ������
					continue;
				}
				else throw ("Incorrect Input!");
			}

			if (tmp == "////") // ���� ����� ������� � //// , �� ...
			{
				tmp = ""; // ������� �����
				continue; // ��������� � ���������� ������� � �������
			}
			if (tmp != "")	throw("Incorrect input"); // ���� �� ����� ����� �� ����, �� ��� ������
			OP_prf.push_back("("); // ��� ������� ��� ����������� ( ���������, ����� �������� � ��������
			continue;

				

				
					
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (PRF1[x] == ')') // ���� ��������� ) , ��...
		{
			if (bkt_pot < 1) throw ("Incorrect input!");   // ���� ����������� ������ ����� ������ , �� ��� ������

			if (tmp == "") // ���� ����� ����, ��...
			{
				if (OP_prf[OP_prf.size() - 1] != ")") throw("Incorrect input"); // ���� ��������� �������� �� ) , �� ��� ������
			}

			if (x == PRF1.size() - 1)
			{

			}

			--bkt_pot;  // �������� �� ���������� ������ 1


			if (ind == 1) // ����� (- �������� ������� � ) 
			{
				ind = 0; // ����������� ���������� 0	
			}

			if (tmp != "") operand.push_back(tmp); //��������� �������� ������ � ���������
			OP_prf.push_back(")"); //��������� ) � ����� ��������
			tmp = ""; // �������� �����
			continue; // ��������� � ���������� �������
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		string buf; // ������� ����� ��� �������� ������������� ��������
		for (int z = 0; z < OP_ex1.size(); z++) // ��������� ���� ������ �������������� ��������
		{
			if (PRF1[x] == OP_ex1[z][0]) // ���� ������ ������ � ��������� , �� ...
			{
				if (x == 0) throw("Incorrect input!");
				if (tmp == "") // ���� ����� ������
				{
					if (OP_prf[OP_prf.size() - 1] != ")") throw("Incorrect input"); // ���� ��������� �������� �� ) , �� ��� ������
					if (OP_prf[OP_prf.size() - 1] == ")") // ���� ��������� �������� ) , �� ...
					{
						// �� ������ �� ��������� � ���������
						buf = OP_ex1[z]; // ������ �������� � �����
						tmp = "////";  // ����������� ������ ////
						break;    // ������� �� ����� ������ �������������� ��������
					}
				}
				
				buf = OP_ex1[z];
				operand.push_back(tmp);  //��������� �������� ������ � ���������
				tmp = "////";  // ����������� ������ ////
				break;    // ������� �� ����� ������ �������������� ��������
			}
		}

		if (tmp == "////")
		{
			if (ind == 1) throw("Incorrect input!");  // ����� (- �������� ������� � ) , � ��������� �� ) , => ������
			tmp = "";
			OP_prf.push_back(buf);
			continue;
		}

		if (OP_prf.size() != 0)  // ���� ��� �� ������ ��������, ��...
		{
			if (OP_prf[OP_prf.size() - 1] == ")") throw("Incorrect input");  // ���� ��������� �������� ) , �� ��� ������
		}

		tmp += PRF1[x];

	}
	if (bkt_pot != 0) throw ("Incorrect input");

	return 1;
}

int Postfix::check_level_OP(string OP)
{
	if (OP == "+" || OP == "-") return 1;
	if (OP == "*" || OP == "%" || OP == "/") return 2;
	if (OP == "^") return 3;

	return 0;
}

bool Postfix::Make_Postfix()
{
	int on_pos = 0; // ������� � ������� ���������
	if (operand.size() != 1) PSTF.push_back(operand[on_pos++]); // ��������� ������ �������
	if (!OP_prf.size()) return 0;
	TStack <string> OP_s;
	string operator_now;
	int ind = 1;
	for (int x = 0; x < OP_prf.size() + 1; x++)
	{

		if (x == OP_prf.size())
		{
			while (!OP_s.is_empty())
			{
				if (OP_s.top() == "////")
					OP_s.pop();
				PSTF.push_back(OP_s.pop());
			}

			break;
		}

		string tmp = "";

		operator_now = OP_prf[x];

		for (int y = 2; y < OP_ex1.size(); y++)
		{
			if (OP_ex1[y] == OP_prf[x])
			{
				operator_now = "ex1";
				tmp = OP_prf[x];
				break;
			}
		}
		if (tmp == "")
		for (int y = 0; y < OP_ex2.size(); y++)
		{
			if (OP_ex2[y] == OP_prf[x])
			{
				operator_now = "ex2";
				tmp = OP_prf[x];
				break;
			}
		}

		SWITCH (operator_now)
		{
			CASE("(") :
			{
				OP_s.push("(");
				OP_s.push("////");
				ind = 1; // ��� � ��� ������?

				break;
			}
			CASE("(-") :
			{
				if (on_pos == 0) PSTF.push_back(operand[on_pos++]);
				PSTF.push_back("(-)");
				++x;
				break;
			}
			CASE(")") :
			{
				while (OP_s.top() != "////")
				{
					PSTF.push_back(OP_s.pop());
				}
				OP_s.pop();
				if(OP_s.top() != "(") PSTF.push_back(OP_s.pop() + "()");
				else OP_s.pop();
				if (!OP_s.is_empty()) ind = check_level_OP(OP_s.top());
				else ind = 1;

				break;
			}
			CASE("ex1") :
			{
				if (ind < check_level_OP(tmp))
				{
					OP_s.push(tmp);
					ind = check_level_OP(tmp);
				}
				else
				{
					if (!OP_s.is_empty())
					{
						if (OP_s.top() != "////")
						{
							while (ind >= check_level_OP(tmp))
							{
								PSTF.push_back(OP_s.pop());
								if (OP_s.is_empty()) break;
								if (OP_s.top() == "////") break;
								ind = check_level_OP(OP_s.top());
							}
						}
					}
					OP_s.push(tmp);
					ind = check_level_OP(OP_s.top());
				}

				if (on_pos == 0) PSTF.push_back(operand[on_pos++]);
				PSTF.push_back(operand[on_pos++]);

				break;
			}
			CASE("ex2") :
			{
				if (on_pos == 0) PSTF.push_back(operand[on_pos++]);
				OP_s.push(tmp);
				OP_s.push("////");
				ind = 1;

				
			}

		}

		//cout << endl;
		//cout << x << ' ';
		//for (int i = 0; i < PSTF.size(); i++)
		//{
		//	cout << PSTF[i] << ' , ';
		//}
		//cout << endl;
	}

	
}

bool Postfix::this_unknow_operand(string opn)
{
	string ex_double = ".0123456789";
	for (int y = 0; y < opn.size(); ++y)
	{
		int z = 0;
		for (z; z < ex_double.size(); ++z)
		{
			if (opn[y] == ex_double[z]) break;
		}
		if (z == 11) return 1;
	}

	return 0;
}

void Postfix::Make_PSTF_str()
{
	for (int i = 0; i < PSTF.size(); i++)
	{
		PSTF_str += PSTF[i];
	}
}

bool Postfix::there_is_unknow_value()
{

	string ex_double = ".0123456789";
	for (int x = 0; x < operand.size(); ++x)
	{
		if (this_unknow_operand(operand[x])) return 1;
	}

	return 0;
}

TStack<string> Postfix::Get_unknow_value()
{
	TStack<string> vs;

	for (int i = operand.size(); i >= 0; --i)
	{
		if (this_unknow_operand(operand[i])) vs.push(operand[i]);
	}

	return vs;

}

vector<string> Postfix::Get_OP_prf()
{
	return OP_prf;
}

string Postfix::Get_PRF()
{
	return PRF;
}

vector<string> Postfix::Get_operands()
{
	return operand;
}

string Postfix::Get_Postfix()
{
	return PSTF_str;
}

