#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <cstring>
#include "GooString.h"

// Test default constructor
TEST(GooStringTest_20, DefaultConstructor_20) {
    GooString str;
    EXPECT_EQ(str.toStr(), "");
    EXPECT_EQ(str.toStr().size(), 0u);
}

// Test constructor from const char*
TEST(GooStringTest_20, ConstructFromCString_20) {
    GooString str("hello");
    EXPECT_EQ(str.toStr(), "hello");
    EXPECT_EQ(str.toStr().size(), 5u);
}

// Test constructor from nullptr const char* (should result in empty string)
TEST(GooStringTest_20, ConstructFromNullCString_20) {
    const char* nullStr = nullptr;
    GooString str(nullStr);
    EXPECT_EQ(str.toStr(), "");
}

// Test constructor from std::string
TEST(GooStringTest_20, ConstructFromStdString_20) {
    std::string s = "world";
    GooString str(s);
    EXPECT_EQ(str.toStr(), "world");
}

// Test constructor from std::string rvalue
TEST(GooStringTest_20, ConstructFromStdStringRvalue_20) {
    std::string s = "moved";
    GooString str(std::move(s));
    EXPECT_EQ(str.toStr(), "moved");
}

// Test constructor from const char* with length
TEST(GooStringTest_20, ConstructFromCStringWithLength_20) {
    GooString str("hello world", 5);
    EXPECT_EQ(str.toStr(), "hello");
    EXPECT_EQ(str.toStr().size(), 5u);
}

// Test constructor from null const char* with length
TEST(GooStringTest_20, ConstructFromNullCStringWithLength_20) {
    const char* nullStr = nullptr;
    GooString str(nullStr, 5);
    EXPECT_EQ(str.toStr(), "");
}

// Test constructor from string_view
TEST(GooStringTest_20, ConstructFromStringView_20) {
    std::string_view sv = "string_view_test";
    GooString str(sv);
    EXPECT_EQ(str.toStr(), "string_view_test");
}

// Test constructor from GooString* with index and length
TEST(GooStringTest_20, ConstructFromGooStringPtrSubstring_20) {
    GooString original("hello world");
    GooString str(&original, 6, 5);
    EXPECT_EQ(str.toStr(), "world");
}

// Test constructor from std::string with index and length
TEST(GooStringTest_20, ConstructFromStdStringSubstring_20) {
    std::string original = "hello world";
    GooString str(original, 6, 5);
    EXPECT_EQ(str.toStr(), "world");
}

// Test move constructor
TEST(GooStringTest_20, MoveConstructor_20) {
    GooString original("moveable");
    GooString str(std::move(original));
    EXPECT_EQ(str.toStr(), "moveable");
}

// Test move assignment
TEST(GooStringTest_20, MoveAssignment_20) {
    GooString original("assign_me");
    GooString str;
    str = std::move(original);
    EXPECT_EQ(str.toStr(), "assign_me");
}

// Test toStr() returns correct const reference
TEST(GooStringTest_20, ToStrReturnsConstRef_20) {
    GooString str("test");
    const std::string& ref = str.toStr();
    EXPECT_EQ(ref, "test");
}

// Test toNonConstStr() returns modifiable reference
TEST(GooStringTest_20, ToNonConstStr_20) {
    GooString str("mutable");
    std::string& ref = str.toNonConstStr();
    ref = "changed";
    EXPECT_EQ(str.toStr(), "changed");
}

// Test copy()
TEST(GooStringTest_20, CopyCreatesNewInstance_20) {
    GooString str("copyable");
    std::unique_ptr<GooString> copied = str.copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_EQ(copied->toStr(), "copyable");
    // Ensure it's a separate copy
    copied->toNonConstStr() = "modified";
    EXPECT_EQ(str.toStr(), "copyable");
    EXPECT_EQ(copied->toStr(), "modified");
}

// Test getChar
TEST(GooStringTest_20, GetChar_20) {
    GooString str("abcdef");
    EXPECT_EQ(str.getChar(0), 'a');
    EXPECT_EQ(str.getChar(3), 'd');
    EXPECT_EQ(str.getChar(5), 'f');
}

// Test setChar
TEST(GooStringTest_20, SetChar_20) {
    GooString str("hello");
    str.setChar(0, 'H');
    EXPECT_EQ(str.getChar(0), 'H');
    EXPECT_EQ(str.toStr(), "Hello");
}

