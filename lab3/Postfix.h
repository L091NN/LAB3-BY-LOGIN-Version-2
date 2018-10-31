#ifndef __TPOSTFIX_H__
#define __TPOSTFIX_H__

#include <iostream>
#include <vector>
#include "TStack.h"

using namespace std;




class TPostfix
{
	string PRF;
	vector<string> OP_ex; // доступные операции
	TStack<string> OP_s;  // стек операций
	vector<string> OP_prf;// упорядоченные операции префиксного вида
	vector<string> operand; // упорядоченныt операнды префиксного вида

	void fill()
	{
		OP_ex.push_back("+"); //0
		OP_ex.push_back("-"); //1
		OP_ex.push_back("*"); //2
		OP_ex.push_back("/"); //3
		OP_ex.push_back("%"); //4
		OP_ex.push_back("("); //5
		OP_ex.push_back(")"); //6
	}

	void disassemble(string PRF1)
	{
		vector <int> OP_n;
		vector <string> OP_d;
		vector <int> NOP_n;

		for (int x = 0; x < OP_ex.size(); x++)
		{
			string tmp = "";
			for (int y = 0; y < PRF1.size(); y++)
			{
				
				if (PRF1.size() - y <= OP_ex[x].size()) 
					continue;
				int count = 0;
				for (int z = 0; z < OP_ex[x].size(); z++)
				{
					if (OP_ex[x][z] != PRF1[y + z])
					{
						count++;
					}
				}
				if (count == 0)
				{
					OP_d.push_back(tmp);
					tmp = "";
					OP_n.push_back(x);
					NOP_n.push_back(y);
					x += (OP_ex[x].size() - 1);
				}
			}
		}

		//остается отсортировать OP_n и NOP_n и распихать OP_prf и Operand
	}
public:
	TPostfix(string PRF1 = "")
	{
		fill();


	}
	~TPostfix()
	{

	}
	void set_prf(string PRF1)
	{

	}

};


#endif
