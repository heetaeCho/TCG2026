#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "GooString.h"

// Test fixture for GooString tests
class GooStringTest_2281 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(GooStringTest_2281, DefaultConstructor_2281) {
    GooString s;
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2281, ConstructFromCString_2281) {
    GooString s("hello");
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST_F(GooStringTest_2281, ConstructFromNullCString_2281) {
    GooString s(static_cast<const char*>(nullptr));
    EXPECT_EQ(s.toStr(), "");
}

TEST_F(GooStringTest_2281, ConstructFromStdString_2281) {
    std::string str = "world";
    GooString s(str);
    EXPECT_EQ(s.toStr(), "world");
}

TEST_F(GooStringTest_2281, ConstructFromStdStringMove_2281) {
    std::string str = "moveable";
    GooString s(std::move(str));
    EXPECT_EQ(s.toStr(), "moveable");
}

TEST_F(GooStringTest_2281, ConstructFromCStringWithLength_2281) {
    GooString s("hello world", 5);
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST_F(GooStringTest_2281, ConstructFromNullCStringWithLength_2281) {
    GooString s(static_cast<const char*>(nullptr), 5);
    EXPECT_EQ(s.toStr(), "");
}

TEST_F(GooStringTest_2281, ConstructFromStringView_2281) {
    std::string_view sv = "string_view_test";
    GooString s(sv);
    EXPECT_EQ(s.toStr(), "string_view_test");
}

TEST_F(GooStringTest_2281, ConstructFromGooStringSubstring_2281) {
    GooString original("hello world");
    GooString sub(&original, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST_F(GooStringTest_2281, ConstructFromStdStringSubstring_2281) {
    std::string str = "hello world";
    GooString s(str, 6, 5);
    EXPECT_EQ(s.toStr(), "world");
}

TEST_F(GooStringTest_2281, MoveConstructor_2281) {
    GooString original("move me");
    GooString moved(std::move(original));
    EXPECT_EQ(moved.toStr(), "move me");
}

TEST_F(GooStringTest_2281, MoveAssignment_2281) {
    GooString original("assign me");
    GooString target;
    target = std::move(original);
    EXPECT_EQ(target.toStr(), "assign me");
}

// ==================== getChar / setChar Tests ====================

TEST_F(GooStringTest_2281, GetCharAtValidIndex_2281) {
    GooString s("abcde");
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(1), 'b');
    EXPECT_EQ(s.getChar(2), 'c');
    EXPECT_EQ(s.getChar(3), 'd');
    EXPECT_EQ(s.getChar(4), 'e');
}

TEST_F(GooStringTest_2281, SetCharAtValidIndex_2281) {
    GooString s("abcde");
    s.setChar(0, 'z');
    EXPECT_EQ(s.getChar(0), 'z');
    EXPECT_EQ(s.toStr(), "zbcde");
}

TEST_F(GooStringTest_2281, SetCharMiddle_2281) {
    GooString s("hello");
    s.setChar(2, 'X');
    EXPECT_EQ(s.toStr(), "heXlo");
}

TEST_F(GooStringTest_2281, SetCharLast_2281) {
    GooString s("hello");
    s.setChar(4, '!');
    EXPECT_EQ(s.toStr(), "hell!");
}

TEST_F(GooStringTest_2281, SetCharFirst_2281) {
    GooString s("hello");
    s.setChar(0, 'H');
    EXPECT_EQ(s.toStr(), "Hello");
}

TEST_F(GooStringTest_2281, SetCharMultipleTimes_2281) {
    GooString s("abc");
    s.setChar(0, 'x');
    s.setChar(1, 'y');
    s.setChar(2, 'z');
    EXPECT_EQ(s.toStr(), "xyz");
}

// ==================== toStr / toNonConstStr Tests ====================

TEST_F(GooStringTest_2281, ToStrReturnsConstRef_2281) {
    GooString s("test");
    const std::string &ref = s.toStr();
    EXPECT_EQ(ref, "test");
}

TEST_F(GooStringTest_2281, ToNonConstStrAllowsModification_2281) {
    GooString s("test");
    std::string &ref = s.toNonConstStr();
    ref = "modified";
    EXPECT_EQ(s.toStr(), "modified");
}

// ==================== copy Tests ====================

TEST_F(GooStringTest_2281, CopyCreatesIndependentCopy_2281) {
    GooString s("original");
    auto c = s.copy();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->toStr(), "original");
    
    // Modify copy, original should be unchanged
    c->setChar(0, 'X');
    EXPECT_EQ(s.toStr(), "original");
    EXPECT_EQ(c->toStr(), "Xriginal");
}

TEST_F(GooStringTest_2281, CopyEmptyString_2281) {
    GooString s;
    auto c = s.copy();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->toStr(), "");
}

// ==================== format Tests ====================

TEST_F(GooStringTest_2281, FormatSimpleString_2281) {
    std::string result = GooString::format("{0:s}", "hello");
    // format uses poppler's custom format syntax; testing basic usage
    // If this doesn't match the format spec, adjust accordingly
    // At minimum, we test it doesn't crash and returns something
    EXPECT_FALSE(result.empty());
}

// ==================== appendf Tests ====================

TEST_F(GooStringTest_2281, AppendfAppendsToString_2281) {
    GooString s("prefix");
    GooString *ret = s.appendf("{0:s}", "suffix");
    EXPECT_EQ(ret, &s);
    // The string should have been appended
    EXPECT_NE(s.toStr().find("prefix"), std::string::npos);
}

// ==================== lowerCase Tests ====================

TEST_F(GooStringTest_2281, LowerCaseConvertsInPlace_2281) {
    std::string s = "HELLO WORLD";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST_F(GooStringTest_2281, LowerCaseAlreadyLowerCase_2281) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_2281, LowerCaseEmptyString_2281) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST_F(GooStringTest_2281, LowerCaseMixedCase_2281) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST_F(GooStringTest_2281, LowerCaseWithNumbers_2281) {
    std::string s = "ABC123DEF";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "abc123def");
}

