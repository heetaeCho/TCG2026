#include <gtest/gtest.h>

#include "GooString.h"



class GooStringTest_2280 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(GooStringTest_2280, GetChar_ReturnsCorrectCharacter_NormalCase_2280) {

    GooString str("Hello");

    EXPECT_EQ(str.getChar(0), 'H');

    EXPECT_EQ(str.getChar(1), 'e');

    EXPECT_EQ(str.getChar(4), 'o');

}



TEST_F(GooStringTest_2280, GetChar_ReturnsCorrectCharacter_BoundaryCase_Start_2280) {

    GooString str("World");

    EXPECT_EQ(str.getChar(0), 'W');

}



TEST_F(GooStringTest_2280, GetChar_ReturnsCorrectCharacter_BoundaryCase_End_2280) {

    GooString str("Example");

    EXPECT_EQ(str.getChar(6), 'e');

}



TEST_F(GooStringTest_2280, GetChar_OutOfBounds_ThrowsException_2280) {

    GooString str("Test");

    EXPECT_THROW(str.getChar(4), std::out_of_range);

}



TEST_F(GooStringTest_2280, GetChar_EmptyString_ThrowsException_2280) {

    GooString str("");

    EXPECT_THROW(str.getChar(0), std::out_of_range);

}
