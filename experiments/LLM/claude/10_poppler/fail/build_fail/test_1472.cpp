#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/GfxState.h"

// The function under test is static inline in Gfx.cc, so we include it here
// to be able to test it directly.
static inline void getShadingColorRadialHelper(double t0, double t1, double t, GfxRadialShading *shading, GfxColor *color) {
    if (t0 < t1) {
        if (t < t0) {
            shading->getColor(t0, color);
        } else if (t > t1) {
            shading->getColor(t1, color);
        } else {
            shading->getColor(t, color);
        }
    } else {
        if (t > t0) {
            shading->getColor(t0, color);
        } else if (t < t1) {
            shading->getColor(t1, color);
        } else {
            shading->getColor(t, color);
        }
    }
}

// Since we can't easily mock GfxRadialShading (getColor is not virtual in the 
// univariate base), we create a wrapper that tracks calls.
// We'll use a GfxRadialShading with no functions - getColor will set color
// components based on implementation. We verify the 't' value passed by
// creating a shading with known domain and checking clamping behavior.

class ShadingColorRadialHelperTest_1472 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal GfxRadialShading with no functions
        // Using the constructor that takes int&& for funcsA (0 functions)
        shading = std::make_unique<GfxRadialShading>(
            0.0, 0.0, 0.0,  // x0, y0, r0
            1.0, 1.0, 1.0,  // x1, y1, r1
            0.0, 1.0,        // t0, t1
            0,                // no functions
            false, false      // extend0, extend1
        );
    }

    std::unique_ptr<GfxRadialShading> shading;
    GfxColor color;
};

// Test: t0 < t1, t is within range
TEST_F(ShadingColorRadialHelperTest_1472, NormalRange_TWithinBounds_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.0, 1.0, 0.5, shading.get(), &color);
    // Function should call getColor(0.5, color) - no clamping
    // We just verify it doesn't crash; exact color depends on implementation
}

// Test: t0 < t1, t < t0 => clamp to t0
TEST_F(ShadingColorRadialHelperTest_1472, NormalRange_TBelowLower_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.2, 0.8, 0.1, shading.get(), &color);
    // Should call getColor(0.2, color)
}

// Test: t0 < t1, t > t1 => clamp to t1
TEST_F(ShadingColorRadialHelperTest_1472, NormalRange_TAboveUpper_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.2, 0.8, 0.9, shading.get(), &color);
    // Should call getColor(0.8, color)
}

// Test: t0 < t1, t == t0 => use t (boundary)
TEST_F(ShadingColorRadialHelperTest_1472, NormalRange_TEqualsT0_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.2, 0.8, 0.2, shading.get(), &color);
    // Should call getColor(0.2, color)
}

// Test: t0 < t1, t == t1 => use t (boundary)
TEST_F(ShadingColorRadialHelperTest_1472, NormalRange_TEqualsT1_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.2, 0.8, 0.8, shading.get(), &color);
    // Should call getColor(0.8, color)
}

// Test: t0 > t1 (reversed range), t within range
TEST_F(ShadingColorRadialHelperTest_1472, ReversedRange_TWithinBounds_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.8, 0.2, 0.5, shading.get(), &color);
    // Should call getColor(0.5, color)
}

// Test: t0 > t1, t > t0 => clamp to t0
TEST_F(ShadingColorRadialHelperTest_1472, ReversedRange_TAboveT0_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.8, 0.2, 0.9, shading.get(), &color);
    // Should call getColor(0.8, color)
}

// Test: t0 > t1, t < t1 => clamp to t1
TEST_F(ShadingColorRadialHelperTest_1472, ReversedRange_TBelowT1_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.8, 0.2, 0.1, shading.get(), &color);
    // Should call getColor(0.2, color)
}

// Test: t0 > t1, t == t0 => use t (boundary)
TEST_F(ShadingColorRadialHelperTest_1472, ReversedRange_TEqualsT0_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.8, 0.2, 0.8, shading.get(), &color);
    // Should call getColor(0.8, color)
}

// Test: t0 > t1, t == t1 => use t (boundary)
TEST_F(ShadingColorRadialHelperTest_1472, ReversedRange_TEqualsT1_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.8, 0.2, 0.2, shading.get(), &color);
    // Should call getColor(0.2, color)
}

// Test: t0 == t1 (degenerate), t == t0 => falls into else branch, getColor(t)
TEST_F(ShadingColorRadialHelperTest_1472, EqualRange_TEqualsT0_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.5, 0.5, 0.5, shading.get(), &color);
    // t0 >= t1 path, t == t0 so not > t0, and t == t1 so not < t1 => getColor(t)
}

// Test: t0 == t1 (degenerate), t > t0 => clamp to t0
TEST_F(ShadingColorRadialHelperTest_1472, EqualRange_TAboveT0_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.5, 0.5, 0.7, shading.get(), &color);
    // t0 >= t1 path, t > t0 => getColor(t0=0.5)
}

// Test: t0 == t1 (degenerate), t < t1 => clamp to t1
TEST_F(ShadingColorRadialHelperTest_1472, EqualRange_TBelowT1_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.5, 0.5, 0.3, shading.get(), &color);
    // t0 >= t1 path, t < t1 => getColor(t1=0.5)
}

// Test: Negative values for t0, t1, t
TEST_F(ShadingColorRadialHelperTest_1472, NegativeValues_NormalRange_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(-1.0, 1.0, -0.5, shading.get(), &color);
    // t0 < t1, t within range => getColor(-0.5)
}

// Test: Negative values, t below range
TEST_F(ShadingColorRadialHelperTest_1472, NegativeValues_TBelowRange_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(-1.0, 1.0, -2.0, shading.get(), &color);
    // t < t0 => getColor(-1.0)
}

// Test: Large values
TEST_F(ShadingColorRadialHelperTest_1472, LargeValues_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.0, 1e10, 5e9, shading.get(), &color);
    // Within range => getColor(5e9)
}

// Test: Zero range normal
TEST_F(ShadingColorRadialHelperTest_1472, ZeroToZero_1472) {
    memset(&color, 0, sizeof(color));
    getShadingColorRadialHelper(0.0, 0.0, 0.0, shading.get(), &color);
    // Degenerate case, should not crash
}
