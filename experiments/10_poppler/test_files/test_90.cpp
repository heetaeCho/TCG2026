#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_90 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(ObjectTest_90, IsCmd_ReturnsTrueForMatchingCommand_90) {

    Object obj(ObjType::objCmd, "testCmd");

    EXPECT_TRUE(obj.isCmd("testCmd"));

}



TEST_F(ObjectTest_90, IsCmd_ReturnsFalseForNonMatchingCommand_90) {

    Object obj(ObjType::objCmd, "testCmd");

    EXPECT_FALSE(obj.isCmd("otherCmd"));

}



TEST_F(ObjectTest_90, IsCmd_ReturnsFalseForDifferentType_90) {

    Object obj(ObjType::objName, "testCmd");

    EXPECT_FALSE(obj.isCmd("testCmd"));

}



TEST_F(ObjectTest_90, IsCmd_ReturnsTrueForEmptyCommand_90) {

    Object obj(ObjType::objCmd, "");

    EXPECT_TRUE(obj.isCmd(""));

}



TEST_F(ObjectTest_90, IsCmd_ReturnsFalseForNullString_90) {

    Object obj;

    EXPECT_FALSE(obj.isCmd("testCmd"));

}
