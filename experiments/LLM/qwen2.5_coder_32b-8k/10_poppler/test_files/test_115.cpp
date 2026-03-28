#include <gtest/gtest.h>

#include "Dict.h"

#include "Object.h"



class DictTest_115 : public ::testing::Test {

protected:

    XRef* mockXRef = nullptr;  // Assuming XRef is a class that might be used internally by Dict



    void SetUp() override {

        mockXRef = new XRef();

    }



    void TearDown() override {

        delete mockXRef;

    }

};



TEST_F(DictTest_115, GetVal_ReturnsValidObject_115) {

    Dict dict(mockXRef);

    Object obj(42);

    dict.add("key", std::move(obj));



    Object retrievedObj = dict.getVal(0);



    EXPECT_TRUE(retrievedObj.isInt());

    EXPECT_EQ(retrievedObj.getInt(), 42);

}



TEST_F(DictTest_115, GetVal_OutOfBoundsIndex_ReturnsErrorObject_115) {

    Dict dict(mockXRef);

    Object retrievedObj = dict.getVal(0);



    EXPECT_TRUE(retrievedObj.isError());

}



TEST_F(DictTest_115, GetVal_EmptyDict_ReturnsErrorObject_115) {

    Dict dict(mockXRef);

    Object retrievedObj = dict.getVal(0);



    EXPECT_TRUE(retrievedObj.isError());

}



// Assuming there's a way to add multiple entries and check the last one

TEST_F(DictTest_115, GetVal_LastEntry_ReturnsLastObject_115) {

    Dict dict(mockXRef);

    Object obj1(42);

    Object obj2(3.14);

    dict.add("key1", std::move(obj1));

    dict.add("key2", std::move(obj2));



    Object retrievedObj = dict.getVal(1);



    EXPECT_TRUE(retrievedObj.isReal());

    EXPECT_DOUBLE_EQ(retrievedObj.getReal(), 3.14);

}



// Assuming there's a way to handle different types of objects

TEST_F(DictTest_115, GetVal_DifferentTypes_ReturnsCorrectType_115) {

    Dict dict(mockXRef);

    Object objBool(true);

    Object objInt(100);

    Object objString("test");

    dict.add("keyBool", std::move(objBool));

    dict.add("keyInt", std::move(objInt));

    dict.add("keyString", std::move(objString));



    EXPECT_TRUE(dict.getVal(0).isBool());

    EXPECT_TRUE(dict.getVal(1).isInt());

    EXPECT_TRUE(dict.getVal(2).isString());

}



// Assuming there's a way to handle null objects

TEST_F(DictTest_115, GetVal_NullObject_ReturnsNull_115) {

    Dict dict(mockXRef);

    Object obj = Object::null();

    dict.add("keyNull", std::move(obj));



    Object retrievedObj = dict.getVal(0);



    EXPECT_TRUE(retrievedObj.isNull());

}



// Assuming there's a way to handle error objects

TEST_F(DictTest_115, GetVal_ErrorObject_ReturnsError_115) {

    Dict dict(mockXRef);

    Object obj = Object::error();

    dict.add("keyError", std::move(obj));



    Object retrievedObj = dict.getVal(0);



    EXPECT_TRUE(retrievedObj.isError());

}
