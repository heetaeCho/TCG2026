#include <gtest/gtest.h>
#include "Annot.h"

class AnnotBorderArrayTest_750 : public ::testing::Test {
protected:
    AnnotBorderArray borderArray;
};

// Test default construction and initial horizontal corner value
TEST_F(AnnotBorderArrayTest_750, DefaultConstructor_750) {
    // After default construction, getHorizontalCorner and getVerticalCorner should return some default
    // We test that they are callable and return a value (likely 0.0 by default)
    double hc = borderArray.getHorizontalCorner();
    double vc = borderArray.getVerticalCorner();
    EXPECT_DOUBLE_EQ(hc, 0.0);
    EXPECT_DOUBLE_EQ(vc, 0.0);
}

// Test setHorizontalCorner and getHorizontalCorner basic operation
TEST_F(AnnotBorderArrayTest_750, SetAndGetHorizontalCorner_750) {
    borderArray.setHorizontalCorner(5.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 5.0);
}

// Test setVerticalCorner and getVerticalCorner basic operation
TEST_F(AnnotBorderArrayTest_750, SetAndGetVerticalCorner_750) {
    borderArray.setVerticalCorner(3.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 3.0);
}

// Test setting horizontal corner to zero
TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerToZero_750) {
    borderArray.setHorizontalCorner(10.0);
    borderArray.setHorizontalCorner(0.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 0.0);
}

// Test setting vertical corner to zero
TEST_F(AnnotBorderArrayTest_750, SetVerticalCornerToZero_750) {
    borderArray.setVerticalCorner(10.0);
    borderArray.setVerticalCorner(0.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 0.0);
}

// Test setting horizontal corner to a negative value
TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerNegative_750) {
    borderArray.setHorizontalCorner(-2.5);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), -2.5);
}

// Test setting vertical corner to a negative value
TEST_F(AnnotBorderArrayTest_750, SetVerticalCornerNegative_750) {
    borderArray.setVerticalCorner(-7.3);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), -7.3);
}

// Test setting horizontal corner to a very large value
TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerLargeValue_750) {
    borderArray.setHorizontalCorner(1e15);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 1e15);
}

// Test setting vertical corner to a very large value
TEST_F(AnnotBorderArrayTest_750, SetVerticalCornerLargeValue_750) {
    borderArray.setVerticalCorner(1e15);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 1e15);
}

// Test setting horizontal corner to a very small positive value
TEST_F(AnnotBorderArrayTest_750, SetHorizontalCornerSmallPositive_750) {
    borderArray.setHorizontalCorner(1e-10);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 1e-10);
}

// Test setting vertical corner to a very small positive value
TEST_F(AnnotBorderArrayTest_750, SetVerticalCornerSmallPositive_750) {
    borderArray.setVerticalCorner(1e-10);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 1e-10);
}

// Test multiple sequential sets on horizontal corner
TEST_F(AnnotBorderArrayTest_750, MultipleSetHorizontalCorner_750) {
    borderArray.setHorizontalCorner(1.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 1.0);
    borderArray.setHorizontalCorner(2.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 2.0);
    borderArray.setHorizontalCorner(3.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 3.0);
}

// Test multiple sequential sets on vertical corner
TEST_F(AnnotBorderArrayTest_750, MultipleSetVerticalCorner_750) {
    borderArray.setVerticalCorner(1.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 1.0);
    borderArray.setVerticalCorner(2.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 2.0);
    borderArray.setVerticalCorner(3.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 3.0);
}

// Test that setting horizontal corner does not affect vertical corner
TEST_F(AnnotBorderArrayTest_750, SetHorizontalDoesNotAffectVertical_750) {
    borderArray.setVerticalCorner(5.0);
    borderArray.setHorizontalCorner(10.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 5.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 10.0);
}

// Test that setting vertical corner does not affect horizontal corner
TEST_F(AnnotBorderArrayTest_750, SetVerticalDoesNotAffectHorizontal_750) {
    borderArray.setHorizontalCorner(5.0);
    borderArray.setVerticalCorner(10.0);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 5.0);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 10.0);
}

// Test copy method returns a valid copy
TEST_F(AnnotBorderArrayTest_750, CopyReturnsValidObject_750) {
    borderArray.setHorizontalCorner(4.5);
    borderArray.setVerticalCorner(6.7);
    auto copied = borderArray.copy();
    ASSERT_NE(copied, nullptr);
}

// Test that setting corners with fractional values works
TEST_F(AnnotBorderArrayTest_750, FractionalValues_750) {
    borderArray.setHorizontalCorner(3.14159);
    borderArray.setVerticalCorner(2.71828);
    EXPECT_DOUBLE_EQ(borderArray.getHorizontalCorner(), 3.14159);
    EXPECT_DOUBLE_EQ(borderArray.getVerticalCorner(), 2.71828);
}
