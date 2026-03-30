#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_84 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_84, IsError_ReturnsFalse_ForNonErrorObject_84) {

    Object obj(Object::error());

    obj = Object(0); // Assuming 0 is not objError

    EXPECT_FALSE(obj.isError());

}



TEST_F(ObjectTest_84, IsError_ReturnsTrue_ForErrorObject_84) {

    Object obj(Object::objError);

    EXPECT_TRUE(obj.isError());

}



TEST_F(ObjectTest_84, IsNone_ReturnsTrue_ForNoneObject_84) {

    Object obj;

    EXPECT_TRUE(obj.isNone());

}



TEST_F(ObjectTest_84, IsBool_ReturnsTrue_ForBoolObject_84) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

}



TEST_F(ObjectTest_84, IsInt_ReturnsTrue_ForIntObject_84) {

    Object obj(0);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_84, IsReal_ReturnsTrue_ForRealObject_84) {

    Object obj(0.0);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_84, IsString_ReturnsTrue_ForStringObject_84) {

    Object obj(std::string("test"));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_84, IsName_ReturnsTrue_ForNameObject_84) {

    Object obj = Object(Object::objName, "name");

    EXPECT_TRUE(obj.isName());

}



TEST_F(ObjectTest_84, IsNull_ReturnsTrue_ForNullObject_84) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_84, IsArray_ReturnsTrue_ForArrayObject_84) {

    Array* array = new Array;

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

    delete array;

}



TEST_F(ObjectTest_84, IsDict_ReturnsTrue_ForDictObject_84) {

    Dict* dict = new Dict;

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

    delete dict;

}



TEST_F(ObjectTest_84, IsStream_ReturnsTrue_ForStreamObject_84) {

    Stream* stream = nullptr; // Assuming a valid stream can be created

    Object obj(stream);

    EXPECT_TRUE(obj.isStream());

}



TEST_F(ObjectTest_84, IsRef_ReturnsTrue_ForRefObject_84) {

    Ref ref;

    Object obj(ref.num, ref.gen);

    EXPECT_TRUE(obj.isRef());

}



TEST_F(ObjectTest_84, IsCmd_ReturnsTrue_ForCmdObject_84) {

    Object obj = Object(Object::objCmd, "cmd");

    EXPECT_TRUE(obj.isCmd());

}



TEST_F(ObjectTest_84, IsEOF_ReturnsTrue_ForEOFObject_84) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_84, IsInt64_ReturnsTrue_ForInt64Object_84) {

    Object obj(0LL);

    EXPECT_TRUE(obj.isInt64());

}
