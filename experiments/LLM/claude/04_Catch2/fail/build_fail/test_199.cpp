#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstring>

// Include the necessary Catch2 headers
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using namespace Catch::Matchers;
using Catch::Matchers::Detail::FloatingPointKind;

class WithinUlpsMatcherTest_199 : public ::testing::Test {
protected:
    // Helper to create matchers easily
};

// ==================== Normal Operation Tests ====================

TEST_F(WithinUlpsMatcherTest_199, ExactMatchDouble_199) {
    WithinUlpsMatcher matcher(1.0, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinUlpsMatcherTest_199, ExactMatchFloat_199) {
    WithinUlpsMatcher matcher(1.0f, 0, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(1.0));
}

TEST_F(WithinUlpsMatcherTest_199, WithinOneUlpDouble_199) {
    double target = 1.0;
    // Next representable double after 1.0
    double next = std::nextafter(1.0, 2.0);
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_199, WithinOneUlpFloat_199) {
    float target = 1.0f;
    float next = std::nextafterf(1.0f, 2.0f);
    WithinUlpsMatcher matcher(static_cast<double>(target), 1, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(next)));
}

TEST_F(WithinUlpsMatcherTest_199, WithinMultipleUlpsDouble_199) {
    double target = 1.0;
    double val = target;
    for (int i = 0; i < 5; ++i) {
        val = std::nextafter(val, 2.0);
    }
    WithinUlpsMatcher matcher(target, 5, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, WithinMultipleUlpsFloat_199) {
    float target = 1.0f;
    float val = target;
    for (int i = 0; i < 5; ++i) {
        val = std::nextafterf(val, 2.0f);
    }
    WithinUlpsMatcher matcher(static_cast<double>(target), 5, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(val)));
}

// ==================== Boundary Condition Tests ====================

