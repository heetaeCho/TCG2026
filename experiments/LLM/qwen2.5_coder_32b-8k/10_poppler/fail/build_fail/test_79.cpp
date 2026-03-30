#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest : public ::testing::Test {

protected:

    Object boolObj;

    Object intObj;

    Object realObj;

    Object stringObj;

    Object nameObj;

    Object nullObj;

    Object arrayObj;

    Object dictObj;

    Object streamObj;

    Object refObj;

    Object cmdObj;

    Object errorObj;

    Object eofObj;

    Object noneObj;

    Object int64Obj;

    Object hexStringObj;



    ObjectTest()

        : boolObj(true),

          intObj(10),

          realObj(3.14),

          stringObj("test"),

          nameObj("/Name"),

          nullObj(Object::null()),

          arrayObj(new Array()),

          dictObj(new Dict()),

          streamObj(ObjType::objStream, "streamData"),

          refObj(Ref(1, 0)),

          cmdObj("cmd"),

          errorObj(Object::error()),

          eofObj(Object::eof()),

          noneObj(),

          int64Obj(static_cast<long long>(1234567890123LL)),

          hexStringObj("#1a2b3c") {}

};



TEST_F(ObjectTest_79, IsArray_ReturnsTrueForArray_79) {

    EXPECT_TRUE(arrayObj.isArray());

}



TEST_F(ObjectTest_79, IsArray_ReturnsFalseForNonArray_79) {

    EXPECT_FALSE(boolObj.isArray());

    EXPECT_FALSE(intObj.isArray());

    EXPECT_FALSE(realObj.isArray());

    EXPECT_FALSE(stringObj.isArray());

    EXPECT_FALSE(nameObj.isArray());

    EXPECT_FALSE(nullObj.isArray());

    EXPECT_FALSE(dictObj.isArray());

    EXPECT_FALSE(streamObj.isArray());

    EXPECT_FALSE(refObj.isArray());

    EXPECT_FALSE(cmdObj.isArray());

    EXPECT_FALSE(errorObj.isArray());

    EXPECT_FALSE(eofObj.isArray());

    EXPECT_FALSE(noneObj.isArray());

    EXPECT_FALSE(int64Obj.isArray());

    EXPECT_FALSE(hexStringObj.isArray());

}



TEST_F(ObjectTest_79, IsArray_BoundaryCondition_EmptyArray_79) {

    Object emptyArrayObj(new Array());

    EXPECT_TRUE(emptyArrayObj.isArray());

}



TEST_F(ObjectTest_79, IsArray_ExceptionalCase_NoTypeSet_79) {

    // Since the constructor sets a type, we cannot easily test this.

    // However, if there were a way to set an invalid type, it would be tested here.

}
