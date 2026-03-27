#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"

#include "GooString.h"



class ObjectTest_96 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> testString;

    Object* obj;



    void SetUp() override {

        testString = std::make_unique<GooString>("testString");

        obj = new Object(std::move(testString));

    }



    void TearDown() override {

        delete obj;

    }

};



TEST_F(ObjectTest_96, GetString_ReturnsCorrectPointer_96) {

    const GooString* result = obj->getString();

    EXPECT_EQ(result->cmp("testString"), 0);

}



TEST_F(ObjectTest_96, GetString_NotNullAfterMove_96) {

    std::unique_ptr<GooString> anotherString = std::make_unique<GooString>("anotherString");

    Object anotherObj(std::move(anotherString));

    EXPECT_NE(anotherObj.getString(), nullptr);

}



TEST_F(ObjectTest_96, IsString_ReturnsTrueForStringType_96) {

    EXPECT_TRUE(obj->isString());

}



TEST_F(ObjectTest_96, IsString_ReturnsFalseForNonStringType_96) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isString());

}



TEST_F(ObjectTest_96, GetString_ReturnsNullForNonStringType_96) {

    Object intObj(42);

    EXPECT_EQ(intObj.getString(), nullptr);

}



TEST_F(ObjectTest_96, GetType_ReturnsCorrectObjectType_96) {

    EXPECT_EQ(obj->getType(), objString);

}



TEST_F(ObjectTest_96, GetString_AfterMove_96) {

    std::unique_ptr<GooString> movedString = std::make_unique<GooString>("movedString");

    Object movedObj(std::move(movedString));

    const GooString* result = movedObj.getString();

    EXPECT_EQ(result->cmp("movedString"), 0);

}



TEST_F(ObjectTest_96, GetString_ReturnsNullAfterTakingString_96) {

    obj->takeString();

    EXPECT_EQ(obj->getString(), nullptr);

}
