#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_66 : public ::testing::Test {

protected:

    Object obj;

};



TEST_F(ObjectTest_66, IsError_ReturnsTrueForErrorObject_66) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}



TEST_F(ObjectTest_66, IsNull_ReturnsTrueForNullObject_66) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNull());

}



TEST_F(ObjectTest_66, IsEOF_ReturnsTrueForEOFObject_66) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_66, GetType_ReturnsCorrectTypeForObjectError_66) {

    Object errorObj = Object::error();

    EXPECT_EQ(errorObj.getType(), objError);

}



TEST_F(ObjectTest_66, GetType_ReturnsCorrectTypeForObjectNull_66) {

    Object nullObj = Object::null();

    EXPECT_EQ(nullObj.getType(), objNull);

}



TEST_F(ObjectTest_66, GetType_ReturnsCorrectTypeForObjectEOF_66) {

    Object eofObj = Object::eof();

    EXPECT_EQ(eofObj.getType(), objEOF);

}



TEST_F(ObjectTest_66, IsNone_ReturnsTrueForDefaultConstructedObject_66) {

    Object defaultObj;

    EXPECT_TRUE(defaultObj.isNone());

}



TEST_F(ObjectTest_66, GetType_ReturnsCorrectTypeForDefaultConstructedObject_66) {

    Object defaultObj;

    EXPECT_EQ(defaultObj.getType(), objNone);

}
