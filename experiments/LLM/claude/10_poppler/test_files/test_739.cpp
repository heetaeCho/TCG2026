#include <gtest/gtest.h>
#include "Annot.h"

class AnnotCalloutLineTest_739 : public ::testing::Test {
protected:
};

// Test normal construction and getX2
TEST_F(AnnotCalloutLineTest_739, GetX2ReturnsCorrectValue_739) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(3.0, line.getX2());
}

// Test normal construction and getX1
TEST_F(AnnotCalloutLineTest_739, GetX1ReturnsCorrectValue_739) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(1.0, line.getX1());
}

// Test normal construction and getY1
TEST_F(AnnotCalloutLineTest_739, GetY1ReturnsCorrectValue_739) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(2.0, line.getY1());
}

// Test normal construction and getY2
TEST_F(AnnotCalloutLineTest_739, GetY2ReturnsCorrectValue_739) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(4.0, line.getY2());
}

// Test with zero coordinates
TEST_F(AnnotCalloutLineTest_739, ZeroCoordinates_739) {
    AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, line.getX1());
    EXPECT_DOUBLE_EQ(0.0, line.getY1());
    EXPECT_DOUBLE_EQ(0.0, line.getX2());
    EXPECT_DOUBLE_EQ(0.0, line.getY2());
}

// Test with negative coordinates
TEST_F(AnnotCalloutLineTest_739, NegativeCoordinates_739) {
    AnnotCalloutLine line(-5.5, -10.3, -20.7, -30.9);
    EXPECT_DOUBLE_EQ(-5.5, line.getX1());
    EXPECT_DOUBLE_EQ(-10.3, line.getY1());
    EXPECT_DOUBLE_EQ(-20.7, line.getX2());
    EXPECT_DOUBLE_EQ(-30.9, line.getY2());
}

// Test with large coordinate values
TEST_F(AnnotCalloutLineTest_739, LargeCoordinateValues_739) {
    AnnotCalloutLine line(1e15, 2e15, 3e15, 4e15);
    EXPECT_DOUBLE_EQ(1e15, line.getX1());
    EXPECT_DOUBLE_EQ(2e15, line.getY1());
    EXPECT_DOUBLE_EQ(3e15, line.getX2());
    EXPECT_DOUBLE_EQ(4e15, line.getY2());
}

// Test with very small coordinate values
TEST_F(AnnotCalloutLineTest_739, VerySmallCoordinateValues_739) {
    AnnotCalloutLine line(1e-15, 2e-15, 3e-15, 4e-15);
    EXPECT_DOUBLE_EQ(1e-15, line.getX1());
    EXPECT_DOUBLE_EQ(2e-15, line.getY1());
    EXPECT_DOUBLE_EQ(3e-15, line.getX2());
    EXPECT_DOUBLE_EQ(4e-15, line.getY2());
}

// Test with mixed positive and negative coordinates
TEST_F(AnnotCalloutLineTest_739, MixedPositiveNegativeCoordinates_739) {
    AnnotCalloutLine line(-1.0, 2.0, 3.0, -4.0);
    EXPECT_DOUBLE_EQ(-1.0, line.getX1());
    EXPECT_DOUBLE_EQ(2.0, line.getY1());
    EXPECT_DOUBLE_EQ(3.0, line.getX2());
    EXPECT_DOUBLE_EQ(-4.0, line.getY2());
}

// Test with same coordinates for both points (degenerate line)
TEST_F(AnnotCalloutLineTest_739, DegenerateLine_739) {
    AnnotCalloutLine line(5.5, 7.7, 5.5, 7.7);
    EXPECT_DOUBLE_EQ(5.5, line.getX1());
    EXPECT_DOUBLE_EQ(7.7, line.getY1());
    EXPECT_DOUBLE_EQ(5.5, line.getX2());
    EXPECT_DOUBLE_EQ(7.7, line.getY2());
}

// Test with fractional coordinates
TEST_F(AnnotCalloutLineTest_739, FractionalCoordinates_739) {
    AnnotCalloutLine line(0.1, 0.2, 0.3, 0.4);
    EXPECT_DOUBLE_EQ(0.1, line.getX1());
    EXPECT_DOUBLE_EQ(0.2, line.getY1());
    EXPECT_DOUBLE_EQ(0.3, line.getX2());
    EXPECT_DOUBLE_EQ(0.4, line.getY2());
}

// Test AnnotCoord default constructor
TEST_F(AnnotCalloutLineTest_739, AnnotCoordDefaultConstructor_739) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(0.0, coord.getX());
    EXPECT_DOUBLE_EQ(0.0, coord.getY());
}

// Test AnnotCoord parameterized constructor
TEST_F(AnnotCalloutLineTest_739, AnnotCoordParameterizedConstructor_739) {
    AnnotCoord coord(42.5, -17.3);
    EXPECT_DOUBLE_EQ(42.5, coord.getX());
    EXPECT_DOUBLE_EQ(-17.3, coord.getY());
}

// Test AnnotCoord with zero values
TEST_F(AnnotCalloutLineTest_739, AnnotCoordZeroValues_739) {
    AnnotCoord coord(0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, coord.getX());
    EXPECT_DOUBLE_EQ(0.0, coord.getY());
}

// Test multiple AnnotCalloutLine instances are independent
TEST_F(AnnotCalloutLineTest_739, MultipleInstancesIndependent_739) {
    AnnotCalloutLine line1(1.0, 2.0, 3.0, 4.0);
    AnnotCalloutLine line2(10.0, 20.0, 30.0, 40.0);
    
    EXPECT_DOUBLE_EQ(3.0, line1.getX2());
    EXPECT_DOUBLE_EQ(30.0, line2.getX2());
    EXPECT_DOUBLE_EQ(1.0, line1.getX1());
    EXPECT_DOUBLE_EQ(10.0, line2.getX1());
}
