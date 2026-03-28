#include <gtest/gtest.h>
#include "Annot.h"

class AnnotCalloutLineTest_737 : public ::testing::Test {
protected:
};

TEST_F(AnnotCalloutLineTest_737, ConstructorSetsCoordinates_737) {
    AnnotCalloutLine line(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(line.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(line.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(line.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(line.getY2(), 4.0);
}

TEST_F(AnnotCalloutLineTest_737, ZeroCoordinates_737) {
    AnnotCalloutLine line(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(line.getX1(), 0.0);
    EXPECT_DOUBLE_EQ(line.getY1(), 0.0);
    EXPECT_DOUBLE_EQ(line.getX2(), 0.0);
    EXPECT_DOUBLE_EQ(line.getY2(), 0.0);
}

TEST_F(AnnotCalloutLineTest_737, NegativeCoordinates_737) {
    AnnotCalloutLine line(-5.5, -10.3, -20.1, -0.7);
    EXPECT_DOUBLE_EQ(line.getX1(), -5.5);
    EXPECT_DOUBLE_EQ(line.getY1(), -10.3);
    EXPECT_DOUBLE_EQ(line.getX2(), -20.1);
    EXPECT_DOUBLE_EQ(line.getY2(), -0.7);
}

TEST_F(AnnotCalloutLineTest_737, LargeCoordinates_737) {
    AnnotCalloutLine line(1e15, 1e15, -1e15, -1e15);
    EXPECT_DOUBLE_EQ(line.getX1(), 1e15);
    EXPECT_DOUBLE_EQ(line.getY1(), 1e15);
    EXPECT_DOUBLE_EQ(line.getX2(), -1e15);
    EXPECT_DOUBLE_EQ(line.getY2(), -1e15);
}

TEST_F(AnnotCalloutLineTest_737, SmallCoordinates_737) {
    AnnotCalloutLine line(1e-15, 2e-15, 3e-15, 4e-15);
    EXPECT_DOUBLE_EQ(line.getX1(), 1e-15);
    EXPECT_DOUBLE_EQ(line.getY1(), 2e-15);
    EXPECT_DOUBLE_EQ(line.getX2(), 3e-15);
    EXPECT_DOUBLE_EQ(line.getY2(), 4e-15);
}

TEST_F(AnnotCalloutLineTest_737, MixedPositiveNegativeCoordinates_737) {
    AnnotCalloutLine line(-1.0, 2.0, 3.0, -4.0);
    EXPECT_DOUBLE_EQ(line.getX1(), -1.0);
    EXPECT_DOUBLE_EQ(line.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(line.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(line.getY2(), -4.0);
}

TEST_F(AnnotCalloutLineTest_737, SameStartAndEndPoint_737) {
    AnnotCalloutLine line(5.5, 7.7, 5.5, 7.7);
    EXPECT_DOUBLE_EQ(line.getX1(), 5.5);
    EXPECT_DOUBLE_EQ(line.getY1(), 7.7);
    EXPECT_DOUBLE_EQ(line.getX2(), 5.5);
    EXPECT_DOUBLE_EQ(line.getY2(), 7.7);
}

TEST_F(AnnotCalloutLineTest_737, FractionalCoordinates_737) {
    AnnotCalloutLine line(0.123456789, 0.987654321, 1.111111111, 2.222222222);
    EXPECT_DOUBLE_EQ(line.getX1(), 0.123456789);
    EXPECT_DOUBLE_EQ(line.getY1(), 0.987654321);
    EXPECT_DOUBLE_EQ(line.getX2(), 1.111111111);
    EXPECT_DOUBLE_EQ(line.getY2(), 2.222222222);
}

TEST_F(AnnotCalloutLineTest_737, GettersAreConst_737) {
    const AnnotCalloutLine line(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(line.getX1(), 10.0);
    EXPECT_DOUBLE_EQ(line.getY1(), 20.0);
    EXPECT_DOUBLE_EQ(line.getX2(), 30.0);
    EXPECT_DOUBLE_EQ(line.getY2(), 40.0);
}

// Test AnnotCoord default constructor
TEST_F(AnnotCalloutLineTest_737, AnnotCoordDefaultConstructor_737) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

// Test AnnotCoord parameterized constructor
TEST_F(AnnotCalloutLineTest_737, AnnotCoordParameterizedConstructor_737) {
    AnnotCoord coord(3.14, 2.72);
    EXPECT_DOUBLE_EQ(coord.getX(), 3.14);
    EXPECT_DOUBLE_EQ(coord.getY(), 2.72);
}

TEST_F(AnnotCalloutLineTest_737, AnnotCoordNegativeValues_737) {
    AnnotCoord coord(-100.5, -200.75);
    EXPECT_DOUBLE_EQ(coord.getX(), -100.5);
    EXPECT_DOUBLE_EQ(coord.getY(), -200.75);
}
