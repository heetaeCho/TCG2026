#include <gtest/gtest.h>

// Forward declare and include necessary headers
// Based on the provided code, we need to define/include TextUnderline
// Since we're testing the class as defined in the partial code, we replicate the interface

class TextUnderline {
public:
    double x0, y0, x1, y1;
    bool horiz;

    TextUnderline(double x0A, double y0A, double x1A, double y1A) {
        x0 = x0A;
        y0 = y0A;
        x1 = x1A;
        y1 = y1A;
        horiz = y0 == y1;
    }

    ~TextUnderline() = default;
};

class TextUnderlineTest_2787 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal horizontal underline (y0 == y1)
TEST_F(TextUnderlineTest_2787, HorizontalUnderline_2787) {
    TextUnderline underline(1.0, 5.0, 10.0, 5.0);
    EXPECT_DOUBLE_EQ(underline.x0, 1.0);
    EXPECT_DOUBLE_EQ(underline.y0, 5.0);
    EXPECT_DOUBLE_EQ(underline.x1, 10.0);
    EXPECT_DOUBLE_EQ(underline.y1, 5.0);
    EXPECT_TRUE(underline.horiz);
}

// Test non-horizontal underline (y0 != y1)
TEST_F(TextUnderlineTest_2787, NonHorizontalUnderline_2787) {
    TextUnderline underline(1.0, 5.0, 10.0, 15.0);
    EXPECT_DOUBLE_EQ(underline.x0, 1.0);
    EXPECT_DOUBLE_EQ(underline.y0, 5.0);
    EXPECT_DOUBLE_EQ(underline.x1, 10.0);
    EXPECT_DOUBLE_EQ(underline.y1, 15.0);
    EXPECT_FALSE(underline.horiz);
}

// Test vertical underline (x0 == x1, y0 != y1)
TEST_F(TextUnderlineTest_2787, VerticalUnderline_2787) {
    TextUnderline underline(5.0, 1.0, 5.0, 10.0);
    EXPECT_DOUBLE_EQ(underline.x0, 5.0);
    EXPECT_DOUBLE_EQ(underline.y0, 1.0);
    EXPECT_DOUBLE_EQ(underline.x1, 5.0);
    EXPECT_DOUBLE_EQ(underline.y1, 10.0);
    EXPECT_FALSE(underline.horiz);
}

// Test zero-length underline (all coordinates the same)
TEST_F(TextUnderlineTest_2787, ZeroLengthUnderline_2787) {
    TextUnderline underline(5.0, 5.0, 5.0, 5.0);
    EXPECT_DOUBLE_EQ(underline.x0, 5.0);
    EXPECT_DOUBLE_EQ(underline.y0, 5.0);
    EXPECT_DOUBLE_EQ(underline.x1, 5.0);
    EXPECT_DOUBLE_EQ(underline.y1, 5.0);
    EXPECT_TRUE(underline.horiz);
}

