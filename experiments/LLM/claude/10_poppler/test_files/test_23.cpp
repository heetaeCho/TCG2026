#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "GooString.h"

// Normal operation tests

TEST(GooStringTest_23, DefaultConstructor_23) {
    GooString str;
    EXPECT_EQ(str.toStr().size(), 0u);
    EXPECT_TRUE(str.toStr().empty());
}

TEST(GooStringTest_23, ConstructFromCString_23) {
    GooString str("hello");
    EXPECT_EQ(str.toStr(), "hello");
    EXPECT_EQ(str.toStr().size(), 5u);
}

TEST(GooStringTest_23, ConstructFromNullCString_23) {
    const char *nullStr = nullptr;
    GooString str(nullStr);
    EXPECT_EQ(str.toStr(), "");
    EXPECT_EQ(str.toStr().size(), 0u);
}

TEST(GooStringTest_23, ConstructFromStdString_23) {
    std::string s = "world";
    GooString str(s);
    EXPECT_EQ(str.toStr(), "world");
}

TEST(GooStringTest_23, ConstructFromStdStringMove_23) {
    std::string s = "moveable";
    GooString str(std::move(s));
    EXPECT_EQ(str.toStr(), "moveable");
}

TEST(GooStringTest_23, ConstructFromStringView_23) {
    std::string_view sv = "view_test";
    GooString str(sv);
    EXPECT_EQ(str.toStr(), "view_test");
}

TEST(GooStringTest_23, ConstructFromCStringWithLength_23) {
    GooString str("hello world", 5);
    EXPECT_EQ(str.toStr(), "hello");
    EXPECT_EQ(str.toStr().size(), 5u);
}

TEST(GooStringTest_23, ConstructFromNullCStringWithLength_23) {
    const char *nullStr = nullptr;
    GooString str(nullStr, 5);
    EXPECT_EQ(str.toStr(), "");
    EXPECT_EQ(str.toStr().size(), 0u);
}

