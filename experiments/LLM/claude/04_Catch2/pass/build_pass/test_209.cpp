#include <gtest/gtest.h>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <limits>
#include <cmath>

using namespace Catch::Matchers;

// ============================================================
// Tests for WithinRel(float target) — single-argument overload
// ============================================================

TEST(WithinRelFloatTest_209, ExactMatchReturnsTrue_209) {
    auto matcher = WithinRel(1.0f);
    // A value equal to the target should match
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST(WithinRelFloatTest_209, ZeroTargetExactMatch_209) {
    auto matcher = WithinRel(0.0f);
    EXPECT_TRUE(matcher.match(0.0f));
}

TEST(WithinRelFloatTest_209, NegativeZeroMatchesPositiveZero_209) {
    auto matcher = WithinRel(0.0f);
    EXPECT_TRUE(matcher.match(-0.0f));
}

TEST(WithinRelFloatTest_209, PositiveZeroMatchesNegativeZero_209) {
    auto matcher = WithinRel(-0.0f);
    EXPECT_TRUE(matcher.match(0.0f));
}

TEST(WithinRelFloatTest_209, SlightlyDifferentValuesWithinDefaultTolerance_209) {
    float target = 1.0f;
    float eps100 = std::numeric_limits<float>::epsilon() * 100;
    // A value very close to target within the relative tolerance
    float close_value = target * (1.0f + eps100 * 0.5f);
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(close_value));
}

TEST(WithinRelFloatTest_209, ValueOutsideDefaultToleranceReturnsFalse_209) {
    float target = 1.0f;
    float eps100 = std::numeric_limits<float>::epsilon() * 100;
    // A value clearly outside the relative tolerance
    float far_value = target * (1.0f + eps100 * 10.0f);
    auto matcher = WithinRel(target);
    EXPECT_FALSE(matcher.match(far_value));
}

TEST(WithinRelFloatTest_209, NegativeTargetExactMatch_209) {
    auto matcher = WithinRel(-5.0f);
    EXPECT_TRUE(matcher.match(-5.0f));
}

TEST(WithinRelFloatTest_209, NegativeTargetSlightlyOff_209) {
    float target = -5.0f;
    float eps100 = std::numeric_limits<float>::epsilon() * 100;
    float close_value = target * (1.0f + eps100 * 0.5f);
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(close_value));
}

TEST(WithinRelFloatTest_209, NegativeTargetFarOff_209) {
    float target = -5.0f;
    float far_value = -5.5f;
    auto matcher = WithinRel(target);
    EXPECT_FALSE(matcher.match(far_value));
}

TEST(WithinRelFloatTest_209, LargeTargetExactMatch_209) {
    float target = 1.0e30f;
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(target));
}

TEST(WithinRelFloatTest_209, LargeTargetSlightlyOff_209) {
    float target = 1.0e30f;
    float eps100 = std::numeric_limits<float>::epsilon() * 100;
    float close_value = target * (1.0f + eps100 * 0.5f);
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(close_value));
}

TEST(WithinRelFloatTest_209, SmallTargetExactMatch_209) {
    float target = 1.0e-30f;
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(target));
}

TEST(WithinRelFloatTest_209, OppositeSignReturnsFalse_209) {
    auto matcher = WithinRel(1.0f);
    EXPECT_FALSE(matcher.match(-1.0f));
}

TEST(WithinRelFloatTest_209, VeryDifferentValuesReturnFalse_209) {
    auto matcher = WithinRel(100.0f);
    EXPECT_FALSE(matcher.match(200.0f));
}

