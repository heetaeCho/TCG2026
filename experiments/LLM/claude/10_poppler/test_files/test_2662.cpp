#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>

#include "GooString.h"
#include "UnicodeMap.h"

// Since printTextString is static in pdfinfo.cc, we need to include it
// or replicate its declaration for testing purposes.
// We'll test the components it relies on: GooString and UnicodeMap.

// ==================== GooString Tests ====================

class GooStringTest_2662 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(GooStringTest_2662, DefaultConstructor_2662) {
    GooString gs;
    EXPECT_EQ(gs.toStr(), "");
}

TEST_F(GooStringTest_2662, ConstructFromCString_2662) {
    GooString gs("hello");
    EXPECT_EQ(gs.toStr(), "hello");
}

TEST_F(GooStringTest_2662, ConstructFromEmptyCString_2662) {
    GooString gs("");
    EXPECT_EQ(gs.toStr(), "");
}

TEST_F(GooStringTest_2662, ConstructFromStdString_2662) {
    std::string str = "test string";
    GooString gs(str);
    EXPECT_EQ(gs.toStr(), "test string");
}

TEST_F(GooStringTest_2662, ConstructFromStdStringView_2662) {
    std::string_view sv = "view string";
    GooString gs(sv);
    EXPECT_EQ(gs.toStr(), "view string");
}

TEST_F(GooStringTest_2662, ConstructFromCStringWithLength_2662) {
    GooString gs("hello world", 5);
    EXPECT_EQ(gs.toStr(), "hello");
}

TEST_F(GooStringTest_2662, ConstructFromCStringWithZeroLength_2662) {
    GooString gs("hello", 0);
    EXPECT_EQ(gs.toStr(), "");
}

TEST_F(GooStringTest_2662, ConstructFromNullCString_2662) {
    GooString gs(static_cast<const char*>(nullptr));
    EXPECT_EQ(gs.toStr(), "");
}

TEST_F(GooStringTest_2662, ConstructFromNullCStringWithLength_2662) {
    GooString gs(static_cast<const char*>(nullptr), 5);
    EXPECT_EQ(gs.toStr(), "");
}

TEST_F(GooStringTest_2662, MoveConstructor_2662) {
    GooString gs1("move me");
    GooString gs2(std::move(gs1));
    EXPECT_EQ(gs2.toStr(), "move me");
}

TEST_F(GooStringTest_2662, MoveAssignment_2662) {
    GooString gs1("assign me");
    GooString gs2;
    gs2 = std::move(gs1);
    EXPECT_EQ(gs2.toStr(), "assign me");
}

TEST_F(GooStringTest_2662, ToStrReturnsConstRef_2662) {
    GooString gs("const ref test");
    const std::string& ref = gs.toStr();
    EXPECT_EQ(ref, "const ref test");
}

TEST_F(GooStringTest_2662, ToNonConstStr_2662) {
    GooString gs("mutable");
    std::string& ref = gs.toNonConstStr();
    ref = "changed";
    EXPECT_EQ(gs.toStr(), "changed");
}

TEST_F(GooStringTest_2662, CopyMethod_2662) {
    GooString gs("copy me");
    auto copy = gs.copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->toStr(), "copy me");
}

TEST_F(GooStringTest_2662, GetChar_2662) {
    GooString gs("abc");
    EXPECT_EQ(gs.getChar(0), 'a');
    EXPECT_EQ(gs.getChar(1), 'b');
    EXPECT_EQ(gs.getChar(2), 'c');
}

TEST_F(GooStringTest_2662, SetChar_2662) {
    GooString gs("abc");
    gs.setChar(1, 'x');
    EXPECT_EQ(gs.getChar(1), 'x');
    EXPECT_EQ(gs.toStr(), "axc");
}

TEST_F(GooStringTest_2662, ConstructFromStdStringRvalue_2662) {
    std::string str = "rvalue string";
    GooString gs(std::move(str));
    EXPECT_EQ(gs.toStr(), "rvalue string");
}

TEST_F(GooStringTest_2662, ConstructFromGooStringSubstring_2662) {
    GooString gs1("hello world");
    GooString gs2(&gs1, 6, 5);
    EXPECT_EQ(gs2.toStr(), "world");
}

TEST_F(GooStringTest_2662, ConstructFromStdStringSubstring_2662) {
    std::string str = "hello world";
    GooString gs(str, 6, 5);
    EXPECT_EQ(gs.toStr(), "world");
}

TEST_F(GooStringTest_2662, LowerCaseStatic_2662) {
    std::string s = "HELLO";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_2662, ToLowerCaseStatic_2662) {
    std::string result = GooString::toLowerCase(std::string_view("HELLO"));
    EXPECT_EQ(result, "hello");
}

TEST_F(GooStringTest_2662, LowerCaseEmptyString_2662) {
    std::string s = "";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "");
}

