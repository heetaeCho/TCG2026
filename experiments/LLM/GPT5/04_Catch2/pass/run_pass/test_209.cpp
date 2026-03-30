// File: within_rel_matcher_gtest_209.cpp

#include <gtest/gtest.h>
#include <limits>
#include <type_traits>

// Catch2 matcher header (public interface)
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinRelMatcher;

class WithinRelMatcherTest_209 : public ::testing::Test {};

// ------------------------------------------------------------------
// Type/traits surface checks (interface-level; no internal peeking)
// ------------------------------------------------------------------

TEST_F(WithinRelMatcherTest_209, ReturnsWithinRelMatcherType_209) {
    auto m = WithinRel(1.0f);
    (void)m;
    // Ensure the return type is the documented matcher type
    static_assert(std::is_same<decltype(m), WithinRelMatcher>::value,
                  "WithinRel(float) must return WithinRelMatcher");
    // Basic value semantics commonly expected for matchers:
    static_assert(std::is_copy_constructible<WithinRelMatcher>::value,
                  "WithinRelMatcher should be copy-constructible");
    static_assert(std::is_move_constructible<WithinRelMatcher>::value,
                  "WithinRelMatcher should be move-constructible");
}

// ------------------------------------------------------------------
// Behavioral tests based strictly on public, observable behavior
// ------------------------------------------------------------------

TEST_F(WithinRelMatcherTest_209, SelfMatchesForSameTarget_209) {
    const float target = 123.45f;
    auto m = WithinRel(target);

    // A value should match itself with a relative matcher
    EXPECT_TRUE(m.match(target));
}

TEST_F(WithinRelMatcherTest_209, ClearlyDistantValueDoesNotMatch_209) {
    const float target = 1.0f;
    auto m = WithinRel(target);

    // A value far from the target should not match with a small default relative margin
    EXPECT_FALSE(m.match(10.0f));
}

TEST_F(WithinRelMatcherTest_209, NegativeTargetMatchesItself_209) {
    const float target = -50.0f;
    auto m = WithinRel(target);

    EXPECT_TRUE(m.match(target));
}

TEST_F(WithinRelMatcherTest_209, ZeroTargetOnlyMatchesZeroUnderDefaultMargin_209) {
    const float target = 0.0f;
    auto m = WithinRel(target);

    // Zero should match zero
    EXPECT_TRUE(m.match(0.0f));

    // A small-but-not-microscopic nonzero should *not* match with the default margin
    // (avoids relying on the exact internal epsilon; just uses a comfortably larger delta)
    EXPECT_FALSE(m.match(1e-2f));
}

TEST_F(WithinRelMatcherTest_209, NaNNeverMatches_209) {
    const float target = 1.0f;
    auto m = WithinRel(target);

    const float nanv = std::numeric_limits<float>::quiet_NaN();

    EXPECT_FALSE(m.match(nanv))        << "NaN value should not match";
    EXPECT_FALSE(WithinRel(nanv).match(1.0f)) << "Matcher with NaN target should not match a finite value";
}

TEST_F(WithinRelMatcherTest_209, InfinityHandling_209) {
    const float pos_inf = std::numeric_limits<float>::infinity();
    const float neg_inf = -std::numeric_limits<float>::infinity();

    auto m_pos = WithinRel(pos_inf);
    auto m_neg = WithinRel(neg_inf);

    // Same infinities should match themselves
    EXPECT_TRUE(m_pos.match(pos_inf));
    EXPECT_TRUE(m_neg.match(neg_inf));

    // Finite vs infinite should not match
    EXPECT_FALSE(m_pos.match(1.0f));
    EXPECT_FALSE(m_neg.match(-1.0f));

    // Opposite infinities should not match
    EXPECT_FALSE(m_pos.match(neg_inf));
    EXPECT_FALSE(m_neg.match(pos_inf));
}
