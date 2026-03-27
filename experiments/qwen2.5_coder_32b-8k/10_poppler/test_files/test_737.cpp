#include <gtest/gtest.h>

#include "Annot.h"



class AnnotCalloutLineTest_737 : public ::testing::Test {

protected:

    AnnotCalloutLine* calloutLine;



    void SetUp() override {

        calloutLine = new AnnotCalloutLine(1.0, 2.0, 3.0, 4.0);

    }



    void TearDown() override {

        delete calloutLine;

    }

};



TEST_F(AnnotCalloutLineTest_737, GetX1_ReturnsCorrectValue_737) {

    EXPECT_EQ(calloutLine->getX1(), 1.0);

}



TEST_F(AnnotCalloutLineTest_737, GetY1_ReturnsCorrectValue_737) {

    EXPECT_EQ(calloutLine->getY1(), 2.0);

}



TEST_F(AnnotCalloutLineTest_737, BoundaryCondition_GetX1_Zero_737) {

    AnnotCalloutLine zeroLine(0.0, 0.0, 0.0, 0.0);

    EXPECT_EQ(zeroLine.getX1(), 0.0);

}



TEST_F(AnnotCalloutLineTest_737, BoundaryCondition_GetY1_Zero_737) {

    AnnotCalloutLine zeroLine(0.0, 0.0, 0.0, 0.0);

    EXPECT_EQ(zeroLine.getY1(), 0.0);

}



TEST_F(AnnotCalloutLineTest_737, BoundaryCondition_GetX1_Negative_737) {

    AnnotCalloutLine negativeLine(-1.0, -2.0, -3.0, -4.0);

    EXPECT_EQ(negativeLine.getX1(), -1.0);

}



TEST_F(AnnotCalloutLineTest_737, BoundaryCondition_GetY1_Negative_737) {

    AnnotCalloutLine negativeLine(-1.0, -2.0, -3.0, -4.0);

    EXPECT_EQ(negativeLine.getY1(), -2.0);

}
