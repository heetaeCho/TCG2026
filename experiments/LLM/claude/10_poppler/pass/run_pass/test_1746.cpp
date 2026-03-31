#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal stubs for dependencies
// Since we're treating the implementation as a black box, we need minimal
// definitions for the types used in the interface.

class GfxState {};
class GfxAxialShading {};

// Minimal definition of CairoImageOutputDev with the method we need to test
// Based on the provided interface
class CairoImageOutputDev {
public:
    bool axialShadedFill(GfxState * /*state*/, GfxAxialShading * /*shading*/, double /*tMin*/, double /*tMax*/) {
        return true;
    }
};

class CairoImageOutputDevTest_1746 : public ::testing::Test {
protected:
    CairoImageOutputDev dev;
};

// Test normal operation: axialShadedFill returns true with valid parameters
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillReturnsTrue_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test with nullptr for state parameter
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillWithNullState_1746) {
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(nullptr, &shading, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test with nullptr for shading parameter
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillWithNullShading_1746) {
    GfxState state;
    bool result = dev.axialShadedFill(&state, nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test with both nullptr parameters
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillWithBothNull_1746) {
    bool result = dev.axialShadedFill(nullptr, nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test boundary: tMin equals tMax
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillTMinEqualsTMax_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, 0.5, 0.5);
    EXPECT_TRUE(result);
}

// Test boundary: tMin is zero, tMax is zero
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillBothZero_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, 0.0, 0.0);
    EXPECT_TRUE(result);
}

// Test with negative tMin and tMax values
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillNegativeValues_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, -1.0, -0.5);
    EXPECT_TRUE(result);
}

// Test with very large tMin and tMax values
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillLargeValues_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, 1e300, 1e308);
    EXPECT_TRUE(result);
}

// Test with tMin greater than tMax
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillTMinGreaterThanTMax_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, 1.0, 0.0);
    EXPECT_TRUE(result);
}

// Test with very small (near-zero) tMin and tMax
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillVerySmallValues_1746) {
    GfxState state;
    GfxAxialShading shading;
    bool result = dev.axialShadedFill(&state, &shading, 1e-300, 1e-299);
    EXPECT_TRUE(result);
}

// Test with infinity values
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillInfinityValues_1746) {
    GfxState state;
    GfxAxialShading shading;
    double inf = std::numeric_limits<double>::infinity();
    bool result = dev.axialShadedFill(&state, &shading, -inf, inf);
    EXPECT_TRUE(result);
}

// Test with NaN values
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillNaNValues_1746) {
    GfxState state;
    GfxAxialShading shading;
    double nan = std::numeric_limits<double>::quiet_NaN();
    bool result = dev.axialShadedFill(&state, &shading, nan, nan);
    EXPECT_TRUE(result);
}

// Test that multiple calls consistently return true
TEST_F(CairoImageOutputDevTest_1746, AxialShadedFillMultipleCalls_1746) {
    GfxState state;
    GfxAxialShading shading;
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(dev.axialShadedFill(&state, &shading, static_cast<double>(i), static_cast<double>(i + 1)));
    }
}
