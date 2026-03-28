#include <gtest/gtest.h>
#include "GfxState_helpers.h"

TEST_F(GfxStateHelpersTest_1881, Clip01_NormalOperation_1881) {
    // Test the normal case where the input is within bounds
    EXPECT_EQ(clip01(0.5), 0.5);
    EXPECT_EQ(clip01(0.0), 0.0);
    EXPECT_EQ(clip01(1.0), 1.0);
}

TEST_F(GfxStateHelpersTest_1882, Clip01_LowerBoundary_1882) {
    // Test the lower boundary case where the input is below the minimum
    EXPECT_EQ(clip01(-0.5), 0.0);
    EXPECT_EQ(clip01(-100.0), 0.0);
}

TEST_F(GfxStateHelpersTest_1883, Clip01_UpperBoundary_1883) {
    // Test the upper boundary case where the input exceeds the maximum
    EXPECT_EQ(clip01(1.2), gfxColorComp1);
    EXPECT_EQ(clip01(70000), gfxColorComp1);
}

TEST_F(GfxStateHelpersTest_1884, Clip01_EqualBoundary_1884) {
    // Test the case where input is exactly at the boundaries
    EXPECT_EQ(clip01(0), 0.0);
    EXPECT_EQ(clip01(gfxColorComp1), gfxColorComp1);
}

TEST_F(GfxStateHelpersTest_1885, Clip01_FloatBoundary_1885) {
    // Test with floating-point numbers that are very close to boundaries
    EXPECT_EQ(clip01(gfxColorComp1 - 0.0001), gfxColorComp1);
    EXPECT_EQ(clip01(0.0001), 0.0);
}

TEST_F(GfxStateHelpersTest_1886, Clip01_InvalidInput_1886) {
    // Test invalid cases - although the function expects a valid GfxColorComp,
    // we assume here that we pass numbers that are unreasonably large or small.
    EXPECT_EQ(clip01(-std::numeric_limits<double>::infinity()), 0.0);
    EXPECT_EQ(clip01(std::numeric_limits<double>::infinity()), gfxColorComp1);
    EXPECT_EQ(clip01(std::nan("1")), 0.0);  // NaN should be treated as lower bound
}