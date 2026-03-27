// File: tests/is_nan_matcher_test_212.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// We rely only on the public interface provided by Catch2's headers.
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::IsNaN;
using Catch::Matchers::IsNaNMatcher;

class IsNaNMatcherTest_212 : public ::testing::Test {};

// --- Construction & type traits ---

TEST_F(IsNaNMatcherTest_212, CallableAndReturnsMatcher_212) {
    auto m = IsNaN(); // Must be callable without args
    (void)m;          // Suppress unused warning
    // Basic type check via decltype and (incomplete) name; no internal logic used.
    // If the symbol is available, this line compiles.
    bool is_expected_type = std::is_same<decltype(m), IsNaNMatcher>::value;
    EXPECT_TRUE(is_expected_type);
}

TEST_F(IsNaNMatcherTest_212, MatcherIsCopyable_212) {
    auto m = IsNaN();
    IsNaNMatcher copy(m);        // copy-constructible
    IsNaNMatcher assigned = m;   // copy-assignable
    (void)copy;
    (void)assigned;
    SUCCEED(); // If compilation & construction succeed, interface contract holds
}

// --- Observable matching behavior (black-box): NaN vs non-NaN ---

TEST_F(IsNaNMatcherTest_212, MatchesQuietNaNDouble_212) {
    auto m = IsNaN();
    double v = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(m.match(v));
}

TEST_F(IsNaNMatcherTest_212, MatchesQuietNaNFloat_212) {
    auto m = IsNaN();
    float v = std::numeric_limits<float>::quiet_NaN();
    EXPECT_TRUE(m.match(v));
}

TEST_F(IsNaNMatcherTest_212, MatchesQuietNaNLongDouble_212) {
    auto m = IsNaN();
    long double v = std::numeric_limits<long double>::quiet_NaN();
    EXPECT_TRUE(m.match(v));
}

TEST_F(IsNaNMatcherTest_212, MatchesSignalingNaNIfAvailable_212) {
    auto m = IsNaN();

    // Guard for platforms that don’t provide signaling NaN
#if defined(__cpp_lib_numeric_limits) || defined(__GNUC__) || defined(_MSC_VER)
    if (std::numeric_limits<double>::has_signaling_NaN) {
        double v = std::numeric_limits<double>::signaling_NaN();
        // Behavior should depend only on value being NaN (observable)
        EXPECT_TRUE(m.match(v));
    } else {
        GTEST_SKIP() << "signaling_NaN not available on this platform";
    }
#else
    GTEST_SKIP() << "signaling_NaN availability unknown on this platform";
#endif
}

// --- Non-NaN values should not match ---

TEST_F(IsNaNMatcherTest_212, DoesNotMatchFiniteNumbers_212) {
    auto m = IsNaN();
    EXPECT_FALSE(m.match(0.0));
    EXPECT_FALSE(m.match(-0.0));
    EXPECT_FALSE(m.match(1.0));
    EXPECT_FALSE(m.match(-123.456));
}

TEST_F(IsNaNMatcherTest_212, DoesNotMatchInfinities_212) {
    auto m = IsNaN();
    double pos_inf = std::numeric_limits<double>::infinity();
    double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_FALSE(m.match(pos_inf));
    EXPECT_FALSE(m.match(neg_inf));
}

// --- Cross-type behavior consistency ---

TEST_F(IsNaNMatcherTest_212, ConsistentAcrossTypes_212) {
    auto m = IsNaN();
    float f = std::numeric_limits<float>::quiet_NaN();
    double d = std::numeric_limits<double>::quiet_NaN();
    long double ld = std::numeric_limits<long double>::quiet_NaN();

    EXPECT_TRUE(m.match(f));
    EXPECT_TRUE(m.match(d));
    EXPECT_TRUE(m.match(ld));

    EXPECT_FALSE(m.match(42.0f));
    EXPECT_FALSE(m.match(42.0));
    EXPECT_FALSE(m.match((long double)42.0));
}
