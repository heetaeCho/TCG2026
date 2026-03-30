#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_83 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_83, IsCmd_ReturnsTrueForCmdType_83) {

    Object obj(ObjType::objCmd);

    EXPECT_TRUE(obj.isCmd());

}



TEST_F(ObjectTest_83, IsCmd_ReturnsFalseForNonCmdType_83) {

    Object obj(ObjType::objNull);

    EXPECT_FALSE(obj.isCmd());

}



TEST_F(ObjectTest_83, IsCmd_DefaultConstructorReturnsFalse_83) {

    Object obj;

    EXPECT_FALSE(obj.isCmd());

}



TEST_F(ObjectTest_83, IsCmd_CmdStringMatches_83) {

    Object obj(ObjType::objCmd, "someCmd");

    EXPECT_TRUE(obj.isCmd("someCmd"));

}



TEST_F(ObjectTest_83, IsCmd_CmdStringDoesNotMatch_83) {

    Object obj(ObjType::objCmd, "someCmd");

    EXPECT_FALSE(obj.isCmd("anotherCmd"));

}
