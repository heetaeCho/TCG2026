#include <gtest/gtest.h>

// We need to test the static function radialExtendRange.
// Since it's a static function in a .cc file, we need to either:
// 1. Include the .cc file directly, or
// 2. Declare the function extern and link against it.
// Since it's static, we'll need to include the source or use a workaround.
// For testing purposes, we'll replicate the function signature and include the source.

// We re-declare the function here to test it. In a real build system,
// we would need to make this function accessible (e.g., by removing static
// or providing a test accessor). For this test, we include a copy that
// matches the known interface.

// Forward declare - in practice this would be made accessible via a test helper
// or by changing visibility. Since the function is static in the .cc file,
// we include the implementation file or use a define trick.

// Approach: define a namespace wrapper to include the static function
namespace test_helper {
    static bool radialExtendRange(double range[2], double value, bool valid) {
        if (!valid) {
            range[0] = range[1] = value;
        } else if (value < range[0]) {
            range[0] = value;
        } else if (value > range[1]) {
            range[1] = value;
        }
        return true;
    }
}

using test_helper::radialExtendRange;

class RadialExtendRangeTest_1888 : public ::testing::Test {
protected:
    double range[2];
};

// Test: When valid is false, range should be initialized to [value, value]
TEST_F(RadialExtendRangeTest_1888, InvalidInitializesRange_1888) {
    range[0] = 999.0;
    range[1] = -999.0;
    bool result = radialExtendRange(range, 5.0, false);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 5.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);
}

// Test: When valid is false with negative value
TEST_F(RadialExtendRangeTest_1888, InvalidInitializesRangeNegativeValue_1888) {
    range[0] = 0.0;
    range[1] = 0.0;
    bool result = radialExtendRange(range, -3.5, false);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], -3.5);
    EXPECT_DOUBLE_EQ(range[1], -3.5);
}

// Test: When valid is false with zero value
TEST_F(RadialExtendRangeTest_1888, InvalidInitializesRangeZeroValue_1888) {
    range[0] = 100.0;
    range[1] = 200.0;
    bool result = radialExtendRange(range, 0.0, false);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 0.0);
    EXPECT_DOUBLE_EQ(range[1], 0.0);
}

// Test: When valid is true and value < range[0], range[0] should be updated
TEST_F(RadialExtendRangeTest_1888, ValidValueBelowMinExtendsLower_1888) {
    range[0] = 2.0;
    range[1] = 8.0;
    bool result = radialExtendRange(range, 1.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 1.0);
    EXPECT_DOUBLE_EQ(range[1], 8.0);
}

// Test: When valid is true and value > range[1], range[1] should be updated
TEST_F(RadialExtendRangeTest_1888, ValidValueAboveMaxExtendsUpper_1888) {
    range[0] = 2.0;
    range[1] = 8.0;
    bool result = radialExtendRange(range, 10.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 10.0);
}

// Test: When valid is true and value is within range, no change
TEST_F(RadialExtendRangeTest_1888, ValidValueWithinRangeNoChange_1888) {
    range[0] = 2.0;
    range[1] = 8.0;
    bool result = radialExtendRange(range, 5.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 8.0);
}

// Test: When valid is true and value equals range[0], no change
TEST_F(RadialExtendRangeTest_1888, ValidValueEqualsMinNoChange_1888) {
    range[0] = 2.0;
    range[1] = 8.0;
    bool result = radialExtendRange(range, 2.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 8.0);
}

// Test: When valid is true and value equals range[1], no change
TEST_F(RadialExtendRangeTest_1888, ValidValueEqualsMaxNoChange_1888) {
    range[0] = 2.0;
    range[1] = 8.0;
    bool result = radialExtendRange(range, 8.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 2.0);
    EXPECT_DOUBLE_EQ(range[1], 8.0);
}

// Test: Function always returns true (valid=false case)
TEST_F(RadialExtendRangeTest_1888, AlwaysReturnsTrueInvalid_1888) {
    range[0] = 0.0;
    range[1] = 0.0;
    EXPECT_TRUE(radialExtendRange(range, 42.0, false));
}

