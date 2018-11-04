#include "Postfix.h"

#include "gtest.h"

TEST(Postfix, can_create_postfix)
{
	ASSERT_NO_THROW(Postfix p("a+b-(c/d)*ln(f)+h"));
}

TEST(Postfix, can_accept_empty_string)
{
	ASSERT_NO_THROW(Postfix p(""));
}

TEST(Postfix, can_accept_only_one_operand)
{
	ASSERT_NO_THROW(Postfix p("opa"));
}

TEST(Postfix, can_accept_only_one_operand_with_minus)
{
	ASSERT_NO_THROW(Postfix p("(-a)"));
}

TEST(Postfix, can_accept_one_operation)
{
	ASSERT_NO_THROW(Postfix p("a^b"));
}

TEST(Postfix, can_accept_two_operation)
{
	ASSERT_NO_THROW(Postfix p("abs(ln(a))"));
}

TEST(Postfix, throw_when_only_operator_1)
{
	ASSERT_ANY_THROW(Postfix p("+"));
}

TEST(Postfix, throw_when_only_operator_2)
{
	ASSERT_ANY_THROW(Postfix p("sign()"));
}

TEST(Postfix, throw_when_bkt_close_early_bkt_open)
{
	ASSERT_ANY_THROW(Postfix p(")a+b("));
}

TEST(Postfix, throw_when_single_operator_in_a_row)
{
	ASSERT_ANY_THROW(Postfix p("a++b"));
}

TEST(Postfix, throw_when_single_operator_before_bkt_close)
{
	ASSERT_ANY_THROW(Postfix p("(a+b-)"));
}

TEST(Postfix, throw_when_single_operator_after_bkt_open)
{
	ASSERT_ANY_THROW(Postfix p("(-a+b)"));
}

TEST(Postfix, throw_when_bkt_open_after_not_operator)
{
	ASSERT_ANY_THROW(Postfix p("acos(b)"));
}

TEST(Postfix, throw_when_minus_after_operator)
{
	ASSERT_ANY_THROW(Postfix p("cos(-b)"));
}

TEST(Postfix, throw_when_number_bkt_open_and_bkt_close_not_equal)
{
	ASSERT_ANY_THROW(Postfix p("((a/b)"));
}

TEST(Postfix, throw_when_bkt_close_before_not_operator)
{
	ASSERT_ANY_THROW(Postfix p("cos(b)a+v"));
}

TEST(Postfix, throw_when_bkt_close_before_bkt_open)
{
	ASSERT_ANY_THROW(Postfix p("abs(a)(b^c)"));
}

TEST(Postfix, check_correct_postfix_1)
{
	Postfix p("a+b-(c/d)*ln(f)+h");
	string s = "ab+cd/fln()*-h+";

	EXPECT_EQ(s, p.Get_Postfix());
}

TEST(Postfix, check_correct_postfix_2)
{
	Postfix p("(-a)+b+c-d*ln(cos(e))");
	string s = "a(-)b+c+decos()ln()*-";

	EXPECT_EQ(s, p.Get_Postfix());
}

TEST(Postfix, check_correct_postfix_3)
{
	Postfix p("a*cos(b)+(-c)^ln(d+abs(e-f))");
	string s = "abcos()*c(-)def-abs()+ln()^+";

	EXPECT_EQ(s, p.Get_Postfix());
}

TEST(Postfix, check_correct_postfix_4)
{
	Postfix p("sin(cos(tg(ctg(abs(ln(exp(sign(a))))))))");
	string s = "asign()exp()ln()abs()ctg()tg()cos()sin()";

	EXPECT_EQ(s, p.Get_Postfix());
}

TEST(Postfix, check_correct_postfix_5)
{
	Postfix p("sin(cos(tg(ctg(abs(ln(exp(sign((-a)+b^c*d/e-f*g))))))))");
	string s = "a(-)bc^d*e/+fg*-sign()exp()ln()abs()ctg()tg()cos()sin()";

	EXPECT_EQ(s, p.Get_Postfix());
}

TEST(Postfix, check_erase_gap_1)
{
	Postfix p("a");
	string s = "a+b-c*ln(h^j)";

	EXPECT_EQ(s, p.erase_gap("a + b - c * ln( h ^ j)"));
}

TEST(Postfix, check_erase_gap_2)
{
	Postfix p("sin(cos(tg   ( ctg(  abs(  ln(  exp(  sign(  (  -a  ) + b ^  d / e - f * g))  )))  )))");
	string s = "sin(cos(tg(ctg(abs(ln(exp(sign((-a)+b^d/e-f*g))))))))";

	EXPECT_EQ(s, p.erase_gap("sin(cos(tg   ( ctg(  abs(  ln(  exp(  sign(  (  -a  ) + b ^   d / e - f * g))  )))  )))"));
}

TEST(Postfix, check_there_is_unknow_value_if_false)
{
	Postfix p("7 + 8 - 9 * 1");

	EXPECT_EQ(0,p.there_is_unknow_value());
}

TEST(Postfix, check_there_is_unknow_value_if_true)
{
	Postfix p("7 + b - 9 * n");

	EXPECT_EQ(1, p.there_is_unknow_value());
}

TEST(Postfix, throw_when_vector_with_operands_long)
{
	Postfix p("7 + b - 9 * n");
	vector<string> ts;
	ts.push_back("8");
	ts.push_back("8");
	ts.push_back("8");

	ASSERT_ANY_THROW(p.Set_unknow_operand(ts));
}

TEST(Postfix, check_set_uknow_operand)
{
	Postfix p("7 + b - 9 * n");
	string s = "78+98*-";
	vector<string> ts;
	ts.push_back("8");
	ts.push_back("8");
	p.Set_unknow_operand(ts);


	EXPECT_EQ(s,p.Get_Postfix());
}

TEST(Postfix, check_calc_1)
{
	Postfix p(" ((7 * 8) / 2^2 - 4)^2");

	EXPECT_EQ(100, p.calc());
}

TEST(Postfix, check_calc_2)
{
	Postfix p("sign(((-7) * (-7) - 9) * 25 -1000) * exp( sin (3.1415)) / (1 + 1/10000) ^ 10000 ");

	EXPECT_EQ(0, p.calc());
}

TEST(Postfix, throw_when_one_unknow_operator)
{
	Postfix p("sign(((-a) * (-7) - 9) * 25 -1000) * exp( sin (3.1415)) / (1 + 1/10000) ^ 10000 ");

	ASSERT_ANY_THROW(p.calc());
}