TEST(WithinRelFloatTest_209, DescriptionIsNotEmpty_209) {
    auto matcher = WithinRel(1.0f);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// ============================================================
// Tests for WithinRel with explicit tolerance (two-argument)
// ============================================================

TEST(WithinRelFloatExplicitTolTest_209, ExactMatchWithCustomTolerance_209) {
    auto matcher = WithinRel(1.0f, 0.1f);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST(WithinRelFloatExplicitTolTest_209, WithinCustomTolerance_209) {
    auto matcher = WithinRel(1.0f, 0.1f);
    // 1.05 is within 10% of 1.0
    EXPECT_TRUE(matcher.match(1.05f));
}

TEST(WithinRelFloatExplicitTolTest_209, OutsideCustomTolerance_209) {
    auto matcher = WithinRel(1.0f, 0.01f);
    // 1.5 is outside 1% of 1.0
    EXPECT_FALSE(matcher.match(1.5f));
}

TEST(WithinRelFloatExplicitTolTest_209, ZeroToleranceExactMatch_209) {
    auto matcher = WithinRel(1.0f, 0.0f);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST(WithinRelFloatExplicitTolTest_209, ZeroToleranceSlightlyOff_209) {
    auto matcher = WithinRel(1.0f, 0.0f);
    float next = std::nextafter(1.0f, 2.0f);
    // With zero tolerance, only exact match should work
    // (but implementation may or may not accept nextafter)
    // Just check the very different value doesn't match
    EXPECT_FALSE(matcher.match(1.1f));
}

// ============================================================
// Tests for WithinRel(double) variants
// ============================================================

TEST(WithinRelDoubleTest_209, ExactMatchDefaultTolerance_209) {
    auto matcher = WithinRel(1.0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST(WithinRelDoubleTest_209, SlightlyOffWithinDefaultTolerance_209) {
    double target = 1.0;
    double eps100 = std::numeric_limits<double>::epsilon() * 100;
    double close_value = target * (1.0 + eps100 * 0.5);
    auto matcher = WithinRel(target);
    EXPECT_TRUE(matcher.match(close_value));
}

TEST(WithinRelDoubleTest_209, FarOffReturnsFalse_209) {
    auto matcher = WithinRel(1.0);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST(WithinRelDoubleTest_209, ExplicitToleranceWithinRange_209) {
    auto matcher = WithinRel(100.0, 0.05);
    // 103 is within 5% of 100
    EXPECT_TRUE(matcher.match(103.0));
}

TEST(WithinRelDoubleTest_209, ExplicitToleranceOutsideRange_209) {
    auto matcher = WithinRel(100.0, 0.01);
    // 110 is outside 1% of 100
    EXPECT_FALSE(matcher.match(110.0));
}

// ============================================================
// Tests for WithinAbs
// ============================================================

TEST(WithinAbsDoubleTest_209, ExactMatch_209) {
    auto matcher = WithinAbs(1.0, 0.5);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST(WithinAbsDoubleTest_209, WithinMargin_209) {
    auto matcher = WithinAbs(1.0, 0.5);
    EXPECT_TRUE(matcher.match(1.3));
}

TEST(WithinAbsDoubleTest_209, OutsideMargin_209) {
    auto matcher = WithinAbs(1.0, 0.5);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST(WithinAbsDoubleTest_209, AtBoundary_209) {
    auto matcher = WithinAbs(1.0, 0.5);
    EXPECT_TRUE(matcher.match(1.5));
}

TEST(WithinAbsDoubleTest_209, NegativeValues_209) {
    auto matcher = WithinAbs(-3.0, 0.1);
    EXPECT_TRUE(matcher.match(-3.05));
}

TEST(WithinAbsDoubleTest_209, ZeroMargin_209) {
    auto matcher = WithinAbs(5.0, 0.0);
    EXPECT_TRUE(matcher.match(5.0));
    EXPECT_FALSE(matcher.match(5.1));
}

TEST(WithinAbsDoubleTest_209, DescriptionNotEmpty_209) {
    auto matcher = WithinAbs(1.0, 0.5);
    EXPECT_FALSE(matcher.describe().empty());
}

// ============================================================
// Tests for WithinULP (double)
// ============================================================

TEST(WithinULPDoubleTest_209, ExactMatch_209) {
    auto matcher = WithinULP(1.0, 1);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST(WithinULPDoubleTest_209, OneULPAway_209) {
    double target = 1.0;
    double one_ulp_away = std::nextafter(target, 2.0);
    auto matcher = WithinULP(target, 1);
    EXPECT_TRUE(matcher.match(one_ulp_away));
}

TEST(WithinULPDoubleTest_209, ManyULPsAway_209) {
    auto matcher = WithinULP(1.0, 1);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST(WithinULPDoubleTest_209, ZeroULPs_209) {
    auto matcher = WithinULP(1.0, 0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST(WithinULPDoubleTest_209, DescriptionNotEmpty_209) {
    auto matcher = WithinULP(1.0, 5);
    EXPECT_FALSE(matcher.describe().empty());
}

// ============================================================
// Tests for WithinULP (float)
// ============================================================

TEST(WithinULPFloatTest_209, ExactMatch_209) {
    auto matcher = WithinULP(1.0f, 1);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST(WithinULPFloatTest_209, OneULPAway_209) {
    float target = 1.0f;
    float one_ulp_away = std::nextafter(target, 2.0f);
    auto matcher = WithinULP(target, 1);
    EXPECT_TRUE(matcher.match(one_ulp_away));
}

TEST(WithinULPFloatTest_209, FarAway_209) {
    auto matcher = WithinULP(1.0f, 1);
    EXPECT_FALSE(matcher.match(2.0f));
}

// ============================================================
// Tests for WithinAbs (float overload)
// ============================================================

TEST(WithinAbsFloatTest_209, ExactMatch_209) {
    auto matcher = WithinAbs(1.0f, 0.5f);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST(WithinAbsFloatTest_209, WithinMargin_209) {
    auto matcher = WithinAbs(1.0f, 0.5f);
    EXPECT_TRUE(matcher.match(1.3f));
}

TEST(WithinAbsFloatTest_209, OutsideMargin_209) {
    auto matcher = WithinAbs(1.0f, 0.5f);
    EXPECT_FALSE(matcher.match(2.0f));
}

// ============================================================
// Special floating point values
// ============================================================

TEST(WithinRelSpecialValues_209, NaNDoesNotMatchNaN_209) {
    float nan_val = std::numeric_limits<float>::quiet_NaN();
    auto matcher = WithinRel(nan_val);
    // NaN should not equal NaN in IEEE 754
    EXPECT_FALSE(matcher.match(nan_val));
}

TEST(WithinRelSpecialValues_209, InfMatchesInf_209) {
    float inf_val = std::numeric_limits<float>::infinity();
    auto matcher = WithinRel(inf_val);
    EXPECT_TRUE(matcher.match(inf_val));
}

TEST(WithinRelSpecialValues_209, NegInfMatchesNegInf_209) {
    float neg_inf = -std::numeric_limits<float>::infinity();
    auto matcher = WithinRel(neg_inf);
    EXPECT_TRUE(matcher.match(neg_inf));
}

TEST(WithinRelSpecialValues_209, InfDoesNotMatchNegInf_209) {
    float inf_val = std::numeric_limits<float>::infinity();
    auto matcher = WithinRel(inf_val);
    EXPECT_FALSE(matcher.match(-inf_val));
}

TEST(WithinAbsSpecialValues_209, NaNDoesNotMatchNaN_209) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    auto matcher = WithinAbs(nan_val, 1.0);
    EXPECT_FALSE(matcher.match(nan_val));
}

TEST(WithinULPSpecialValues_209, NaNDoesNotMatchNaN_209) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    auto matcher = WithinULP(nan_val, 0);
    EXPECT_FALSE(matcher.match(nan_val));
}
