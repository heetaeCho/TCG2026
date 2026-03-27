#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



using namespace poppler;



class ObjectTest_72 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_72, IsInt_ReturnsTrueForIntegerObject_72) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_72, IsInt_ReturnsFalseForNonIntegerObject_72) {

    Object obj("someString");

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_72, IsInt_ReturnsFalseForNullObject_72) {

    Object obj = Object::null();

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_72, IsInt_ReturnsFalseForEOFObject_72) {

    Object obj = Object::eof();

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_72, IsInt_ReturnsFalseForErrorObject_72) {

    Object obj = Object::error();

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_72, GetType_ReturnsObjIntForIntegerObject_72) {

    Object obj(42);

    EXPECT_EQ(obj.getType(), objInt);

}



TEST_F(ObjectTest_72, GetType_ReturnsCorrectTypeForStringObject_72) {

    Object obj("someString");

    EXPECT_EQ(obj.getType(), objString);

}
