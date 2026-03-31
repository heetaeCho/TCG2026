#include <gtest/gtest.h>
#include "Annot.h"

class AnnotCalloutLineTest_738 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal construction and getY1
TEST_F(AnnotCalloutLineTest_738, GetY1ReturnsCorrectValue_738) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(2.0, line.getY1());
}

// Test normal construction and getX1
TEST_F(AnnotCalloutLineTest_738, GetX1ReturnsCorrectValue_738) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(1.0, line.getX1());
}

// Test normal construction and getX2
TEST_F(AnnotCalloutLineTest_738, GetX2ReturnsCorrectValue_738) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(3.0, line.getX2());
}

// Test normal construction and getY2
TEST_F(AnnotCalloutLineTest_738, GetY2ReturnsCorrectValue_738) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(4.0, line.getY2());
}

// Test with zero coordinates
TEST_F(AnnotCalloutLineTest_738, ZeroCoordinates_738) {
    AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, line.getX1());
    EXPECT_DOUBLE_EQ(0.0, line.getY1());
    EXPECT_DOUBLE_EQ(0.0, line.getX2());
    EXPECT_DOUBLE_EQ(0.0, line.getY2());
}

// Test with negative coordinates
TEST_F(AnnotCalloutLineTest_738, NegativeCoordinates_738) {
    AnnotCalloutLine line(-5.5, -10.3, -20.1, -30.7);
    EXPECT_DOUBLE_EQ(-5.5, line.getX1());
    EXPECT_DOUBLE_EQ(-10.3, line.getY1());
    EXPECT_DOUBLE_EQ(-20.1, line.getX2());
    EXPECT_DOUBLE_EQ(-30.7, line.getY2());
}

// Test with very large coordinates
TEST_F(AnnotCalloutLineTest_738, LargeCoordinates_738) {
    double large = 1e15;
    AnnotCalloutLine line(large, large + 1.0, large + 2.0, large + 3.0);
    EXPECT_DOUBLE_EQ(large, line.getX1());
    EXPECT_DOUBLE_EQ(large + 1.0, line.getY1());
    EXPECT_DOUBLE_EQ(large + 2.0, line.getX2());
    EXPECT_DOUBLE_EQ(large + 3.0, line.getY2());
}

// Test with very small (near-zero) coordinates
TEST_F(AnnotCalloutLineTest_738, VerySmallCoordinates_738) {
    double small = 1e-15;
    AnnotCalloutLine line(small, small * 2, small * 3, small * 4);
    EXPECT_DOUBLE_EQ(small, line.getX1());
    EXPECT_DOUBLE_EQ(small * 2, line.getY1());
    EXPECT_DOUBLE_EQ(small * 3, line.getX2());
    EXPECT_DOUBLE_EQ(small * 4, line.getY2());
}

// Test with mixed positive and negative coordinates
TEST_F(AnnotCalloutLineTest_738, MixedPositiveNegativeCoordinates_738) {
    AnnotCalloutLine line(-100.5, 200.3, 300.7, -400.9);
    EXPECT_DOUBLE_EQ(-100.5, line.getX1());
    EXPECT_DOUBLE_EQ(200.3, line.getY1());
    EXPECT_DOUBLE_EQ(300.7, line.getX2());
    EXPECT_DOUBLE_EQ(-400.9, line.getY2());
}

// Test that coord1 and coord2 are independent
TEST_F(AnnotCalloutLineTest_738, CoordinatesAreIndependent_738) {
    AnnotCalloutLine line(1.0, 2.0, 1.0, 2.0);
    EXPECT_DOUBLE_EQ(line.getX1(), line.getX2());
    EXPECT_DOUBLE_EQ(line.getY1(), line.getY2());
}

// Test with same x different y
TEST_F(AnnotCalloutLineTest_738, SameXDifferentY_738) {
    AnnotCalloutLine line(5.0, 10.0, 5.0, 20.0);
    EXPECT_DOUBLE_EQ(5.0, line.getX1());
    EXPECT_DOUBLE_EQ(10.0, line.getY1());
    EXPECT_DOUBLE_EQ(5.0, line.getX2());
    EXPECT_DOUBLE_EQ(20.0, line.getY2());
}

// Test multiple instances are independent
TEST_F(AnnotCalloutLineTest_738, MultipleInstancesIndependent_738) {
    AnnotCalloutLine line1(1.0, 2.0, 3.0, 4.0);
    AnnotCalloutLine line2(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(1.0, line1.getX1());
    EXPECT_DOUBLE_EQ(2.0, line1.getY1());
    EXPECT_DOUBLE_EQ(10.0, line2.getX1());
    EXPECT_DOUBLE_EQ(20.0, line2.getY1());
}

// Test AnnotCoord default constructor
class AnnotCoordTest_738 : public ::testing::Test {};

TEST_F(AnnotCoordTest_738, DefaultConstructorZeroes_738) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(0.0, coord.getX());
    EXPECT_DOUBLE_EQ(0.0, coord.getY());
}

TEST_F(AnnotCoordTest_738, ParameterizedConstructor_738) {
    AnnotCoord coord(3.14, 2.71);
    EXPECT_DOUBLE_EQ(3.14, coord.getX());
    EXPECT_DOUBLE_EQ(2.71, coord.getY());
}

TEST_F(AnnotCoordTest_738, NegativeValues_738) {
    AnnotCoord coord(-1.5, -2.5);
    EXPECT_DOUBLE_EQ(-1.5, coord.getX());
    EXPECT_DOUBLE_EQ(-2.5, coord.getY());
}
