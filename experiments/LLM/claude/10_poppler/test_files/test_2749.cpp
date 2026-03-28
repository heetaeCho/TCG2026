#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <string_view>
#include "Object.h"

// Test construction with objName type and string_view
TEST(ObjectConstructorTest_2749, ConstructWithObjNameAndStringView_2749) {
    std::string_view sv = "TestName";
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

// Test construction with objCmd type and string_view
TEST(ObjectConstructorTest_2749, ConstructWithObjCmdAndStringView_2749) {
    std::string_view sv = "TestCmd";
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

// Test construction with empty string_view for objName
TEST(ObjectConstructorTest_2749, ConstructWithObjNameAndEmptyStringView_2749) {
    std::string_view sv = "";
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "");
}

// Test construction with empty string_view for objCmd
TEST(ObjectConstructorTest_2749, ConstructWithObjCmdAndEmptyStringView_2749) {
    std::string_view sv = "";
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "");
}

// Test construction with a long string for objName
TEST(ObjectConstructorTest_2749, ConstructWithObjNameAndLongString_2749) {
    std::string longStr(1000, 'A');
    std::string_view sv(longStr);
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), longStr.c_str());
}

// Test construction with a long string for objCmd
TEST(ObjectConstructorTest_2749, ConstructWithObjCmdAndLongString_2749) {
    std::string longStr(1000, 'B');
    std::string_view sv(longStr);
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), longStr.c_str());
}

// Test that string is properly null-terminated (string_view with embedded data)
TEST(ObjectConstructorTest_2749, StringIsNullTerminated_2749) {
    const char data[] = "Hello";
    std::string_view sv(data, 5);
    Object obj(objName, sv);
    
    const char* name = obj.getName();
    EXPECT_EQ(strlen(name), 5u);
    EXPECT_STREQ(name, "Hello");
}

// Test construction from const char* (which converts to string_view)
TEST(ObjectConstructorTest_2749, ConstructWithObjNameAndConstCharPtr_2749) {
    Object obj(objName, "DirectCharPtr");
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "DirectCharPtr");
}

// Test construction from const char* for objCmd
TEST(ObjectConstructorTest_2749, ConstructWithObjCmdAndConstCharPtr_2749) {
    Object obj(objCmd, "CmdFromCharPtr");
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "CmdFromCharPtr");
}

// Test isName with matching name
TEST(ObjectConstructorTest_2749, IsNameWithMatchingString_2749) {
    Object obj(objName, "MatchMe");
    
    EXPECT_TRUE(obj.isName("MatchMe"));
    EXPECT_FALSE(obj.isName("NoMatch"));
}

// Test isCmd with matching command
TEST(ObjectConstructorTest_2749, IsCmdWithMatchingString_2749) {
    Object obj(objCmd, "DoSomething");
    
    EXPECT_TRUE(obj.isCmd("DoSomething"));
    EXPECT_FALSE(obj.isCmd("DoSomethingElse"));
}

// Test that objName is not a cmd and vice versa
TEST(ObjectConstructorTest_2749, ObjNameIsNotCmd_2749) {
    Object nameObj(objName, "Test");
    Object cmdObj(objCmd, "Test");
    
    EXPECT_TRUE(nameObj.isName());
    EXPECT_FALSE(nameObj.isCmd());
    
    EXPECT_TRUE(cmdObj.isCmd());
    EXPECT_FALSE(cmdObj.isName());
}

// Test type checking - objName should not be other types
TEST(ObjectConstructorTest_2749, ObjNameTypeChecks_2749) {
    Object obj(objName, "TypeCheck");
    
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isHexString());
}

// Test type checking - objCmd should not be other types
TEST(ObjectConstructorTest_2749, ObjCmdTypeChecks_2749) {
    Object obj(objCmd, "CmdTypeCheck");
    
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isHexString());
}

// Test getTypeName for objName
TEST(ObjectConstructorTest_2749, GetTypeNameForObjName_2749) {
    Object obj(objName, "SomeName");
    const char* typeName = obj.getTypeName();
    EXPECT_NE(typeName, nullptr);
}

// Test getTypeName for objCmd
TEST(ObjectConstructorTest_2749, GetTypeNameForObjCmd_2749) {
    Object obj(objCmd, "SomeCmd");
    const char* typeName = obj.getTypeName();
    EXPECT_NE(typeName, nullptr);
}

// Test move constructor
TEST(ObjectConstructorTest_2749, MoveConstructor_2749) {
    Object obj1(objName, "MovableName");
    Object obj2(std::move(obj1));
    
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "MovableName");
}

// Test move assignment
TEST(ObjectConstructorTest_2749, MoveAssignment_2749) {
    Object obj1(objName, "AssignableName");
    Object obj2;
    obj2 = std::move(obj1);
    
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "AssignableName");
}

// Test with string_view that is a substring (not null-terminated)
TEST(ObjectConstructorTest_2749, ConstructWithSubstringView_2749) {
    std::string full = "HelloWorld";
    std::string_view sv(full.data(), 5); // "Hello"
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Hello");
}

// Test construction with special characters
TEST(ObjectConstructorTest_2749, ConstructWithSpecialChars_2749) {
    Object obj(objName, "Name/With#Special@Chars");
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Name/With#Special@Chars");
}

// Test getNameString returns proper std::string
TEST(ObjectConstructorTest_2749, GetNameString_2749) {
    Object obj(objName, "StringName");
    
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "StringName");
}

// Test single character name
TEST(ObjectConstructorTest_2749, SingleCharacterName_2749) {
    Object obj(objName, "X");
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "X");
}

// Test single character command
TEST(ObjectConstructorTest_2749, SingleCharacterCmd_2749) {
    Object obj(objCmd, "Q");
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "Q");
}

// Test copy method
TEST(ObjectConstructorTest_2749, CopyMethod_2749) {
    Object obj(objName, "CopyMe");
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyMe");
}

// Test setToNull changes the type
TEST(ObjectConstructorTest_2749, SetToNullChangesType_2749) {
    Object obj(objName, "WillBeNull");
    obj.setToNull();
    
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isName());
}

// Test string with embedded whitespace
TEST(ObjectConstructorTest_2749, NameWithWhitespace_2749) {
    Object obj(objName, "Name With Spaces");
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Name With Spaces");
}

// Test isNum returns false for name type
TEST(ObjectConstructorTest_2749, IsNumReturnsFalseForName_2749) {
    Object obj(objName, "NotANumber");
    EXPECT_FALSE(obj.isNum());
    EXPECT_FALSE(obj.isIntOrInt64());
}
