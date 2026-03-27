#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_2744, ConstructorWithInt_2744) {

    Object obj(42);

    EXPECT_EQ(obj.getType(), objInt);

    EXPECT_EQ(obj.getInt(), 42);

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForIntObject_2744) {

    Object obj(42);

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsTrueForIntObject_2744) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_2744, ConstructorWithBool_2744) {

    Object obj(true);

    EXPECT_EQ(obj.getType(), objBool);

    EXPECT_TRUE(obj.getBool());

}



TEST_F(ObjectTest_2744, IsBoolReturnsTrueForBoolObject_2744) {

    Object obj(false);

    EXPECT_TRUE(obj.isBool());

    EXPECT_FALSE(obj.getBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForBoolObject_2744) {

    Object obj(true);

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_2744, ConstructorWithDouble_2744) {

    Object obj(3.14);

    EXPECT_EQ(obj.getType(), objReal);

    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForDoubleObject_2744) {

    Object obj(3.14);

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForDoubleObject_2744) {

    Object obj(3.14);

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_2744, ConstructorWithStringView_2744) {

    Object obj(objString, "example");

    EXPECT_EQ(obj.getType(), objString);

    EXPECT_STREQ(obj.getName(), "example");

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForStringObject_2744) {

    Object obj(objString, "example");

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForStringObject_2744) {

    Object obj(objString, "example");

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_2744, ConstructorWithUniquePtrGooString_2744) {

    auto stringA = std::make_unique<GooString>("unique example");

    Object obj(std::move(stringA));

    EXPECT_EQ(obj.getType(), objHexString);

    EXPECT_STREQ(obj.getString()->c_str(), "unique example");

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForUniquePtrGooStringObject_2744) {

    auto stringA = std::make_unique<GooString>("unique example");

    Object obj(std::move(stringA));

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForUniquePtrGooStringObject_2744) {

    auto stringA = std::make_unique<GooString>("unique example");

    Object obj(std::move(stringA));

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_2744, StaticMethodNull_2744) {

    Object obj = Object::null();

    EXPECT_EQ(obj.getType(), objNull);

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForNullObject_2744) {

    Object obj = Object::null();

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForNullObject_2744) {

    Object obj = Object::null();

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_2744, StaticMethodEof_2744) {

    Object obj = Object::eof();

    EXPECT_EQ(obj.getType(), objEOF);

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForEofObject_2744) {

    Object obj = Object::eof();

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForEofObject_2744) {

    Object obj = Object::eof();

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_2744, StaticMethodError_2744) {

    Object obj = Object::error();

    EXPECT_EQ(obj.getType(), objError);

}



TEST_F(ObjectTest_2744, IsBoolReturnsFalseForErrorObject_2744) {

    Object obj = Object::error();

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_2744, IsIntReturnsFalseForErrorObject_2744) {

    Object obj = Object::error();

    EXPECT_FALSE(obj.isInt());

}