TEST_F(WithinUlpsMatcherTest_199, BeyondUlpsRangeDouble_199) {
    double target = 1.0;
    double val = target;
    // Move 6 ULPs away
    for (int i = 0; i < 6; ++i) {
        val = std::nextafter(val, 2.0);
    }
    WithinUlpsMatcher matcher(target, 5, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, BeyondUlpsRangeFloat_199) {
    float target = 1.0f;
    float val = target;
    // Move 6 ULPs away
    for (int i = 0; i < 6; ++i) {
        val = std::nextafterf(val, 2.0f);
    }
    WithinUlpsMatcher matcher(static_cast<double>(target), 5, FloatingPointKind::Float);
    EXPECT_FALSE(matcher.match(static_cast<double>(val)));
}

TEST_F(WithinUlpsMatcherTest_199, ExactlyAtBoundaryDouble_199) {
    double target = 1.0;
    double val = target;
    // Move exactly 3 ULPs away
    for (int i = 0; i < 3; ++i) {
        val = std::nextafter(val, 2.0);
    }
    WithinUlpsMatcher matcher(target, 3, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, OneOverBoundaryDouble_199) {
    double target = 1.0;
    double val = target;
    // Move exactly 4 ULPs away, but allow only 3
    for (int i = 0; i < 4; ++i) {
        val = std::nextafter(val, 2.0);
    }
    WithinUlpsMatcher matcher(target, 3, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, ZeroUlpsExactMatchDouble_199) {
    WithinUlpsMatcher matcher(3.14, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(3.14));
}

TEST_F(WithinUlpsMatcherTest_199, ZeroUlpsNoMatchDouble_199) {
    double target = 3.14;
    double next = std::nextafter(target, 4.0);
    WithinUlpsMatcher matcher(target, 0, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(next));
}

TEST_F(WithinUlpsMatcherTest_199, NegativeDirectionDouble_199) {
    double target = 1.0;
    double val = target;
    // Move ULPs in negative direction
    for (int i = 0; i < 3; ++i) {
        val = std::nextafter(val, 0.0);
    }
    WithinUlpsMatcher matcher(target, 3, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, NegativeDirectionFloat_199) {
    float target = 1.0f;
    float val = target;
    for (int i = 0; i < 3; ++i) {
        val = std::nextafterf(val, 0.0f);
    }
    WithinUlpsMatcher matcher(static_cast<double>(target), 3, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(val)));
}

TEST_F(WithinUlpsMatcherTest_199, ZeroTargetDouble_199) {
    WithinUlpsMatcher matcher(0.0, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(WithinUlpsMatcherTest_199, ZeroTargetFloat_199) {
    WithinUlpsMatcher matcher(0.0, 0, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(0.0));
}

TEST_F(WithinUlpsMatcherTest_199, NegativeZeroMatchesPositiveZeroDouble_199) {
    WithinUlpsMatcher matcher(0.0, 0, FloatingPointKind::Double);
    // -0.0 and 0.0 should ideally match within 0 ULPs as they are equal
    EXPECT_TRUE(matcher.match(-0.0));
}

TEST_F(WithinUlpsMatcherTest_199, NegativeValuesDouble_199) {
    double target = -1.0;
    double val = std::nextafter(target, -2.0);
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, NegativeValuesFloat_199) {
    float target = -1.0f;
    float val = std::nextafterf(target, -2.0f);
    WithinUlpsMatcher matcher(static_cast<double>(target), 1, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(val)));
}

TEST_F(WithinUlpsMatcherTest_199, LargeValuesDouble_199) {
    double target = 1e100;
    double val = std::nextafter(target, std::numeric_limits<double>::infinity());
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, SmallValuesDouble_199) {
    double target = std::numeric_limits<double>::min(); // smallest normal
    double val = std::nextafter(target, 1.0);
    WithinUlpsMatcher matcher(target, 1, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, VeryDifferentValuesDouble_199) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(2.0));
}

TEST_F(WithinUlpsMatcherTest_199, VeryDifferentValuesFloat_199) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Float);
    EXPECT_FALSE(matcher.match(2.0));
}

// ==================== Describe Tests ====================

TEST_F(WithinUlpsMatcherTest_199, DescribeReturnsNonEmptyStringDouble_199) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(WithinUlpsMatcherTest_199, DescribeReturnsNonEmptyStringFloat_199) {
    WithinUlpsMatcher matcher(1.0f, 3, FloatingPointKind::Float);
    std::string desc = matcher.describe();
    EXPECT_FALSE(desc.empty());
}

TEST_F(WithinUlpsMatcherTest_199, DescribeContainsUlpsInfo_199) {
    WithinUlpsMatcher matcher(1.0, 5, FloatingPointKind::Double);
    std::string desc = matcher.describe();
    // The description should contain some reference to ULPs
    EXPECT_NE(desc.find("ULP"), std::string::npos);
}

// ==================== Float vs Double precision tests ====================

TEST_F(WithinUlpsMatcherTest_199, FloatPrecisionLessStrictThanDouble_199) {
    // Two values that are within 1 float ULP but many double ULPs apart
    float ftarget = 1.0f;
    float fnext = std::nextafterf(ftarget, 2.0f);
    
    // As float, these should match within 1 ULP
    WithinUlpsMatcher floatMatcher(static_cast<double>(ftarget), 1, FloatingPointKind::Float);
    EXPECT_TRUE(floatMatcher.match(static_cast<double>(fnext)));
}

TEST_F(WithinUlpsMatcherTest_199, MatchWithSameValueDifferentRepresentationDouble_199) {
    double a = 0.1 + 0.2;
    double b = 0.3;
    // These may not be exactly equal due to floating point arithmetic
    // but should be very close in ULPs
    WithinUlpsMatcher matcher(b, 5, FloatingPointKind::Double);
    // We just verify it doesn't crash; actual result depends on implementation
    bool result = matcher.match(a);
    (void)result; // Just ensure no crash
}

// ==================== Special floating point values ====================

TEST_F(WithinUlpsMatcherTest_199, InfinityMatchDouble_199) {
    double inf = std::numeric_limits<double>::infinity();
    WithinUlpsMatcher matcher(inf, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(inf));
}

TEST_F(WithinUlpsMatcherTest_199, NegativeInfinityMatchDouble_199) {
    double neginf = -std::numeric_limits<double>::infinity();
    WithinUlpsMatcher matcher(neginf, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(neginf));
}

TEST_F(WithinUlpsMatcherTest_199, NaNDoesNotMatchNaNDouble_199) {
    double nan = std::numeric_limits<double>::quiet_NaN();
    WithinUlpsMatcher matcher(nan, 0, FloatingPointKind::Double);
    // NaN should not equal NaN
    EXPECT_FALSE(matcher.match(nan));
}

TEST_F(WithinUlpsMatcherTest_199, NaNDoesNotMatchNaNFloat_199) {
    float nan = std::numeric_limits<float>::quiet_NaN();
    WithinUlpsMatcher matcher(static_cast<double>(nan), 0, FloatingPointKind::Float);
    EXPECT_FALSE(matcher.match(static_cast<double>(nan)));
}

TEST_F(WithinUlpsMatcherTest_199, NaNDoesNotMatchRegularValueDouble_199) {
    double nan = std::numeric_limits<double>::quiet_NaN();
    WithinUlpsMatcher matcher(1.0, 100, FloatingPointKind::Double);
    EXPECT_FALSE(matcher.match(nan));
}

TEST_F(WithinUlpsMatcherTest_199, MaxDoubleMatchesSelf_199) {
    double maxd = std::numeric_limits<double>::max();
    WithinUlpsMatcher matcher(maxd, 0, FloatingPointKind::Double);
    EXPECT_TRUE(matcher.match(maxd));
}

TEST_F(WithinUlpsMatcherTest_199, MaxFloatMatchesSelf_199) {
    float maxf = std::numeric_limits<float>::max();
    WithinUlpsMatcher matcher(static_cast<double>(maxf), 0, FloatingPointKind::Float);
    EXPECT_TRUE(matcher.match(static_cast<double>(maxf)));
}

TEST_F(WithinUlpsMatcherTest_199, LargeUlpToleranceDouble_199) {
    WithinUlpsMatcher matcher(1.0, 1000000, FloatingPointKind::Double);
    double val = 1.0;
    for (int i = 0; i < 1000; ++i) {
        val = std::nextafter(val, 2.0);
    }
    EXPECT_TRUE(matcher.match(val));
}

TEST_F(WithinUlpsMatcherTest_199, DenormalizedValuesDouble_199) {
    double denorm = std::numeric_limits<double>::denorm_min();
    WithinUlpsMatcher matcher(0.0, 1, FloatingPointKind::Double);
    // denorm_min is one ULP away from 0
    EXPECT_TRUE(matcher.match(denorm));
}
