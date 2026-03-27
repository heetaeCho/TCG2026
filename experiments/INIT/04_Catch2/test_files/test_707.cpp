// File: tests/test_approx_literal_707.cpp

#include <gtest/gtest.h>
#include <catch2/catch_approx.hpp>

using Catch::Approx;

class ApproxLiteralTest_707 : public ::testing::Test {};

// [Normal] Exact equality with same numeric value via literal
TEST_F(ApproxLiteralTest_707, ExactEquality_707) {
    using namespace Catch::literals; // bring "_a" into scope
    EXPECT_TRUE(1.0 == 1.0_a);
    EXPECT_TRUE(123.0 == 123.0_a);
}

// [Boundary-ish sanity] Clearly different values are not equal
TEST_F(ApproxLiteralTest_707, ObviousInequality_707) {
    using namespace Catch::literals;
    EXPECT_FALSE(2.0 == 1.0_a);
    EXPECT_FALSE(-5.0 == 5.0_a);
}

// [Normal] Works seamlessly with long double literals
TEST_F(ApproxLiteralTest_707, WorksWithLongDoubleLiteralSyntax_707) {
    using namespace Catch::literals;
    auto a = 2.5L_a;            // UDL takes long double
    EXPECT_TRUE(2.5 == a);      // observable behavior: compares approximately to the base value
    EXPECT_FALSE(3.0 == a);     // clearly different -> should not compare equal
}

// [Namespace usage] Importing the operator directly (no 'using namespace')
TEST_F(ApproxLiteralTest_707, UsingOperatorImport_707) {
    using Catch::literals::operator ""_a; // import just this UDL
    auto approx = 7.0_a;
    EXPECT_TRUE(7.0 == approx);
    EXPECT_FALSE(8.0 == approx);
}
