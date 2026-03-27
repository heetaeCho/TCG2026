#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_95 : public ::testing::Test {

protected:

    bool ok;

};



TEST_F(ObjectTest_95, GetNum_ReturnsDoubleForInt_95) {

    Object obj(42);

    double result = obj.getNum(&ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 42.0);

}



TEST_F(ObjectTest_95, GetNum_ReturnsDoubleForInt64_95) {

    Object obj(static_cast<long long>(123456789012345LL));

    double result = obj.getNum(&ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 123456789012345.0);

}



TEST_F(ObjectTest_95, GetNum_ReturnsDoubleForReal_95) {

    Object obj(3.14);

    double result = obj.getNum(&ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 3.14);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForString_95) {

    Object obj("test");

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForName_95) {

    Object obj(std::string_view("name"));

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForNull_95) {

    Object obj = Object::null();

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForArray_95) {

    Array array;

    Object obj(&array);

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForDict_95) {

    Dict dict;

    Object obj(&dict);

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForStream_95) {

    Stream stream(nullptr, nullptr, 0);

    Object obj(&stream);

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForRef_95) {

    Ref ref(1, 2);

    Object obj(ref.num, ref.gen);

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForCmd_95) {

    Object obj(std::string_view("cmd"));

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForError_95) {

    Object obj = Object::error();

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForEOF_95) {

    Object obj = Object::eof();

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}



TEST_F(ObjectTest_95, GetNum_SetsOkFalseForNone_95) {

    Object obj;

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}
