#include <gtest/gtest.h>

#include "GooString.h"



class GooStringTest_23 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(GooStringTest_23, GetChar_NormalOperation_23) {

    GooString str("Hello");

    EXPECT_EQ('H', str.getChar(0));

    EXPECT_EQ('e', str.getChar(1));

    EXPECT_EQ('l', str.getChar(2));

}



TEST_F(GooStringTest_23, GetChar_BoundaryCondition_Start_23) {

    GooString str("Hello");

    EXPECT_EQ('H', str.getChar(0));

}



TEST_F(GooStringTest_23, GetChar_BoundaryCondition_End_23) {

    GooString str("Hello");

    EXPECT_EQ('o', str.getChar(4));

}



TEST_F(GooStringTest_23, GetChar_Exceptional_OutOfBounds_23) {

    GooString str("Hello");

    EXPECT_THROW(str.getChar(5), std::out_of_range);

}



TEST_F(GooStringTest_23, GetChar_Exceptional_EmptyString_23) {

    GooString str("");

    EXPECT_THROW(str.getChar(0), std::out_of_range);

}