// Test setChar at various positions
TEST(GooStringTest_20, SetCharMultiplePositions_20) {
    GooString str("abcde");
    str.setChar(0, 'A');
    str.setChar(4, 'E');
    EXPECT_EQ(str.toStr(), "AbcdE");
}

// Test format static method with simple string
TEST(GooStringTest_20, FormatSimpleString_20) {
    std::string result = GooString::format("hello");
    EXPECT_EQ(result, "hello");
}

// Test format with formatted arguments
TEST(GooStringTest_20, FormatWithArguments_20) {
    std::string result = GooString::format("{0:s}", "world");
    // The exact format depends on implementation, but we test it doesn't crash
    EXPECT_FALSE(result.empty());
}

// Test appendf
TEST(GooStringTest_20, Appendf_20) {
    GooString str("prefix");
    GooString* ret = str.appendf("_suffix");
    EXPECT_EQ(ret, &str);
    EXPECT_NE(str.toStr().find("prefix"), std::string::npos);
}

// Test lowerCase static method
TEST(GooStringTest_20, LowerCase_20) {
    std::string s = "HELLO WORLD";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

// Test lowerCase with already lowercase
TEST(GooStringTest_20, LowerCaseAlreadyLower_20) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

// Test lowerCase with mixed case
TEST(GooStringTest_20, LowerCaseMixed_20) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

// Test lowerCase with empty string
TEST(GooStringTest_20, LowerCaseEmpty_20) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

// Test toLowerCase static method (string_view version)
TEST(GooStringTest_20, ToLowerCaseStringView_20) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

// Test toLowerCase with empty string_view
TEST(GooStringTest_20, ToLowerCaseEmptyStringView_20) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

// Test lowerCase with numbers and special characters (should remain unchanged)
TEST(GooStringTest_20, LowerCaseWithNumbersAndSpecialChars_20) {
    std::string s = "HELLO123!@#";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello123!@#");
}

// Test empty string operations
TEST(GooStringTest_20, EmptyStringOperations_20) {
    GooString str("");
    EXPECT_EQ(str.toStr(), "");
    EXPECT_EQ(str.toStr().size(), 0u);
    std::unique_ptr<GooString> copied = str.copy();
    EXPECT_EQ(copied->toStr(), "");
}

// Test string with embedded null characters via length constructor
TEST(GooStringTest_20, StringWithEmbeddedNull_20) {
    const char data[] = "he\0lo";
    GooString str(data, 5);
    EXPECT_EQ(str.toStr().size(), 5u);
}

// Test copy of empty string
TEST(GooStringTest_20, CopyEmptyString_20) {
    GooString str;
    auto copied = str.copy();
    EXPECT_NE(copied, nullptr);
    EXPECT_EQ(copied->toStr(), "");
}

// Test getChar boundary - first and last character
TEST(GooStringTest_20, GetCharBoundary_20) {
    GooString str("x");
    EXPECT_EQ(str.getChar(0), 'x');
}

// Test setChar on single character string
TEST(GooStringTest_20, SetCharSingleChar_20) {
    GooString str("a");
    str.setChar(0, 'z');
    EXPECT_EQ(str.toStr(), "z");
}

// Test long string
TEST(GooStringTest_20, LongString_20) {
    std::string longStr(10000, 'a');
    GooString str(longStr);
    EXPECT_EQ(str.toStr().size(), 10000u);
    EXPECT_EQ(str.getChar(0), 'a');
    EXPECT_EQ(str.getChar(9999), 'a');
}

// Test substring from beginning
TEST(GooStringTest_20, SubstringFromBeginning_20) {
    GooString original("hello world");
    GooString str(&original, 0, 5);
    EXPECT_EQ(str.toStr(), "hello");
}

// Test substring of length zero
TEST(GooStringTest_20, SubstringZeroLength_20) {
    GooString original("hello");
    GooString str(&original, 0, 0);
    EXPECT_EQ(str.toStr(), "");
}

// Test format with empty string
TEST(GooStringTest_20, FormatEmptyString_20) {
    std::string result = GooString::format("");
    EXPECT_EQ(result, "");
}

// Test toNonConstStr modification reflected in toStr
TEST(GooStringTest_20, ToNonConstStrModification_20) {
    GooString str("original");
    str.toNonConstStr().append("_appended");
    EXPECT_EQ(str.toStr(), "original_appended");
}

// Test toLowerCase with int argument
TEST(GooStringTest_20, ToLowerCaseInt_20) {
    // 'A' = 65
    std::string result = GooString::toLowerCase(static_cast<int>('A'));
    EXPECT_FALSE(result.empty());
}
