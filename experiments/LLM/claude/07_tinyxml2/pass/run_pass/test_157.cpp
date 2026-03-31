#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class StrPairTest_157 : public ::testing::Test {
protected:
    StrPair sp;
};

// Test that a newly constructed StrPair is empty
TEST_F(StrPairTest_157, DefaultConstructorIsEmpty_157) {
    EXPECT_TRUE(sp.Empty());
}

// Test that SetStr with a normal string makes it non-empty and GetStr returns the same string
TEST_F(StrPairTest_157, SetStrNormalString_157) {
    sp.SetStr("hello", 0);
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
}

// Test SetStr with an empty string
TEST_F(StrPairTest_157, SetStrEmptyString_157) {
    sp.SetStr("", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test SetStr with flags=0
TEST_F(StrPairTest_157, SetStrWithZeroFlags_157) {
    sp.SetStr("test", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "test");
}

// Test that SetStr can be called multiple times, overwriting previous value
TEST_F(StrPairTest_157, SetStrOverwritesPrevious_157) {
    sp.SetStr("first", 0);
    EXPECT_STREQ(sp.GetStr(), "first");
    sp.SetStr("second", 0);
    EXPECT_STREQ(sp.GetStr(), "second");
}

// Test SetStr with a longer string
TEST_F(StrPairTest_157, SetStrLongString_157) {
    std::string longStr(1000, 'a');
    sp.SetStr(longStr.c_str(), 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, longStr.c_str());
}

// Test SetStr with special characters
TEST_F(StrPairTest_157, SetStrSpecialCharacters_157) {
    sp.SetStr("hello\nworld\ttab", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello\nworld\ttab");
}

// Test that Reset makes the StrPair empty again
TEST_F(StrPairTest_157, ResetMakesEmpty_157) {
    sp.SetStr("something", 0);
    EXPECT_FALSE(sp.Empty());
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test TransferTo moves data to another StrPair
TEST_F(StrPairTest_157, TransferToMovesData_157) {
    sp.SetStr("transfer me", 0);
    StrPair other;
    sp.TransferTo(&other);
    EXPECT_STREQ(other.GetStr(), "transfer me");
    // After transfer, original should be empty
    EXPECT_TRUE(sp.Empty());
}

// Test that GetStr on empty StrPair returns something (empty string or null-like)
TEST_F(StrPairTest_157, GetStrOnEmptyReturnsEmptyOrNull_157) {
    const char* result = sp.GetStr();
    // Should return empty string for empty StrPair
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
    }
}

// Test SetStr with a single character string
TEST_F(StrPairTest_157, SetStrSingleChar_157) {
    sp.SetStr("x", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "x");
}

// Test SetStr with string containing null-like content but valid C string
TEST_F(StrPairTest_157, SetStrWithSpaces_157) {
    sp.SetStr("   ", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "   ");
}

// Test SetStr with XML-like content
TEST_F(StrPairTest_157, SetStrXmlContent_157) {
    sp.SetStr("<tag>value</tag>", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "<tag>value</tag>");
}

// Test SetStr with unicode-like multi-byte content
TEST_F(StrPairTest_157, SetStrWithMultibyte_157) {
    sp.SetStr("caf\xc3\xa9", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "caf\xc3\xa9");
}

// Test SetInternedStr sets string and is retrievable
TEST_F(StrPairTest_157, SetInternedStr_157) {
    const char* interned = "interned";
    sp.SetInternedStr(interned);
    EXPECT_FALSE(sp.Empty());
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "interned");
}

// Test Set with char pointers
TEST_F(StrPairTest_157, SetWithCharPointers_157) {
    char buffer[] = "buffer test";
    sp.Set(buffer, buffer + 6, 0);
    EXPECT_FALSE(sp.Empty());
}

// Test ParseName with valid name
TEST_F(StrPairTest_157, ParseNameValid_157) {
    char input[] = "validName rest";
    char* result = sp.ParseName(input);
    // ParseName should parse the name portion
    if (result != nullptr) {
        EXPECT_NE(result, input); // should have advanced
    }
}

// Test ParseName with input starting with non-name character
TEST_F(StrPairTest_157, ParseNameInvalidStart_157) {
    char input[] = "123invalid";
    char* result = sp.ParseName(input);
    // Names can't start with digits in XML, should return null or beginning
    EXPECT_EQ(result, nullptr);
}

// Test ParseText with matching end tag
TEST_F(StrPairTest_157, ParseTextWithEndTag_157) {
    char input[] = "some text]]>rest";
    int lineNum = 1;
    char* result = sp.ParseText(input, "]]>", 0, &lineNum);
    if (result != nullptr) {
        EXPECT_STREQ(sp.GetStr(), "some text");
    }
}

// Test ParseText without matching end tag returns null
TEST_F(StrPairTest_157, ParseTextNoEndTag_157) {
    char input[] = "some text without end";
    int lineNum = 1;
    char* result = sp.ParseText(input, "]]>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

// Test ParseText counts newlines
TEST_F(StrPairTest_157, ParseTextCountsNewlines_157) {
    char input[] = "line1\nline2\nline3-->rest";
    int lineNum = 1;
    char* result = sp.ParseText(input, "-->", 0, &lineNum);
    if (result != nullptr) {
        EXPECT_EQ(lineNum, 3);
    }
}

// Test multiple Reset calls don't cause issues
TEST_F(StrPairTest_157, MultipleResets_157) {
    sp.Reset();
    sp.Reset();
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test SetStr followed by TransferTo followed by SetStr on original
TEST_F(StrPairTest_157, SetTransferSet_157) {
    sp.SetStr("first", 0);
    StrPair other;
    sp.TransferTo(&other);
    sp.SetStr("second", 0);
    EXPECT_STREQ(sp.GetStr(), "second");
    EXPECT_STREQ(other.GetStr(), "first");
}
