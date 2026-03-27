#include <gtest/gtest.h>

#include "OutputDev.h"



class OutputDevTest_1058 : public ::testing::Test {

protected:

    OutputDev outputDev;

};



TEST_F(OutputDevTest_1058, UseShadedFills_ReturnsFalseForAnyType_1058) {

    EXPECT_FALSE(outputDev.useShadedFills(0));

    EXPECT_FALSE(outputDev.useShadedFills(-1));

    EXPECT_FALSE(outputDev.useShadedFills(1));

    EXPECT_FALSE(outputDev.useShadedFills(INT_MAX));

}



TEST_F(OutputDevTest_1058, UseShadedFills_BoundaryConditions_1058) {

    EXPECT_FALSE(outputDev.useShadedFills(INT_MIN));

    EXPECT_FALSE(outputDev.useShadedFills(INT_MAX));

}
