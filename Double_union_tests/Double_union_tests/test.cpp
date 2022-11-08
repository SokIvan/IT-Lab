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


}
TEST(Double_union, good_operator_addition) {


}
TEST(Double_union, good_operator_subtraction) {


}
TEST(Double_union, good_operator_multiplication) {


}
TEST(Double_union, good_operator_division) {


}
TEST(Double_union, good_operator_get_mask) {


}
TEST(Double_union, good_operator_Check_expMAX) {


}
TEST(Double_union, good_operator_Check_expMIN) {


}
TEST(Double_union, good_operator_EXP_CHECK) {


}
TEST(Double_union, good_operator_special_infinity_check) {


}
TEST(Double_union, do_DOUBLE_equal_NULL_when_exp_more_then_max_exp) {


}
TEST(Double_union, do_DOUBLE_equal_INFINITY_when_exp_less_then_min_exp) {


}
TEST(Double_union, change_DOUBLE_exactly_when_change_mantiss_count_of_bits) {


}
TEST(Double_union, change_mantiss_exactly_when_change_mantiss_count_of_bits) {


}

TEST(Double_union, good_constructor_copy) {


}
TEST(Double_union, good_work_with_boundary_values_close_to_zero) {


}
TEST(Double_union, good_work_with_boundary_values_close_to_infinity) {


}