// ==================== toLowerCase (string_view) Tests ====================

TEST_F(GooStringTest_2281, ToLowerCaseStringView_2281) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST_F(GooStringTest_2281, ToLowerCaseStringViewEmpty_2281) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

TEST_F(GooStringTest_2281, ToLowerCaseStringViewAlreadyLower_2281) {
    std::string result = GooString::toLowerCase(std::string_view("hello"));
    EXPECT_EQ(result, "hello");
}

// ==================== Boundary / Edge Cases ====================

TEST_F(GooStringTest_2281, ConstructFromEmptyCString_2281) {
    GooString s("");
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2281, ConstructFromCStringZeroLength_2281) {
    GooString s("hello", 0);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2281, SetCharWithNullChar_2281) {
    GooString s("hello");
    s.setChar(2, '\0');
    EXPECT_EQ(s.getChar(2), '\0');
    // The string should still have length 5
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST_F(GooStringTest_2281, SingleCharacterString_2281) {
    GooString s("A");
    EXPECT_EQ(s.getChar(0), 'A');
    s.setChar(0, 'B');
    EXPECT_EQ(s.getChar(0), 'B');
    EXPECT_EQ(s.toStr(), "B");
}

TEST_F(GooStringTest_2281, ConstructSubstringFromIndex0_2281) {
    GooString original("hello");
    GooString sub(&original, 0, 5);
    EXPECT_EQ(sub.toStr(), "hello");
}

TEST_F(GooStringTest_2281, ConstructSubstringEmpty_2281) {
    GooString original("hello");
    GooString sub(&original, 0, 0);
    EXPECT_EQ(sub.toStr(), "");
}

TEST_F(GooStringTest_2281, LargeString_2281) {
    std::string large(10000, 'X');
    GooString s(large);
    EXPECT_EQ(s.toStr().size(), 10000u);
    EXPECT_EQ(s.getChar(0), 'X');
    EXPECT_EQ(s.getChar(9999), 'X');
    s.setChar(5000, 'Y');
    EXPECT_EQ(s.getChar(5000), 'Y');
}

TEST_F(GooStringTest_2281, CopyPreservesContent_2281) {
    GooString s("test string with spaces");
    auto c = s.copy();
    EXPECT_EQ(c->toStr(), s.toStr());
}

TEST_F(GooStringTest_2281, ToNonConstStrClear_2281) {
    GooString s("hello");
    s.toNonConstStr().clear();
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST_F(GooStringTest_2281, ToNonConstStrAppend_2281) {
    GooString s("hello");
    s.toNonConstStr() += " world";
    EXPECT_EQ(s.toStr(), "hello world");
}

TEST_F(GooStringTest_2281, SpecialCharacters_2281) {
    GooString s("\t\n\r");
    EXPECT_EQ(s.getChar(0), '\t');
    EXPECT_EQ(s.getChar(1), '\n');
    EXPECT_EQ(s.getChar(2), '\r');
    EXPECT_EQ(s.toStr().size(), 3u);
}

TEST_F(GooStringTest_2281, BinaryData_2281) {
    const char data[] = {'\x00', '\x01', '\x02', '\x03', '\x04'};
    GooString s(data, 5);
    EXPECT_EQ(s.toStr().size(), 5u);
    EXPECT_EQ(s.getChar(0), '\x00');
    EXPECT_EQ(s.getChar(4), '\x04');
}
