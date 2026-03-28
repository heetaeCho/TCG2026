#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_77 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_77, IsName_ReturnsTrueForNameType_77) {

    Object obj(ObjType::objName);

    EXPECT_TRUE(obj.isName());

}



TEST_F(ObjectTest_77, IsName_ReturnsFalseForNonNameType_77) {

    Object obj(ObjType::objInt);

    EXPECT_FALSE(obj.isName());

}



TEST_F(ObjectTest_77, IsName_StringOverload_ReturnsTrueForMatchingName_77) {

    Object obj(ObjType::objName, "example");

    EXPECT_TRUE(obj.isName("example"));

}



TEST_F(ObjectTest_77, IsName_StringOverload_ReturnsFalseForNonMatchingName_77) {

    Object obj(ObjType::objName, "example");

    EXPECT_FALSE(obj.isName("non_example"));

}



TEST_F(ObjectTest_77, GetType_ReturnsCorrectType_77) {

    Object obj(ObjType::objString);

    EXPECT_EQ(obj.getType(), ObjType::objString);

}



TEST_F(ObjectTest_77, IsNone_ReturnsTrueForDefaultConstructedObject_77) {

    Object obj;

    EXPECT_TRUE(obj.isNone());

}



TEST_F(ObjectTest_77, IsBool_ReturnsFalseForNonBoolType_77) {

    Object obj(ObjType::objInt);

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_77, IsInt_ReturnsTrueForIntType_77) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_77, IsReal_ReturnsTrueForRealType_77) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_77, IsString_ReturnsTrueForStringType_77) {

    Object obj(std::string("test_string"));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_77, IsHexString_ReturnsFalseForNonHexStringType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isHexString());

}



TEST_F(ObjectTest_77, IsNull_ReturnsTrueForNullType_77) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_77, IsArray_ReturnsFalseForNonArrayType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isArray());

}



TEST_F(ObjectTest_77, IsDict_ReturnsFalseForNonDictType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_77, IsStream_ReturnsFalseForNonStreamType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isStream());

}



TEST_F(ObjectTest_77, IsRef_ReturnsFalseForNonRefType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isRef());

}



TEST_F(ObjectTest_77, IsCmd_ReturnsFalseForNonCmdType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isCmd());

}



TEST_F(ObjectTest_77, IsError_ReturnsFalseForNonErrorType_77) {

    Object obj(42);

    EXPECT_FALSE(obj.isError());

}



TEST_F(ObjectTest_77, IsEOF_ReturnsTrueForEOFType_77) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}
