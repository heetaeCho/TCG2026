#include <gtest/gtest.h>

#include "poppler/Object.h"



class ObjectTest_104 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_104, IsBool_ReturnsTrueForBooleanObject_104) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

}



TEST_F(ObjectTest_104, IsInt_ReturnsTrueForIntegerObject_104) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_104, IsReal_ReturnsTrueForRealObject_104) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_104, IsString_ReturnsTrueForStringObject_104) {

    Object obj(std::make_unique<GooString>("test"));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_104, IsHexString_ReturnsFalseForNonHexStringObject_104) {

    Object obj("test");

    EXPECT_FALSE(obj.isHexString());

}



TEST_F(ObjectTest_104, IsName_ReturnsTrueForNameObject_104) {

    Object obj(ObjType::objName, "name");

    EXPECT_TRUE(obj.isName("name"));

}



TEST_F(ObjectTest_104, IsNull_ReturnsTrueForNullObject_104) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_104, IsArray_ReturnsTrueForArrayObject_104) {

    Array* array = new Array;

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

}



TEST_F(ObjectTest_104, IsDict_ReturnsTrueForDictObject_104) {

    Dict* dict = new Dict;

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

}



TEST_F(ObjectTest_104, IsStream_ReturnsFalseForNonStreamObject_104) {

    Object obj(ObjType::objInt, 42);

    EXPECT_FALSE(obj.isStream());

}



TEST_F(ObjectTest_104, IsRef_ReturnsTrueForRefObject_104) {

    Ref ref;

    Object obj(ref);

    EXPECT_TRUE(obj.isRef());

}



TEST_F(ObjectTest_104, IsCmd_ReturnsFalseForNonCommandObject_104) {

    Object obj(ObjType::objInt, 42);

    EXPECT_FALSE(obj.isCmd("test"));

}



TEST_F(ObjectTest_104, IsError_ReturnsTrueForErrorObject_104) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}



TEST_F(ObjectTest_104, IsEOF_ReturnsTrueForEOFObject_104) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_104, GetBool_ReturnsCorrectValueForBooleanObject_104) {

    Object obj(true);

    EXPECT_TRUE(obj.getBool());

}



TEST_F(ObjectTest_104, GetInt_ReturnsCorrectValueForIntegerObject_104) {

    Object obj(42);

    EXPECT_EQ(42, obj.getInt());

}



TEST_F(ObjectTest_104, GetReal_ReturnsCorrectValueForRealObject_104) {

    Object obj(3.14);

    EXPECT_DOUBLE_EQ(3.14, obj.getReal());

}



TEST_F(ObjectTest_104, GetString_ReturnsCorrectPointerForStringObject_104) {

    std::unique_ptr<GooString> str = std::make_unique<GooString>("test");

    const char* expectedStr = str->getCString();

    Object obj(std::move(str));

    EXPECT_STREQ(expectedStr, obj.getString()->getCString());

}



TEST_F(ObjectTest_104, GetName_ReturnsCorrectNameForNameObject_104) {

    Object obj(ObjType::objName, "name");

    EXPECT_STREQ("name", obj.getName());

}



TEST_F(ObjectTest_104, GetRef_ReturnsValidReferenceForRefObject_104) {

    Ref ref = {123, 456};

    Object obj(ref);

    EXPECT_EQ(123, obj.getRef().num);

    EXPECT_EQ(456, obj.getRef().gen);

}



TEST_F(ObjectTest_104, GetCmd_ReturnsCorrectCommandForCommandObject_104) {

    Object obj(ObjType::objCmd, "command");

    EXPECT_STREQ("command", obj.getCmd());

}
