#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "GooString.h"

// Normal operation tests

TEST(GooStringTest_22, DefaultConstructor_22) {
    GooString s;
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_22, ConstructFromCString_22) {
    GooString s("hello");
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST(GooStringTest_22, ConstructFromStdString_22) {
    std::string str = "world";
    GooString s(str);
    EXPECT_EQ(s.toStr(), "world");
}

TEST(GooStringTest_22, ConstructFromStdStringRvalue_22) {
    std::string str = "moved";
    GooString s(std::move(str));
    EXPECT_EQ(s.toStr(), "moved");
}

TEST(GooStringTest_22, ConstructFromStringView_22) {
    std::string_view sv = "view_string";
    GooString s(sv);
    EXPECT_EQ(s.toStr(), "view_string");
}

TEST(GooStringTest_22, ConstructFromCStringWithLength_22) {
    GooString s("hello world", 5);
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST(GooStringTest_22, ConstructFromGooStringSubstring_22) {
    GooString original("hello world");
    GooString sub(&original, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST(GooStringTest_22, ConstructFromStdStringSubstring_22) {
    std::string original = "hello world";
    GooString sub(original, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST(GooStringTest_22, MoveConstructor_22) {
    GooString original("moveable");
    GooString moved(std::move(original));
    EXPECT_EQ(moved.toStr(), "moveable");
}

TEST(GooStringTest_22, MoveAssignment_22) {
    GooString original("assign_me");
    GooString target;
    target = std::move(original);
    EXPECT_EQ(target.toStr(), "assign_me");
}

TEST(GooStringTest_22, CopyMethod_22) {
    GooString original("copy_me");
    std::unique_ptr<GooString> copied = original.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->toStr(), "copy_me");
    EXPECT_EQ(copied->toStr(), original.toStr());
}

TEST(GooStringTest_22, CopyMethodEmptyString_22) {
    GooString original;
    std::unique_ptr<GooString> copied = original.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->toStr(), "");
}

TEST(GooStringTest_22, GetChar_22) {
    GooString s("abcdef");
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(3), 'd');
    EXPECT_EQ(s.getChar(5), 'f');
}

TEST(GooStringTest_22, SetChar_22) {
    GooString s("abcdef");
    s.setChar(0, 'z');
    EXPECT_EQ(s.getChar(0), 'z');
    EXPECT_EQ(s.toStr(), "zbcdef");
}

TEST(GooStringTest_22, SetCharMiddle_22) {
    GooString s("hello");
    s.setChar(2, 'X');
    EXPECT_EQ(s.toStr(), "heXlo");
}

TEST(GooStringTest_22, ToNonConstStr_22) {
    GooString s("mutable");
    std::string &ref = s.toNonConstStr();
    ref += "_appended";
    EXPECT_EQ(s.toStr(), "mutable_appended");
}

TEST(GooStringTest_22, ToStrConst_22) {
    const GooString s("const_string");
    const std::string &ref = s.toStr();
    EXPECT_EQ(ref, "const_string");
}

// Boundary condition tests

TEST(GooStringTest_22, ConstructFromNullCString_22) {
    GooString s(static_cast<const char *>(nullptr));
    EXPECT_EQ(s.toStr(), "");
}

TEST(GooStringTest_22, ConstructFromNullCStringWithLength_22) {
    GooString s(static_cast<const char *>(nullptr), 5);
    EXPECT_EQ(s.toStr(), "");
}

TEST(GooStringTest_22, ConstructFromEmptyCString_22) {
    GooString s("");
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_22, ConstructFromCStringZeroLength_22) {
    GooString s("hello", 0);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_22, SubstringZeroLength_22) {
    GooString original("hello");
    GooString sub(&original, 0, 0);
    EXPECT_EQ(sub.toStr(), "");
}

TEST(GooStringTest_22, SubstringFromBeginning_22) {
    GooString original("hello");
    GooString sub(&original, 0, 5);
    EXPECT_EQ(sub.toStr(), "hello");
}

TEST(GooStringTest_22, GetCharFirstAndLast_22) {
    GooString s("AB");
    EXPECT_EQ(s.getChar(0), 'A');
    EXPECT_EQ(s.getChar(1), 'B');
}

TEST(GooStringTest_22, SetCharFirstPosition_22) {
    GooString s("A");
    s.setChar(0, 'Z');
    EXPECT_EQ(s.getChar(0), 'Z');
    EXPECT_EQ(s.toStr(), "Z");
}

// Static method tests

TEST(GooStringTest_22, LowerCaseInPlace_22) {
    std::string s = "HELLO WORLD";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_22, LowerCaseAlreadyLower_22) {
    std::string s = "already lower";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "already lower");
}

TEST(GooStringTest_22, LowerCaseEmpty_22) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST(GooStringTest_22, LowerCaseMixedCase_22) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_22, ToLowerCaseStringView_22) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST(GooStringTest_22, ToLowerCaseStringViewEmpty_22) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

TEST(GooStringTest_22, ToLowerCaseWithNumbers_22) {
    std::string s = "ABC123DEF";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "abc123def");
}

// Test copy independence (modifying copy doesn't affect original)
TEST(GooStringTest_22, CopyIndependence_22) {
    GooString original("original");
    std::unique_ptr<GooString> copied = original.copy();
    copied->setChar(0, 'X');
    EXPECT_EQ(original.toStr(), "original");
    EXPECT_EQ(copied->toStr(), "Xriginal");
}

// Test with special characters
TEST(GooStringTest_22, SpecialCharacters_22) {
    GooString s("hello\nworld\t!");
    EXPECT_EQ(s.toStr(), "hello\nworld\t!");
    EXPECT_EQ(s.toStr().size(), 13u);
}

TEST(GooStringTest_22, NullByteInString_22) {
    std::string str("hel\0lo", 6);
    GooString s(str);
    EXPECT_EQ(s.toStr().size(), 6u);
}

// Test appendf
TEST(GooStringTest_22, Appendf_22) {
    GooString s("prefix_");
    GooString *result = s.appendf("{0:s}", "suffix");
    EXPECT_EQ(result, &s);
    // The string should have been modified
    EXPECT_NE(s.toStr(), "prefix_");
}

// Test format static method
TEST(GooStringTest_22, FormatBasic_22) {
    std::string result = GooString::format("{0:d}", 42);
    EXPECT_FALSE(result.empty());
}

// Long string test
TEST(GooStringTest_22, LongString_22) {
    std::string longStr(10000, 'x');
    GooString s(longStr);
    EXPECT_EQ(s.toStr().size(), 10000u);
    EXPECT_EQ(s.getChar(0), 'x');
    EXPECT_EQ(s.getChar(9999), 'x');
}

TEST(GooStringTest_22, CopyLongString_22) {
    std::string longStr(10000, 'y');
    GooString s(longStr);
    auto copied = s.copy();
    EXPECT_EQ(copied->toStr(), s.toStr());
    EXPECT_EQ(copied->toStr().size(), 10000u);
}
