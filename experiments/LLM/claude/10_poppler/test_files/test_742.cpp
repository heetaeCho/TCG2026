#include <gtest/gtest.h>
#include "Annot.h"

class AnnotCalloutMultiLineTest_742 : public ::testing::Test {
protected:
};

TEST_F(AnnotCalloutMultiLineTest_742, GetY3ReturnsCorrectValue_742) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(6.0, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, GetX3ReturnsCorrectValue_742) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(5.0, line.getX3());
}

TEST_F(AnnotCalloutMultiLineTest_742, ZeroCoordinates_742) {
    AnnotCalloutMultiLine line(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, line.getX3());
    EXPECT_DOUBLE_EQ(0.0, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, NegativeCoordinates_742) {
    AnnotCalloutMultiLine line(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);
    EXPECT_DOUBLE_EQ(-5.0, line.getX3());
    EXPECT_DOUBLE_EQ(-6.0, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, LargeCoordinates_742) {
    AnnotCalloutMultiLine line(1e10, 2e10, 3e10, 4e10, 5e10, 6e10);
    EXPECT_DOUBLE_EQ(5e10, line.getX3());
    EXPECT_DOUBLE_EQ(6e10, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, VerySmallCoordinates_742) {
    AnnotCalloutMultiLine line(1e-15, 2e-15, 3e-15, 4e-15, 5e-15, 6e-15);
    EXPECT_DOUBLE_EQ(5e-15, line.getX3());
    EXPECT_DOUBLE_EQ(6e-15, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, MixedSignCoordinates_742) {
    AnnotCalloutMultiLine line(-1.5, 2.5, -3.5, 4.5, -5.5, 6.5);
    EXPECT_DOUBLE_EQ(-5.5, line.getX3());
    EXPECT_DOUBLE_EQ(6.5, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, Coord3IndependentOfCoord1And2_742) {
    AnnotCalloutMultiLine line1(0.0, 0.0, 0.0, 0.0, 7.7, 8.8);
    AnnotCalloutMultiLine line2(100.0, 200.0, 300.0, 400.0, 7.7, 8.8);
    EXPECT_DOUBLE_EQ(line1.getX3(), line2.getX3());
    EXPECT_DOUBLE_EQ(line1.getY3(), line2.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, FractionalCoordinates_742) {
    AnnotCalloutMultiLine line(0.1, 0.2, 0.3, 0.4, 0.123456789, 0.987654321);
    EXPECT_DOUBLE_EQ(0.123456789, line.getX3());
    EXPECT_DOUBLE_EQ(0.987654321, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, MaxDoubleCoordinates_742) {
    double maxVal = std::numeric_limits<double>::max();
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, maxVal, maxVal);
    EXPECT_DOUBLE_EQ(maxVal, line.getX3());
    EXPECT_DOUBLE_EQ(maxVal, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_742, MinDoubleCoordinates_742) {
    double minVal = std::numeric_limits<double>::lowest();
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, minVal, minVal);
    EXPECT_DOUBLE_EQ(minVal, line.getX3());
    EXPECT_DOUBLE_EQ(minVal, line.getY3());
}