// Test with all zero coordinates
TEST_F(TextUnderlineTest_2787, AllZeroCoordinates_2787) {
    TextUnderline underline(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(underline.x0, 0.0);
    EXPECT_DOUBLE_EQ(underline.y0, 0.0);
    EXPECT_DOUBLE_EQ(underline.x1, 0.0);
    EXPECT_DOUBLE_EQ(underline.y1, 0.0);
    EXPECT_TRUE(underline.horiz);
}

// Test with negative coordinates, horizontal
TEST_F(TextUnderlineTest_2787, NegativeCoordinatesHorizontal_2787) {
    TextUnderline underline(-10.0, -5.0, -1.0, -5.0);
    EXPECT_DOUBLE_EQ(underline.x0, -10.0);
    EXPECT_DOUBLE_EQ(underline.y0, -5.0);
    EXPECT_DOUBLE_EQ(underline.x1, -1.0);
    EXPECT_DOUBLE_EQ(underline.y1, -5.0);
    EXPECT_TRUE(underline.horiz);
}

// Test with negative coordinates, non-horizontal
TEST_F(TextUnderlineTest_2787, NegativeCoordinatesNonHorizontal_2787) {
    TextUnderline underline(-10.0, -5.0, -1.0, -3.0);
    EXPECT_DOUBLE_EQ(underline.x0, -10.0);
    EXPECT_DOUBLE_EQ(underline.y0, -5.0);
    EXPECT_DOUBLE_EQ(underline.x1, -1.0);
    EXPECT_DOUBLE_EQ(underline.y1, -3.0);
    EXPECT_FALSE(underline.horiz);
}

// Test with very large coordinates
TEST_F(TextUnderlineTest_2787, LargeCoordinates_2787) {
    double large = 1e15;
    TextUnderline underline(large, large, large + 100.0, large);
    EXPECT_DOUBLE_EQ(underline.x0, large);
    EXPECT_DOUBLE_EQ(underline.y0, large);
    EXPECT_DOUBLE_EQ(underline.x1, large + 100.0);
    EXPECT_DOUBLE_EQ(underline.y1, large);
    EXPECT_TRUE(underline.horiz);
}

// Test with very small difference in y (not exactly equal)
TEST_F(TextUnderlineTest_2787, SmallDifferenceInY_2787) {
    TextUnderline underline(1.0, 5.0, 10.0, 5.0 + 1e-15);
    EXPECT_DOUBLE_EQ(underline.x0, 1.0);
    EXPECT_DOUBLE_EQ(underline.y0, 5.0);
    EXPECT_DOUBLE_EQ(underline.x1, 10.0);
    EXPECT_DOUBLE_EQ(underline.y1, 5.0 + 1e-15);
    // y0 != y1 due to floating point, so horiz should be false
    // Note: 5.0 + 1e-15 may or may not equal 5.0 depending on precision
    // 5.0 + 1e-15 != 5.0 in double precision, so horiz should be false
    EXPECT_FALSE(underline.horiz);
}

// Test diagonal underline
TEST_F(TextUnderlineTest_2787, DiagonalUnderline_2787) {
    TextUnderline underline(0.0, 0.0, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(underline.x0, 0.0);
    EXPECT_DOUBLE_EQ(underline.y0, 0.0);
    EXPECT_DOUBLE_EQ(underline.x1, 10.0);
    EXPECT_DOUBLE_EQ(underline.y1, 10.0);
    EXPECT_FALSE(underline.horiz);
}

// Test with reversed coordinates (x1 < x0)
TEST_F(TextUnderlineTest_2787, ReversedXCoordinatesHorizontal_2787) {
    TextUnderline underline(10.0, 3.0, 1.0, 3.0);
    EXPECT_DOUBLE_EQ(underline.x0, 10.0);
    EXPECT_DOUBLE_EQ(underline.y0, 3.0);
    EXPECT_DOUBLE_EQ(underline.x1, 1.0);
    EXPECT_DOUBLE_EQ(underline.y1, 3.0);
    EXPECT_TRUE(underline.horiz);
}

// Test with fractional coordinates, horizontal
TEST_F(TextUnderlineTest_2787, FractionalCoordinatesHorizontal_2787) {
    TextUnderline underline(1.5, 2.75, 10.25, 2.75);
    EXPECT_DOUBLE_EQ(underline.x0, 1.5);
    EXPECT_DOUBLE_EQ(underline.y0, 2.75);
    EXPECT_DOUBLE_EQ(underline.x1, 10.25);
    EXPECT_DOUBLE_EQ(underline.y1, 2.75);
    EXPECT_TRUE(underline.horiz);
}

// Test y0 == 0 and y1 == 0 (horizontal at origin)
TEST_F(TextUnderlineTest_2787, HorizontalAtYZero_2787) {
    TextUnderline underline(1.0, 0.0, 10.0, 0.0);
    EXPECT_DOUBLE_EQ(underline.x0, 1.0);
    EXPECT_DOUBLE_EQ(underline.y0, 0.0);
    EXPECT_DOUBLE_EQ(underline.x1, 10.0);
    EXPECT_DOUBLE_EQ(underline.y1, 0.0);
    EXPECT_TRUE(underline.horiz);
}

// Test with y0 slightly different from y1 due to computation
TEST_F(TextUnderlineTest_2787, FloatingPointEqualityCheck_2787) {
    double y = 1.0 / 3.0;
    TextUnderline underline(0.0, y, 10.0, y);
    EXPECT_TRUE(underline.horiz);
}

// Test that y0 computed differently but same value still gives horiz
TEST_F(TextUnderlineTest_2787, SameValueDifferentComputation_2787) {
    double y0 = 0.1 + 0.2;  // May not be exactly 0.3
    double y1 = 0.1 + 0.2;  // Same computation, same result
    TextUnderline underline(0.0, y0, 10.0, y1);
    EXPECT_TRUE(underline.horiz);
}
