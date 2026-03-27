#include <gtest/gtest.h>

#include "Object.h"



// Assuming Object class and related dependencies are available



class IsInlineAlignNameTest : public ::testing::Test {

protected:

    std::unique_ptr<Object> objStart;

    std::unique_ptr<Object> objEnd;

    std::unique_ptr<Object> objCenter;

    std::unique_ptr<Object> objOther;



    void SetUp() override {

        objStart = std::make_unique<Object>("Start");

        objEnd = std::make_unique<Object>("End");

        objCenter = std::make_unique<Object>("Center");

        objOther = std::make_unique<Object>("Other");

    }

};



TEST_F(IsInlineAlignNameTest_1759, Start_ReturnsTrue_1759) {

    EXPECT_TRUE(isInlineAlignName(objStart.get()));

}



TEST_F(IsInlineAlignNameTest_1759, End_ReturnsTrue_1759) {

    EXPECT_TRUE(isInlineAlignName(objEnd.get()));

}



TEST_F(IsInlineAlignNameTest_1759, Center_ReturnsTrue_1759) {

    EXPECT_TRUE(isInlineAlignName(objCenter.get()));

}



TEST_F(IsInlineAlignNameTest_1759, Other_ReturnsFalse_1759) {

    EXPECT_FALSE(isInlineAlignName(objOther.get()));

}



TEST_F(IsInlineAlignNameTest_1759, NullObject_ReturnsFalse_1759) {

    Object objNull = Object::null();

    EXPECT_FALSE(isInlineAlignName(&objNull));

}



TEST_F(IsInlineAlignNameTest_1759, EofObject_ReturnsFalse_1759) {

    Object objEof = Object::eof();

    EXPECT_FALSE(isInlineAlignName(&objEof));

}



TEST_F(IsInlineAlignNameTest_1759, ErrorObject_ReturnsFalse_1759) {

    Object objError = Object::error();

    EXPECT_FALSE(isInlineAlignName(&objError));

}
