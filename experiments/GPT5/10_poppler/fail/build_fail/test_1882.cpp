#include <gtest/gtest.h>

// The function to be tested
static inline double clip01(double x) {
    return (x < 0) ? 0 : (x > 1) ? 1 : x;
}

// Unit tests for clip01 function

// Normal operation tests
TEST_F(GfxStateHelpersTest_1882, ClipNegativeValue_1882) {
    double input = -0.5;
    double expected = 0.0;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}

TEST_F(GfxStateHelpersTest_1882, ClipZeroValue_1882) {
    double input = 0.0;
    double expected = 0.0;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}

TEST_F(GfxStateHelpersTest_1882, ClipPositiveValueWithinRange_1882) {
    double input = 0.5;
    double expected = 0.5;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}

TEST_F(GfxStateHelpersTest_1882, ClipOneValue_1882) {
    double input = 1.0;
    double expected = 1.0;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}

// Boundary condition tests
TEST_F(GfxStateHelpersTest_1882, ClipGreaterThanOneValue_1882) {
    double input = 1.5;
    double expected = 1.0;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}

// Exceptional or error cases (if observable through the interface)
TEST_F(GfxStateHelpersTest_1882, ClipLargeNegativeValue_1882) {
    double input = -1000.0;
    double expected = 0.0;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}

TEST_F(GfxStateHelpersTest_1882, ClipLargePositiveValue_1882) {
    double input = 1000.0;
    double expected = 1.0;
    EXPECT_DOUBLE_EQ(clip01(input), expected);
}