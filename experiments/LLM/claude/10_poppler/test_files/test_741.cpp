#include <gtest/gtest.h>
#include "Annot.h"

class AnnotCalloutMultiLineTest_741 : public ::testing::Test {
protected:
};

TEST_F(AnnotCalloutMultiLineTest_741, GetX3ReturnsCorrectValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(5.0, line.getX3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetY3ReturnsCorrectValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(6.0, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3WithZeroValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 0.0, 6.0);
    EXPECT_DOUBLE_EQ(0.0, line.getX3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetY3WithZeroValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3WithNegativeValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, -10.5, 6.0);
    EXPECT_DOUBLE_EQ(-10.5, line.getX3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetY3WithNegativeValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, -20.3);
    EXPECT_DOUBLE_EQ(-20.3, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3WithLargeValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 1e15, 6.0);
    EXPECT_DOUBLE_EQ(1e15, line.getX3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetY3WithLargeValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 1e15);
    EXPECT_DOUBLE_EQ(1e15, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetX3WithVerySmallValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 1e-15, 6.0);
    EXPECT_DOUBLE_EQ(1e-15, line.getX3());
}

TEST_F(AnnotCalloutMultiLineTest_741, GetY3WithVerySmallValue_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 1e-15);
    EXPECT_DOUBLE_EQ(1e-15, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, AllCoordinatesZero_741) {
    AnnotCalloutMultiLine line(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, line.getX3());
    EXPECT_DOUBLE_EQ(0.0, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, AllCoordinatesSameValue_741) {
    AnnotCalloutMultiLine line(7.7, 7.7, 7.7, 7.7, 7.7, 7.7);
    EXPECT_DOUBLE_EQ(7.7, line.getX3());
    EXPECT_DOUBLE_EQ(7.7, line.getY3());
}

TEST_F(AnnotCalloutMultiLineTest_741, InheritsFromAnnotCalloutLine_741) {
    AnnotCalloutMultiLine line(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    AnnotCalloutLine* basePtr = &line;
    // Verify base class methods still accessible
    EXPECT_DOUBLE_EQ(1.0, basePtr->getX1());
    EXPECT_DOUBLE_EQ(2.0, basePtr->getY1());
    EXPECT_DOUBLE_EQ(3.0, basePtr->getX2());
    EXPECT_DOUBLE_EQ(4.0, basePtr->getY2());
}

TEST_F(AnnotCalloutMultiLineTest_741, Coord3IndependentOfCoord1And2_741) {
    AnnotCalloutMultiLine line(100.0, 200.0, 300.0, 400.0, 500.0, 600.0);
    EXPECT_DOUBLE_EQ(500.0, line.getX3());
    EXPECT_DOUBLE_EQ(600.0, line.getY3());
    // Also verify coord1 and coord2 are independent
    EXPECT_DOUBLE_EQ(100.0, line.getX1());
    EXPECT_DOUBLE_EQ(200.0, line.getY1());
    EXPECT_DOUBLE_EQ(300.0, line.getX2());
    EXPECT_DOUBLE_EQ(400.0, line.getY2());
}
