#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class StrPairTest_158 : public ::testing::Test {
protected:
    StrPair sp;
    int lineNum;

    void SetUp() override {
        lineNum = 1;
    }
};

// Test normal text parsing with a simple end tag
TEST_F(StrPairTest_158, ParseText_NormalOperation_158) {
    char buffer[] = "Hello World</end>";
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    // result should point past the end tag
    EXPECT_EQ(*result, '\0'); // nothing after end tag
    EXPECT_EQ(lineNum, 1);
}

// Test that ParseText returns null when end tag is not found
TEST_F(StrPairTest_158, ParseText_EndTagNotFound_ReturnsNull_158) {
    char buffer[] = "Hello World";
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

// Test ParseText with empty input string (just null terminator)
TEST_F(StrPairTest_158, ParseText_EmptyInput_ReturnsNull_158) {
    char buffer[] = "";
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

// Test ParseText with end tag at the very beginning
TEST_F(StrPairTest_158, ParseText_EndTagAtBeginning_158) {
    char buffer[] = "]]>remaining";
    char* result = sp.ParseText(buffer, "]]>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "remaining");
}

// Test ParseText increments line number on newlines
TEST_F(StrPairTest_158, ParseText_NewlinesIncrementLineNum_158) {
    char buffer[] = "line1\nline2\nline3</end>";
    lineNum = 1;
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 3); // two newlines encountered
}

// Test ParseText with single character end tag
TEST_F(StrPairTest_158, ParseText_SingleCharEndTag_158) {
    char buffer[] = "Hello>World";
    char* result = sp.ParseText(buffer, ">", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "World");
}

// Test ParseText where end tag character appears but full tag doesn't match
TEST_F(StrPairTest_158, ParseText_PartialEndTagMatch_158) {
    char buffer[] = "Hello </ not end </end>";
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, '\0');
}

// Test ParseText with multiple newlines before end tag
TEST_F(StrPairTest_158, ParseText_MultipleNewlines_158) {
    char buffer[] = "\n\n\n\n\nEND";
    lineNum = 1;
    char* result = sp.ParseText(buffer, "END", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 6); // 5 newlines
}

// Test ParseText with content after end tag
TEST_F(StrPairTest_158, ParseText_ContentAfterEndTag_158) {
    char buffer[] = "some text-->more content";
    char* result = sp.ParseText(buffer, "-->", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "more content");
}

// Test ParseText with no newlines, lineNum stays the same
TEST_F(StrPairTest_158, ParseText_NoNewlines_LineNumUnchanged_158) {
    char buffer[] = "abcdef]]>";
    lineNum = 42;
    char* result = sp.ParseText(buffer, "]]>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(lineNum, 42);
}

// Test ParseText where end tag first char appears multiple times but only last matches fully
TEST_F(StrPairTest_158, ParseText_MultiplePartialMatches_158) {
    char buffer[] = "a<b<c<d</end>";
    char* result = sp.ParseText(buffer, "</end>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, '\0');
}

// Test that GetStr returns stored text after successful parse
TEST_F(StrPairTest_158, ParseText_GetStrAfterParse_158) {
    char buffer[] = "stored text</tag>";
    char* result = sp.ParseText(buffer, "</tag>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_STREQ(str, "stored text");
}

// Test Empty() after default construction
TEST_F(StrPairTest_158, Empty_DefaultConstruction_158) {
    StrPair freshPair;
    EXPECT_TRUE(freshPair.Empty());
}

// Test Empty() after ParseText succeeds
TEST_F(StrPairTest_158, Empty_AfterSuccessfulParse_158) {
    char buffer[] = "content-->rest";
    sp.ParseText(buffer, "-->", 0, &lineNum);
    // After successful parse, the pair should not be empty (it has content)
    // Note: depends on whether empty string parsed is considered empty
    // "content" is non-empty
    EXPECT_FALSE(sp.Empty());
}

// Test Reset clears the StrPair
TEST_F(StrPairTest_158, Reset_ClearsPair_158) {
    char buffer[] = "text-->rest";
    sp.ParseText(buffer, "-->", 0, &lineNum);
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test SetStr and GetStr
TEST_F(StrPairTest_158, SetStr_GetStr_158) {
    sp.SetStr("hello world", 0);
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "hello world");
}

// Test TransferTo moves data to another StrPair
TEST_F(StrPairTest_158, TransferTo_MovesData_158) {
    sp.SetStr("transfer me", 0);
    StrPair other;
    sp.TransferTo(&other);
    const char* otherStr = other.GetStr();
    EXPECT_STREQ(otherStr, "transfer me");
    EXPECT_TRUE(sp.Empty());
}

// Test ParseText with long end tag
TEST_F(StrPairTest_158, ParseText_LongEndTag_158) {
    char buffer[] = "data<!--longendtag-->after";
    char* result = sp.ParseText(buffer, "<!--longendtag-->", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "after");
}

// Test ParseText with end tag that is just a newline character
TEST_F(StrPairTest_158, ParseText_NewlineAsEndTag_158) {
    char buffer[] = "before\nafter";
    lineNum = 1;
    char* result = sp.ParseText(buffer, "\n", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    // The newline is the end tag, so lineNum incremented before matching
    EXPECT_STREQ(result, "after");
}

// Test ParseName with a valid XML name
TEST_F(StrPairTest_158, ParseName_ValidName_158) {
    char buffer[] = "element attribute";
    char* result = sp.ParseName(buffer);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_STREQ(str, "element");
}

// Test ParseName with empty input
TEST_F(StrPairTest_158, ParseName_EmptyInput_158) {
    char buffer[] = "";
    char* result = sp.ParseName(buffer);
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with name starting with a digit (invalid XML name start)
TEST_F(StrPairTest_158, ParseName_StartsWithDigit_158) {
    char buffer[] = "123abc";
    char* result = sp.ParseName(buffer);
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with name containing colons and underscores
TEST_F(StrPairTest_158, ParseName_WithColonAndUnderscore_158) {
    char buffer[] = "_my:name rest";
    char* result = sp.ParseName(buffer);
    ASSERT_NE(result, nullptr);
}

// Test ParseText with strFlags parameter (non-zero)
TEST_F(StrPairTest_158, ParseText_WithStrFlags_158) {
    char buffer[] = "flagged text-->rest";
    char* result = sp.ParseText(buffer, "-->", 1, &lineNum);
    ASSERT_NE(result, nullptr);
}

// Test SetInternedStr and GetStr
TEST_F(StrPairTest_158, SetInternedStr_GetStr_158) {
    sp.SetInternedStr("interned");
    const char* result = sp.GetStr();
    EXPECT_STREQ(result, "interned");
}

// Test ParseText where buffer has only the end tag
TEST_F(StrPairTest_158, ParseText_OnlyEndTag_158) {
    char buffer[] = "-->";
    char* result = sp.ParseText(buffer, "-->", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_STREQ(str, "");
}
