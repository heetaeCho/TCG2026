#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::isCmd(std::string_view) tests
class ObjectIsCmdTest_1238 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an Object of type objCmd with matching command string returns true
TEST_F(ObjectIsCmdTest_1238, CmdObjectWithMatchingString_ReturnsTrue_1238) {
    Object obj(objCmd, "myCommand");
    EXPECT_TRUE(obj.isCmd("myCommand"));
}

// Test that an Object of type objCmd with non-matching command string returns false
TEST_F(ObjectIsCmdTest_1238, CmdObjectWithNonMatchingString_ReturnsFalse_1238) {
    Object obj(objCmd, "myCommand");
    EXPECT_FALSE(obj.isCmd("otherCommand"));
}

// Test that an Object of type objCmd with empty command matches empty string_view
TEST_F(ObjectIsCmdTest_1238, CmdObjectWithEmptyString_MatchesEmpty_1238) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd(""));
}

// Test that an Object of type objCmd with empty command does not match non-empty string
TEST_F(ObjectIsCmdTest_1238, CmdObjectWithEmptyString_DoesNotMatchNonEmpty_1238) {
    Object obj(objCmd, "");
    EXPECT_FALSE(obj.isCmd("something"));
}

// Test that an Object of type objCmd with non-empty command does not match empty string
TEST_F(ObjectIsCmdTest_1238, CmdObjectWithNonEmptyString_DoesNotMatchEmpty_1238) {
    Object obj(objCmd, "myCommand");
    EXPECT_FALSE(obj.isCmd(""));
}

// Test that a non-Cmd Object (objBool) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, BoolObject_ReturnsFalse_1238) {
    Object obj(true);
    EXPECT_FALSE(obj.isCmd("anyString"));
}

// Test that a non-Cmd Object (objInt) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, IntObject_ReturnsFalse_1238) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("test"));
}

// Test that a non-Cmd Object (objReal) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, RealObject_ReturnsFalse_1238) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isCmd("test"));
}

// Test that a null Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, NullObject_ReturnsFalse_1238) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isCmd("test"));
}

// Test that an error Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, ErrorObject_ReturnsFalse_1238) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isCmd("test"));
}

// Test that an EOF Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, EofObject_ReturnsFalse_1238) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isCmd("test"));
}

// Test that a default-constructed (objNone) Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_1238, NoneObject_ReturnsFalse_1238) {
    Object obj;
    EXPECT_FALSE(obj.isCmd("test"));
}

// Test that an objName Object does not match isCmd even with same string
TEST_F(ObjectIsCmdTest_1238, NameObjectWithSameString_ReturnsFalse_1238) {
    Object obj(objName, "myCommand");
    EXPECT_FALSE(obj.isCmd("myCommand"));
}

// Test case sensitivity: command strings should be case-sensitive
TEST_F(ObjectIsCmdTest_1238, CmdObjectCaseSensitive_ReturnsFalse_1238) {
    Object obj(objCmd, "MyCommand");
    EXPECT_FALSE(obj.isCmd("mycommand"));
}

// Test case sensitivity: exact case match returns true
TEST_F(ObjectIsCmdTest_1238, CmdObjectCaseSensitiveExactMatch_ReturnsTrue_1238) {
    Object obj(objCmd, "MyCommand");
    EXPECT_TRUE(obj.isCmd("MyCommand"));
}

// Test partial match: substring should not match
TEST_F(ObjectIsCmdTest_1238, CmdObjectPartialMatch_ReturnsFalse_1238) {
    Object obj(objCmd, "myCommand");
    EXPECT_FALSE(obj.isCmd("myComm"));
}

// Test that a longer string does not match
TEST_F(ObjectIsCmdTest_1238, CmdObjectLongerString_ReturnsFalse_1238) {
    Object obj(objCmd, "myCommand");
    EXPECT_FALSE(obj.isCmd("myCommandExtra"));
}

// Test the no-argument isCmd() returns true for objCmd type
TEST_F(ObjectIsCmdTest_1238, CmdObjectNoArgIsCmd_ReturnsTrue_1238) {
    Object obj(objCmd, "anyCmd");
    EXPECT_TRUE(obj.isCmd());
}

// Test the no-argument isCmd() returns false for non-cmd type
TEST_F(ObjectIsCmdTest_1238, NonCmdObjectNoArgIsCmd_ReturnsFalse_1238) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

// Test with a single character command
TEST_F(ObjectIsCmdTest_1238, CmdObjectSingleChar_MatchesSingleChar_1238) {
    Object obj(objCmd, "x");
    EXPECT_TRUE(obj.isCmd("x"));
    EXPECT_FALSE(obj.isCmd("y"));
}

// Test with special characters in command string
TEST_F(ObjectIsCmdTest_1238, CmdObjectSpecialChars_MatchesSpecialChars_1238) {
    Object obj(objCmd, "cm*");
    EXPECT_TRUE(obj.isCmd("cm*"));
    EXPECT_FALSE(obj.isCmd("cm"));
}

// Test that after move, the moved-to object retains isCmd behavior
TEST_F(ObjectIsCmdTest_1238, MovedCmdObject_RetainsCmdBehavior_1238) {
    Object obj1(objCmd, "testCmd");
    Object obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isCmd("testCmd"));
    EXPECT_FALSE(obj2.isCmd("wrong"));
}

// Test getCmd returns the correct command string for a cmd object
TEST_F(ObjectIsCmdTest_1238, GetCmd_ReturnsCorrectString_1238) {
    Object obj(objCmd, "hello");
    EXPECT_TRUE(obj.isCmd());
    const char* cmd = obj.getCmd();
    ASSERT_NE(cmd, nullptr);
    EXPECT_STREQ(cmd, "hello");
}

// Test getType returns objCmd for a cmd object
TEST_F(ObjectIsCmdTest_1238, GetType_ReturnsObjCmd_1238) {
    Object obj(objCmd, "test");
    EXPECT_EQ(obj.getType(), objCmd);
}
