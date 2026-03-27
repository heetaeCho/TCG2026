#include <gtest/gtest.h>

#include "Annot.h"



class AnnotCalloutLineTest_738 : public ::testing::Test {

protected:

    AnnotCalloutLine calloutLine;



    void SetUp() override {

        // Initialize with some default values for the coordinates

        calloutLine = AnnotCalloutLine(1.0, 2.0, 3.0, 4.0);

    }

};



TEST_F(AnnotCalloutLineTest_738, GetY1_ReturnsCorrectValue_738) {

    EXPECT_DOUBLE_EQ(calloutLine.getY1(), 2.0);

}



TEST_F(AnnotCalloutLineTest_738, BoundaryCondition_GetY1_Zero_738) {

    AnnotCalloutLine calloutLineZero(1.0, 0.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(calloutLineZero.getY1(), 0.0);

}



TEST_F(AnnotCalloutLineTest_738, BoundaryCondition_GetY1_Negative_738) {

    AnnotCalloutLine calloutLineNegative(1.0, -2.0, 3.0, 4.0);

    EXPECT_DOUBLE_EQ(calloutLineNegative.getY1(), -2.0);

}



TEST_F(AnnotCalloutLineTest_738, BoundaryCondition_GetY1_MaxDouble_738) {

    AnnotCalloutLine calloutLineMax(1.0, std::numeric_limits<double>::max(), 3.0, 4.0);

    EXPECT_DOUBLE_EQ(calloutLineMax.getY1(), std::numeric_limits<double>::max());

}



TEST_F(AnnotCalloutLineTest_738, BoundaryCondition_GetY1_MinDouble_738) {

    AnnotCalloutLine calloutLineMin(1.0, std::numeric_limits<double>::lowest(), 3.0, 4.0);

    EXPECT_DOUBLE_EQ(calloutLineMin.getY1(), std::numeric_limits<double>::lowest());

}
