// File: catch_polyfills_isnan_test.cpp

#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cfloat>

// Forward declare the function under test (link with the real implementation)
namespace Catch {
    bool isnan(float f);
}

class CatchPolyfillsIsnanTest_635 : public ::testing::Test {};

// Normal operation: quiet NaN should be detected
TEST_F(CatchPolyfillsIsnanTest_635, QuietNaNIsTrue_635) {
    const float qnan = std::numeric_limits<float>::quiet_NaN();
    EXPECT_TRUE(Catch::isnan(qnan));
}

// Normal operation: typical finite values should not be NaN
TEST_F(CatchPolyfillsIsnanTest_635, FiniteValuesAreFalse_635) {
    EXPECT_FALSE(Catch::isnan(0.0f));
    EXPECT_FALSE(Catch::isnan(1.0f));
    EXPECT_FALSE(Catch::isnan(-123.45f));
    EXPECT_FALSE(Catch::isnan(FLT_MAX));
    EXPECT_FALSE(Catch::isnan(-FLT_MAX));
}

// Boundary condition: infinities are not NaN
TEST_F(CatchPolyfillsIsnanTest_635, InfinitiesAreFalse_635) {
    const float pinf = std::numeric_limits<float>::infinity();
    const float ninf = -std::numeric_limits<float>::infinity();
    EXPECT_FALSE(Catch::isnan(pinf));
    EXPECT_FALSE(Catch::isnan(ninf));
}

// Boundary condition: subnormal (denormal) values are finite, not NaN
TEST_F(CatchPolyfillsIsnanTest_635, SubnormalIsFalse_635) {
    const float sub = std::numeric_limits<float>::denorm_min();
    EXPECT_FALSE(Catch::isnan(sub));
    EXPECT_FALSE(Catch::isnan(-sub));
}

// Exceptional/edge: signaling NaN, if supported on this platform, should be detected
TEST_F(CatchPolyfillsIsnanTest_635, SignalingNaNIsTrueIfAvailable_635) {
    if (!std::numeric_limits<float>::has_signaling_NaN) {
        GTEST_SKIP() << "signaling NaN not supported on this platform";
    }
    const float snan = std::numeric_limits<float>::signaling_NaN();
    EXPECT_TRUE(Catch::isnan(snan));
}

// Cross-check: Catch::isnan should match std::isnan for a variety of values
TEST_F(CatchPolyfillsIsnanTest_635, MatchesStdIsnanForVariety_635) {
    const float values[] = {
        0.0f,
        -0.0f,
        1.0f,
        -2.5f,
        FLT_MIN,
        -FLT_MIN,
        FLT_MAX,
        -FLT_MAX,
        std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::quiet_NaN()
    };

    for (float v : values) {
        EXPECT_EQ(Catch::isnan(v), static_cast<bool>(std::isnan(v)))
            << "Mismatch for value";
    }
}
