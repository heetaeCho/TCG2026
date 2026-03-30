#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_68 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



// Test normal operation of getType()

TEST_F(ObjectTest_68, GetType_ReturnsCorrectType_68) {

    Object obj(ObjType::objInt);

    EXPECT_EQ(obj.getType(), ObjType::objInt);

}



// Test boundary condition with null object

TEST_F(ObjectTest_68, IsNull_ReturnsTrueForNullObject_68) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



// Test boundary condition with eof object

TEST_F(ObjectTest_68, IsEOF_ReturnsTrueForEofObject_68) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



// Test boundary condition with error object

TEST_F(ObjectTest_68, IsError_ReturnsTrueForErrorObject_68) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}



// Test normal operation of isBool()

TEST_F(ObjectTest_68, IsBool_ReturnsTrueForBoolObject_68) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

}



// Test normal operation of isInt()

TEST_F(ObjectTest_68, IsInt_ReturnsTrueForIntObject_68) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

}



// Test normal operation of isReal()

TEST_F(ObjectTest_68, IsReal_ReturnsTrueForRealObject_68) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

}



// Test normal operation of isString()

TEST_F(ObjectTest_68, IsString_ReturnsTrueForStringObject_68) {

    std::unique_ptr<GooString> str = std::make_unique<GooString>("test");

    Object obj(std::move(str));

    EXPECT_TRUE(obj.isString());

}



// Test normal operation of isName()

TEST_F(ObjectTest_68, IsName_ReturnsTrueForNameObject_68) {

    Object obj(ObjType::objName, "name");

    EXPECT_TRUE(obj.isName("name"));

}



// Test normal operation of isArray()

TEST_F(ObjectTest_68, IsArray_ReturnsTrueForArrayObject_68) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

    delete array;

}



// Test normal operation of isDict()

TEST_F(ObjectTest_68, IsDict_ReturnsTrueForDictObject_68) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

    delete dict;

}



// Test normal operation of setToNull()

TEST_F(ObjectTest_68, SetToNull_ChangesTypeToNull_68) {

    Object obj(42);

    obj.setToNull();

    EXPECT_TRUE(obj.isNull());

}



// Test move assignment operator

TEST_F(ObjectTest_68, MoveAssignment_OperatesCorrectly_68) {

    Object srcObj(42);

    Object destObj;

    destObj = std::move(srcObj);



    EXPECT_TRUE(destObj.isInt());

    EXPECT_EQ(destObj.getInt(), 42);

}



// Test normal operation of getNameString()

TEST_F(ObjectTest_68, GetNameString_ReturnsCorrectName_68) {

    Object obj(ObjType::objName, "testName");

    EXPECT_EQ(obj.getNameString(), "testName");

}



// Test exceptional case for getting int from non-int object

TEST_F(ObjectTest_68, GetInt_ThrowsErrorForNonIntObject_68) {

    Object obj(true);

    EXPECT_THROW(obj.getInt(), std::runtime_error); // Assuming some exception is thrown if type mismatch occurs

}



// Test exceptional case for getting real from non-real object

TEST_F(ObjectTest_68, GetReal_ThrowsErrorForNonRealObject_68) {

    Object obj(42);

    EXPECT_THROW(obj.getReal(), std::runtime_error); // Assuming some exception is thrown if type mismatch occurs

}



// Test exceptional case for getting string from non-string object

TEST_F(ObjectTest_68, GetString_ThrowsErrorForNonStringObject_68) {

    Object obj(true);

    EXPECT_THROW(obj.getString(), std::runtime_error); // Assuming some exception is thrown if type mismatch occurs

}
