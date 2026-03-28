#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_2753 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if necessary

    }



    void TearDown() override {

        // Cleanup can be done here if necessary

    }

};



// Normal operation tests



TEST_F(ObjectTest_2753, TestConstruction_2753) {

    Object obj1(true);

    EXPECT_TRUE(obj1.isBool());



    Object obj2(42);

    EXPECT_TRUE(obj2.isInt());



    Object obj3(3.14);

    EXPECT_TRUE(obj3.isReal());



    std::unique_ptr<GooString> gooStr = std::make_unique<GooString>("test");

    Object obj4(std::move(gooStr));

    EXPECT_TRUE(obj4.isString());



    Object obj5("test");

    EXPECT_TRUE(obj5.isString());



    Object obj6(ObjType::objName, "test");

    EXPECT_TRUE(obj6.isName());

}



TEST_F(ObjectTest_2753, TestArrayOperations_2753) {

    Object arrayObj = Object::null();

    arrayObj.setToNull();



    Array* array = new Array();

    Object objWithArray(array);

    EXPECT_TRUE(objWithArray.isArray());



    int length = objWithArray.arrayGetLength();

    EXPECT_EQ(length, 0);



    Object elem(true);

    objWithArray.arrayAdd(std::move(elem));

    length = objWithArray.arrayGetLength();

    EXPECT_EQ(length, 1);



    const Object& retrievedElem = objWithArray.arrayGetNF(0);

    EXPECT_TRUE(retrievedElem.isBool());



    objWithArray.arrayRemove(0);

    length = objWithArray.arrayGetLength();

    EXPECT_EQ(length, 0);

}



TEST_F(ObjectTest_2753, TestDictOperations_2753) {

    Object dictObj = Object::null();

    dictObj.setToNull();



    Dict* dict = new Dict();

    Object objWithDict(dict);

    EXPECT_TRUE(objWithDict.isDict());



    int length = objWithDict.dictGetLength();

    EXPECT_EQ(length, 0);



    Object value(true);

    objWithDict.dictAdd("key1", std::move(value));

    length = objWithDict.dictGetLength();

    EXPECT_EQ(length, 1);



    const Object& retrievedValue = objWithDict.dictLookupNF("key1");

    EXPECT_TRUE(retrievedValue.isBool());



    objWithDict.dictRemove("key1");

    length = objWithDict.dictGetLength();

    EXPECT_EQ(length, 0);

}



// Boundary condition tests



TEST_F(ObjectTest_2753, TestEmptyArray_2753) {

    Object arrayObj = Object::null();

    arrayObj.setToNull();



    Array* array = new Array();

    Object objWithArray(array);

    EXPECT_TRUE(objWithArray.isArray());



    int length = objWithArray.arrayGetLength();

    EXPECT_EQ(length, 0);



    const Object& retrievedElem = objWithArray.arrayGetNF(0);

    EXPECT_FALSE(retrievedElem.isBool());

}



TEST_F(ObjectTest_2753, TestEmptyDict_2753) {

    Object dictObj = Object::null();

    dictObj.setToNull();



    Dict* dict = new Dict();

    Object objWithDict(dict);

    EXPECT_TRUE(objWithDict.isDict());



    int length = objWithDict.dictGetLength();

    EXPECT_EQ(length, 0);



    const Object& retrievedValue = objWithDict.dictLookupNF("key1");

    EXPECT_FALSE(retrievedValue.isBool());

}



// Exceptional or error cases



TEST_F(ObjectTest_2753, TestInvalidArrayIndex_2753) {

    Object arrayObj = Object::null();

    arrayObj.setToNull();



    Array* array = new Array();

    Object objWithArray(array);

    EXPECT_TRUE(objWithArray.isArray());



    int length = objWithArray.arrayGetLength();

    EXPECT_EQ(length, 0);



    // Assuming out-of-bounds access does not throw but returns a null object

    const Object& retrievedElem = objWithArray.arrayGetNF(10);

    EXPECT_TRUE(retrievedElem.isNull());

}



TEST_F(ObjectTest_2753, TestInvalidDictKey_2753) {

    Object dictObj = Object::null();

    dictObj.setToNull();



    Dict* dict = new Dict();

    Object objWithDict(dict);

    EXPECT_TRUE(objWithDict.isDict());



    int length = objWithDict.dictGetLength();

    EXPECT_EQ(length, 0);



    // Assuming non-existent key access does not throw but returns a null object

    const Object& retrievedValue = objWithDict.dictLookupNF("nonexistent");

    EXPECT_TRUE(retrievedValue.isNull());

}



// Verification of external interactions



TEST_F(ObjectTest_2753, TestMoveConstructor_2753) {

    Object original(true);

    EXPECT_TRUE(original.isBool());



    Object moved(std::move(original));

    EXPECT_FALSE(original.getType() == objDead); // Assuming move constructor sets type to objDead

    EXPECT_TRUE(moved.isBool());

}



TEST_F(ObjectTest_2753, TestStaticNullObject_2753) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNull());

}



TEST_F(ObjectTest_2753, TestStaticEofObject_2753) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_2753, TestStaticErrorObject_2753) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}
