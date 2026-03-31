#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <cstring>
#include "GooString.h"

// ===== Construction Tests =====

TEST(GooStringTest_21, DefaultConstruction_21) {
    GooString s;
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_21, ConstructFromCString_21) {
    GooString s("hello");
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST(GooStringTest_21, ConstructFromNullCString_21) {
    const char *nullStr = nullptr;
    GooString s(nullStr);
    EXPECT_EQ(s.toStr(), "");
}

TEST(GooStringTest_21, ConstructFromEmptyCString_21) {
    GooString s("");
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_21, ConstructFromStdString_21) {
    std::string str("world");
    GooString s(str);
    EXPECT_EQ(s.toStr(), "world");
}

TEST(GooStringTest_21, ConstructFromStdStringMove_21) {
    std::string str("movable");
    GooString s(std::move(str));
    EXPECT_EQ(s.toStr(), "movable");
}

TEST(GooStringTest_21, ConstructFromStringView_21) {
    std::string_view sv("view_test");
    GooString s(sv);
    EXPECT_EQ(s.toStr(), "view_test");
}

TEST(GooStringTest_21, ConstructFromCStringWithLength_21) {
    GooString s("hello world", 5);
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST(GooStringTest_21, ConstructFromNullCStringWithLength_21) {
    const char *nullStr = nullptr;
    GooString s(nullStr, 5);
    EXPECT_EQ(s.toStr(), "");
}

TEST(GooStringTest_21, ConstructFromCStringWithZeroLength_21) {
    GooString s("hello", 0);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_21, ConstructFromGooStringSubstring_21) {
    GooString original("hello world");
    GooString s(&original, 6, 5);
    EXPECT_EQ(s.toStr(), "world");
}

TEST(GooStringTest_21, ConstructFromStdStringSubstring_21) {
    std::string original("hello world");
    GooString s(original, 6, 5);
    EXPECT_EQ(s.toStr(), "world");
}

TEST(GooStringTest_21, MoveConstruction_21) {
    GooString original("move_me");
    GooString moved(std::move(original));
    EXPECT_EQ(moved.toStr(), "move_me");
}

TEST(GooStringTest_21, MoveAssignment_21) {
    GooString original("assign_me");
    GooString target;
    target = std::move(original);
    EXPECT_EQ(target.toStr(), "assign_me");
}

// ===== toStr and toNonConstStr Tests =====

TEST(GooStringTest_21, ToStrReturnsConstRef_21) {
    GooString s("test");
    const std::string &ref = s.toStr();
    EXPECT_EQ(ref, "test");
}

TEST(GooStringTest_21, ToNonConstStrAllowsModification_21) {
    GooString s("test");
    std::string &ref = s.toNonConstStr();
    ref = "modified";
    EXPECT_EQ(s.toStr(), "modified");
}

// ===== getChar and setChar Tests =====

TEST(GooStringTest_21, GetCharAtValidIndex_21) {
    GooString s("abc");
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(1), 'b');
    EXPECT_EQ(s.getChar(2), 'c');
}

TEST(GooStringTest_21, SetCharAtValidIndex_21) {
    GooString s("abc");
    s.setChar(1, 'x');
    EXPECT_EQ(s.getChar(1), 'x');
    EXPECT_EQ(s.toStr(), "axc");
}

TEST(GooStringTest_21, SetCharFirstPosition_21) {
    GooString s("abc");
    s.setChar(0, 'z');
    EXPECT_EQ(s.toStr(), "zbc");
}

TEST(GooStringTest_21, SetCharLastPosition_21) {
    GooString s("abc");
    s.setChar(2, 'z');
    EXPECT_EQ(s.toStr(), "abz");
}

// ===== copy Tests =====

TEST(GooStringTest_21, CopyCreatesIndependentObject_21) {
    GooString s("original");
    std::unique_ptr<GooString> c = s.copy();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->toStr(), "original");
    // Modify copy, original should be unchanged
    c->setChar(0, 'X');
    EXPECT_EQ(s.toStr(), "original");
    EXPECT_EQ(c->toStr(), "Xriginal");
}

TEST(GooStringTest_21, CopyEmptyString_21) {
    GooString s;
    std::unique_ptr<GooString> c = s.copy();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->toStr(), "");
}

// ===== format Tests =====

TEST(GooStringTest_21, FormatSimpleString_21) {
    std::string result = GooString::format("{0:s}", "hello");
    // We test that at least the function returns something; exact format depends on implementation
    EXPECT_FALSE(result.empty());
}

// ===== appendf Tests =====

TEST(GooStringTest_21, AppendfReturnsSelf_21) {
    GooString s("start");
    GooString *ret = s.appendf("{0:s}", " end");
    EXPECT_EQ(ret, &s);
    // The string should have been appended to
    EXPECT_NE(s.toStr(), "start");
}

// ===== lowerCase Tests =====

TEST(GooStringTest_21, LowerCaseInPlace_21) {
    std::string s = "HELLO WORLD";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_21, LowerCaseAlreadyLower_21) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST(GooStringTest_21, LowerCaseEmptyString_21) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST(GooStringTest_21, LowerCaseMixedCase_21) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_21, LowerCaseWithNumbers_21) {
    std::string s = "ABC123DEF";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "abc123def");
}

// ===== toLowerCase (string_view) Tests =====

TEST(GooStringTest_21, ToLowerCaseStringView_21) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST(GooStringTest_21, ToLowerCaseStringViewEmpty_21) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

TEST(GooStringTest_21, ToLowerCaseStringViewMixed_21) {
    std::string result = GooString::toLowerCase(std::string_view("AbCdEf"));
    EXPECT_EQ(result, "abcdef");
}

// ===== Boundary Tests =====

TEST(GooStringTest_21, SingleCharacterString_21) {
    GooString s("X");
    EXPECT_EQ(s.toStr().size(), 1u);
    EXPECT_EQ(s.getChar(0), 'X');
    s.setChar(0, 'Y');
    EXPECT_EQ(s.getChar(0), 'Y');
}

TEST(GooStringTest_21, LongString_21) {
    std::string longStr(10000, 'a');
    GooString s(longStr);
    EXPECT_EQ(s.toStr().size(), 10000u);
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(9999), 'a');
}

TEST(GooStringTest_21, StringWithNullBytes_21) {
    std::string withNull("he\0lo", 5);
    GooString s(withNull);
    EXPECT_EQ(s.toStr().size(), 5u);
    EXPECT_EQ(s.getChar(2), '\0');
}

TEST(GooStringTest_21, SubstringFromBeginning_21) {
    GooString original("hello world");
    GooString s(&original, 0, 5);
    EXPECT_EQ(s.toStr(), "hello");
}

TEST(GooStringTest_21, SubstringZeroLength_21) {
    GooString original("hello world");
    GooString s(&original, 5, 0);
    EXPECT_EQ(s.toStr(), "");
}

// ===== Interaction between toNonConstStr and other methods =====

TEST(GooStringTest_21, ToNonConstStrReflectsInToStr_21) {
    GooString s("initial");
    s.toNonConstStr().append("_appended");
    EXPECT_EQ(s.toStr(), "initial_appended");
}

TEST(GooStringTest_21, ToNonConstStrClearString_21) {
    GooString s("something");
    s.toNonConstStr().clear();
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}
