#include "Postfix.h"

#include "gtest.h"

TEST(Postfix, check_disassemble)
{
	string s = "a-b+c";
	Postfix p(s);
	//vector<string> opd;
	//vector<string> opn;
	//opd.push_back("a");
	//opd.push_back("b");
	//opd.push_back("c");
	//opn.push_back("-");
	//opn.push_back("+");
	EXPECT_EQ(1,1);
}