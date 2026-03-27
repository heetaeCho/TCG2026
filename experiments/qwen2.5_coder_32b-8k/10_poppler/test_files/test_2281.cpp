#include <gtest/gtest.h>

#include "GooString.h"



class GooStringTest_2281 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> gooString;



    void SetUp() override {

        gooString = std::make_unique<GooString>("Hello, World!");

    }

};



TEST_F(GooStringTest_2281, SetCharChangesCharacterAtPosition_2281) {

    gooString->setChar(0, 'h');

    EXPECT_EQ(gooString->toStr(), "hello, World!");

}



TEST_F(GooStringTest_2281, SetCharOnBoundaryConditionStart_2281) {

    gooString->setChar(0, 'J');

    EXPECT_EQ(gooString->toStr(), "Jello, World!");

}



TEST_F(GooStringTest_2281, SetCharOnBoundaryConditionEnd_2281) {

    gooString->setChar(12, '!');

    EXPECT_EQ(gooString->toStr(), "Hello, World!");

}



TEST_F(GooStringTest_2281, SetCharBeyondLengthDoesNotChangeString_2281) {

    gooString->setChar(13, 'X');

    EXPECT_EQ(gooString->toStr(), "Hello, World!");

}



TEST_F(GooStringTest_2281, SetCharWithEmptyString_2281) {

    auto emptyGooString = std::make_unique<GooString>("");

    emptyGooString->setChar(0, 'A');

    EXPECT_EQ(emptyGooString->toStr(), "");

}



TEST_F(GooStringTest_2281, SetCharWithSingleCharacterString_2281) {

    auto singleCharGooString = std::make_unique<GooString>("A");

    singleCharGooString->setChar(0, 'B');

    EXPECT_EQ(singleCharGooString->toStr(), "B");

}



TEST_F(GooStringTest_2281, SetCharWithLargeIndexDoesNotChangeString_2281) {

    gooString->setChar(50, 'Z');

    EXPECT_EQ(gooString->toStr(), "Hello, World!");

}
