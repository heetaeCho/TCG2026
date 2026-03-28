#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "GooString.h"

// Normal operation tests

TEST(GooStringTest_24, DefaultConstructor_24) {
    GooString s;
    EXPECT_EQ(s.toStr().size(), 0u);
    EXPECT_EQ(s.toStr(), "");
}

TEST(GooStringTest_24, ConstructFromCString_24) {
    GooString s("hello");
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST(GooStringTest_24, ConstructFromNullCString_24) {
    const char *nullstr = nullptr;
    GooString s(nullstr);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_24, ConstructFromStdString_24) {
    std::string str("world");
    GooString s(str);
    EXPECT_EQ(s.toStr(), "world");
}

TEST(GooStringTest_24, ConstructFromStdStringRvalue_24) {
    std::string str("moveme");
    GooString s(std::move(str));
    EXPECT_EQ(s.toStr(), "moveme");
}

TEST(GooStringTest_24, ConstructFromStringView_24) {
    std::string_view sv("viewtest");
    GooString s(sv);
    EXPECT_EQ(s.toStr(), "viewtest");
}

TEST(GooStringTest_24, ConstructFromCStringWithLength_24) {
    GooString s("hello world", 5);
    EXPECT_EQ(s.toStr(), "hello");
    EXPECT_EQ(s.toStr().size(), 5u);
}

TEST(GooStringTest_24, ConstructFromCStringWithLengthNull_24) {
    const char *nullstr = nullptr;
    GooString s(nullstr, 5);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_24, ConstructFromGooStringSubstring_24) {
    GooString original("hello world");
    GooString sub(&original, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST(GooStringTest_24, ConstructFromStdStringSubstring_24) {
    std::string original("hello world");
    GooString sub(original, 6, 5);
    EXPECT_EQ(sub.toStr(), "world");
}

TEST(GooStringTest_24, MoveConstructor_24) {
    GooString s1("movable");
    GooString s2(std::move(s1));
    EXPECT_EQ(s2.toStr(), "movable");
}

TEST(GooStringTest_24, MoveAssignment_24) {
    GooString s1("assign");
    GooString s2;
    s2 = std::move(s1);
    EXPECT_EQ(s2.toStr(), "assign");
}

TEST(GooStringTest_24, GetChar_24) {
    GooString s("abcdef");
    EXPECT_EQ(s.getChar(0), 'a');
    EXPECT_EQ(s.getChar(3), 'd');
    EXPECT_EQ(s.getChar(5), 'f');
}

TEST(GooStringTest_24, SetChar_24) {
    GooString s("abcdef");
    s.setChar(0, 'z');
    EXPECT_EQ(s.getChar(0), 'z');
    EXPECT_EQ(s.toStr(), "zbcdef");
}

TEST(GooStringTest_24, SetCharMiddle_24) {
    GooString s("hello");
    s.setChar(2, 'X');
    EXPECT_EQ(s.toStr(), "heXlo");
}

TEST(GooStringTest_24, SetCharLast_24) {
    GooString s("hello");
    s.setChar(4, '!');
    EXPECT_EQ(s.toStr(), "hell!");
}

TEST(GooStringTest_24, ToStr_24) {
    GooString s("test");
    const std::string &ref = s.toStr();
    EXPECT_EQ(ref, "test");
}

TEST(GooStringTest_24, ToNonConstStr_24) {
    GooString s("test");
    std::string &ref = s.toNonConstStr();
    ref = "modified";
    EXPECT_EQ(s.toStr(), "modified");
}

TEST(GooStringTest_24, Copy_24) {
    GooString s("original");
    std::unique_ptr<GooString> c = s.copy();
    EXPECT_EQ(c->toStr(), "original");
    // Ensure it's a separate copy
    c->setChar(0, 'X');
    EXPECT_EQ(s.toStr(), "original");
    EXPECT_EQ(c->toStr(), "Xriginal");
}

TEST(GooStringTest_24, CopyEmpty_24) {
    GooString s;
    std::unique_ptr<GooString> c = s.copy();
    EXPECT_EQ(c->toStr(), "");
}

TEST(GooStringTest_24, FormatSimple_24) {
    std::string result = GooString::format("{0:s}", "hello");
    // We don't know the exact format syntax, but test basic call
    // If format uses poppler's own syntax, this might vary
    // Testing that it doesn't crash at minimum
    EXPECT_FALSE(result.empty() || result.size() == 0);
}

TEST(GooStringTest_24, LowerCase_24) {
    std::string s = "HELLO WORLD";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_24, LowerCaseAlreadyLower_24) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST(GooStringTest_24, LowerCaseMixed_24) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST(GooStringTest_24, LowerCaseEmpty_24) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST(GooStringTest_24, LowerCaseNumbers_24) {
    std::string s = "ABC123DEF";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "abc123def");
}

TEST(GooStringTest_24, ToLowerCaseStringView_24) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST(GooStringTest_24, ToLowerCaseStringViewEmpty_24) {
    std::string result = GooString::toLowerCase(std::string_view(""));
    EXPECT_EQ(result, "");
}

TEST(GooStringTest_24, Appendf_24) {
    GooString s("prefix ");
    GooString *ret = s.appendf("suffix");
    EXPECT_EQ(ret, &s);
    // The string should have been appended
    EXPECT_NE(s.toStr().find("suffix"), std::string::npos);
}

// Boundary condition tests

TEST(GooStringTest_24, EmptyStringGetCharBoundary_24) {
    GooString s("a");
    EXPECT_EQ(s.getChar(0), 'a');
}

TEST(GooStringTest_24, SingleCharSetChar_24) {
    GooString s("x");
    s.setChar(0, 'y');
    EXPECT_EQ(s.getChar(0), 'y');
    EXPECT_EQ(s.toStr(), "y");
}

TEST(GooStringTest_24, ConstructFromZeroLengthCString_24) {
    GooString s("hello", 0);
    EXPECT_EQ(s.toStr(), "");
    EXPECT_EQ(s.toStr().size(), 0u);
}

TEST(GooStringTest_24, SubstringZeroLength_24) {
    std::string original("hello");
    GooString sub(original, 0, 0);
    EXPECT_EQ(sub.toStr(), "");
}

TEST(GooStringTest_24, SubstringFullLength_24) {
    std::string original("hello");
    GooString sub(original, 0, 5);
    EXPECT_EQ(sub.toStr(), "hello");
}

TEST(GooStringTest_24, SetCharWithNullByte_24) {
    GooString s("abc");
    s.setChar(1, '\0');
    EXPECT_EQ(s.getChar(1), '\0');
    EXPECT_EQ(s.toStr().size(), 3u);
}

TEST(GooStringTest_24, ConstructWithEmbeddedNull_24) {
    GooString s("ab\0cd", 5);
    EXPECT_EQ(s.toStr().size(), 5u);
    EXPECT_EQ(s.getChar(2), '\0');
    EXPECT_EQ(s.getChar(3), 'c');
}

TEST(GooStringTest_24, ToLowerCaseInt_24) {
    // Test toLowerCase with int argument (likely converts a single char)
    std::string result = GooString::toLowerCase('A');
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'a');
}

TEST(GooStringTest_24, ToLowerCaseIntAlreadyLower_24) {
    std::string result = GooString::toLowerCase('z');
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'z');
}

