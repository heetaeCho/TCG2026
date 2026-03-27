#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_81 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(ObjectTest_81, IsStream_ReturnsFalseForNonStreamObject_81) {

    Object obj(objNone);

    EXPECT_FALSE(obj.isStream());

}



TEST_F(ObjectTest_81, IsStream_ReturnsTrueForStreamObject_81) {

    Object obj(objStream);

    EXPECT_TRUE(obj.isStream());

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForBoolObject_81) {

    Object obj(true);

    EXPECT_EQ(obj.getType(), objBool);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForIntObject_81) {

    Object obj(42);

    EXPECT_EQ(obj.getType(), objInt);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForRealObject_81) {

    Object obj(3.14);

    EXPECT_EQ(obj.getType(), objReal);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForStringObject_81) {

    Object obj(std::make_unique<GooString>("test"));

    EXPECT_EQ(obj.getType(), objString);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForHexStringObject_81) {

    Object obj(std::unique_ptr<GooString>(new GooString("hex")));

    // Assuming there's a way to set the type to hex string

    EXPECT_EQ(obj.getType(), objHexString);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForNameObject_81) {

    Object obj(ObjType::objName, "name");

    EXPECT_EQ(obj.getType(), objName);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForNullObject_81) {

    Object obj = Object::null();

    EXPECT_EQ(obj.getType(), objNull);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForArrayObject_81) {

    Array* array = new Array;

    Object obj(array);

    EXPECT_EQ(obj.getType(), objArray);

    delete array;

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForDictObject_81) {

    Dict* dict = new Dict;

    Object obj(dict);

    EXPECT_EQ(obj.getType(), objDict);

    delete dict;

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForStreamObject_81) {

    Object obj(objStream);

    EXPECT_EQ(obj.getType(), objStream);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForRefObject_81) {

    Ref ref = {0, 0};

    Object obj(ref.num, ref.gen);

    // Assuming there's a constructor that takes num and gen

    EXPECT_EQ(obj.getType(), objRef);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForCmdObject_81) {

    Object obj(ObjType::objCmd, "cmd");

    EXPECT_EQ(obj.getType(), objCmd);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForErrorObject_81) {

    Object obj = Object::error();

    EXPECT_EQ(obj.getType(), objError);

}



TEST_F(ObjectTest_81, GetType_ReturnsCorrectTypeForEOFObject_81) {

    Object obj = Object::eof();

    EXPECT_EQ(obj.getType(), objEOF);

}



TEST_F(ObjectTest_81, IsNone_ReturnsTrueForDefaultConstructedObject_81) {

    Object obj;

    EXPECT_TRUE(obj.isNone());

}



TEST_F(ObjectTest_81, IsBool_ReturnsFalseForNonBoolObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isBool());

}



TEST_F(ObjectTest_81, IsBool_ReturnsTrueForBoolObject_81) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

}



TEST_F(ObjectTest_81, IsInt_ReturnsFalseForNonIntObject_81) {

    Object obj(3.14);

    EXPECT_FALSE(obj.isInt());

}



TEST_F(ObjectTest_81, IsInt_ReturnsTrueForIntObject_81) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



TEST_F(ObjectTest_81, IsReal_ReturnsFalseForNonRealObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_81, IsReal_ReturnsTrueForRealObject_81) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_81, IsNum_ReturnsFalseForNonNumericObject_81) {

    Object obj("string");

    // Assuming there's a constructor for string

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_81, IsNum_ReturnsTrueForIntObject_81) {

    Object obj(42);

    EXPECT_TRUE(obj.isNum());

}



TEST_F(ObjectTest_81, IsNum_ReturnsTrueForRealObject_81) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isNum());

}



TEST_F(ObjectTest_81, IsString_ReturnsFalseForNonStringObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_81, IsString_ReturnsTrueForStringObject_81) {

    Object obj(std::make_unique<GooString>("test"));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_81, IsHexString_ReturnsFalseForNonHexStringObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isHexString());

}



TEST_F(ObjectTest_81, IsHexString_ReturnsTrueForHexStringObject_81) {

    Object obj(std::unique_ptr<GooString>(new GooString("hex")));

    // Assuming there's a way to set the type to hex string

    EXPECT_TRUE(obj.isHexString());

}



TEST_F(ObjectTest_81, IsName_ReturnsFalseForNonNameObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isName("name"));

}



TEST_F(ObjectTest_81, IsName_ReturnsTrueForMatchingNameObject_81) {

    Object obj(ObjType::objName, "name");

    EXPECT_TRUE(obj.isName("name"));

}



TEST_F(ObjectTest_81, IsNull_ReturnsFalseForNonNullObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isNull());

}



TEST_F(ObjectTest_81, IsNull_ReturnsTrueForNullObject_81) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_81, IsArray_ReturnsFalseForNonArrayObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isArray());

}



TEST_F(ObjectTest_81, IsArray_ReturnsTrueForArrayObject_81) {

    Array* array = new Array;

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

    delete array;

}



TEST_F(ObjectTest_81, IsDict_ReturnsFalseForNonDictObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_81, IsDict_ReturnsTrueForDictObject_81) {

    Dict* dict = new Dict;

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

    delete dict;

}



TEST_F(ObjectTest_81, IsRef_ReturnsFalseForNonRefObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isRef());

}



TEST_F(ObjectTest_81, IsCmd_ReturnsFalseForNonCmdObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isCmd());

}



TEST_F(ObjectTest_81, IsCmd_ReturnsTrueForCmdObject_81) {

    Object obj(ObjType::objCmd, "cmd");

    EXPECT_TRUE(obj.isCmd());

}



TEST_F(ObjectTest_81, IsError_ReturnsFalseForNonErrorObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isError());

}



TEST_F(ObjectTest_81, IsError_ReturnsTrueForErrorObject_81) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}



TEST_F(ObjectTest_81, IsEOF_ReturnsFalseForNonEOFObject_81) {

    Object obj(42);

    EXPECT_FALSE(obj.isEOF());

}



TEST_F(ObjectTest_81, IsEOF_ReturnsTrueForEOFObject_81) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}
