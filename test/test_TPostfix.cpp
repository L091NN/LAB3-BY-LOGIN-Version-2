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

TEST(Postfix, throw_when_number_bkt_open_and_bkt_close_not_equal)
{
	ASSERT_ANY_THROW(Postfix p("((a/b)"));
}

TEST(Postfix, throw_when_bkt_close_before_not_operator)
{
	ASSERT_ANY_THROW(Postfix p("cos(b)a"));
}

TEST(Postfix, throw_when_bkt_close_before_bkt_open)
{
	ASSERT_ANY_THROW(Postfix p("abs(a)(b^c)"));
}