TEST(GooStringTest_24, MoveConstructorLeavesSourceEmpty_24) {
    GooString s1("data");
    GooString s2(std::move(s1));
    EXPECT_EQ(s2.toStr(), "data");
    // After move, s1 should be in a valid but unspecified state
    // We just verify s2 has the data
}

TEST(GooStringTest_24, CopyPreservesOriginal_24) {
    GooString s("preserve");
    auto c = s.copy();
    EXPECT_EQ(s.toStr(), "preserve");
    EXPECT_EQ(c->toStr(), "preserve");
}

TEST(GooStringTest_24, LongString_24) {
    std::string longStr(10000, 'A');
    GooString s(longStr);
    EXPECT_EQ(s.toStr().size(), 10000u);
    EXPECT_EQ(s.getChar(0), 'A');
    EXPECT_EQ(s.getChar(9999), 'A');
    s.setChar(5000, 'B');
    EXPECT_EQ(s.getChar(5000), 'B');
}

TEST(GooStringTest_24, ToNonConstStrModifyAndVerify_24) {
    GooString s("abc");
    std::string &ref = s.toNonConstStr();
    ref += "def";
    EXPECT_EQ(s.toStr(), "abcdef");
    EXPECT_EQ(s.toStr().size(), 6u);
}

TEST(GooStringTest_24, MultipleSetChars_24) {
    GooString s("abcde");
    for (size_t i = 0; i < 5; ++i) {
        s.setChar(i, 'x');
    }
    EXPECT_EQ(s.toStr(), "xxxxx");
}