TEST(GooStringTest_23, ConstructFromGooStringSubstring_23) {
    GooString original("hello world");
    GooString sub(&original, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST(GooStringTest_23, ConstructFromStdStringSubstring_23) {
    std::string s = "hello world";
    GooString sub(s, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST(GooStringTest_23, MoveConstructor_23) {
    GooString original("move me");
    GooString moved(std::move(original));
    EXPECT_EQ(moved.toStr(), "move me");
}

TEST(GooStringTest_23, MoveAssignment_23) {
    GooString original("assign me");
    GooString target;
    target = std::move(original);
    EXPECT_EQ(target.toStr(), "assign me");
}

TEST(GooStringTest_23, GetChar_23) {
    GooString str("abcde");
    EXPECT_EQ(str.getChar(0), 'a');
    EXPECT_EQ(str.getChar(1), 'b');
    EXPECT_EQ(str.getChar(2), 'c');
    EXPECT_EQ(str.getChar(3), 'd');
    EXPECT_EQ(str.getChar(4), 'e');
}

TEST(GooStringTest_23, SetChar_23) {
    GooString str("abcde");
    str.setChar(0, 'z');
    EXPECT_EQ(str.getChar(0), 'z');
    EXPECT_EQ(str.toStr(), "zbcde");
}

TEST(GooStringTest_23, SetCharMiddle_23) {
    GooString str("hello");
    str.setChar(2, 'X');
    EXPECT_EQ(str.toStr(), "heXlo");
}

TEST(GooStringTest_23, SetCharLast_23) {
    GooString str("hello");
    str.setChar(4, '!');
    EXPECT_EQ(str.toStr(), "hell!");
}

TEST(GooStringTest_23, ToStr_23) {
    GooString str("test");
    const std::string &ref = str.toStr();
    EXPECT_EQ(ref, "test");
}

TEST(GooStringTest_23, ToNonConstStr_23) {
    GooString str("mutable");
    std::string &ref = str.toNonConstStr();
    ref = "changed";
    EXPECT_EQ(str.toStr(), "changed");
}

TEST(GooStringTest_23, Copy_23) {
    GooString str("original");
    std::unique_ptr<GooString> copied = str.copy();
    EXPECT_EQ(copied->toStr(), "original");
    // Verify it's a deep copy
    copied->setChar(0, 'X');
    EXPECT_EQ(str.toStr(), "original");
    EXPECT_EQ(copied->toStr(), "Xriginal");
}

TEST(GooStringTest_23, CopyEmptyString_23) {
    GooString str;
    std::unique_ptr<GooString> copied = str.copy();
    EXPECT_EQ(copied->toStr(), "");
}

TEST(GooStringTest_23, LowerCase_23) {
    std::string s = "HELLO WORLD";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_23, LowerCaseAlreadyLower_23) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST(GooStringTest_23, LowerCaseMixed_23) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_23, LowerCaseEmpty_23) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST(GooStringTest_23, LowerCaseWithNumbers_23) {
    std::string s = "ABC123DEF";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "abc123def");
}

TEST(GooStringTest_23, ToLowerCaseStringView_23) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST(GooStringTest_23, ToLowerCaseEmptyStringView_23) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

TEST(GooStringTest_23, Format_23) {
    std::string result = GooString::format("{0:s}", "test");
    // We test that it returns a non-empty string; exact format depends on implementation
    EXPECT_FALSE(result.empty());
}

TEST(GooStringTest_23, Appendf_23) {
    GooString str("prefix ");
    GooString *ret = str.appendf("{0:s}", "suffix");
    EXPECT_EQ(ret, &str);
    // The string should have been appended to
    EXPECT_TRUE(str.toStr().size() > 7u);
}

// Boundary condition tests

TEST(GooStringTest_23, GetCharAtZeroIndex_23) {
    GooString str("x");
    EXPECT_EQ(str.getChar(0), 'x');
}

TEST(GooStringTest_23, SingleCharString_23) {
    GooString str("a");
    EXPECT_EQ(str.toStr().size(), 1u);
    EXPECT_EQ(str.getChar(0), 'a');
}

TEST(GooStringTest_23, SetCharOnSingleCharString_23) {
    GooString str("a");
    str.setChar(0, 'z');
    EXPECT_EQ(str.toStr(), "z");
}

TEST(GooStringTest_23, ConstructFromCStringWithZeroLength_23) {
    GooString str("hello", 0);
    EXPECT_EQ(str.toStr(), "");
    EXPECT_EQ(str.toStr().size(), 0u);
}

TEST(GooStringTest_23, ConstructFromGooStringSubstringZeroLength_23) {
    GooString original("hello");
    GooString sub(&original, 0, 0);
    EXPECT_EQ(sub.toStr(), "");
}

TEST(GooStringTest_23, ConstructFromStdStringSubstringZeroLength_23) {
    std::string s = "hello";
    GooString sub(s, 0, 0);
    EXPECT_EQ(sub.toStr(), "");
}

TEST(GooStringTest_23, NullByteInString_23) {
    std::string s("hel\0lo", 6);
    GooString str(s);
    EXPECT_EQ(str.toStr().size(), 6u);
    EXPECT_EQ(str.getChar(3), '\0');
}

TEST(GooStringTest_23, ToNonConstStrModify_23) {
    GooString str("abc");
    std::string &ref = str.toNonConstStr();
    ref += "def";
    EXPECT_EQ(str.toStr(), "abcdef");
    EXPECT_EQ(str.toStr().size(), 6u);
}

TEST(GooStringTest_23, SetCharWithNullByte_23) {
    GooString str("hello");
    str.setChar(2, '\0');
    EXPECT_EQ(str.getChar(2), '\0');
    EXPECT_EQ(str.toStr().size(), 5u);
}

TEST(GooStringTest_23, MoveConstructorLeavesSourceValid_23) {
    GooString original("test");
    GooString moved(std::move(original));
    EXPECT_EQ(moved.toStr(), "test");
    // After move, original should be in a valid but unspecified state
    // We just check it doesn't crash
    (void)original.toStr();
}

TEST(GooStringTest_23, MoveAssignmentLeavesSourceValid_23) {
    GooString original("test");
    GooString target;
    target = std::move(original);
    EXPECT_EQ(target.toStr(), "test");
    (void)original.toStr();
}

TEST(GooStringTest_23, LongString_23) {
    std::string longStr(10000, 'x');
    GooString str(longStr);
    EXPECT_EQ(str.toStr().size(), 10000u);
    EXPECT_EQ(str.getChar(0), 'x');
    EXPECT_EQ(str.getChar(9999), 'x');
}

TEST(GooStringTest_23, CopyPreservesContent_23) {
    std::string longStr(1000, 'A');
    GooString str(longStr);
    auto copied = str.copy();
    EXPECT_EQ(copied->toStr(), str.toStr());
    EXPECT_EQ(copied->toStr().size(), 1000u);
}
