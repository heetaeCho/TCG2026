#include <gtest/gtest.h>
#include "Annot.h"

// Test default constructor sets y to 0
TEST(AnnotCoordTest_735, DefaultConstructorYIsZero_735) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

// Test default constructor sets x to 0
TEST(AnnotCoordTest_735, DefaultConstructorXIsZero_735) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
}

// Test parameterized constructor sets x and y correctly
TEST(AnnotCoordTest_735, ParameterizedConstructorSetsValues_735) {
    AnnotCoord coord(3.5, 7.2);
    EXPECT_DOUBLE_EQ(coord.getX(), 3.5);
    EXPECT_DOUBLE_EQ(coord.getY(), 7.2);
}

// Test with positive values
TEST(AnnotCoordTest_735, PositiveValues_735) {
    AnnotCoord coord(100.0, 200.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 100.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 200.0);
}

// Test with negative values
TEST(AnnotCoordTest_735, NegativeValues_735) {
    AnnotCoord coord(-5.5, -10.3);
    EXPECT_DOUBLE_EQ(coord.getX(), -5.5);
    EXPECT_DOUBLE_EQ(coord.getY(), -10.3);
}

// Test with zero values explicitly
TEST(AnnotCoordTest_735, ZeroValues_735) {
    AnnotCoord coord(0.0, 0.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

// Test with very large values
TEST(AnnotCoordTest_735, VeryLargeValues_735) {
    AnnotCoord coord(1e15, 1e15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e15);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e15);
}

// Test with very small values
TEST(AnnotCoordTest_735, VerySmallValues_735) {
    AnnotCoord coord(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e-15);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e-15);
}

// Test with mixed positive and negative
TEST(AnnotCoordTest_735, MixedPositiveNegative_735) {
    AnnotCoord coord(-3.14, 2.71);
    EXPECT_DOUBLE_EQ(coord.getX(), -3.14);
    EXPECT_DOUBLE_EQ(coord.getY(), 2.71);
}

// Test that getX and getY are consistent across multiple calls
TEST(AnnotCoordTest_735, ConsistentReturnValues_735) {
    AnnotCoord coord(42.0, 84.0);
    EXPECT_DOUBLE_EQ(coord.getX(), coord.getX());
    EXPECT_DOUBLE_EQ(coord.getY(), coord.getY());
    EXPECT_DOUBLE_EQ(coord.getX(), 42.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 84.0);
}

// Test with maximum double value
TEST(AnnotCoordTest_735, MaxDoubleValues_735) {
    double maxVal = std::numeric_limits<double>::max();
    AnnotCoord coord(maxVal, maxVal);
    EXPECT_DOUBLE_EQ(coord.getX(), maxVal);
    EXPECT_DOUBLE_EQ(coord.getY(), maxVal);
}

// Test with minimum (smallest positive) double value
TEST(AnnotCoordTest_735, MinDoubleValues_735) {
    double minVal = std::numeric_limits<double>::min();
    AnnotCoord coord(minVal, minVal);
    EXPECT_DOUBLE_EQ(coord.getX(), minVal);
    EXPECT_DOUBLE_EQ(coord.getY(), minVal);
}

// Test with negative max double value
TEST(AnnotCoordTest_735, NegativeMaxDoubleValues_735) {
    double negMax = -std::numeric_limits<double>::max();
    AnnotCoord coord(negMax, negMax);
    EXPECT_DOUBLE_EQ(coord.getX(), negMax);
    EXPECT_DOUBLE_EQ(coord.getY(), negMax);
}
