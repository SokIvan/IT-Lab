#include "pch.h"

TEST(Double_union, equel_double_with_full_bitfield) {

	double d = 5.13,c;
	DOUBLE<11, 52> a(d);
	int i = 0;
	while (i < 1000)
	{
		EXPECT_EQ(d, a.D.f);
		c = rand() % 1000 + 999 + ((rand() % 100) / 100.0);
		i++;
		d = c; a = c;
	}
}
TEST(Double_union, non_equel_double_with_not_full_bitfild) {

	DOUBLE<11, 3> a1(11.75);
	DOUBLE<11, 14> a2(11.75);
	double d1 = a1.D.f;
	double d2 = a2.D.f;
	EXPECT_EQ((d1==d2),0);
}
TEST(Double_union, good_operator_copy) {
	
	DOUBLE<11, 52> a1(8.25);
	DOUBLE<11, 52> a2(11.75);
	a1 = a2;
	EXPECT_EQ(a1.D.f, 11.75);
}
TEST(Double_union, good_operator_addition) {

	DOUBLE<11, 52> a1(8.25);
	DOUBLE<11, 52> a2(11.75);
	a1 = a1 + a2;
	EXPECT_EQ(a1.D.f, 20.0);
}
TEST(Double_union, good_operator_subtraction) {

	DOUBLE<11, 52> a1(8.25);
	DOUBLE<11, 52> a2(11.75);
	a1 = a1 - a2;
	EXPECT_EQ(a1.D.f, -3.5);
}
TEST(Double_union, good_operator_multiplication) {

	DOUBLE<11, 52> a1(8.25);
	DOUBLE<11, 52> a2(11.75);
	a1 = a1 * a2;
	EXPECT_EQ(a1.D.f, 96.9375);
}
TEST(Double_union, good_operator_division) {

	DOUBLE<11, 52> a1(36.5625);
	DOUBLE<11, 52> a2(3.75);
	a1 = a1 / a2;
	EXPECT_EQ(a1.D.f, 9.75);
}
TEST(Double_union, good_operator_Check_expMAX) {

	DOUBLE<1, 10> a1(4.0);
	DOUBLE<1, 10> a2(1.25);
	EXPECT_EQ(a1.D.f, INFINITY);
	EXPECT_EQ(a1.Check_expMAX(), 0);
	EXPECT_EQ(a2.Check_expMAX(), 1);
}
TEST(Double_union, good_operator_Check_expMIN) {

	DOUBLE<1, 52> a1(0.1);
	DOUBLE<1, 52> a2(2.1);
	EXPECT_EQ(a1.D.f, NULL);
	EXPECT_EQ(a2.Check_expMIN(), 1);
	EXPECT_EQ(a1.Check_expMIN(), 0);
}
TEST(Double_union, do_DOUBLE_equal_NULL_when_exp_more_then_max_exp) {

	DOUBLE<1, 52> a2(0.1);
	EXPECT_EQ(a2.D.f, NULL);
}
TEST(Double_union, do_DOUBLE_equal_INFINITY_when_exp_less_then_min_exp) {

	DOUBLE<1, 10> a1(4.0);
	EXPECT_EQ(a1.D.f, INFINITY);
}
TEST(Double_union, change_DOUBLE_corectly_when_change_mantiss_count_of_bits) {

	DOUBLE<11, 52> a1(3.795245);
	DOUBLE<11, 2> a2(3.795245);

	EXPECT_EQ(a1.D.f, 3.795245);
	EXPECT_EQ(a2.D.f, 3.5);

}
TEST(Double_union, good_constructor_copy) {

	DOUBLE<11, 52> a1(8.25);
	DOUBLE<11, 52> a2(a1);
	EXPECT_EQ(a1.D.f, a2.D.f);
}
TEST(Double_union, good_work_with_boundary_values_close_to_zero) {

	DOUBLE<11, 52> a1(0.00000000575);
	DOUBLE<11, 52> a2(0.00000000825);

	a1 = a1 + a2;
	EXPECT_EQ(a1.D.f, 0.000000014);
}
TEST(Double_union, good_work_with_boundary_values_close_to_infinity) {

	DOUBLE<11, 52> a1(8999998849999999999999999999999999991234.0);
	DOUBLE<11, 52> a2(1000001150000000000000000000000000007666.0);

	a1 = a1 + a2;
	EXPECT_EQ(a1.D.f, 9999999999999999999999999999999999998900.0);
}
TEST(Double_union, Division_by_zer0) {

	DOUBLE<11, 52> a1(8.25);
	DOUBLE<11, 52> a2(0.0);
	EXPECT_ANY_THROW(a1 = a1 / a2);
}
TEST(Double_union, subtraction_of_two_INFINITYS_is_bad) {

	DOUBLE<1, 10> a1(4.0);
	DOUBLE<1, 10> a2(43.0);
	EXPECT_ANY_THROW(a1 - a2);
	EXPECT_ANY_THROW(a2 - a1);

}

TEST(Double_union, multiplication_of_INFINITY_and_zero) {

	DOUBLE<1, 10> a1(4.0);
	DOUBLE<1, 10> a2(0.0);
	EXPECT_ANY_THROW(a1*a2);
	EXPECT_ANY_THROW(a2 * a1);
}