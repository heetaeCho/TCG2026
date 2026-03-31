#include <gtest/gtest.h>
#include "Annot.h"

class AnnotBorderArrayTest_751 : public ::testing::Test {
protected:
    AnnotBorderArray borderArray;
};

// Test default construction and initial vertical corner value
TEST_F(AnnotBorderArrayTest_751, DefaultConstructor_751) {
    // After default construction, getVerticalCorner should return a defined value (likely 0)
    double vc = borderArray.getVerticalCorner();
    EXPECT_DOUBLE_EQ(0.0, vc);
}

// Test default construction and initial horizontal corner value
TEST_F(AnnotBorderArrayTest_751, DefaultHorizontalCorner_751) {
    double hc = borderArray.getHorizontalCorner();
    EXPECT_DOUBLE_EQ(0.0, hc);
}

// Test setVerticalCorner with a positive value
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerPositive_751) {
    borderArray.setVerticalCorner(5.5);
    EXPECT_DOUBLE_EQ(5.5, borderArray.getVerticalCorner());
}

// Test setVerticalCorner with zero
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerZero_751) {
    borderArray.setVerticalCorner(0.0);
    EXPECT_DOUBLE_EQ(0.0, borderArray.getVerticalCorner());
}

// Test setVerticalCorner with a negative value
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerNegative_751) {
    borderArray.setVerticalCorner(-3.14);
    EXPECT_DOUBLE_EQ(-3.14, borderArray.getVerticalCorner());
}

// Test setVerticalCorner with a very large value
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerLargeValue_751) {
    borderArray.setVerticalCorner(1e15);
    EXPECT_DOUBLE_EQ(1e15, borderArray.getVerticalCorner());
}

// Test setVerticalCorner with a very small positive value
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerSmallPositive_751) {
    borderArray.setVerticalCorner(1e-15);
    EXPECT_DOUBLE_EQ(1e-15, borderArray.getVerticalCorner());
}

// Test setHorizontalCorner with a positive value
TEST_F(AnnotBorderArrayTest_751, SetHorizontalCornerPositive_751) {
    borderArray.setHorizontalCorner(7.25);
    EXPECT_DOUBLE_EQ(7.25, borderArray.getHorizontalCorner());
}

// Test setHorizontalCorner with zero
TEST_F(AnnotBorderArrayTest_751, SetHorizontalCornerZero_751) {
    borderArray.setHorizontalCorner(0.0);
    EXPECT_DOUBLE_EQ(0.0, borderArray.getHorizontalCorner());
}

// Test setHorizontalCorner with a negative value
TEST_F(AnnotBorderArrayTest_751, SetHorizontalCornerNegative_751) {
    borderArray.setHorizontalCorner(-2.71);
    EXPECT_DOUBLE_EQ(-2.71, borderArray.getHorizontalCorner());
}

// Test setting both corners independently
TEST_F(AnnotBorderArrayTest_751, SetBothCornersIndependently_751) {
    borderArray.setHorizontalCorner(10.0);
    borderArray.setVerticalCorner(20.0);
    EXPECT_DOUBLE_EQ(10.0, borderArray.getHorizontalCorner());
    EXPECT_DOUBLE_EQ(20.0, borderArray.getVerticalCorner());
}

// Test that setting vertical corner does not affect horizontal corner
TEST_F(AnnotBorderArrayTest_751, SetVerticalDoesNotAffectHorizontal_751) {
    borderArray.setHorizontalCorner(42.0);
    borderArray.setVerticalCorner(99.0);
    EXPECT_DOUBLE_EQ(42.0, borderArray.getHorizontalCorner());
}

// Test that setting horizontal corner does not affect vertical corner
TEST_F(AnnotBorderArrayTest_751, SetHorizontalDoesNotAffectVertical_751) {
    borderArray.setVerticalCorner(42.0);
    borderArray.setHorizontalCorner(99.0);
    EXPECT_DOUBLE_EQ(42.0, borderArray.getVerticalCorner());
}

// Test overwriting vertical corner multiple times
TEST_F(AnnotBorderArrayTest_751, OverwriteVerticalCorner_751) {
    borderArray.setVerticalCorner(1.0);
    EXPECT_DOUBLE_EQ(1.0, borderArray.getVerticalCorner());
    borderArray.setVerticalCorner(2.0);
    EXPECT_DOUBLE_EQ(2.0, borderArray.getVerticalCorner());
    borderArray.setVerticalCorner(3.0);
    EXPECT_DOUBLE_EQ(3.0, borderArray.getVerticalCorner());
}

// Test overwriting horizontal corner multiple times
TEST_F(AnnotBorderArrayTest_751, OverwriteHorizontalCorner_751) {
    borderArray.setHorizontalCorner(1.0);
    EXPECT_DOUBLE_EQ(1.0, borderArray.getHorizontalCorner());
    borderArray.setHorizontalCorner(2.0);
    EXPECT_DOUBLE_EQ(2.0, borderArray.getHorizontalCorner());
    borderArray.setHorizontalCorner(3.0);
    EXPECT_DOUBLE_EQ(3.0, borderArray.getHorizontalCorner());
}

// Test copy method preserves vertical corner
TEST_F(AnnotBorderArrayTest_751, CopyPreservesVerticalCorner_751) {
    borderArray.setVerticalCorner(12.34);
    borderArray.setHorizontalCorner(56.78);
    auto copied = borderArray.copy();
    ASSERT_NE(copied, nullptr);
    // The copy should be a valid AnnotBorder; we can dynamic_cast to check
    AnnotBorderArray* copiedArray = dynamic_cast<AnnotBorderArray*>(copied.get());
    if (copiedArray) {
        EXPECT_DOUBLE_EQ(12.34, copiedArray->getVerticalCorner());
        EXPECT_DOUBLE_EQ(56.78, copiedArray->getHorizontalCorner());
    }
}

// Test with max double value
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerMaxDouble_751) {
    double maxVal = std::numeric_limits<double>::max();
    borderArray.setVerticalCorner(maxVal);
    EXPECT_DOUBLE_EQ(maxVal, borderArray.getVerticalCorner());
}

// Test with lowest double value
TEST_F(AnnotBorderArrayTest_751, SetVerticalCornerLowestDouble_751) {
    double lowestVal = std::numeric_limits<double>::lowest();
    borderArray.setVerticalCorner(lowestVal);
    EXPECT_DOUBLE_EQ(lowestVal, borderArray.getVerticalCorner());
}
