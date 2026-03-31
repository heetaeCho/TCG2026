#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <cstring>

#include "Object.h"

// Test constructing an Object with objName type and string_view
TEST(ObjectStringViewConstructorTest_2758, ConstructObjNameWithStringView_2758) {
    std::string_view sv = "TestName";
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    EXPECT_STREQ(obj.getName(), "TestName");
}

// Test constructing an Object with objCmd type and string_view
TEST(ObjectStringViewConstructorTest_2758, ConstructObjCmdWithStringView_2758) {
    std::string_view sv = "TestCmd";
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    EXPECT_STREQ(obj.getCmd(), "TestCmd");
}

// Test constructing with an empty string_view for objName
TEST(ObjectStringViewConstructorTest_2758, ConstructObjNameWithEmptyStringView_2758) {
    std::string_view sv = "";
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

// Test constructing with an empty string_view for objCmd
TEST(ObjectStringViewConstructorTest_2758, ConstructObjCmdWithEmptyStringView_2758) {
    std::string_view sv = "";
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "");
}

// Test constructing with a long string for objName
TEST(ObjectStringViewConstructorTest_2758, ConstructObjNameWithLongString_2758) {
    std::string longStr(1000, 'A');
    std::string_view sv = longStr;
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), longStr.c_str());
}

// Test constructing with a long string for objCmd
TEST(ObjectStringViewConstructorTest_2758, ConstructObjCmdWithLongString_2758) {
    std::string longStr(1000, 'Z');
    std::string_view sv = longStr;
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), longStr.c_str());
}

// Test that objName is not confused with other types
TEST(ObjectStringViewConstructorTest_2758, ObjNameIsNotOtherTypes_2758) {
    Object obj(objName, std::string_view("Hello"));
    
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isName());
}

// Test that objCmd is not confused with other types
TEST(ObjectStringViewConstructorTest_2758, ObjCmdIsNotOtherTypes_2758) {
    Object obj(objCmd, std::string_view("SomeCommand"));
    
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_TRUE(obj.isCmd());
}

// Test isName with matching string_view
TEST(ObjectStringViewConstructorTest_2758, IsNameMatchesStringView_2758) {
    Object obj(objName, std::string_view("MyName"));
    
    EXPECT_TRUE(obj.isName("MyName"));
    EXPECT_FALSE(obj.isName("OtherName"));
}

// Test isCmd with matching string_view
TEST(ObjectStringViewConstructorTest_2758, IsCmdMatchesStringView_2758) {
    Object obj(objCmd, std::string_view("MyCmd"));
    
    EXPECT_TRUE(obj.isCmd("MyCmd"));
    EXPECT_FALSE(obj.isCmd("OtherCmd"));
}

// Test constructing with a string_view that has embedded content (no null in the middle for name)
TEST(ObjectStringViewConstructorTest_2758, ConstructObjNameWithSpecialChars_2758) {
    std::string_view sv = "Name/With#Special";
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Name/With#Special");
}

// Test getNameString returns correct string
TEST(ObjectStringViewConstructorTest_2758, GetNameStringReturnsCorrectValue_2758) {
    Object obj(objName, std::string_view("TestNameStr"));
    
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "TestNameStr");
}

// Test constructing from const char* (which delegates to string_view constructor)
TEST(ObjectStringViewConstructorTest_2758, ConstructFromConstCharPtr_2758) {
    const char* str = "FromCharPtr";
    Object obj(objName, str);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "FromCharPtr");
}

// Test constructing objCmd from const char*
TEST(ObjectStringViewConstructorTest_2758, ConstructCmdFromConstCharPtr_2758) {
    const char* str = "CmdFromCharPtr";
    Object obj(objCmd, str);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "CmdFromCharPtr");
}

