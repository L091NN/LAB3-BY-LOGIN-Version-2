#include"Postfix.h"

Postfix::Postfix(string PRF1 = "")
{
	PRF = PRF1;
	fill_OP_ex1();
	fill_OP_ex2();
	disassemble(PRF);
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


void Postfix::set_prf(string PRF1)
{

}

bool Postfix::disassemble(const string PRF1)
{
	if (PRF1 == "") return 0;
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
			cout << x << ' ';
			for (int i = 0; i < OP_prf.size(); i++)
			{
				for (int j = 0; j < OP_prf[i].size(); j++)
					cout << OP_prf[i][j];
				cout << " ";
			}

			cout << " operand: ";
			for (int i = 0; i < operand.size(); i++)
				cout << operand[i][0];
			cout << endl;

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

				if (PRF1[x + 1] == '-') // ���� ��������� ������ - , �� ...
				{
					ind = 1; // ���������� ������������� �������
					OP_prf.push_back("(-"); // ��������� � ���������� ������� -
					++x; // �������� ����� � ���� ������
					continue;
				}
				else                  // ���� ��������� ������ �� - , �� ...
				{
					for (int y = 0; y < OP_ex2.size(); y++)   // ��������� �������� �� ���������� ��������������� ��������
					{
						if (tmp == OP_ex2[y])              // ���� ����� �������� ������� , �� ...
						{
							OP_prf.push_back(OP_ex2[y]);   // ��������� �������� � ������ OP_prf
							tmp = "////";  // ����������� ������ //// 
							break;    // ������� �� ����� ������ ��������������� ��������

						}
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

			operand.push_back(tmp); //��������� �������� ������ � ���������
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

		//cout << x << ' ';
		//		for (int i = 0; i < OP_prf.size(); i++)
		//			cout << OP_prf[i][0] << " ";
		//		cout << " operand: ";
		//		for (int i = 0; i < operand.size(); i++)
		//			cout << operand[i][0];
		//		cout << endl;



	}
	if (bkt_pot != 0) throw ("Incorrect input");
}

vector<string> Postfix::GetOP_prf()
{
	return OP_prf;
}