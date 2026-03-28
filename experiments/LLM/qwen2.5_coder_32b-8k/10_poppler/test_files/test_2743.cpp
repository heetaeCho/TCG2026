#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_2743, Constructor_BoolType_ReturnsCorrectBoolValue_2743) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

    EXPECT_EQ(obj.getBool(), true);

}



TEST_F(ObjectTest_2743, Constructor_BoolType_DefaultFalse_ReturnsFalse_2743) {

    Object obj(false);

    EXPECT_TRUE(obj.isBool());

    EXPECT_EQ(obj.getBool(), false);

}



TEST_F(ObjectTest_2743, Constructor_IntType_ReturnsCorrectIntValue_2743) {

    Object obj(123);

    EXPECT_TRUE(obj.isInt());

    EXPECT_EQ(obj.getInt(), 123);

}



TEST_F(ObjectTest_2743, Constructor_RealType_ReturnsCorrectRealValue_2743) {

    Object obj(123.456);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), 123.456);

}



TEST_F(ObjectTest_2743, Constructor_StringType_ReturnsCorrectStringValue_2743) {

    std::unique_ptr<GooString> str(new GooString("test"));

    Object obj(std::move(str));

    EXPECT_TRUE(obj.isString());

    EXPECT_STREQ(obj.getString()->getCString(), "test");

}



TEST_F(ObjectTest_2743, Constructor_StringViewType_ReturnsCorrectStringValue_2743) {

    std::string_view str = "test";

    Object obj(str);

    EXPECT_TRUE(obj.isString());

    EXPECT_STREQ(obj.getString()->getCString(), "test");

}



TEST_F(ObjectTest_2743, Constructor_LongLongIntType_ReturnsCorrectLongLongValue_2743) {

    Object obj(123456789012LL);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), 123456789012LL);

}



TEST_F(ObjectTest_2743, Constructor_ArrayType_ReturnsCorrectArrayType_2743) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

    delete array;

}



TEST_F(ObjectTest_2743, Constructor_DictType_ReturnsCorrectDictType_2743) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

    delete dict;

}



TEST_F(ObjectTest_2743, StaticMethod_Null_ReturnsNullObject_2743) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_2743, StaticMethod_Eof_ReturnsEofObject_2743) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_2743, StaticMethod_Error_ReturnsErrorObject_2743) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}
