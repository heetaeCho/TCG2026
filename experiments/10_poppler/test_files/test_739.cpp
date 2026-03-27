#include <gtest/gtest.h>

#include "Annot.h"



class AnnotCalloutLineTest : public ::testing::Test {

protected:

    AnnotCalloutLine* calloutLine;



    void SetUp() override {

        calloutLine = new AnnotCalloutLine(1.0, 2.0, 3.0, 4.0);

    }



    void TearDown() override {

        delete calloutLine;

    }

};



TEST_F(AnnotCalloutLineTest_739, GetX2_ReturnsCorrectValue_739) {

    EXPECT_DOUBLE_EQ(calloutLine->getX2(), 3.0);

}



// Boundary condition tests

TEST_F(AnnotCalloutLineTest_739, GetX2_ZeroCoordinates_739) {

    AnnotCalloutLine zeroCalloutLine(0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(zeroCalloutLine.getX2(), 0.0);

}



TEST_F(AnnotCalloutLineTest_739, GetX2_NegativeCoordinates_739) {

    AnnotCalloutLine negativeCalloutLine(-1.0, -2.0, -3.0, -4.0);

    EXPECT_DOUBLE_EQ(negativeCalloutLine.getX2(), -3.0);

}



// Exceptional or error cases

// No observable exceptional/error cases through the provided interface



// Verification of external interactions (no mocks needed in this case)
