#include <gtest/gtest.h>
#include "Annot.h"

// Test default constructor initializes x to 0
TEST(AnnotCoordTest_734, DefaultConstructorGetX_734) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
}

// Test default constructor initializes y to 0
TEST(AnnotCoordTest_734, DefaultConstructorGetY_734) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

// Test parameterized constructor with positive values
TEST(AnnotCoordTest_734, ParameterizedConstructorPositiveValues_734) {
    AnnotCoord coord(3.5, 7.2);
    EXPECT_DOUBLE_EQ(coord.getX(), 3.5);
    EXPECT_DOUBLE_EQ(coord.getY(), 7.2);
}

// Test parameterized constructor with negative values
TEST(AnnotCoordTest_734, ParameterizedConstructorNegativeValues_734) {
    AnnotCoord coord(-1.5, -9.8);
    EXPECT_DOUBLE_EQ(coord.getX(), -1.5);
    EXPECT_DOUBLE_EQ(coord.getY(), -9.8);
}

// Test parameterized constructor with zero values
TEST(AnnotCoordTest_734, ParameterizedConstructorZeroValues_734) {
    AnnotCoord coord(0.0, 0.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

// Test parameterized constructor with mixed positive and negative
TEST(AnnotCoordTest_734, ParameterizedConstructorMixedValues_734) {
    AnnotCoord coord(-4.3, 12.7);
    EXPECT_DOUBLE_EQ(coord.getX(), -4.3);
    EXPECT_DOUBLE_EQ(coord.getY(), 12.7);
}

// Test with very large values
TEST(AnnotCoordTest_734, LargeValues_734) {
    AnnotCoord coord(1e15, 1e15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e15);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e15);
}

// Test with very small values
TEST(AnnotCoordTest_734, VerySmallValues_734) {
    AnnotCoord coord(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e-15);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e-15);
}

// Test with very large negative values
TEST(AnnotCoordTest_734, LargeNegativeValues_734) {
    AnnotCoord coord(-1e15, -1e15);
    EXPECT_DOUBLE_EQ(coord.getX(), -1e15);
    EXPECT_DOUBLE_EQ(coord.getY(), -1e15);
}

// Test that getX and getY return independent values
TEST(AnnotCoordTest_734, IndependentXandY_734) {
    AnnotCoord coord(42.0, 99.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 42.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 99.0);
    EXPECT_NE(coord.getX(), coord.getY());
}

// Test multiple instances are independent
TEST(AnnotCoordTest_734, MultipleInstancesIndependent_734) {
    AnnotCoord coord1(1.0, 2.0);
    AnnotCoord coord2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(coord1.getX(), 1.0);
    EXPECT_DOUBLE_EQ(coord1.getY(), 2.0);
    EXPECT_DOUBLE_EQ(coord2.getX(), 3.0);
    EXPECT_DOUBLE_EQ(coord2.getY(), 4.0);
}

// Test copy semantics (copy constructor if available)
TEST(AnnotCoordTest_734, CopyConstructor_734) {
    AnnotCoord coord1(5.5, 6.6);
    AnnotCoord coord2(coord1);
    EXPECT_DOUBLE_EQ(coord2.getX(), 5.5);
    EXPECT_DOUBLE_EQ(coord2.getY(), 6.6);
}

// Test copy assignment if available
TEST(AnnotCoordTest_734, CopyAssignment_734) {
    AnnotCoord coord1(7.7, 8.8);
    AnnotCoord coord2;
    coord2 = coord1;
    EXPECT_DOUBLE_EQ(coord2.getX(), 7.7);
    EXPECT_DOUBLE_EQ(coord2.getY(), 8.8);
}

// Test with max double values
TEST(AnnotCoordTest_734, MaxDoubleValues_734) {
    double maxVal = std::numeric_limits<double>::max();
    AnnotCoord coord(maxVal, maxVal);
    EXPECT_DOUBLE_EQ(coord.getX(), maxVal);
    EXPECT_DOUBLE_EQ(coord.getY(), maxVal);
}

// Test with min (smallest positive) double values
TEST(AnnotCoordTest_734, MinPositiveDoubleValues_734) {
    double minVal = std::numeric_limits<double>::min();
    AnnotCoord coord(minVal, minVal);
    EXPECT_DOUBLE_EQ(coord.getX(), minVal);
    EXPECT_DOUBLE_EQ(coord.getY(), minVal);
}

// Test with lowest (most negative) double values
TEST(AnnotCoordTest_734, LowestDoubleValues_734) {
    double lowestVal = std::numeric_limits<double>::lowest();
    AnnotCoord coord(lowestVal, lowestVal);
    EXPECT_DOUBLE_EQ(coord.getX(), lowestVal);
    EXPECT_DOUBLE_EQ(coord.getY(), lowestVal);
}
