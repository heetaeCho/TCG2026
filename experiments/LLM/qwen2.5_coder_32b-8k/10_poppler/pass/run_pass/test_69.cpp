#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_69 : public ::testing::Test {

protected:

    Object obj;

};



TEST_F(ObjectTest_69, SetToNullChangesTypeToObjNull_69) {

    obj.setToNull();

    EXPECT_EQ(obj.getType(), objNull);

}



TEST_F(ObjectTest_69, IsNullReturnsTrueAfterSetToNull_69) {

    obj.setToNull();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_69, GetTypeReturnsObjNoneInitially_69) {

    EXPECT_EQ(obj.getType(), objNone);

}



TEST_F(ObjectTest_69, IsDictReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_69, IsArrayReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isArray());

}



TEST_F(ObjectTest_69, IsStringReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_69, IsNameReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isName("test"));

}



TEST_F(ObjectTest_69, IsCmdReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isCmd("test"));

}



TEST_F(ObjectTest_69, IsErrorReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isError());

}



TEST_F(ObjectTest_69, IsEOFReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isEOF());

}



TEST_F(ObjectTest_69, IsNoneReturnsTrueForNewObject_69) {

    EXPECT_TRUE(obj.isNone());

}



TEST_F(ObjectTest_69, IsIntReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_69, IsRealReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_69, IsNumReturnsFalseForNewObject_69) {

    EXPECT_FALSE(obj.isNum());

}
