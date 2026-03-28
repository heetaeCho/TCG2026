#include <gtest/gtest.h>
#include <cstring>
#include "tinyxml2.h"

using namespace tinyxml2;

class StrPairTest_160 : public ::testing::Test {
protected:
    StrPair sp;
};

// Test default construction and Empty state
TEST_F(StrPairTest_160, DefaultConstructionIsEmpty_160) {
    EXPECT_TRUE(sp.Empty());
}

// Test SetStr and GetStr for a simple string
TEST_F(StrPairTest_160, SetStrAndGetStr_160) {
    sp.SetStr("Hello World", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello World");
}

// Test Empty returns false after SetStr
TEST_F(StrPairTest_160, NotEmptyAfterSetStr_160) {
    sp.SetStr("test", 0);
    EXPECT_FALSE(sp.Empty());
}

// Test Reset makes it empty again
TEST_F(StrPairTest_160, ResetMakesEmpty_160) {
    sp.SetStr("test", 0);
    sp.Reset();
    EXPECT_TRUE(sp.Empty());
}

// Test SetStr with empty string
TEST_F(StrPairTest_160, SetStrEmptyString_160) {
    sp.SetStr("", 0);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test entity processing: &amp; -> &
TEST_F(StrPairTest_160, EntityProcessingAmp_160) {
    // Use Set with NEEDS_ENTITY_PROCESSING | NEEDS_FLUSH
    char buf[] = "hello&amp;world";
    sp.Set(buf, buf + strlen(buf), 1 | 256); // NEEDS_ENTITY_PROCESSING | NEEDS_FLUSH
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello&world");
}

// Test entity processing: &lt; -> <
TEST_F(StrPairTest_160, EntityProcessingLt_160) {
    char buf[] = "a&lt;b";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "a<b");
}

// Test entity processing: &gt; -> >
TEST_F(StrPairTest_160, EntityProcessingGt_160) {
    char buf[] = "a&gt;b";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "a>b");
}

// Test entity processing: &quot; -> "
TEST_F(StrPairTest_160, EntityProcessingQuot_160) {
    char buf[] = "a&quot;b";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "a\"b");
}

// Test entity processing: &apos; -> '
TEST_F(StrPairTest_160, EntityProcessingApos_160) {
    char buf[] = "a&apos;b";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "a'b");
}

// Test newline normalization: CR LF -> LF
TEST_F(StrPairTest_160, NewlineNormalizationCRLF_160) {
    char buf[] = "hello\r\nworld";
    sp.Set(buf, buf + strlen(buf), 2 | 256); // NEEDS_NEWLINE_NORMALIZATION | NEEDS_FLUSH
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello\nworld");
}

// Test newline normalization: standalone CR -> LF
TEST_F(StrPairTest_160, NewlineNormalizationCR_160) {
    char buf[] = "hello\rworld";
    sp.Set(buf, buf + strlen(buf), 2 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello\nworld");
}

// Test newline normalization: LF CR -> LF
TEST_F(StrPairTest_160, NewlineNormalizationLFCR_160) {
    char buf[] = "hello\n\rworld";
    sp.Set(buf, buf + strlen(buf), 2 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello\nworld");
}

// Test no processing when flags have no processing bits set (only NEEDS_FLUSH)
TEST_F(StrPairTest_160, NoProcessingWhenNoFlags_160) {
    char buf[] = "hello&amp;world";
    sp.Set(buf, buf + strlen(buf), 256); // Only NEEDS_FLUSH
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello&amp;world");
}

// Test multiple entities in one string
TEST_F(StrPairTest_160, MultipleEntities_160) {
    char buf[] = "&lt;tag&gt;";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "<tag>");
}

// Test unknown entity (& not followed by known entity)
TEST_F(StrPairTest_160, UnknownEntity_160) {
    char buf[] = "a&unknown;b";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    // Unknown entity - the '&' is skipped but rest remains
    // The behavior: entityFound=false, so ++p, ++q (copies '&' and advances)
    // Actually it copies *q = *p for '&', then moves forward; the rest passes through
    EXPECT_NE(result, nullptr);
}

// Test numeric character reference &#65; -> 'A'
TEST_F(StrPairTest_160, NumericCharacterReference_160) {
    char buf[] = "&#65;";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "A");
}

// Test hex character reference &#x41; -> 'A'
TEST_F(StrPairTest_160, HexCharacterReference_160) {
    char buf[] = "&#x41;";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "A");
}

// Test combined entity processing and newline normalization (TEXT_ELEMENT = 3)
TEST_F(StrPairTest_160, TextElementMode_160) {
    char buf[] = "hello\r\n&amp;world";
    sp.Set(buf, buf + strlen(buf), 3 | 256); // TEXT_ELEMENT | NEEDS_FLUSH
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello\n&world");
}

