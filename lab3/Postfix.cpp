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
	OP_ex1.push_back("("); //0 скобки !обязательно! в 0 1 храняться
	OP_ex1.push_back(")"); //1
	OP_ex1.push_back("+"); //2
	OP_ex1.push_back("-"); //3
	OP_ex1.push_back("*"); //4
	OP_ex1.push_back("/"); //5
	OP_ex1.push_back("^"); //6
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
	OP_prf = {};
	operand = {};
	if (PRF != "")
	{
		PRF = erase_gap(PRF);
		disassemble(PRF);
		Make_Postfix();
		Make_PSTF_str();
	}
}

void Postfix::Set_unknow_operand(vector<string> Ts)
{
	vector<string> temp = Get_unknow_value();
	if (Ts.size() > temp.size()) throw("Stack very big!");
	int index = 0;
	for (int i = 0; i < operand.size(); i++)
	{
		if (index == Ts.size()) break;
		if (this_unknow_operand(operand[i]))
		{
			operand[i] = Ts[index++];
		}
	}
	Make_Postfix();
	Make_PSTF_str();
}

bool Postfix::disassemble(const string PRF1)
{
	string tmp=""; // буфер
	int bkt_pot = 0; // показатель равновесия скобок : если встречена ( , то +1 , если встречена ) , то -1
	bool ind = 0; //показатель открытости скобки с минусом (- ... : будет равен 1, пока не встречена )
	for (int x = 0; x < PRF1.size()+1; x++)
	{
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (x == PRF1.size())    // чтобы всё выполнилось до конца
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

			break;
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (PRF1[x] == '(') // если встречена ( , то...
		{
			if (ind == 1) throw("Incorrect input!");  // после (- ожидался операнд и ) , а встречена ( , => ошибка

			if (x == PRF1.size() - 1) throw("The last simbol incorrect!");// если это  последний символ в строчке, то это ошибка

			if (OP_prf.size() != 0)  // если это не первая операция, то...
			{
				if (OP_prf[OP_prf.size() - 1] == ")") throw("Incorrect input");  // если последняя операция ) , то это ошибка
			}

			++bkt_pot;    // прибавляем к показателю скобок 1

			for (int y = 0; y < OP_ex2.size(); y++)   // запускаем проверку на совпадение многосимвольных операций
			{
				if (tmp == OP_ex2[y])              // если такая операция нашлась , то ...
				{
					OP_prf.push_back(OP_ex2[y]);   // добавляем операцию в вектор OP_prf
					tmp = "////";  // присваиваем буферу //// 
					break;    // выходим из цикла поиска многосимвольных опреаций

				}
			}

			if (PRF1[x + 1] == '-') // если следующий символ - , то ...
			{
				if (tmp != "////")
				{
					ind = 1; // индикатору присваивается единица
					OP_prf.push_back("(-"); // добавляем к операторам унарный -
					++x; // вымещаем минус и идем дальше
					continue;
				}
				else throw ("Incorrect Input!");
			}

			if (tmp == "////") // если буфер сравним с //// , то ...
			{
				tmp = ""; // очищаем буфер
				continue; // переходим к следующему символу в строчке
			}
			if (tmp != "")	throw("Incorrect input"); // если по итогу буфер не пуст, то это ошибка
			OP_prf.push_back("("); // все условия для определения ( выполнены, можно спокойно её добавить
			continue;		
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (PRF1[x] == ')') // если встречена ) , то...
		{
			if (bkt_pot < 1) throw ("Incorrect input!");   // если закрывающих скобок будет больше , то это ошибка

			if (tmp == "") // если буфер пуст, то...
			{
				if (OP_prf[OP_prf.size() - 1] != ")") throw("Incorrect input"); // если последняя операция не ) , то это ошибка
			}

			--bkt_pot;  // отнимаем от показателя скобок 1


			if (ind == 1) // после (- ожидался операнд и ) 
			{
				ind = 0; // присваиваем индекатору 0	
			}

			if (tmp != "") operand.push_back(tmp); //добавляем значение буфера к операндам
			OP_prf.push_back(")"); //добавляем ) в буфер операций
			tmp = ""; // обнуляем буфер
			continue; // переходим к следующему символу
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		string buf; // создаем буфер для хранения потенциальной операции
		for (int z = 0; z < OP_ex1.size(); z++) // запускаем цикл поиска односимвольных операций
		{
			if (PRF1[x] == OP_ex1[z][0]) // если символ совпал с операцией , то ...
			{
				if (x == 0) throw("Incorrect input!");
				if (tmp == "") // если буфер пустой
				{
					if (OP_prf[OP_prf.size() - 1] != ")") throw("Incorrect input"); // если последняя операция не ) , то это ошибка
					if (OP_prf[OP_prf.size() - 1] == ")") // если последняя операция ) , то ...
					{
						// мы ничего не добавляем к операндам
						buf = OP_ex1[z]; // кидаем операцию в буфер
						tmp = "////";  // присваиваем буферу ////
						break;    // выходим из цикла поиска односимвольных опреаций
					}
				}
				
				buf = OP_ex1[z];
				operand.push_back(tmp);  //добавляем значение буфера к операндам
				tmp = "////";  // присваиваем буферу ////
				break;    // выходим из цикла поиска односимвольных опреаций
			}
		}

		if (tmp == "////")
		{
			if (ind == 1) throw("Incorrect input!");  // после (- ожидался операнд и ) , а встречена не ) , => ошибка
			tmp = "";
			OP_prf.push_back(buf);
			continue;
		}

		if (OP_prf.size() != 0)  // если это не первая операция, то...
		{
			if (OP_prf[OP_prf.size() - 1] == ")") throw("Incorrect input");  // если последняя операция ) , то это ошибка
		}

		tmp += PRF1[x];

	}
	if (bkt_pot != 0) throw ("Incorrect input");

	return 1;
}

int Postfix::check_level_OP(string OP)
{
	if (OP == "+" || OP == "-") return 1;
	if (OP == "*" || OP == "/") return 2;
	if (OP == "^") return 3;

	return 0;
}

bool Postfix::Make_Postfix()
{
	PSTF = {};
	if (OP_prf.size() == 0 && operand.size() == 1)
	{
		PSTF.push_back(operand[0]);
		return 0;
	}
	int on_pos = 0; // позиция в векторе операндов
	if (operand.size() != 1) PSTF.push_back(operand[on_pos++]); // добавляем первый операнд
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
				ind = 1; // что с ним делать?

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
	PSTF_str = "";
	for (int i = 0; i < PSTF.size(); i++)
	{
		if (i == PSTF.size() - 1) PSTF_str += PSTF[i];
		else
		PSTF_str += PSTF[i] + ',';
	}
}

bool Postfix::there_is_unknow_value()
{
	for (int x = 0; x < operand.size(); ++x)
	{
		if (this_unknow_operand(operand[x])) return 1;
	}

	return 0;
}

double Postfix::calc()
{
	if (there_is_unknow_value()) throw ("There is unknow value!");
	TStack<double> op_nd;
	for (int x = 0; x < PSTF.size(); ++x)
	{


		SWITCH(PSTF[x])
		{
			CASE("+") :
			{
				double res;
				res = op_nd.pop();
				res += op_nd.pop();
				op_nd.push(res);

				break;
			}
			CASE("-") :
			{
				double res;
				res = op_nd.pop();
				res = op_nd.pop() - res;
				op_nd.push(res);

				break;
			}
			CASE("(-)") :
			{
				double res;
				res = op_nd.pop();
				if (res > 0) res -= 2 * res;
				else res += 2 * res;
				op_nd.push(res);

				break;
			}
			CASE("*") :
			{
				double res;
				res = op_nd.pop();
				res *= op_nd.pop();
				op_nd.push(res);

				break;
			}
			CASE("/") :
			{
				double res;
				res = op_nd.pop();
				res = op_nd.pop() / res;
				op_nd.push(res);

				break;
			}
			CASE("^") :
			{
				double res;
				res = op_nd.pop();
				res = powf(op_nd.pop(),res);
				op_nd.push(res);

				break;
			}
			CASE("sin()") :
			{
				double res;
				res = op_nd.pop();
				res = sin(res);
				op_nd.push(res);

				break;
			}
			CASE("cos()") :
			{
				double res;
				res = op_nd.pop();
				res = cos(res);
				op_nd.push(res);

				break;
			}
			CASE("tg()") :
			{
				double res;
				res = op_nd.pop();
				res = tan(res);
				op_nd.push(res);

				break;
			}
			CASE("ctg()") :
			{
				double res;
				res = op_nd.pop();
				res = tan(res);
				res = 1 / res;
				op_nd.push(res);

				break;
			}
			CASE("exp()") :
			{
				double res;
				res = op_nd.pop();
				res = exp(res);
				op_nd.push(res);

				break;
			}
			CASE("abs()") :
			{
				double res;
				res = op_nd.pop();
				res = abs(res);
				op_nd.push(res);

				break;
			}
			CASE("sign()") :
			{
				double res;
				res = op_nd.pop();
				if (res > 0.0) res = 1.0;
				if (res == 0.0) res = 0.0;
				if (res < 0.0) res = -1.0;
				op_nd.push(res);

				break;
			}
			CASE("ln()") :
			{
				double res;
				res = op_nd.pop();
				res = log(res);
				op_nd.push(res);

				break;
			}
			DEFAULT :
			{
				op_nd.push(stod(PSTF[x]));
			}
		}
	}

	return op_nd.pop();
}

vector<string> Postfix::Get_unknow_value()
{
	vector<string> vs;

	for (int i = 0; i < operand.size(); ++i)
	{
		if (this_unknow_operand(operand[i])) vs.push_back(operand[i]);
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

vector<string> Postfix::Get_OP_ex1()
{
	return OP_ex1;
}

vector<string> Postfix::Get_OP_ex2()
{
	return OP_ex2;
}