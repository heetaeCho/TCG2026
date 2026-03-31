#include <gtest/gtest.h>
#include "catch2/catch_approx.hpp"
#include <limits>
#include <cmath>

using Catch::Approx;

// ==================== Normal Operation Tests ====================

TEST(ApproxNotEqualTest_696, NotEqualWithDifferentValues_696) {
    Approx approx(1.0);
    EXPECT_TRUE(approx != 2.0);
}

TEST(ApproxNotEqualTest_696, NotEqualWithSignificantlyDifferentValues_696) {
    Approx approx(1.0);
    EXPECT_TRUE(approx != 1.5);
}

TEST(ApproxNotEqualTest_696, NotEqualReturnsFalseForEqualValues_696) {
    Approx approx(1.0);
    EXPECT_FALSE(approx != 1.0);
}

TEST(ApproxNotEqualTest_696, NotEqualReturnsFalseForApproxEqualValues_696) {
    // Values within default epsilon should be considered equal
    double value = 1.0;
    double epsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double nearValue = value + value * epsilon * 0.5;
    Approx approx(value);
    EXPECT_FALSE(approx != nearValue);
}

TEST(ApproxNotEqualTest_696, NotEqualReturnsTrueForValuesOutsideEpsilon_696) {
    double value = 1.0;
    double epsilon = static_cast<double>(std::numeric_limits<float>::epsilon()) * 100.0;
    double farValue = value + value * epsilon * 2.0;
    Approx approx(value);
    EXPECT_TRUE(approx != farValue);
}

TEST(ApproxNotEqualTest_696, NotEqualWithIntegerType_696) {
    Approx approx(5.0);
    EXPECT_TRUE(approx != 10);
}

TEST(ApproxNotEqualTest_696, NotEqualWithIntegerTypeSameValue_696) {
    Approx approx(5.0);
    EXPECT_FALSE(approx != 5);
}

TEST(ApproxNotEqualTest_696, NotEqualWithFloatType_696) {
    Approx approx(3.14);
    EXPECT_TRUE(approx != 2.71f);
}

TEST(ApproxNotEqualTest_696, NotEqualWithNegativeValues_696) {
    Approx approx(-1.0);
    EXPECT_TRUE(approx != 1.0);
}

TEST(ApproxNotEqualTest_696, NotEqualWithNegativeValuesSame_696) {
    Approx approx(-1.0);
    EXPECT_FALSE(approx != -1.0);
}

// ==================== Custom Epsilon Tests ====================

TEST(ApproxNotEqualTest_696, NotEqualWithCustomEpsilon_696) {
    Approx approx = Approx(1.0).epsilon(0.1);
    // 1.05 is within 10% of 1.0, so they should be "equal"
    EXPECT_FALSE(approx != 1.05);
}

TEST(ApproxNotEqualTest_696, NotEqualWithCustomEpsilonOutsideRange_696) {
    Approx approx = Approx(1.0).epsilon(0.01);
    // 1.5 is outside 1% of 1.0
    EXPECT_TRUE(approx != 1.5);
}

// ==================== Custom Margin Tests ====================

TEST(ApproxNotEqualTest_696, NotEqualWithCustomMargin_696) {
    Approx approx = Approx(1.0).margin(0.5);
    // 1.3 is within margin of 0.5
    EXPECT_FALSE(approx != 1.3);
}

TEST(ApproxNotEqualTest_696, NotEqualWithCustomMarginOutsideRange_696) {
    Approx approx = Approx(1.0).margin(0.1);
    // 1.5 is outside margin of 0.1
    EXPECT_TRUE(approx != 1.5);
}

// ==================== Boundary Conditions ====================

TEST(ApproxNotEqualTest_696, NotEqualWithZeroValue_696) {
    Approx approx(0.0);
    EXPECT_FALSE(approx != 0.0);
}

TEST(ApproxNotEqualTest_696, NotEqualZeroAndSmallValue_696) {
    // With default margin of 0, small values near zero should not be equal
    Approx approx(0.0);
    EXPECT_TRUE(approx != 0.001);
}

TEST(ApproxNotEqualTest_696, NotEqualZeroWithMargin_696) {
    Approx approx = Approx(0.0).margin(0.01);
    EXPECT_FALSE(approx != 0.005);
}

TEST(ApproxNotEqualTest_696, NotEqualWithVeryLargeValues_696) {
    double large = 1e15;
    Approx approx(large);
    EXPECT_FALSE(approx != large);
    EXPECT_TRUE(approx != large * 2.0);
}

TEST(ApproxNotEqualTest_696, NotEqualWithVerySmallValues_696) {
    double small = 1e-15;
    Approx approx(small);
    EXPECT_FALSE(approx != small);
}

// ==================== Negated Approx Tests ====================

TEST(ApproxNotEqualTest_696, NotEqualWithNegatedApprox_696) {
    Approx approx = -Approx(1.0);
    EXPECT_FALSE(approx != -1.0);
    EXPECT_TRUE(approx != 1.0);
}

// ==================== Symmetry / Consistency Tests ====================

TEST(ApproxNotEqualTest_696, NotEqualIsConsistentWithEqual_696) {
    Approx approx(1.0);
    double val = 1.0;
    // != should be the negation of ==
    bool eq = (val == approx);
    bool neq = (approx != val);
    EXPECT_NE(eq, neq);
}

TEST(ApproxNotEqualTest_696, NotEqualIsConsistentWithEqualDifferentValues_696) {
    Approx approx(1.0);
    double val = 2.0;
    bool eq = (val == approx);
    bool neq = (approx != val);
    EXPECT_NE(eq, neq);
}

// ==================== Scale Tests ====================

TEST(ApproxNotEqualTest_696, NotEqualWithScale_696) {
    Approx approx = Approx(1.0).scale(10.0);
    // With a larger scale, the tolerance window should be wider
    EXPECT_FALSE(approx != 1.0);
}

// ==================== operator() creates new Approx ====================

TEST(ApproxNotEqualTest_696, NotEqualWithCallOperator_696) {
    Approx approx = Approx(0.0).epsilon(0.01).margin(0.001);
    Approx approx2 = approx(5.0);
    EXPECT_FALSE(approx2 != 5.0);
    EXPECT_TRUE(approx2 != 10.0);
}

// ==================== Multiple numeric types ====================

TEST(ApproxNotEqualTest_696, NotEqualWithLongType_696) {
    Approx approx(100.0);
    long val = 100L;
    EXPECT_FALSE(approx != val);
}

TEST(ApproxNotEqualTest_696, NotEqualWithUnsignedType_696) {
    Approx approx(42.0);
    unsigned int val = 42u;
    EXPECT_FALSE(approx != val);
    EXPECT_TRUE(approx != 43u);
}

TEST(ApproxNotEqualTest_696, NotEqualWithShortType_696) {
    Approx approx(7.0);
    short val = 7;
    EXPECT_FALSE(approx != val);
    EXPECT_TRUE(approx != static_cast<short>(8));
}
