#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"

#include "TestProjects/poppler/poppler/GooString.h"

#include "TestProjects/poppler/poppler/Array.h"

#include "TestProjects/poppler/poppler/Dict.h"

#include "TestProjects/poppler/poppler/XRef.h"



// Test fixture for Object class

class ObjectTest_64 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



// Test for creating a null object

TEST_F(ObjectTest_64, CreateNullObject_64) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



// Test for creating an integer object and checking its type

TEST_F(ObjectTest_64, CreateIntObject_64) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

    EXPECT_EQ(obj.getInt(), 42);

}



// Test for creating a real (double) object and checking its type

TEST_F(ObjectTest_64, CreateRealObject_64) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);

}



// Test for creating a string object using unique_ptr and checking its type

TEST_F(ObjectTest_64, CreateStringObjectUniquePtr_64) {

    std::unique_ptr<GooString> str(new GooString("test"));

    Object obj(std::move(str));

    EXPECT_TRUE(obj.isString());

}



// Test for creating a string object using rvalue reference and checking its type

TEST_F(ObjectTest_64, CreateStringObjectRValueRef_64) {

    Object obj(std::string("test"));

    EXPECT_TRUE(obj.isString());

}



// Test for creating an array object and adding elements to it

TEST_F(ObjectTest_64, ArrayAddElements_64) {

    Object arrObj(Object::arrayA);

    arrObj.arrayAdd(42);

    arrObj.arrayAdd(3.14);

    EXPECT_EQ(arrObj.arrayGetLength(), 2);

}



// Test for getting an element from the array

TEST_F(ObjectTest_64, ArrayGetElement_64) {

    Object arrObj(Object::arrayA);

    arrObj.arrayAdd(42);

    Object elem = arrObj.arrayGetNF(0);

    EXPECT_TRUE(elem.isInt());

    EXPECT_EQ(elem.getInt(), 42);

}



// Test for creating a dictionary object and adding key-value pairs

TEST_F(ObjectTest_64, DictAddElements_64) {

    Object dictObj(Object::dictA);

    dictObj.dictAdd("key1", 42);

    dictObj.dictAdd("key2", 3.14);

    EXPECT_EQ(dictObj.dictGetLength(), 2);

}



// Test for looking up a key in the dictionary

TEST_F(ObjectTest_64, DictLookupKey_64) {

    Object dictObj(Object::dictA);

    dictObj.dictAdd("key1", 42);

    Object value = dictObj.dictLookupNF("key1");

    EXPECT_TRUE(value.isInt());

    EXPECT_EQ(value.getInt(), 42);

}



// Test for boundary condition: empty array

TEST_F(ObjectTest_64, EmptyArray_64) {

    Object arrObj(Object::arrayA);

    EXPECT_EQ(arrObj.arrayGetLength(), 0);

}



// Test for boundary condition: empty dictionary

TEST_F(ObjectTest_64, EmptyDict_64) {

    Object dictObj(Object::dictA);

    EXPECT_EQ(dictObj.dictGetLength(), 0);

}
