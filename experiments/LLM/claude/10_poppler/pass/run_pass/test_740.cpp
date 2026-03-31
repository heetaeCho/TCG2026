#include <gtest/gtest.h>
#include "Annot.h"

class AnnotCalloutLineTest_740 : public ::testing::Test {
protected:
};

// Test normal construction and getY2
TEST_F(AnnotCalloutLineTest_740, GetY2ReturnsCorrectValue_740) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(4.0, line.getY2());
}

// Test getX1 returns correct value
TEST_F(AnnotCalloutLineTest_740, GetX1ReturnsCorrectValue_740) {
    AnnotCalloutLine line(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(10.0, line.getX1());
}

// Test getY1 returns correct value
TEST_F(AnnotCalloutLineTest_740, GetY1ReturnsCorrectValue_740) {
    AnnotCalloutLine line(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(20.0, line.getY1());
}

// Test getX2 returns correct value
TEST_F(AnnotCalloutLineTest_740, GetX2ReturnsCorrectValue_740) {
    AnnotCalloutLine line(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(30.0, line.getX2());
}

// Test all getters together
TEST_F(AnnotCalloutLineTest_740, AllGettersReturnCorrectValues_740) {
    AnnotCalloutLine line(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(1.5, line.getX1());
    EXPECT_DOUBLE_EQ(2.5, line.getY1());
    EXPECT_DOUBLE_EQ(3.5, line.getX2());
    EXPECT_DOUBLE_EQ(4.5, line.getY2());
}

// Test with zero values
TEST_F(AnnotCalloutLineTest_740, ZeroCoordinates_740) {
    AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, line.getX1());
    EXPECT_DOUBLE_EQ(0.0, line.getY1());
    EXPECT_DOUBLE_EQ(0.0, line.getX2());
    EXPECT_DOUBLE_EQ(0.0, line.getY2());
}

// Test with negative values
TEST_F(AnnotCalloutLineTest_740, NegativeCoordinates_740) {
    AnnotCalloutLine line(-1.0, -2.0, -3.0, -4.0);
    EXPECT_DOUBLE_EQ(-1.0, line.getX1());
    EXPECT_DOUBLE_EQ(-2.0, line.getY1());
    EXPECT_DOUBLE_EQ(-3.0, line.getX2());
    EXPECT_DOUBLE_EQ(-4.0, line.getY2());
}

// Test with very large values
TEST_F(AnnotCalloutLineTest_740, LargeCoordinates_740) {
    AnnotCalloutLine line(1e15, 2e15, 3e15, 4e15);
    EXPECT_DOUBLE_EQ(1e15, line.getX1());
    EXPECT_DOUBLE_EQ(2e15, line.getY1());
    EXPECT_DOUBLE_EQ(3e15, line.getX2());
    EXPECT_DOUBLE_EQ(4e15, line.getY2());
}

// Test with very small (near-zero) values
TEST_F(AnnotCalloutLineTest_740, VerySmallCoordinates_740) {
    AnnotCalloutLine line(1e-15, 2e-15, 3e-15, 4e-15);
    EXPECT_DOUBLE_EQ(1e-15, line.getX1());
    EXPECT_DOUBLE_EQ(2e-15, line.getY1());
    EXPECT_DOUBLE_EQ(3e-15, line.getX2());
    EXPECT_DOUBLE_EQ(4e-15, line.getY2());
}

// Test with mixed positive and negative values
TEST_F(AnnotCalloutLineTest_740, MixedSignCoordinates_740) {
    AnnotCalloutLine line(-5.5, 10.3, 7.7, -8.8);
    EXPECT_DOUBLE_EQ(-5.5, line.getX1());
    EXPECT_DOUBLE_EQ(10.3, line.getY1());
    EXPECT_DOUBLE_EQ(7.7, line.getX2());
    EXPECT_DOUBLE_EQ(-8.8, line.getY2());
}

// Test same coordinates for both points (degenerate line)
TEST_F(AnnotCalloutLineTest_740, DegenerateLine_740) {
    AnnotCalloutLine line(5.0, 5.0, 5.0, 5.0);
    EXPECT_DOUBLE_EQ(5.0, line.getX1());
    EXPECT_DOUBLE_EQ(5.0, line.getY1());
    EXPECT_DOUBLE_EQ(5.0, line.getX2());
    EXPECT_DOUBLE_EQ(5.0, line.getY2());
}

// Test with fractional precision values
TEST_F(AnnotCalloutLineTest_740, FractionalPrecisionValues_740) {
    AnnotCalloutLine line(1.123456789, 2.987654321, 3.111111111, 4.999999999);
    EXPECT_DOUBLE_EQ(1.123456789, line.getX1());
    EXPECT_DOUBLE_EQ(2.987654321, line.getY1());
    EXPECT_DOUBLE_EQ(3.111111111, line.getX2());
    EXPECT_DOUBLE_EQ(4.999999999, line.getY2());
}

// Test AnnotCoord default constructor
TEST_F(AnnotCalloutLineTest_740, AnnotCoordDefaultConstructor_740) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(0.0, coord.getX());
    EXPECT_DOUBLE_EQ(0.0, coord.getY());
}

// Test AnnotCoord parameterized constructor
TEST_F(AnnotCalloutLineTest_740, AnnotCoordParameterizedConstructor_740) {
    AnnotCoord coord(3.14, 2.72);
    EXPECT_DOUBLE_EQ(3.14, coord.getX());
    EXPECT_DOUBLE_EQ(2.72, coord.getY());
}

// Test AnnotCoord with negative values
TEST_F(AnnotCalloutLineTest_740, AnnotCoordNegativeValues_740) {
    AnnotCoord coord(-100.5, -200.5);
    EXPECT_DOUBLE_EQ(-100.5, coord.getX());
    EXPECT_DOUBLE_EQ(-200.5, coord.getY());
}
