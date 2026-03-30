// File: catch_polyfills_nextafter_tests_637.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <cfloat>
#include <limits>

// We only have the interface from the snippet; forward-declare it.
namespace Catch {
    float nextafter(float x, float y);
}

// Helper to compare exactly (bitwise) via std::memcmp if needed,
// but for this wrapper we always compare to std::nextafterf results.
static inline bool SameBits(float a, float b) {
    // Handles -0.0 vs +0.0 differences: use memcmp on the bit patterns
    static_assert(sizeof(float) == sizeof(uint32_t), "Unexpected float size");
    uint32_t ua, ub;
    std::memcpy(&ua, &a, sizeof(float));
    std::memcpy(&ub, &b, sizeof(float));
    return ua == ub;
}

// --- Tests ---

// Normal step in positive direction: result should match std::nextafterf
TEST(CatchPolyfillsNextafterTest_637, WrapperMatchesStdNextafterf_PositiveDirection_637) {
    float x = 1.0f;
    float y = 10.0f;

    float expected = std::nextafterf(x, y);
    float actual   = Catch::nextafter(x, y);

    // Exact match expected (wrapper delegates to nextafterf)
    EXPECT_TRUE(SameBits(actual, expected));
}

// When x == y, the result must be y (no step)
TEST(CatchPolyfillsNextafterTest_637, ReturnsYWhenXEqualsY_637) {
    float x = 3.1415927f;
    float y = x;

    float expected = std::nextafterf(x, y);
    float actual   = Catch::nextafter(x, y);

    EXPECT_TRUE(SameBits(actual, expected));
    EXPECT_EQ(actual, y);
}

// Stepping from a large finite value toward +infinity
TEST(CatchPolyfillsNextafterTest_637, HandlesInfinityDirection_637) {
    float x = std::numeric_limits<float>::max();
    float y = std::numeric_limits<float>::infinity();

    float expected = std::nextafterf(x, y);
    float actual   = Catch::nextafter(x, y);

    // On IEEE-754, this becomes +inf; compare exactly to the platform's behavior.
    EXPECT_TRUE(SameBits(actual, expected));
    if (std::isinf(expected)) {
        EXPECT_TRUE(std::isinf(actual));
        EXPECT_GT(actual, 0.0f);
    }
}

// NaN handling: if either argument is NaN, result is NaN
TEST(CatchPolyfillsNextafterTest_637, PropagatesNaN_637) {
    float nan = std::numeric_limits<float>::quiet_NaN();

    // Case 1: x is NaN
    {
        float expected = std::nextafterf(nan, 1.0f);
        float actual   = Catch::nextafter(nan, 1.0f);
        EXPECT_EQ(std::isnan(expected), std::isnan(actual));
        EXPECT_TRUE(std::isnan(actual));
    }
    // Case 2: y is NaN
    {
        float expected = std::nextafterf(1.0f, nan);
        float actual   = Catch::nextafter(1.0f, nan);
        EXPECT_EQ(std::isnan(expected), std::isnan(actual));
        EXPECT_TRUE(std::isnan(actual));
    }
}

// Zero edge: stepping from +0 toward negative side should match std::nextafterf,
// including sign and subnormal behavior on the current platform.
TEST(CatchPolyfillsNextafterTest_637, ZeroTowardsNegativeProducesExpected_637) {
    float x = 0.0f;                 // +0
    float y = -0.0f;                // -0 direction

    float expected = std::nextafterf(x, y);
    float actual   = Catch::nextafter(x, y);

    // Exact bitwise equality, to capture -0.0 vs +0.0 or subnormals precisely
    EXPECT_TRUE(SameBits(actual, expected));

    // Sanity: signbit must match expected
    EXPECT_EQ(std::signbit(expected), std::signbit(actual));
}

// Negative toward positive: should move one representable step toward zero (less negative),
// exactly matching std::nextafterf
TEST(CatchPolyfillsNextafterTest_637, MonotonicStepNegativeTowardsPositive_637) {
    float x = -1.0f;
    float y = +1.0f;

    float expected = std::nextafterf(x, y);
    float actual   = Catch::nextafter(x, y);

    EXPECT_TRUE(SameBits(actual, expected));
    // Additional observable behavior: step is toward larger value (less negative)
    EXPECT_GT(actual, x);
}
