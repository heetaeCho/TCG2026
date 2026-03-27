#include <gtest/gtest.h>

#include "GooString.h"



class GooStringTest_24 : public ::testing::Test {

protected:

    void SetUp() override {

        str = std::make_unique<GooString>("hello");

    }



    std::unique_ptr<GooString> str;

};



TEST_F(GooStringTest_24, SetCharWithinBounds_24) {

    str->setChar(0, 'H');

    EXPECT_EQ(str->getChar(0), 'H');

}



TEST_F(GooStringTest_24, SetCharAtEnd_24) {

    str->setChar(4, 'o');

    EXPECT_EQ(str->getChar(4), 'o');

}



TEST_F(GooStringTest_24, SetCharBoundaryCondition_24) {

    str->setChar(0, 'H');

    EXPECT_EQ(str->toStr(), "Hello");

}



TEST_F(GooStringTest_24, SetCharOutOfUpperBounds_24) {

    EXPECT_THROW(str->setChar(5, '!'), std::out_of_range);

}



TEST_F(GooStringTest_24, SetCharOutOfLowerBounds_24) {

    EXPECT_THROW(str->setChar(-1, '!'), std::out_of_range);

}



TEST_F(GooStringTest_24, SetCharMultipleTimes_24) {

    str->setChar(0, 'H');

    str->setChar(4, '!');

    EXPECT_EQ(str->toStr(), "Hell!");

}