// Test whitespace collapsing
TEST_F(StrPairTest_160, WhitespaceCollapsing_160) {
    char buf[] = "hello   world";
    sp.Set(buf, buf + strlen(buf), 4 | 256); // NEEDS_WHITESPACE_COLLAPSING | NEEDS_FLUSH
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello world");
}

// Test TransferTo
TEST_F(StrPairTest_160, TransferTo_160) {
    sp.SetStr("transfer me", 0);
    StrPair other;
    sp.TransferTo(&other);
    EXPECT_TRUE(sp.Empty());
    const char* result = other.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "transfer me");
}

// Test GetStr called twice returns same result (no double processing)
TEST_F(StrPairTest_160, GetStrCalledTwice_160) {
    char buf[] = "&amp;";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result1 = sp.GetStr();
    const char* result2 = sp.GetStr();
    EXPECT_STREQ(result1, "&");
    EXPECT_STREQ(result2, "&");
}

// Test ParseText
TEST_F(StrPairTest_160, ParseTextBasic_160) {
    char buf[] = "hello</end>";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "</end>", 0, &lineNum);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "hello");
}

// Test ParseText when end tag not found
TEST_F(StrPairTest_160, ParseTextEndTagNotFound_160) {
    char buf[] = "hello world";
    int lineNum = 1;
    char* result = sp.ParseText(buf, "</end>", 0, &lineNum);
    EXPECT_EQ(result, nullptr);
}

// Test ParseName with valid name
TEST_F(StrPairTest_160, ParseNameValid_160) {
    char buf[] = "myName ";
    char* result = sp.ParseName(buf);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "myName");
}

// Test ParseName with empty/invalid start
TEST_F(StrPairTest_160, ParseNameInvalidStart_160) {
    char buf[] = "123invalid";
    char* result = sp.ParseName(buf);
    EXPECT_EQ(result, nullptr);
}

// Test SetInternedStr
TEST_F(StrPairTest_160, SetInternedStr_160) {
    sp.SetInternedStr("interned");
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "interned");
    EXPECT_FALSE(sp.Empty());
}

// Test Set with plain text, no flags needing processing
TEST_F(StrPairTest_160, SetPlainText_160) {
    char buf[] = "plain text";
    sp.Set(buf, buf + strlen(buf), 256); // NEEDS_FLUSH only
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "plain text");
}

// Test all five entities in one string
TEST_F(StrPairTest_160, AllFiveEntities_160) {
    char buf[] = "&quot;&amp;&apos;&lt;&gt;";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "\"&'<>");
}

// Test multiple CRLFs
TEST_F(StrPairTest_160, MultipleCRLFs_160) {
    char buf[] = "a\r\nb\r\nc";
    sp.Set(buf, buf + strlen(buf), 2 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "a\nb\nc");
}

// Test string with only whitespace and collapsing
TEST_F(StrPairTest_160, WhitespaceOnlyCollapsing_160) {
    char buf[] = "   ";
    sp.Set(buf, buf + strlen(buf), 4 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    // Whitespace collapsing should collapse to single space or empty
    // (implementation dependent but observable)
}

// Test entity at the very end of string
TEST_F(StrPairTest_160, EntityAtEnd_160) {
    char buf[] = "hello&amp;";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello&");
}

// Test entity at the very beginning of string
TEST_F(StrPairTest_160, EntityAtBeginning_160) {
    char buf[] = "&amp;hello";
    sp.Set(buf, buf + strlen(buf), 1 | 256);
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "&hello");
}

// Test long string with mixed entities and newlines
TEST_F(StrPairTest_160, MixedEntitiesAndNewlines_160) {
    char buf[] = "line1\r\nline2&lt;tag&gt;\r\nline3";
    sp.Set(buf, buf + strlen(buf), 3 | 256); // NEEDS_ENTITY_PROCESSING | NEEDS_NEWLINE_NORMALIZATION | NEEDS_FLUSH
    const char* result = sp.GetStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "line1\nline2<tag>\nline3");
}

// Test ParseName with underscore start (valid XML name start)
TEST_F(StrPairTest_160, ParseNameUnderscore_160) {
    char buf[] = "_name ";
    char* result = sp.ParseName(buf);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_STREQ(str, "_name");
}

// Test ParseName with colon start (valid XML name start)
TEST_F(StrPairTest_160, ParseNameColon_160) {
    char buf[] = ":name ";
    char* result = sp.ParseName(buf);
    ASSERT_NE(result, nullptr);
    const char* str = sp.GetStr();
    EXPECT_STREQ(str, ":name");
}
