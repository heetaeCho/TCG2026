// File: within_ulp_float_tests_204.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>

// The SUT interface (header) is assumed to be available in your include path.
// If needed, adjust the include to where Catch2's matchers are visible.
namespace Catch { namespace Matchers {
    struct WithinUlpsMatcher {
        // Observable interface we rely on (black-box):
        bool match(float const& v) const;     // returns whether v is within the allowed ULPs of target
        std::string describe() const;         // human-readable description (not asserted on)
    };

    // Function under test:
    WithinUlpsMatcher WithinULP(float target, uint64_t maxUlpDiff);
}}

// Small helper: advance a float by N steps toward +∞ or -∞ using nextafterf.
// This creates inputs that are exactly N ULPs away without peeking at internals.
static float AdvanceByUlps(float start, int stepsTowardPositive) {
    float x = start;
    if (stepsTowardPositive >= 0) {
        for (int i = 0; i < stepsTowardPositive; ++i)
            x = std::nextafterf(x, std::numeric_limits<float>::infinity());
    } else {
        for (int i = 0; i < -stepsTowardPositive; ++i)
            x = std::nextafterf(x, -std::numeric_limits<float>::infinity());
    }
    return x;
}

// Fixture (kept simple for clarity)
class WithinULPTest_204 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(WithinULPTest_204, ExactMatchZeroUlp_204) {
    using namespace Catch::Matchers;
    const float target = 1.0f;
    auto m = WithinULP(target, /*maxUlpDiff=*/0);
    EXPECT_TRUE(m.match(target)); // exact same value should match with 0 ULPs
}

TEST_F(WithinULPTest_204, OneUlpAwayMatchesWhenLimitIsOne_204) {
    using namespace Catch::Matchers;
    const float target = 1.0f;
    auto m = WithinULP(target, /*maxUlpDiff=*/1);
    const float oneUlpUp = AdvanceByUlps(target, +1);
    const float oneUlpDown = AdvanceByUlps(target, -1);

    EXPECT_TRUE(m.match(oneUlpUp));
    EXPECT_TRUE(m.match(oneUlpDown));
}

// --- Boundary conditions ---

TEST_F(WithinULPTest_204, ExactlyAtBoundaryMatches_204) {
    using namespace Catch::Matchers;
    const float target = 123.456f;
    const uint64_t limit = 8;
    auto m = WithinULP(target, limit);

    const float upAtLimit   = AdvanceByUlps(target, static_cast<int>(limit));
    const float downAtLimit = AdvanceByUlps(target, -static_cast<int>(limit));

    EXPECT_TRUE(m.match(upAtLimit));
    EXPECT_TRUE(m.match(downAtLimit));
}

TEST_F(WithinULPTest_204, JustOutsideBoundaryDoesNotMatch_204) {
    using namespace Catch::Matchers;
    const float target = 123.456f;
    const uint64_t limit = 8;
    auto m = WithinULP(target, limit);

    const float upOutside   = AdvanceByUlps(target, static_cast<int>(limit) + 1);
    const float downOutside = AdvanceByUlps(target, -static_cast<int>(limit) - 1);

    EXPECT_FALSE(m.match(upOutside));
    EXPECT_FALSE(m.match(downOutside));
}

// --- Special values ---

TEST_F(WithinULPTest_204, PositiveAndNegativeZeroAreTreatedAsEqual_204) {
    using namespace Catch::Matchers;
    const float posZero = 0.0f;
    const float negZero = -0.0f;

    auto m0 = WithinULP(posZero, /*maxUlpDiff=*/0);
    EXPECT_TRUE(m0.match(negZero)); // observable equality of +0 and -0

    auto m1 = WithinULP(negZero, /*maxUlpDiff=*/0);
    EXPECT_TRUE(m1.match(posZero));
}

TEST_F(WithinULPTest_204, NaNDoesNotMatch_204) {
    using namespace Catch::Matchers;
    const float target = 1.0f;
    auto m = WithinULP(target, /*maxUlpDiff=*/1000);

    const float qnan = std::numeric_limits<float>::quiet_NaN();

    // If either side is NaN, matching should be false (observable behavior).
    EXPECT_FALSE(m.match(qnan));
}

TEST_F(WithinULPTest_204, InfinityMatchesOnlySameInfinity_204) {
    using namespace Catch::Matchers;

    const float posInf = std::numeric_limits<float>::infinity();
    const float negInf = -std::numeric_limits<float>::infinity();
    const float big    = std::numeric_limits<float>::max();

    auto mPos = WithinULP(posInf, /*maxUlpDiff=*/1000);
    auto mNeg = WithinULP(negInf, /*maxUlpDiff=*/1000);

    EXPECT_TRUE(mPos.match(posInf));      // same +inf should match
    EXPECT_FALSE(mPos.match(big));        // finite should not match +inf
    EXPECT_FALSE(mPos.match(negInf));     // opposite infinity should not match

    EXPECT_TRUE(mNeg.match(negInf));      // same -inf should match
    EXPECT_FALSE(mNeg.match(-big));       // finite should not match -inf
    EXPECT_FALSE(mNeg.match(posInf));     // opposite infinity should not match
}

// --- Asymmetric targets ---

TEST_F(WithinULPTest_204, VerySmallNormalNumbersWithinRange_204) {
    using namespace Catch::Matchers;
    // Choose a small positive normal (not subnormal) number near 0
    const float target = std::numeric_limits<float>::min(); // smallest positive normal
    auto m = WithinULP(target, /*maxUlpDiff=*/2);

    const float closeUp   = AdvanceByUlps(target, +2);
    const float closeDown = AdvanceByUlps(target, -2);

    EXPECT_TRUE(m.match(closeUp));
    EXPECT_TRUE(m.match(closeDown));
}

TEST_F(WithinULPTest_204, VerySmallNumbersOutsideRange_204) {
    using namespace Catch::Matchers;
    const float target = std::numeric_limits<float>::min();
    auto m = WithinULP(target, /*maxUlpDiff=*/2);

    const float farUp   = AdvanceByUlps(target, +3);
    const float farDown = AdvanceByUlps(target, -3);

    EXPECT_FALSE(m.match(farUp));
    EXPECT_FALSE(m.match(farDown));
}