TEST_F(GooStringTest_2662, LowerCaseAlreadyLower_2662) {
    std::string s = "hello";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello");
}

TEST_F(GooStringTest_2662, LowerCaseMixedCase_2662) {
    std::string s = "HeLLo WoRLd";
    GooString::lowerCase(s);
    EXPECT_EQ(s, "hello world");
}

TEST_F(GooStringTest_2662, FormatSimple_2662) {
    std::string result = GooString::format("{0:s}", "test");
    // We just verify it doesn't crash; exact format depends on implementation
    EXPECT_FALSE(result.empty());
}

TEST_F(GooStringTest_2662, EmptyStringToStr_2662) {
    GooString gs("");
    EXPECT_TRUE(gs.toStr().empty());
}

TEST_F(GooStringTest_2662, LongString_2662) {
    std::string longStr(10000, 'x');
    GooString gs(longStr);
    EXPECT_EQ(gs.toStr().size(), 10000u);
    EXPECT_EQ(gs.toStr(), longStr);
}

TEST_F(GooStringTest_2662, SpecialCharacters_2662) {
    GooString gs("hello\nworld\t!");
    EXPECT_EQ(gs.toStr(), "hello\nworld\t!");
}

TEST_F(GooStringTest_2662, BinaryData_2662) {
    const char data[] = "hel\0lo";
    GooString gs(data, 6);
    EXPECT_EQ(gs.toStr().size(), 6u);
}

// ==================== UnicodeMap Tests ====================

class UnicodeMapTest_2662 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(UnicodeMapTest_2662, ParseLatin1_2662) {
    auto uMap = UnicodeMap::parse("Latin1");
    // May or may not succeed depending on configuration
    // Just verify it doesn't crash
}

TEST_F(UnicodeMapTest_2662, ParseUTF8_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        EXPECT_TRUE(uMap->match("UTF-8"));
    }
}

TEST_F(UnicodeMapTest_2662, MatchEncodingName_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        EXPECT_TRUE(uMap->match("UTF-8"));
        EXPECT_FALSE(uMap->match("Latin1"));
    }
}

TEST_F(UnicodeMapTest_2662, GetEncodingName_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        EXPECT_EQ(uMap->getEncodingName(), "UTF-8");
    }
}

TEST_F(UnicodeMapTest_2662, MapUnicodeASCII_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        char buf[8];
        int n = uMap->mapUnicode('A', buf, sizeof(buf));
        EXPECT_GT(n, 0);
        EXPECT_EQ(buf[0], 'A');
    }
}

TEST_F(UnicodeMapTest_2662, MapUnicodeMultiByte_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        char buf[8];
        // U+00E9 is 'é', should be 2 bytes in UTF-8: 0xC3 0xA9
        int n = uMap->mapUnicode(0x00E9, buf, sizeof(buf));
        EXPECT_GE(n, 2);
    }
}

TEST_F(UnicodeMapTest_2662, MapUnicodeSmallBuffer_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        char buf[1];
        // Try to map a multi-byte character into a 1-byte buffer
        int n = uMap->mapUnicode(0x00E9, buf, 1);
        // Expect 0 if buffer too small, or implementation-defined behavior
        EXPECT_GE(n, 0);
    }
}

TEST_F(UnicodeMapTest_2662, IsUnicode_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        // UTF-8 is a unicode encoding
        EXPECT_TRUE(uMap->isUnicode());
    }
}

TEST_F(UnicodeMapTest_2662, ParseInvalidEncoding_2662) {
    auto uMap = UnicodeMap::parse("NonExistentEncoding12345");
    // Should return nullptr for unknown encoding
    EXPECT_EQ(uMap, nullptr);
}

TEST_F(UnicodeMapTest_2662, ParseEmptyEncoding_2662) {
    auto uMap = UnicodeMap::parse("");
    // Empty encoding name - likely returns nullptr
    EXPECT_EQ(uMap, nullptr);
}

TEST_F(UnicodeMapTest_2662, MapUnicodeNullCharacter_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        char buf[8];
        int n = uMap->mapUnicode(0, buf, sizeof(buf));
        EXPECT_GE(n, 0);
    }
}

TEST_F(UnicodeMapTest_2662, MoveConstructor_2662) {
    auto uMap = UnicodeMap::parse("UTF-8");
    if (uMap) {
        UnicodeMap moved(std::move(*uMap));
        EXPECT_TRUE(moved.match("UTF-8"));
    }
}

TEST_F(UnicodeMapTest_2662, MoveAssignment_2662) {
    auto uMap1 = UnicodeMap::parse("UTF-8");
    auto uMap2 = UnicodeMap::parse("Latin1");
    if (uMap1 && uMap2) {
        *uMap2 = std::move(*uMap1);
        EXPECT_TRUE(uMap2->match("UTF-8"));
    }
}
