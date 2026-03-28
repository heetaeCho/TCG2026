#include <gtest/gtest.h>

// Declare the function under test (since it's static inline in the .cc file,
// we need to re-declare it here for testing purposes)
static inline unsigned char clip255(int x) { return x < 0 ? 0 : x > 255 ? 255 : x; }

// Normal operation tests
TEST(Clip255Test_1598, ReturnsZeroForNegativeValues_1598) {
    EXPECT_EQ(0, clip255(-1));
    EXPECT_EQ(0, clip255(-100));
    EXPECT_EQ(0, clip255(-1000));
}

TEST(Clip255Test_1598, Returns255ForValuesAbove255_1598) {
    EXPECT_EQ(255, clip255(256));
    EXPECT_EQ(255, clip255(300));
    EXPECT_EQ(255, clip255(1000));
}

TEST(Clip255Test_1598, ReturnsInputForValuesInRange_1598) {
    EXPECT_EQ(0, clip255(0));
    EXPECT_EQ(1, clip255(1));
    EXPECT_EQ(127, clip255(127));
    EXPECT_EQ(128, clip255(128));
    EXPECT_EQ(254, clip255(254));
    EXPECT_EQ(255, clip255(255));
}

// Boundary condition tests
TEST(Clip255Test_1598, BoundaryAtZero_1598) {
    EXPECT_EQ(0, clip255(-1));
    EXPECT_EQ(0, clip255(0));
    EXPECT_EQ(1, clip255(1));
}

TEST(Clip255Test_1598, BoundaryAt255_1598) {
    EXPECT_EQ(254, clip255(254));
    EXPECT_EQ(255, clip255(255));
    EXPECT_EQ(255, clip255(256));
}

TEST(Clip255Test_1598, ExtremeNegativeValue_1598) {
    EXPECT_EQ(0, clip255(INT_MIN));
}

TEST(Clip255Test_1598, ExtremePositiveValue_1598) {
    EXPECT_EQ(255, clip255(INT_MAX));
}

// Verify return type behavior
TEST(Clip255Test_1598, ReturnTypeIsUnsignedChar_1598) {
    unsigned char result = clip255(100);
    EXPECT_EQ(100, result);
    
    result = clip255(-50);
    EXPECT_EQ(0, result);
    
    result = clip255(500);
    EXPECT_EQ(255, result);
}

// Mid-range values
TEST(Clip255Test_1598, MidRangeValues_1598) {
    EXPECT_EQ(50, clip255(50));
    EXPECT_EQ(100, clip255(100));
    EXPECT_EQ(150, clip255(150));
    EXPECT_EQ(200, clip255(200));
}

// Negative values close to zero
TEST(Clip255Test_1598, SmallNegativeValues_1598) {
    EXPECT_EQ(0, clip255(-1));
    EXPECT_EQ(0, clip255(-2));
    EXPECT_EQ(0, clip255(-10));
}

// Values just above 255
TEST(Clip255Test_1598, ValuesJustAbove255_1598) {
    EXPECT_EQ(255, clip255(256));
    EXPECT_EQ(255, clip255(257));
    EXPECT_EQ(255, clip255(260));
}
