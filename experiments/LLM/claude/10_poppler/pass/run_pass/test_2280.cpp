#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "GooString.h"

// Test fixture for GooString tests
class GooStringTest_2280 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Constructor Tests ===

TEST_F(GooStringTest_2280, DefaultConstructor_2280) {
    GooString s;
    EXPECT_EQ(s.toStr().size(), 0u);
    EXPECT_TRUE(s.toStr().empty());
}

TEST_F(GooStringTest_2280, ConstructFromCString_2280) {
    GooString s("hello");
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST_F(GooStringTest_2280, ConstructFromNullCString_2280) {
    const char* nullStr = nullptr;
    GooString s(nullStr);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2280, ConstructFromStdString_2280) {
    std::string str = "world";
    GooString s(str);
    EXPECT_EQ(s.toStr(), "world");
}

TEST_F(GooStringTest_2280, ConstructFromStdStringMove_2280) {
    std::string str = "moveable";
    GooString s(std::move(str));
    EXPECT_EQ(s.toStr(), "moveable");
}

TEST_F(GooStringTest_2280, ConstructFromStringView_2280) {
    std::string_view sv = "view_test";
    GooString s(sv);
    EXPECT_EQ(s.toStr(), "view_test");
}

TEST_F(GooStringTest_2280, ConstructFromCStringWithLength_2280) {
    GooString s("hello world", 5);
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST_F(GooStringTest_2280, ConstructFromNullCStringWithLength_2280) {
    const char* nullStr = nullptr;
    GooString s(nullStr, 5);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2280, ConstructFromCStringWithZeroLength_2280) {
    GooString s("hello", 0);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2280, ConstructFromGooStringSubstring_2280) {
    GooString original("hello world");
    GooString s(&original, 6, 5);
    EXPECT_EQ(s.toStr(), "world");
}

TEST_F(GooStringTest_2280, ConstructFromStdStringSubstring_2280) {
    std::string str = "hello world";
    GooString s(str, 0, 5);
    EXPECT_EQ(s.toStr(), "hello");
}

TEST_F(GooStringTest_2280, MoveConstructor_2280) {
    GooString original("move me");
    GooString s(std::move(original));
    EXPECT_EQ(s.toStr(), "move me");
}

// === getChar Tests ===

TEST_F(GooStringTest_2280, GetCharFirstIndex_2280) {
    GooString s("abc");
    EXPECT_EQ(s.getChar(0), 'a');
}

TEST_F(GooStringTest_2280, GetCharMiddleIndex_2280) {
    GooString s("abc");
    EXPECT_EQ(s.getChar(1), 'b');
}

TEST_F(GooStringTest_2280, GetCharLastIndex_2280) {
    GooString s("abc");
    EXPECT_EQ(s.getChar(2), 'c');
}

TEST_F(GooStringTest_2280, GetCharSingleCharString_2280) {
    GooString s("X");
    EXPECT_EQ(s.getChar(0), 'X');
}

TEST_F(GooStringTest_2280, GetCharNullByte_2280) {
    GooString s(std::string("a\0b", 3));
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(1), '\0');
    EXPECT_EQ(s.getChar(2), 'b');
}

// === setChar Tests ===

TEST_F(GooStringTest_2280, SetCharFirstIndex_2280) {
    GooString s("abc");
    s.setChar(0, 'X');
    EXPECT_EQ(s.getChar(0), 'X');
    EXPECT_EQ(s.toStr(), "Xbc");
}

TEST_F(GooStringTest_2280, SetCharMiddleIndex_2280) {
    GooString s("abc");
    s.setChar(1, 'Y');
    EXPECT_EQ(s.getChar(1), 'Y');
    EXPECT_EQ(s.toStr(), "aYc");
}

TEST_F(GooStringTest_2280, SetCharLastIndex_2280) {
    GooString s("abc");
    s.setChar(2, 'Z');
    EXPECT_EQ(s.getChar(2), 'Z');
    EXPECT_EQ(s.toStr(), "abZ");
}

TEST_F(GooStringTest_2280, SetCharToNullByte_2280) {
    GooString s("abc");
    s.setChar(1, '\0');
    EXPECT_EQ(s.getChar(1), '\0');
    EXPECT_EQ(s.toStr().size(), 3u);
}

// === toStr / toNonConstStr Tests ===

TEST_F(GooStringTest_2280, ToStrReturnsConstRef_2280) {
    GooString s("test");
    const std::string& ref = s.toStr();
    EXPECT_EQ(ref, "test");
}

TEST_F(GooStringTest_2280, ToNonConstStrAllowsModification_2280) {
    GooString s("test");
    std::string& ref = s.toNonConstStr();
    ref += "_modified";
    EXPECT_EQ(s.toStr(), "test_modified");
}

// === copy Tests ===

TEST_F(GooStringTest_2280, CopyCreatesIndependentCopy_2280) {
    GooString s("original");
    auto copied = s.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->toStr(), "original");
    // Verify independence
    copied->setChar(0, 'X');
    EXPECT_EQ(s.toStr(), "original");
    EXPECT_EQ(copied->getChar(0), 'X');
}

