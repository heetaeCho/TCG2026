#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for Object::isCmd(std::string_view) tests
class ObjectIsCmdTest_90 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that an Object of type objCmd with a matching command string returns true
TEST_F(ObjectIsCmdTest_90, CmdObjectWithMatchingString_ReturnsTrue_90) {
    Object obj(objCmd, "myCommand");
    EXPECT_TRUE(obj.isCmd("myCommand"));
}

// Test that an Object of type objCmd with a non-matching command string returns false
TEST_F(ObjectIsCmdTest_90, CmdObjectWithNonMatchingString_ReturnsFalse_90) {
    Object obj(objCmd, "myCommand");
    EXPECT_FALSE(obj.isCmd("otherCommand"));
}

// Test that an Object of type objCmd with empty string matches empty string_view
TEST_F(ObjectIsCmdTest_90, CmdObjectWithEmptyString_MatchesEmpty_90) {
    Object obj(objCmd, "");
    EXPECT_TRUE(obj.isCmd(""));
}

// Test that an Object of type objCmd with empty string does not match non-empty
TEST_F(ObjectIsCmdTest_90, CmdObjectWithEmptyString_DoesNotMatchNonEmpty_90) {
    Object obj(objCmd, "");
    EXPECT_FALSE(obj.isCmd("something"));
}

// Test that an Object of type objCmd with non-empty string does not match empty
TEST_F(ObjectIsCmdTest_90, CmdObjectWithNonEmptyString_DoesNotMatchEmpty_90) {
    Object obj(objCmd, "hello");
    EXPECT_FALSE(obj.isCmd(""));
}

// Test that a non-cmd Object (objBool) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, BoolObject_ReturnsFalse_90) {
    Object obj(true);
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that a non-cmd Object (objInt) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, IntObject_ReturnsFalse_90) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that a non-cmd Object (objReal) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, RealObject_ReturnsFalse_90) {
    Object obj(3.14);
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that a null Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, NullObject_ReturnsFalse_90) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that an error Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, ErrorObject_ReturnsFalse_90) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that an EOF Object returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, EofObject_ReturnsFalse_90) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that a default-constructed Object (objNone) returns false for isCmd(string_view)
TEST_F(ObjectIsCmdTest_90, NoneObject_ReturnsFalse_90) {
    Object obj;
    EXPECT_FALSE(obj.isCmd("anyCommand"));
}

// Test that a name Object returns false for isCmd(string_view), even if string matches
TEST_F(ObjectIsCmdTest_90, NameObjectWithSameString_ReturnsFalse_90) {
    Object obj(objName, "myCommand");
    EXPECT_FALSE(obj.isCmd("myCommand"));
}

// Test case sensitivity: cmd with different case should not match
TEST_F(ObjectIsCmdTest_90, CmdObjectCaseSensitive_ReturnsFalse_90) {
    Object obj(objCmd, "MyCommand");
    EXPECT_FALSE(obj.isCmd("mycommand"));
}

// Test case sensitivity: exact case matches
TEST_F(ObjectIsCmdTest_90, CmdObjectCaseSensitiveExactMatch_ReturnsTrue_90) {
    Object obj(objCmd, "MyCommand");
    EXPECT_TRUE(obj.isCmd("MyCommand"));
}

// Test partial match should return false
TEST_F(ObjectIsCmdTest_90, CmdObjectPartialMatch_ReturnsFalse_90) {
    Object obj(objCmd, "longCommandName");
    EXPECT_FALSE(obj.isCmd("longCommand"));
}

// Test that substring match from the end returns false
TEST_F(ObjectIsCmdTest_90, CmdObjectSubstringFromEnd_ReturnsFalse_90) {
    Object obj(objCmd, "longCommandName");
    EXPECT_FALSE(obj.isCmd("CommandName"));
}

// Test the no-argument isCmd() returns true for objCmd type
TEST_F(ObjectIsCmdTest_90, CmdObject_IsCmdNoArgs_ReturnsTrue_90) {
    Object obj(objCmd, "test");
    EXPECT_TRUE(obj.isCmd());
}

// Test the no-argument isCmd() returns false for non-cmd type
TEST_F(ObjectIsCmdTest_90, NonCmdObject_IsCmdNoArgs_ReturnsFalse_90) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd());
}

// Test getCmd returns the correct command string
TEST_F(ObjectIsCmdTest_90, CmdObject_GetCmd_ReturnsCorrectString_90) {
    Object obj(objCmd, "testCmd");
    EXPECT_STREQ(obj.getCmd(), "testCmd");
}

// Test getType returns objCmd for a command object
TEST_F(ObjectIsCmdTest_90, CmdObject_GetType_ReturnsObjCmd_90) {
    Object obj(objCmd, "xyz");
    EXPECT_EQ(obj.getType(), objCmd);
}

// Test with single character command
TEST_F(ObjectIsCmdTest_90, CmdObjectSingleChar_MatchesSingleChar_90) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd("q"));
    EXPECT_FALSE(obj.isCmd("Q"));
    EXPECT_FALSE(obj.isCmd("qq"));
}

// Test with special characters in command string
TEST_F(ObjectIsCmdTest_90, CmdObjectSpecialChars_MatchesCorrectly_90) {
    Object obj(objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("bt"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// Test that int64 object returns false for isCmd
TEST_F(ObjectIsCmdTest_90, Int64Object_ReturnsFalse_90) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(obj.isCmd("123456789"));
}

// Test move-constructed cmd object still works correctly
TEST_F(ObjectIsCmdTest_90, MovedCmdObject_IsCmdStillWorks_90) {
    Object obj(objCmd, "moved");
    Object obj2(std::move(obj));
    EXPECT_TRUE(obj2.isCmd("moved"));
    EXPECT_FALSE(obj2.isCmd("notmoved"));
}

// Test move-assigned cmd object still works correctly
TEST_F(ObjectIsCmdTest_90, MoveAssignedCmdObject_IsCmdStillWorks_90) {
    Object obj(objCmd, "assigned");
    Object obj2;
    obj2 = std::move(obj);
    EXPECT_TRUE(obj2.isCmd("assigned"));
}
