#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Minimal reproduction of the class under test based on the provided implementation
namespace Catch {
namespace Matchers {

class IsNaNMatcher {
public:
    bool match(double const& matchee) const {
        return std::isnan(matchee);
    }
};

} // namespace Matchers
} // namespace Catch

class IsNaNMatcherTest_210 : public ::testing::Test {
protected:
    Catch::Matchers::IsNaNMatcher matcher;
};

// Test that NaN values are correctly identified
TEST_F(IsNaNMatcherTest_210, MatchesNaN_210) {
    double nan_val = std::nan("");
    EXPECT_TRUE(matcher.match(nan_val));
}

TEST_F(IsNaNMatcherTest_210, MatchesQuietNaN_210) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(matcher.match(nan_val));
}

TEST_F(IsNaNMatcherTest_210, MatchesSignalingNaN_210) {
    double nan_val = std::numeric_limits<double>::signaling_NaN();
    EXPECT_TRUE(matcher.match(nan_val));
}

// Test that regular numbers are not matched as NaN
TEST_F(IsNaNMatcherTest_210, DoesNotMatchZero_210) {
    EXPECT_FALSE(matcher.match(0.0));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchNegativeZero_210) {
    EXPECT_FALSE(matcher.match(-0.0));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchPositiveNumber_210) {
    EXPECT_FALSE(matcher.match(42.0));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchNegativeNumber_210) {
    EXPECT_FALSE(matcher.match(-42.0));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchOne_210) {
    EXPECT_FALSE(matcher.match(1.0));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchSmallPositive_210) {
    EXPECT_FALSE(matcher.match(1e-300));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchSmallNegative_210) {
    EXPECT_FALSE(matcher.match(-1e-300));
}

// Test boundary: infinity is not NaN
TEST_F(IsNaNMatcherTest_210, DoesNotMatchPositiveInfinity_210) {
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::infinity()));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchNegativeInfinity_210) {
    EXPECT_FALSE(matcher.match(-std::numeric_limits<double>::infinity()));
}

// Test boundary: max and min double values
TEST_F(IsNaNMatcherTest_210, DoesNotMatchMaxDouble_210) {
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::max()));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchMinDouble_210) {
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::min()));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchLowestDouble_210) {
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::lowest()));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchDenormMin_210) {
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::denorm_min()));
}

TEST_F(IsNaNMatcherTest_210, DoesNotMatchEpsilon_210) {
    EXPECT_FALSE(matcher.match(std::numeric_limits<double>::epsilon()));
}

// Test NaN generated from arithmetic operations
TEST_F(IsNaNMatcherTest_210, MatchesNaNFromArithmetic_210) {
    double nan_val = 0.0 / 0.0;
    EXPECT_TRUE(matcher.match(nan_val));
}

TEST_F(IsNaNMatcherTest_210, MatchesNaNFromInfinityMinusInfinity_210) {
    double inf = std::numeric_limits<double>::infinity();
    double nan_val = inf - inf;
    EXPECT_TRUE(matcher.match(nan_val));
}

TEST_F(IsNaNMatcherTest_210, MatchesNaNFromInfinityTimesZero_210) {
    double inf = std::numeric_limits<double>::infinity();
    double nan_val = inf * 0.0;
    EXPECT_TRUE(matcher.match(nan_val));
}

// Test that NaN generated via different nan string arguments still matches
TEST_F(IsNaNMatcherTest_210, MatchesNanWithStringArg_210) {
    double nan_val = std::nan("1");
    EXPECT_TRUE(matcher.match(nan_val));
}
