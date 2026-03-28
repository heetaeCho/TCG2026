// File: tests/approx_operator_minus_tests_705.cpp

#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"

using Catch::Approx;

class ApproxNegationTest_705 : public ::testing::Test {};

// [Normal] Negating a positive value should yield a representation with a '-' sign
TEST_F(ApproxNegationTest_705, NegatesPositiveValue_705) {
    const Approx a(2);          // use integer to avoid formatting surprises
    const Approx b = -a;

    const std::string aStr = a.toString();
    const std::string bStr = b.toString();

    // Observable behavior: string representations differ and the negated one shows a minus
    EXPECT_NE(aStr, bStr);
    // We expect "-2" to appear somewhere in the representation of b
    EXPECT_NE(std::string::npos, bStr.find("-2"));
    // And original should *not* show "-2"
    EXPECT_EQ(std::string::npos, aStr.find("-2"));
}

// [Normal] Double negation should restore the original observable representation
TEST_F(ApproxNegationTest_705, DoubleNegationRestores_705) {
    const Approx a(2);
    const Approx b = -(-a);

    EXPECT_EQ(a.toString(), b.toString());
}

// [Boundary] Negating a negative value should remove the minus sign in its representation
TEST_F(ApproxNegationTest_705, NegatesNegativeValueToPositive_705) {
    const Approx a(-3);
    const Approx b = -a;

    const std::string aStr = a.toString();
    const std::string bStr = b.toString();

    // Original should show "-3"
    EXPECT_NE(std::string::npos, aStr.find("-3"));
    // Negated should show "3" but not "-3"
    EXPECT_NE(std::string::npos, bStr.find("3"));
    EXPECT_EQ(std::string::npos, bStr.find("-3"));
}

// [Behavioral] Negation should not mutate the original object (const-correctness / copy semantics)
TEST_F(ApproxNegationTest_705, OriginalUnchangedAfterNegation_705) {
    const Approx a(2);
    const std::string before = a.toString();

    const Approx b = -a;  // create a negated copy

    const std::string after = a.toString();
    EXPECT_EQ(before, after) << "Unary minus must not mutate the source Approx";
    EXPECT_NE(before, b.toString());
}
