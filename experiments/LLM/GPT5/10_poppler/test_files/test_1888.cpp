#include <gtest/gtest.h>

// Function to be tested
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

// Test suite for radialExtendRange function
class RadialExtendRangeTest_1888 : public ::testing::Test {
protected:
    double range[2];

    void SetUp() override {
        range[0] = range[1] = 0.0;
    }
};

// Test for normal operation (value falls within the existing range)
TEST_F(RadialExtendRangeTest_1888, NormalOperation_1888) {
    double value = 5.0;
    bool valid = true;
    radialExtendRange(range, value, valid);

    // Check that the range remains unchanged since the value is within the range
    EXPECT_EQ(range[0], 0.0);
    EXPECT_EQ(range[1], 0.0);
}

// Test when the value is outside the range (lower bound)
TEST_F(RadialExtendRangeTest_1888, LowerBound_1888) {
    double value = -10.0;
    bool valid = true;
    radialExtendRange(range, value, valid);

    // The range should extend to include the new lower value
    EXPECT_EQ(range[0], -10.0);
    EXPECT_EQ(range[1], 0.0);
}

// Test when the value is outside the range (upper bound)
TEST_F(RadialExtendRangeTest_1888, UpperBound_1888) {
    double value = 20.0;
    bool valid = true;
    radialExtendRange(range, value, valid);

    // The range should extend to include the new upper value
    EXPECT_EQ(range[0], 0.0);
    EXPECT_EQ(range[1], 20.0);
}

// Test when the value is outside the range and valid is false
TEST_F(RadialExtendRangeTest_1888, InvalidRange_1888) {
    double value = 15.0;
    bool valid = false;
    radialExtendRange(range, value, valid);

    // When valid is false, the range should be set to the new value
    EXPECT_EQ(range[0], 15.0);
    EXPECT_EQ(range[1], 15.0);
}

// Test with edge case values (e.g., very large value)
TEST_F(RadialExtendRangeTest_1888, LargeValue_1888) {
    double value = 1e6;
    bool valid = true;
    radialExtendRange(range, value, valid);

    // The range should extend to include the large value
    EXPECT_EQ(range[0], 0.0);
    EXPECT_EQ(range[1], 1e6);
}

// Test with very small values
TEST_F(RadialExtendRangeTest_1888, SmallValue_1888) {
    double value = -1e-6;
    bool valid = true;
    radialExtendRange(range, value, valid);

    // The range should extend to include the small value
    EXPECT_EQ(range[0], -1e-6);
    EXPECT_EQ(range[1], 0.0);
}