#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstring>

// Include the necessary Catch2 headers for the matchers
#include "catch2/matchers/catch_matchers_floating_point.hpp"

// Helper function to check if a matcher matches a given value
// Since Catch2 matchers have a `match` method, we can use that directly.

class WithinUlpsMatcherTest_203 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for WithinULP(double, uint64_t)
// ============================================================

TEST_F(WithinUlpsMatcherTest_203, ExactMatch_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinUlpsMatcherTest_203, WithinOneUlp_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1);
    double val = 1.0;
    // Get next representable double
    double next = std::nextafter(val, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_203, WithinOneUlpPrev_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1);
    double val = 1.0;
    double prev = std::nextafter(val, -std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(prev));
}

TEST_F(WithinUlpsMatcherTest_203, ExactMatchZeroUlp_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 0);
    double next = std::nextafter(1.0, std::numeric_limits<double>::infinity());
    EXPECT_FALSE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_203, BeyondUlpRange_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1);
    double next1 = std::nextafter(1.0, std::numeric_limits<double>::infinity());
    double next2 = std::nextafter(next1, std::numeric_limits<double>::infinity());
    EXPECT_FALSE(matcher.match(next2));
}

TEST_F(WithinUlpsMatcherTest_203, MultipleUlps_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 5);
    double val = 1.0;
    for (int i = 0; i < 5; ++i) {
        val = std::nextafter(val, std::numeric_limits<double>::infinity());
    }
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_203, MultipleUlpsExceeded_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 5);
    double val = 1.0;
    for (int i = 0; i < 6; ++i) {
        val = std::nextafter(val, std::numeric_limits<double>::infinity());
    }
    EXPECT_FALSE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_203, ZeroTarget_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(0.0, 1);
    EXPECT_TRUE(matcher.match(0.0));
    // Smallest positive subnormal
    double smallest_pos = std::numeric_limits<double>::denorm_min();
    EXPECT_TRUE(matcher.match(smallest_pos));
}

TEST_F(WithinUlpsMatcherTest_203, NegativeZeroTarget_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(-0.0, 0);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(WithinUlpsMatcherTest_203, NegativeValues_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(-1.0, 1);
    double prev = std::nextafter(-1.0, -std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(prev));
    double next = std::nextafter(-1.0, 0.0);
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_203, LargeTarget_Double_203) {
    double large = 1e300;
    auto matcher = Catch::Matchers::WithinULP(large, 2);
    double next1 = std::nextafter(large, std::numeric_limits<double>::infinity());
    double next2 = std::nextafter(next1, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next2));
}

TEST_F(WithinUlpsMatcherTest_203, SmallTarget_Double_203) {
    double small = std::numeric_limits<double>::denorm_min();
    auto matcher = Catch::Matchers::WithinULP(small, 1);
    EXPECT_TRUE(matcher.match(small));
    double next = std::nextafter(small, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_203, VeryDifferentValues_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 10);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST_F(WithinUlpsMatcherTest_203, DescribeReturnsNonEmpty_Double_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 5);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

// ============================================================
// Tests for WithinULP(float, uint64_t) if available
// ============================================================

class WithinUlpsMatcherFloatTest_203 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(WithinUlpsMatcherFloatTest_203, ExactMatch_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 0);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST_F(WithinUlpsMatcherFloatTest_203, WithinOneUlp_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 1);
    float next = std::nextafter(1.0f, std::numeric_limits<float>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherFloatTest_203, BeyondUlpRange_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 1);
    float next1 = std::nextafter(1.0f, std::numeric_limits<float>::infinity());
    float next2 = std::nextafter(next1, std::numeric_limits<float>::infinity());
    EXPECT_FALSE(matcher.match(next2));
}

TEST_F(WithinUlpsMatcherFloatTest_203, ZeroUlpNoMatch_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 0);
    float next = std::nextafter(1.0f, std::numeric_limits<float>::infinity());
    EXPECT_FALSE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherFloatTest_203, NegativeValues_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(-1.0f, 1);
    float prev = std::nextafter(-1.0f, -std::numeric_limits<float>::infinity());
    EXPECT_TRUE(matcher.match(prev));
}

TEST_F(WithinUlpsMatcherFloatTest_203, ZeroTarget_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(0.0f, 1);
    EXPECT_TRUE(matcher.match(0.0f));
    float smallest_pos = std::numeric_limits<float>::denorm_min();
    EXPECT_TRUE(matcher.match(smallest_pos));
}

TEST_F(WithinUlpsMatcherFloatTest_203, DescribeReturnsNonEmpty_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 5);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(WithinUlpsMatcherFloatTest_203, MultipleUlps_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 3);
    float val = 1.0f;
    for (int i = 0; i < 3; ++i) {
        val = std::nextafter(val, std::numeric_limits<float>::infinity());
    }
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherFloatTest_203, MultipleUlpsExceeded_Float_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0f, 3);
    float val = 1.0f;
    for (int i = 0; i < 4; ++i) {
        val = std::nextafter(val, std::numeric_limits<float>::infinity());
    }
    EXPECT_FALSE(matcher.match(val));
}

// ============================================================
// Tests for WithinAbs and WithinRel if available in the same header
// ============================================================

class WithinAbsMatcherTest_203 : public ::testing::Test {};

TEST_F(WithinAbsMatcherTest_203, ExactMatch_203) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinAbsMatcherTest_203, WithinMargin_203) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.5);
    EXPECT_TRUE(matcher.match(1.3));
    EXPECT_TRUE(matcher.match(0.7));
}

TEST_F(WithinAbsMatcherTest_203, OutsideMargin_203) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_FALSE(matcher.match(1.2));
    EXPECT_FALSE(matcher.match(0.8));
}

