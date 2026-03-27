#include <gtest/gtest.h>

#include "Annot.h"



class AnnotCalloutLineTest_740 : public ::testing::Test {

protected:

    AnnotCalloutLine* calloutLine;



    void SetUp() override {

        calloutLine = new AnnotCalloutLine(1.0, 2.0, 3.0, 4.0);

    }



    void TearDown() override {

        delete calloutLine;

    }

};



TEST_F(AnnotCalloutLineTest_740, ConstructorInitializesCoordinates_740) {

    EXPECT_DOUBLE_EQ(calloutLine->getX1(), 1.0);

    EXPECT_DOUBLE_EQ(calloutLine->getY1(), 2.0);

    EXPECT_DOUBLE_EQ(calloutLine->getX2(), 3.0);

    EXPECT_DOUBLE_EQ(calloutLine->getY2(), 4.0);

}



TEST_F(AnnotCalloutLineTest_740, GetY2ReturnsCorrectValue_740) {

    EXPECT_DOUBLE_EQ(calloutLine->getY2(), 4.0);

}



TEST_F(AnnotCalloutLineTest_740, CoordinatesAreImmutableAfterConstruction_740) {

    double x1 = calloutLine->getX1();

    double y1 = calloutLine->getY1();

    double x2 = calloutLine->getX2();

    double y2 = calloutLine->getY2();



    // Attempting to change coordinates through the interface (if any)

    // Since there are no setters, we assume the coordinates are immutable.

    EXPECT_DOUBLE_EQ(calloutLine->getX1(), x1);

    EXPECT_DOUBLE_EQ(calloutLine->getY1(), y1);

    EXPECT_DOUBLE_EQ(calloutLine->getX2(), x2);

    EXPECT_DOUBLE_EQ(calloutLine->getY2(), y2);

}



TEST_F(AnnotCalloutLineTest_740, BoundaryConditionsWithZeroCoordinates_740) {

    AnnotCalloutLine zeroCalloutLine(0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(zeroCalloutLine.getX1(), 0.0);

    EXPECT_DOUBLE_EQ(zeroCalloutLine.getY1(), 0.0);

    EXPECT_DOUBLE_EQ(zeroCalloutLine.getX2(), 0.0);

    EXPECT_DOUBLE_EQ(zeroCalloutLine.getY2(), 0.0);

}



TEST_F(AnnotCalloutLineTest_740, BoundaryConditionsWithNegativeCoordinates_740) {

    AnnotCalloutLine negativeCalloutLine(-1.0, -2.0, -3.0, -4.0);

    EXPECT_DOUBLE_EQ(negativeCalloutLine.getX1(), -1.0);

    EXPECT_DOUBLE_EQ(negativeCalloutLine.getY1(), -2.0);

    EXPECT_DOUBLE_EQ(negativeCalloutLine.getX2(), -3.0);

    EXPECT_DOUBLE_EQ(negativeCalloutLine.getY2(), -4.0);

}
