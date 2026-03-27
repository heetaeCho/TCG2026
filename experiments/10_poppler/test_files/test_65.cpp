#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_65 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_65, CreateEofObject_65) {

    Object eofObj = Object::eof();

    EXPECT_TRUE(eofObj.isEOF());

}



TEST_F(ObjectTest_65, CreateNullObject_65) {

    Object nullObj = Object::null();

    EXPECT_TRUE(nullObj.isNull());

}



TEST_F(ObjectTest_65, CreateErrorObject_65) {

    Object errorObj = Object::error();

    EXPECT_TRUE(errorObj.isError());

}



TEST_F(ObjectTest_65, TypeCheckingFunctions_65) {

    Object boolObj(true);

    Object intObj(42);

    Object realObj(3.14);

    Object stringObj(std::string("test"));

    Object hexStringObj((std::unique_ptr<GooString>(new GooString("hex"))));

    Object nameObj(Object::objName, "name");

    Object arrayObj(new Array());

    Object dictObj(new Dict());



    EXPECT_TRUE(boolObj.isBool());

    EXPECT_TRUE(intObj.isInt());

    EXPECT_TRUE(realObj.isReal());

    EXPECT_TRUE(stringObj.isString());

    EXPECT_TRUE(hexStringObj.isHexString());

    EXPECT_TRUE(nameObj.isName("name"));

    EXPECT_TRUE(arrayObj.isArray());

    EXPECT_TRUE(dictObj.isDict());

}



TEST_F(ObjectTest_65, ArrayOperations_65) {

    Object arrayObj(new Array());

    Object intObj(42);

    Object realObj(3.14);



    arrayObj.arrayAdd(std::move(intObj));

    arrayObj.arrayAdd(std::move(realObj));



    EXPECT_EQ(arrayObj.arrayGetLength(), 2);

    EXPECT_TRUE(arrayObj.arrayGetNF(0).isInt());

    EXPECT_TRUE(arrayObj.arrayGetNF(1).isReal());



    arrayObj.arrayRemove(0);

    EXPECT_EQ(arrayObj.arrayGetLength(), 1);

}



TEST_F(ObjectTest_65, DictOperations_65) {

    Object dictObj(new Dict());

    Object intObj(42);

    Object realObj(3.14);



    dictObj.dictAdd("key1", std::move(intObj));

    dictObj.dictAdd("key2", std::move(realObj));



    EXPECT_EQ(dictObj.dictGetLength(), 2);

    EXPECT_TRUE(dictObj.dictLookupNF("key1").isInt());

    EXPECT_TRUE(dictObj.dictLookupNF("key2").isReal());



    dictObj.dictRemove("key1");

    EXPECT_EQ(dictObj.dictGetLength(), 1);

}



TEST_F(ObjectTest_65, BoundaryConditions_65) {

    Object nullObj = Object::null();

    Object errorObj = Object::error();



    // Array operations with empty array

    Object arrayObj(new Array());

    EXPECT_EQ(arrayObj.arrayGetLength(), 0);



    // Dict operations with empty dict

    Object dictObj(new Dict());

    EXPECT_EQ(dictObj.dictGetLength(), 0);

}



TEST_F(ObjectTest_65, ExceptionalCases_65) {

    Object nullObj = Object::null();

    Object errorObj = Object::error();



    // Accessing values from null and error objects should not cause crashes

    EXPECT_NO_THROW(nullObj.isDict());

    EXPECT_NO_THROW(errorObj.isDict());



    Object arrayObj(new Array());

    EXPECT_THROW(arrayObj.arrayGetNF(0), std::runtime_error); // Assuming out of bounds access throws



    Object dictObj(new Dict());

    EXPECT_THROW(dictObj.dictLookupNF("nonexistent"), std::runtime_error); // Assuming lookup of non-existent key throws

}
