#include <gtest/gtest.h>

#include "Annot.h"



class AnnotBorderArrayTest_750 : public ::testing::Test {

protected:

    AnnotBorderArray borderArray;

};



TEST_F(AnnotBorderArrayTest_750, SetHorizontalCorner_NormalOperation_750) {

    borderArray.setHorizontalCorner(1.5);

    EXPECT_EQ(borderArray.getHorizontalCorner(), 1.5);

}



TEST_F(AnnotBorderArrayTest_750, SetHorizontalCorner_BoundaryCondition_Zero_750) {

    borderArray.setHorizontalCorner(0.0);

    EXPECT_EQ(borderArray.getHorizontalCorner(), 0.0);

}



TEST_F(AnnotBorderArrayTest_750, SetHorizontalCorner_BoundaryCondition_Negative_750) {

    borderArray.setHorizontalCorner(-1.5);

    EXPECT_EQ(borderArray.getHorizontalCorner(), -1.5);

}



TEST_F(AnnotBorderArrayTest_750, SetHorizontalCorner_BoundaryCondition_LargeNumber_750) {

    borderArray.setHorizontalCorner(999999.999);

    EXPECT_EQ(borderArray.getHorizontalCorner(), 999999.999);

}
