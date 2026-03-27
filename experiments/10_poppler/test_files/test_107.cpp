#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"



class ObjectTest_107 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_107, IsCmd_ReturnsTrueForCommandObject_107) {

    Object obj(objCmd, "testCmd");

    EXPECT_TRUE(obj.isCmd());

}



TEST_F(ObjectTest_107, IsCmd_ReturnsFalseForNonCommandObject_107) {

    Object obj(objInt, 42);

    EXPECT_FALSE(obj.isCmd());

}



TEST_F(ObjectTest_107, GetCmd_ReturnsCorrectCommandString_107) {

    const char* expectedCmd = "testCmd";

    Object obj(objCmd, expectedCmd);

    EXPECT_STREQ(expectedCmd, obj.getCmd());

}



TEST_F(ObjectTest_107, GetCmd_ThrowsForNonCommandObject_107) {

    Object obj(objInt, 42);

    EXPECT_DEATH({obj.getCmd();}, "Assertion failed");

}



TEST_F(ObjectTest_107, IsDict_ReturnsTrueForDictionaryObject_107) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

    delete dict;

}



TEST_F(ObjectTest_107, IsDict_ReturnsFalseForNonDictionaryObject_107) {

    Object obj(objInt, 42);

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_107, GetType_ReturnsCorrectType_107) {

    Object obj(objCmd, "testCmd");

    EXPECT_EQ(objCmd, obj.getType());

}



TEST_F(ObjectTest_107, IsNull_ReturnsTrueForNullObject_107) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_107, IsEof_ReturnsTrueForEofObject_107) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_107, IsError_ReturnsTrueForErrorObject_107) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}