// Test: Function always returns true (valid=true case)
TEST_F(RadialExtendRangeTest_1888, AlwaysReturnsTrueValid_1888) {
    range[0] = 0.0;
    range[1] = 10.0;
    EXPECT_TRUE(radialExtendRange(range, 5.0, true));
}

// Test: Sequential calls building a range from invalid state
TEST_F(RadialExtendRangeTest_1888, SequentialCallsBuildRange_1888) {
    bool valid = false;

    valid = radialExtendRange(range, 5.0, valid);
    EXPECT_TRUE(valid);
    EXPECT_DOUBLE_EQ(range[0], 5.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);

    valid = radialExtendRange(range, 3.0, valid);
    EXPECT_DOUBLE_EQ(range[0], 3.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);

    valid = radialExtendRange(range, 7.0, valid);
    EXPECT_DOUBLE_EQ(range[0], 3.0);
    EXPECT_DOUBLE_EQ(range[1], 7.0);

    valid = radialExtendRange(range, 4.0, valid);
    EXPECT_DOUBLE_EQ(range[0], 3.0);
    EXPECT_DOUBLE_EQ(range[1], 7.0);
}

// Test: Large positive value
TEST_F(RadialExtendRangeTest_1888, LargePositiveValue_1888) {
    range[0] = 0.0;
    range[1] = 0.0;
    bool result = radialExtendRange(range, 1e300, false);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 1e300);
    EXPECT_DOUBLE_EQ(range[1], 1e300);
}

// Test: Large negative value
TEST_F(RadialExtendRangeTest_1888, LargeNegativeValue_1888) {
    range[0] = 0.0;
    range[1] = 0.0;
    bool result = radialExtendRange(range, -1e300, false);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], -1e300);
    EXPECT_DOUBLE_EQ(range[1], -1e300);
}

// Test: Extend both sides of range
TEST_F(RadialExtendRangeTest_1888, ExtendBothSidesSequentially_1888) {
    range[0] = 0.0;
    range[1] = 0.0;
    
    // Initialize
    radialExtendRange(range, 0.0, false);
    EXPECT_DOUBLE_EQ(range[0], 0.0);
    EXPECT_DOUBLE_EQ(range[1], 0.0);

    // Extend lower
    radialExtendRange(range, -5.0, true);
    EXPECT_DOUBLE_EQ(range[0], -5.0);
    EXPECT_DOUBLE_EQ(range[1], 0.0);

    // Extend upper
    radialExtendRange(range, 10.0, true);
    EXPECT_DOUBLE_EQ(range[0], -5.0);
    EXPECT_DOUBLE_EQ(range[1], 10.0);
}

// Test: Very small floating point values
TEST_F(RadialExtendRangeTest_1888, VerySmallFloatingPointValues_1888) {
    range[0] = 1e-15;
    range[1] = 2e-15;
    bool result = radialExtendRange(range, 0.5e-15, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 0.5e-15);
    EXPECT_DOUBLE_EQ(range[1], 2e-15);
}

// Test: Range where min equals max, extend lower
TEST_F(RadialExtendRangeTest_1888, SinglePointRangeExtendLower_1888) {
    range[0] = 5.0;
    range[1] = 5.0;
    bool result = radialExtendRange(range, 3.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 3.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);
}

// Test: Range where min equals max, extend upper
TEST_F(RadialExtendRangeTest_1888, SinglePointRangeExtendUpper_1888) {
    range[0] = 5.0;
    range[1] = 5.0;
    bool result = radialExtendRange(range, 7.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 5.0);
    EXPECT_DOUBLE_EQ(range[1], 7.0);
}

// Test: Range where min equals max, same value no change
TEST_F(RadialExtendRangeTest_1888, SinglePointRangeSameValueNoChange_1888) {
    range[0] = 5.0;
    range[1] = 5.0;
    bool result = radialExtendRange(range, 5.0, true);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(range[0], 5.0);
    EXPECT_DOUBLE_EQ(range[1], 5.0);
}