TEST_F(WithinAbsMatcherTest_203, BoundaryExact_203) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.5);
    EXPECT_TRUE(matcher.match(1.5));
    EXPECT_TRUE(matcher.match(0.5));
}

TEST_F(WithinAbsMatcherTest_203, NegativeTarget_203) {
    auto matcher = Catch::Matchers::WithinAbs(-1.0, 0.1);
    EXPECT_TRUE(matcher.match(-1.05));
    EXPECT_FALSE(matcher.match(-1.2));
}

TEST_F(WithinAbsMatcherTest_203, ZeroMargin_203) {
    auto matcher = Catch::Matchers::WithinAbs(5.0, 0.0);
    EXPECT_TRUE(matcher.match(5.0));
    EXPECT_FALSE(matcher.match(5.0 + std::numeric_limits<double>::epsilon()));
}

TEST_F(WithinAbsMatcherTest_203, DescribeNonEmpty_203) {
    auto matcher = Catch::Matchers::WithinAbs(1.0, 0.1);
    EXPECT_FALSE(matcher.describe().empty());
}

// ============================================================
// Tests for WithinRel
// ============================================================

class WithinRelMatcherTest_203 : public ::testing::Test {};

TEST_F(WithinRelMatcherTest_203, ExactMatch_Double_203) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinRelMatcherTest_203, WithinRelativeTolerance_203) {
    auto matcher = Catch::Matchers::WithinRel(100.0, 0.01); // 1% tolerance
    EXPECT_TRUE(matcher.match(100.5));
    EXPECT_TRUE(matcher.match(99.5));
}

TEST_F(WithinRelMatcherTest_203, OutsideRelativeTolerance_203) {
    auto matcher = Catch::Matchers::WithinRel(100.0, 0.01); // 1% tolerance
    EXPECT_FALSE(matcher.match(102.0));
    EXPECT_FALSE(matcher.match(98.0));
}

TEST_F(WithinRelMatcherTest_203, DefaultTolerance_Double_203) {
    // WithinRel with default tolerance (epsilon * 100)
    auto matcher = Catch::Matchers::WithinRel(1.0);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinRelMatcherTest_203, DescribeNonEmpty_203) {
    auto matcher = Catch::Matchers::WithinRel(1.0, 0.01);
    EXPECT_FALSE(matcher.describe().empty());
}

TEST_F(WithinRelMatcherTest_203, NegativeTarget_203) {
    auto matcher = Catch::Matchers::WithinRel(-100.0, 0.01);
    EXPECT_TRUE(matcher.match(-100.5));
    EXPECT_FALSE(matcher.match(-102.0));
}

// ============================================================
// Float versions of WithinRel
// ============================================================

TEST_F(WithinRelMatcherTest_203, ExactMatch_Float_203) {
    auto matcher = Catch::Matchers::WithinRel(1.0f, 0.0f);
    EXPECT_TRUE(matcher.match(1.0f));
}

TEST_F(WithinRelMatcherTest_203, WithinRelativeTolerance_Float_203) {
    auto matcher = Catch::Matchers::WithinRel(100.0f, 0.01f);
    EXPECT_TRUE(matcher.match(100.5f));
}

TEST_F(WithinRelMatcherTest_203, DefaultTolerance_Float_203) {
    auto matcher = Catch::Matchers::WithinRel(1.0f);
    EXPECT_TRUE(matcher.match(1.0f));
}

// ============================================================
// Edge cases with special floating point values
// ============================================================

class FloatingPointEdgeCases_203 : public ::testing::Test {};

TEST_F(FloatingPointEdgeCases_203, InfinityUlp_203) {
    auto matcher = Catch::Matchers::WithinULP(std::numeric_limits<double>::infinity(), 0);
    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::infinity()));
}

TEST_F(FloatingPointEdgeCases_203, NegativeInfinityUlp_203) {
    auto matcher = Catch::Matchers::WithinULP(-std::numeric_limits<double>::infinity(), 0);
    EXPECT_TRUE(matcher.match(-std::numeric_limits<double>::infinity()));
}

TEST_F(FloatingPointEdgeCases_203, NaNDoesNotMatchNaN_WithinAbs_203) {
    auto matcher = Catch::Matchers::WithinAbs(std::numeric_limits<double>::quiet_NaN(), 1.0);
    // NaN should not match NaN
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::quiet_NaN()));
}

TEST_F(FloatingPointEdgeCases_203, MaxDoubleWithinUlp_203) {
    double maxd = std::numeric_limits<double>::max();
    auto matcher = Catch::Matchers::WithinULP(maxd, 0);
    EXPECT_TRUE(matcher.match(maxd));
}

TEST_F(FloatingPointEdgeCases_203, MinDoubleWithinUlp_203) {
    double mind = std::numeric_limits<double>::min();
    auto matcher = Catch::Matchers::WithinULP(mind, 1);
    double next = std::nextafter(mind, std::numeric_limits<double>::infinity());
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(FloatingPointEdgeCases_203, NegativeZeroPositiveZero_WithinUlp_203) {
    auto matcher = Catch::Matchers::WithinULP(0.0, 0);
    EXPECT_TRUE(matcher.match(-0.0));
}

TEST_F(FloatingPointEdgeCases_203, LargeUlpDiff_203) {
    auto matcher = Catch::Matchers::WithinULP(1.0, 1000000);
    // With a large ulp diff, values close to 1.0 should match
    double val = 1.0;
    for (int i = 0; i < 100; ++i) {
        val = std::nextafter(val, std::numeric_limits<double>::infinity());
    }
    EXPECT_TRUE(matcher.match(val));
}
