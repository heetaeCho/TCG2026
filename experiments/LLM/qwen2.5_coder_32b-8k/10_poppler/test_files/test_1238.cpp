#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



using namespace std::string_literals;



class ObjectTest_1238 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(ObjectTest_1238, IsCmd_ReturnsTrueForMatchingCommand_1238) {

    Object obj(ObjType::objCmd, "command"s);

    EXPECT_TRUE(obj.isCmd("command"s));

}



TEST_F(ObjectTest_1238, IsCmd_ReturnsFalseForNonMatchingCommand_1238) {

    Object obj(ObjType::objCmd, "command"s);

    EXPECT_FALSE(obj.isCmd("other_command"s));

}



TEST_F(ObjectTest_1238, IsCmd_ReturnsFalseForDifferentType_1238) {

    Object obj(ObjType::objName, "name"s);

    EXPECT_FALSE(obj.isCmd("name"s));

}



TEST_F(ObjectTest_1238, IsCmd_ReturnsFalseForEmptyCommand_1238) {

    Object obj(ObjType::objCmd, ""s);

    EXPECT_FALSE(obj.isCmd(""s));

}



TEST_F(ObjectTest_1238, IsCmd_ReturnsTrueForEmptyCommandWhenObjectIsEmpty_1238) {

    Object obj(ObjType::objCmd, ""s);

    EXPECT_TRUE(obj.isCmd(""s));

}
