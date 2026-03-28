#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



class AnnotCalloutMultiLineTest_742 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotCalloutMultiLine> callout;



    void SetUp() override {

        callout = std::make_unique<AnnotCalloutMultiLine>(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);

    }

};



TEST_F(AnnotCalloutMultiLineTest_742, GetY3_ReturnsCorrectValue_742) {

    EXPECT_DOUBLE_EQ(callout->getY3(), 6.0);

}



TEST_F(AnnotCalloutMultiLineTest_742, GetX3_ReturnsCorrectValue_742) {

    EXPECT_DOUBLE_EQ(callout->getX3(), 5.0);

}



TEST_F(AnnotCalloutMultiLineTest_742, BoundaryCondition_ZeroCoordinates_742) {

    AnnotCalloutMultiLine zeroCallout(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(zeroCallout.getX3(), 0.0);

    EXPECT_DOUBLE_EQ(zeroCallout.getY3(), 0.0);

}



TEST_F(AnnotCalloutMultiLineTest_742, BoundaryCondition_NegativeCoordinates_742) {

    AnnotCalloutMultiLine negativeCallout(-1.5, -2.5, -3.5, -4.5, -5.5, -6.5);

    EXPECT_DOUBLE_EQ(negativeCallout.getX3(), -5.5);

    EXPECT_DOUBLE_EQ(negativeCallout.getY3(), -6.5);

}
