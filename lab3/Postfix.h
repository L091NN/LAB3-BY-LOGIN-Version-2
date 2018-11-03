#ifndef __TPOSTFIX_H__
#define __TPOSTFIX_H__

#include <iostream>
#include <vector>
#include "TStack.h"
#include "str_switch.h"

using namespace std;




class Postfix
{
	string PRF = {}; // префиксный вид
	vector<string> OP_ex1; // доступные односимвольные операции 
	vector<string> OP_ex2; // доступные многосимвольные операции
	//TStack<string> OP_s = {};  // стек операций
	vector<string> OP_prf = {};// упорядоченные операции префиксного вида
	vector<string> operand = {}; // упорядоченные операнды префиксного вида
	vector<string> PSTF = {}; // все символы в постфиксном виде
	string PSTF_str = {}; // постфиксный вид , т.е. сумма всех символов в постфиксном виде 

	void fill_OP_ex1();
	void fill_OP_ex2();
	bool disassemble(string PRF1);
	bool Make_Postfix();
	void Make_PSTF_str();

public:
		
	Postfix(string PRF1);
	Postfix(const Postfix &P);
	~Postfix();
	void set_prf(string PRF1);


	int check_level_OP(string OP);
	string Get_PRF();
	vector<string> Get_OP_prf();
	vector<string> Get_operands();
	string Get_Postfix();
};


#endif
