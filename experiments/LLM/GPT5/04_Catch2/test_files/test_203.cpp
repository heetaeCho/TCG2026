// File: test_within_ulp_203.cpp
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Catch2 matcher headers (public interface)
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinULP;
using Catch::Matchers::WithinUlpsMatcher;

class WithinULPTest_203 : public ::testing::Test {};

TEST_F(WithinULPTest_203, ExactMatchWithZeroUlps_203) {
    const double target = 1.0;
    WithinUlpsMatcher m = WithinULP(target, /*maxUlpDiff=*/0);

    EXPECT_TRUE(m.match(target)) << "Exact same double should match with 0 ULPs";
}

TEST_F(WithinULPTest_203, DifferentValueFailsWithZeroUlps_203) {
    const double target = 1.0;
    const double other  = 1.0 + 1e-12; // Observably different double
    WithinUlpsMatcher m = WithinULP(target, /*maxUlpDiff=*/0);

    EXPECT_FALSE(m.match(other)) << "Different value must not match with 0 ULPs";
}

TEST_F(WithinULPTest_203, OneUlpAwayMatchesWhenAllowed_203) {
    const double target = 1.0;
    const double oneUlp = std::nextafter(target, std::numeric_limits<double>::infinity());

    // With 0 ULPs it should NOT match
    EXPECT_FALSE(WithinULP(target, 0).match(oneUlp));

    // With 1 ULP it SHOULD match
    EXPECT_TRUE(WithinULP(target, 1).match(oneUlp));
}

TEST_F(WithinULPTest_203, OneUlpAwayOnNegativeSideMatchesWhenAllowed_203) {
    const double target = -2.5;
    const double oneUlpTowardZero =
        std::nextafter(target, 0.0); // adjacent representable double

    // With 0 ULPs it should NOT match
    EXPECT_FALSE(WithinULP(target, 0).match(oneUlpTowardZero));

    // With 1 ULP it SHOULD match
    EXPECT_TRUE(WithinULP(target, 1).match(oneUlpTowardZero));
}

TEST_F(WithinULPTest_203, NaNNeverMatches_203) {
    const double target = 3.14;
    const double nanVal = std::numeric_limits<double>::quiet_NaN();

    EXPECT_FALSE(WithinULP(target, 0).match(nanVal));
    EXPECT_FALSE(WithinULP(target, 1000).match(nanVal));
}

TEST_F(WithinULPTest_203, InfinityMatchingBehavior_203) {
    const double posInf = std::numeric_limits<double>::infinity();
    const double negInf = -std::numeric_limits<double>::infinity();

    // Same infinities should match (any ULP budget)
    EXPECT_TRUE(WithinULP(posInf, 0).match(posInf));
    EXPECT_TRUE(WithinULP(negInf, 0).match(negInf));

    // Opposite infinities should not match
    EXPECT_FALSE(WithinULP(posInf, 1000).match(negInf));
    EXPECT_FALSE(WithinULP(negInf, 1000).match(posInf));

    // Infinite vs finite should not match
    EXPECT_FALSE(WithinULP(posInf, 1000).match(1.0));
    EXPECT_FALSE(WithinULP(negInf, 1000).match(-1.0));
}

TEST_F(WithinULPTest_203, DescriptionIsNonEmpty_203) {
    const double target = 42.0;
    WithinUlpsMatcher m = WithinULP(target, 10);

    // We only verify that some human-readable description exists; we do not
    // assert any internal wording.
    auto desc = m.describe();
    EXPECT_FALSE(desc.empty());
}
