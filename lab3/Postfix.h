#ifndef __TPOSTFIX_H__
#define __TPOSTFIX_H__

#include <iostream>
#include <vector>
#include "TStack.h"

using namespace std;




class Postfix
{
	string PRF = {}; // префиксный вид
	vector<string> OP_ex1; // доступные односимвольные операции 
	vector<string> OP_ex2; // доступные многосимвольные операции
	TStack<string> OP_s = {};  // стек операций
	vector<string> OP_prf = {};// упорядоченные операции префиксного вида
	vector<string> operand = {}; // упорядоченные операнды префиксного вида
	string PSTF = {}; // постфиксный вид

	


public:
	void fill_OP_ex1();
	void fill_OP_ex2();
	bool disassemble(string PRF1);	
	Postfix(string PRF1);	
	~Postfix();
	void set_prf(string PRF1);

	vector<string> GetOP_prf();

};


#endif