TEST_F(GooStringTest_2280, CopyEmptyString_2280) {
    GooString s;
    auto copied = s.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->toStr(), "");
}

// === Move Assignment Tests ===

TEST_F(GooStringTest_2280, MoveAssignment_2280) {
    GooString s1("first");
    GooString s2("second");
    s1 = std::move(s2);
    EXPECT_EQ(s1.toStr(), "second");
}

// === format Tests ===

TEST_F(GooStringTest_2280, FormatSimpleString_2280) {
    std::string result = GooString::format("{0:s}", "hello");
    // format uses poppler-specific format strings; test basic usage
    // If this uses a different format convention, we check it doesn't crash
    EXPECT_FALSE(result.empty());
}

// === appendf Tests ===

TEST_F(GooStringTest_2280, AppendfBasic_2280) {
    GooString s("prefix");
    s.appendf("{0:s}", "suffix");
    // Verify the string was appended (starts with prefix)
    EXPECT_TRUE(s.toStr().find("prefix") == 0);
    EXPECT_GT(s.toStr().size(), 6u);
}

// === lowerCase Tests ===

TEST_F(GooStringTest_2280, LowerCaseInPlace_2280) {
    std::string s = "HELLO";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_2280, LowerCaseAlreadyLower_2280) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_2280, LowerCaseMixed_2280) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST_F(GooStringTest_2280, LowerCaseEmptyString_2280) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST_F(GooStringTest_2280, LowerCaseNumbers_2280) {
    std::string s = "ABC123";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "abc123");
}

// === toLowerCase (string_view) Tests ===

TEST_F(GooStringTest_2280, ToLowerCaseStringView_2280) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST_F(GooStringTest_2280, ToLowerCaseStringViewEmpty_2280) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

// === Boundary / Special Cases ===

TEST_F(GooStringTest_2280, ConstructLongString_2280) {
    std::string longStr(10000, 'a');
    GooString s(longStr);
    EXPECT_EQ(s.toStr().size(), 10000u);
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(9999), 'a');
}

TEST_F(GooStringTest_2280, SetCharOverEntireString_2280) {
    GooString s("abcdef");
    for (size_t i = 0; i < s.toStr().size(); ++i) {
        s.setChar(i, 'x');
    }
    EXPECT_EQ(s.toStr(), "xxxxxx");
}

TEST_F(GooStringTest_2280, GetCharWithSpecialCharacters_2280) {
    GooString s("\t\n\r");
    EXPECT_EQ(s.getChar(0), '\t');
    EXPECT_EQ(s.getChar(1), '\n');
    EXPECT_EQ(s.getChar(2), '\r');
}

TEST_F(GooStringTest_2280, SubstringFromBeginning_2280) {
    GooString original("abcdef");
    GooString s(&original, 0, 3);
    EXPECT_EQ(s.toStr(), "abc");
}

TEST_F(GooStringTest_2280, SubstringZeroLength_2280) {
    GooString original("abcdef");
    GooString s(&original, 3, 0);
    EXPECT_EQ(s.toStr(), "");
}

TEST_F(GooStringTest_2280, CStringWithExactLength_2280) {
    GooString s("exact", 5);
    EXPECT_EQ(s.toStr(), "exact");
}