// Test move constructor preserves name
TEST(ObjectStringViewConstructorTest_2758, MoveConstructorPreservesName_2758) {
    Object obj1(objName, std::string_view("MoveName"));
    Object obj2(std::move(obj1));
    
    EXPECT_TRUE(obj2.isName());
    EXPECT_STREQ(obj2.getName(), "MoveName");
}

// Test move assignment preserves cmd
TEST(ObjectStringViewConstructorTest_2758, MoveAssignmentPreservesCmd_2758) {
    Object obj1(objCmd, std::string_view("MoveCmd"));
    Object obj2;
    obj2 = std::move(obj1);
    
    EXPECT_TRUE(obj2.isCmd());
    EXPECT_STREQ(obj2.getCmd(), "MoveCmd");
}

// Test getTypeName for objName
TEST(ObjectStringViewConstructorTest_2758, GetTypeNameForObjName_2758) {
    Object obj(objName, std::string_view("SomeName"));
    
    const char* typeName = obj.getTypeName();
    EXPECT_NE(typeName, nullptr);
}

// Test getTypeName for objCmd
TEST(ObjectStringViewConstructorTest_2758, GetTypeNameForObjCmd_2758) {
    Object obj(objCmd, std::string_view("SomeCmd"));
    
    const char* typeName = obj.getTypeName();
    EXPECT_NE(typeName, nullptr);
}

// Test single character name
TEST(ObjectStringViewConstructorTest_2758, SingleCharacterName_2758) {
    Object obj(objName, std::string_view("X"));
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "X");
}

// Test single character command
TEST(ObjectStringViewConstructorTest_2758, SingleCharacterCmd_2758) {
    Object obj(objCmd, std::string_view("Y"));
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "Y");
}

// Test that copy() works for name object
TEST(ObjectStringViewConstructorTest_2758, CopyWorksForNameObject_2758) {
    Object obj(objName, std::string_view("CopyMe"));
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyMe");
}

// Test that copy() works for cmd object
TEST(ObjectStringViewConstructorTest_2758, CopyWorksForCmdObject_2758) {
    Object obj(objCmd, std::string_view("CopyCmd"));
    Object copied = obj.copy();
    
    EXPECT_TRUE(copied.isCmd());
    EXPECT_STREQ(copied.getCmd(), "CopyCmd");
}

// Test setToNull changes type
TEST(ObjectStringViewConstructorTest_2758, SetToNullChangesType_2758) {
    Object obj(objName, std::string_view("WillBeNull"));
    obj.setToNull();
    
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isName());
}

// Test string_view from substring (not null-terminated)
TEST(ObjectStringViewConstructorTest_2758, StringViewFromSubstring_2758) {
    std::string fullStr = "HelloWorld";
    std::string_view sv(fullStr.data(), 5); // "Hello"
    Object obj(objName, sv);
    
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "Hello");
}

// Test string_view from substring for cmd
TEST(ObjectStringViewConstructorTest_2758, StringViewFromSubstringCmd_2758) {
    std::string fullStr = "CmdExtra";
    std::string_view sv(fullStr.data(), 3); // "Cmd"
    Object obj(objCmd, sv);
    
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "Cmd");
}

// Test destruction doesn't cause issues (implicit - no crash)
TEST(ObjectStringViewConstructorTest_2758, DestructionDoesNotCrash_2758) {
    {
        Object obj(objName, std::string_view("Temporary"));
        EXPECT_TRUE(obj.isName());
    }
    // If we reach here, destruction was successful
    SUCCEED();
}

// Test multiple objects can coexist
TEST(ObjectStringViewConstructorTest_2758, MultipleObjectsCoexist_2758) {
    Object name1(objName, std::string_view("Name1"));
    Object name2(objName, std::string_view("Name2"));
    Object cmd1(objCmd, std::string_view("Cmd1"));
    
    EXPECT_STREQ(name1.getName(), "Name1");
    EXPECT_STREQ(name2.getName(), "Name2");
    EXPECT_STREQ(cmd1.getCmd(), "Cmd1");
}
