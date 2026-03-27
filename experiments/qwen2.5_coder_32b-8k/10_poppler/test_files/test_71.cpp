#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_71 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_71, IsBool_ReturnsTrueForBoolObject_71) {

    Object boolObj(true);

    EXPECT_TRUE(boolObj.isBool());

}



TEST_F(ObjectTest_71, IsBool_ReturnsFalseForNonBoolObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isBool());

}



TEST_F(ObjectTest_71, IsInt_ReturnsTrueForIntObject_71) {

    Object intObj(42);

    EXPECT_TRUE(intObj.isInt());

}



TEST_F(ObjectTest_71, IsInt_ReturnsFalseForNonIntObject_71) {

    Object boolObj(true);

    EXPECT_FALSE(boolObj.isInt());

}



TEST_F(ObjectTest_71, IsReal_ReturnsTrueForRealObject_71) {

    Object realObj(3.14);

    EXPECT_TRUE(realObj.isReal());

}



TEST_F(ObjectTest_71, IsReal_ReturnsFalseForNonRealObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isReal());

}



TEST_F(ObjectTest_71, IsString_ReturnsTrueForStringObject_71) {

    std::unique_ptr<GooString> stringObj(new GooString("test"));

    Object obj(std::move(stringObj));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_71, IsString_ReturnsFalseForNonStringObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isString());

}



TEST_F(ObjectTest_71, IsName_ReturnsTrueForNameObject_71) {

    Object nameObj("name");

    EXPECT_TRUE(nameObj.isName("name"));

}



TEST_F(ObjectTest_71, IsName_ReturnsFalseForNonNameObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isName("name"));

}



TEST_F(ObjectTest_71, IsNull_ReturnsTrueForNullObject_71) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNull());

}



TEST_F(ObjectTest_71, IsNull_ReturnsFalseForNonNullObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isNull());

}



TEST_F(ObjectTest_71, IsArray_ReturnsTrueForArrayObject_71) {

    Array* array = new Array();

    Object arrayObj(array);

    EXPECT_TRUE(arrayObj.isArray());

    delete array;

}



TEST_F(ObjectTest_71, IsArray_ReturnsFalseForNonArrayObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isArray());

}



TEST_F(ObjectTest_71, IsDict_ReturnsTrueForDictObject_71) {

    Dict* dict = new Dict();

    Object dictObj(dict);

    EXPECT_TRUE(dictObj.isDict());

    delete dict;

}



TEST_F(ObjectTest_71, IsDict_ReturnsFalseForNonDictObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isDict());

}



TEST_F(ObjectTest_71, IsStream_ReturnsTrueForStreamObject_71) {

    Stream* stream = new Stream();

    Object streamObj(stream);

    EXPECT_TRUE(streamObj.isStream());

    delete stream;

}



TEST_F(ObjectTest_71, IsStream_ReturnsFalseForNonStreamObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isStream());

}



TEST_F(ObjectTest_71, IsRef_ReturnsTrueForRefObject_71) {

    Ref ref;

    ref.num = 42;

    ref.gen = 0;

    Object refObj(ref);

    EXPECT_TRUE(refObj.isRef());

}



TEST_F(ObjectTest_71, IsCmd_ReturnsTrueForCmdObject_71) {

    Object cmdObj("cmd");

    EXPECT_TRUE(cmdObj.isCmd("cmd"));

}



TEST_F(ObjectTest_71, IsCmd_ReturnsFalseForNonCmdObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isCmd("cmd"));

}



TEST_F(ObjectTest_71, IsError_ReturnsTrueForErrorObject_71) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}



TEST_F(ObjectTest_71, IsError_ReturnsFalseForNonErrorObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isError());

}



TEST_F(ObjectTest_71, IsEOF_ReturnsTrueForEOFObject_71) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_71, IsEOF_ReturnsFalseForNonEOFObject_71) {

    Object intObj(42);

    EXPECT_FALSE(intObj.isEOF());

}
