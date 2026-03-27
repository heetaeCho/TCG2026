#include <gtest/gtest.h>

#include "Object.h"

#include <memory>



class ObjectTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> CreateGooString(const char* content) {

        return std::make_unique<GooString>(content);

    }

};



TEST_F(ObjectTest_2746, ConstructorWithString_2746) {

    auto gooString = CreateGooString("test");

    Object obj(std::move(gooString));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2746, GetTypeForString_2746) {

    auto gooString = CreateGooString("test");

    Object obj(std::move(gooString));

    EXPECT_EQ(obj.getType(), objString);

}



TEST_F(ObjectTest_2746, GetStringContent_2746) {

    auto gooString = CreateGooString("test");

    Object obj(std::move(gooString));

    const GooString* str = obj.getString();

    ASSERT_NE(str, nullptr);

    EXPECT_STREQ(str->getCString(), "test");

}



TEST_F(ObjectTest_2746, MoveConstructor_2746) {

    auto gooString = CreateGooString("test");

    Object obj1(std::move(gooString));

    Object obj2(std::move(obj1));

    EXPECT_TRUE(obj2.isString());

    const GooString* str = obj2.getString();

    ASSERT_NE(str, nullptr);

    EXPECT_STREQ(str->getCString(), "test");

}



TEST_F(ObjectTest_2746, TakeStringOwnership_2746) {

    auto gooString = CreateGooString("test");

    Object obj(std::move(gooString));

    std::unique_ptr<GooString> takenStr = obj.takeString();

    ASSERT_NE(takenStr.get(), nullptr);

    EXPECT_STREQ(takenStr->getCString(), "test");

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_2746, IsStringInitiallyTrue_2746) {

    auto gooString = CreateGooString("test");

    Object obj(std::move(gooString));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_2746, NullObject_2746) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_2746, EofObject_2746) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_2746, ErrorObject_2746) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}



TEST_F(ObjectTest_2746, SetToNull_2746) {

    auto gooString = CreateGooString("test");

    Object obj(std::move(gooString));

    obj.setToNull();

    EXPECT_TRUE(obj.isNull());

}
