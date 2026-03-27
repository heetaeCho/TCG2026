#include <gtest/gtest.h>
#include "poppler-rectangle.h"

namespace poppler {

class RectangleTest_1019 : public ::testing::Test {
protected:
    rectangle<int> rect;
};

// Test for normal operation: Setting a new right value
TEST_F(RectangleTest_1019, SetRight_NormalOperation_1019) {
    rect.set_right(10);
    EXPECT_EQ(rect.right(), 10);
}

// Boundary Test: Setting a right value equal to the left
TEST_F(RectangleTest_1019, SetRight_EqualToLeft_1019) {
    rect.set_left(5);
    rect.set_right(5);
    EXPECT_EQ(rect.right(), 5);
}

// Boundary Test: Setting a right value smaller than the left (should not create invalid geometry)
TEST_F(RectangleTest_1019, SetRight_SmallerThanLeft_1019) {
    rect.set_left(10);
    rect.set_right(5);
    EXPECT_EQ(rect.right(), 5);  // Expect the right to be smaller than left but it's a valid case
}

// Exceptional Case: Setting a very large value for right (boundary testing for large integers)
TEST_F(RectangleTest_1019, SetRight_LargeValue_1019) {
    rect.set_right(1000000);
    EXPECT_EQ(rect.right(), 1000000);
}

// Exceptional Case: Setting a negative value for right (boundary testing for negative values)
TEST_F(RectangleTest_1019, SetRight_NegativeValue_1019) {
    rect.set_right(-10);
    EXPECT_EQ(rect.right(), -10);
}

// Test for verifying that setting right modifies only the right value and not other members
TEST_F(RectangleTest_1019, SetRight_DoesNotAffectOtherValues_1019) {
    rect.set_left(5);
    rect.set_top(5);
    rect.set_bottom(10);
    rect.set_right(20);

    // Verify that only the right value changed
    EXPECT_EQ(rect.left(), 5);
    EXPECT_EQ(rect.top(), 5);
    EXPECT_EQ(rect.bottom(), 10);
    EXPECT_EQ(rect.right(), 20);
}

// Boundary Test: Testing when set_right is called on an already empty rectangle (initial value 0)
TEST_F(RectangleTest_1019, SetRight_EmptyRectangle_1019) {
    rect.set_right(0);
    EXPECT_EQ(rect.right(), 0);
}

// Test for a rectangle that is not empty and verifying right is set correctly
TEST_F(RectangleTest_1019, SetRight_NonEmptyRectangle_1019) {
    rect = rectangle<int>(0, 0, 5, 5);  // Rectangle with width 5 and height 5
    rect.set_right(10);
    EXPECT_EQ(rect.right(), 10);
}
}  // namespace poppler