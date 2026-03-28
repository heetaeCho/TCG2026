#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// Test fixture for PCRE tests
class PCRETest_201 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== NumberOfCapturingGroups Tests ====================

TEST_F(PCRETest_201, NumberOfCapturingGroups_NoGroups_201) {
    PCRE re("abc");
    EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_OneGroup_201) {
    PCRE re("(abc)");
    EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_MultipleGroups_201) {
    PCRE re("(a)(b)(c)");
    EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_NestedGroups_201) {
    PCRE re("((a)(b))");
    EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_InvalidPattern_201) {
    PCRE re("(abc");  // Invalid pattern - unclosed paren
    EXPECT_EQ(-1, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_EmptyPattern_201) {
    PCRE re("");
    EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_NonCapturingGroup_201) {
    PCRE re("(?:abc)");
    EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_MixedGroups_201) {
    PCRE re("(?:abc)(def)");
    EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST_F(PCRETest_201, NumberOfCapturingGroups_ComplexPattern_201) {
    PCRE re("(\\d+)-(\\w+)-(\\S+)");
    EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

// ==================== Constructor Tests ====================

TEST_F(PCRETest_201, ConstructFromCString_201) {
    PCRE re("hello");
    EXPECT_EQ("hello", re.pattern());
}

TEST_F(PCRETest_201, ConstructFromStdString_201) {
    std::string pattern = "world";
    PCRE re(pattern);
    EXPECT_EQ("world", re.pattern());
}

TEST_F(PCRETest_201, InvalidPatternHasError_201) {
    PCRE re("[invalid");
    EXPECT_FALSE(re.error().empty());
}

TEST_F(PCRETest_201, ValidPatternNoError_201) {
    PCRE re("valid");
    EXPECT_TRUE(re.error().empty());
}

// ==================== Pattern Tests ====================

TEST_F(PCRETest_201, PatternReturnsOriginalPattern_201) {
    PCRE re("foo.*bar");
    EXPECT_EQ("foo.*bar", re.pattern());
}

// ==================== HitLimit Tests ====================

TEST_F(PCRETest_201, HitLimitInitiallyFalse_201) {
    PCRE re("abc");
    EXPECT_FALSE(re.HitLimit());
}

TEST_F(PCRETest_201, ClearHitLimitDoesNotCrash_201) {
    PCRE re("abc");
    re.ClearHitLimit();
    EXPECT_FALSE(re.HitLimit());
}

// ==================== QuoteMeta Tests ====================

TEST_F(PCRETest_201, QuoteMetaPlainString_201) {
    std::string result = PCRE::QuoteMeta("hello");
    EXPECT_EQ("hello", result);
}

TEST_F(PCRETest_201, QuoteMetaSpecialCharacters_201) {
    std::string result = PCRE::QuoteMeta("hello.world");
    EXPECT_NE(std::string::npos, result.find("\\.")); 
}

TEST_F(PCRETest_201, QuoteMetaEmptyString_201) {
    std::string result = PCRE::QuoteMeta("");
    EXPECT_EQ("", result);
}

TEST_F(PCRETest_201, QuoteMetaAllSpecialChars_201) {
    std::string result = PCRE::QuoteMeta("[]()+*?.\\{}^$|");
    // Each special char should be escaped
    EXPECT_GT(result.size(), strlen("[]()+*?.\\{}^$|"));
}

// ==================== DoMatch Tests ====================

TEST_F(PCRETest_201, DoMatchSimpleMatch_201) {
    PCRE re("hello");
    EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_201, DoMatchNoMatch_201) {
    PCRE re("hello");
    EXPECT_FALSE(re.DoMatch("world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_201, DoMatchUnanchored_201) {
    PCRE re("hello");
    EXPECT_TRUE(re.DoMatch("say hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST_F(PCRETest_201, DoMatchAnchorStart_201) {
    PCRE re("hello");
    EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST_F(PCRETest_201, DoMatchAnchorStartFails_201) {
    PCRE re("world");
    EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST_F(PCRETest_201, DoMatchEmptyPattern_201) {
    PCRE re("");
    EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST_F(PCRETest_201, DoMatchEmptyText_201) {
    PCRE re("abc");
    EXPECT_FALSE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ==================== Replace Tests ====================

TEST_F(PCRETest_201, ReplaceSimple_201) {
    std::string str = "hello world";
    PCRE re("world");
    EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
    EXPECT_EQ("hello there", str);
}

TEST_F(PCRETest_201, ReplaceNoMatch_201) {
    std::string str = "hello world";
    PCRE re("xyz");
    EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
    EXPECT_EQ("hello world", str);
}

TEST_F(PCRETest_201, ReplaceWithCapture_201) {
    std::string str = "hello world";
    PCRE re("(\\w+) (\\w+)");
    EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
    EXPECT_EQ("world hello", str);
}

// ==================== GlobalReplace Tests ====================

TEST_F(PCRETest_201, GlobalReplaceMultipleMatches_201) {
    std::string str = "aaa";
    PCRE re("a");
    int count = PCRE::GlobalReplace(&str, re, "b");
    EXPECT_EQ(3, count);
    EXPECT_EQ("bbb", str);
}

TEST_F(PCRETest_201, GlobalReplaceNoMatch_201) {
    std::string str = "hello";
    PCRE re("xyz");
    int count = PCRE::GlobalReplace(&str, re, "abc");
    EXPECT_EQ(0, count);
    EXPECT_EQ("hello", str);
}

// ==================== Extract Tests ====================

TEST_F(PCRETest_201, ExtractSimple_201) {
    std::string out;
    PCRE re("(\\w+)@(\\w+)");
    EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
    EXPECT_EQ("user at host", out);
}

TEST_F(PCRETest_201, ExtractNoMatch_201) {
    std::string out;
    PCRE re("(\\d+)");
    EXPECT_FALSE(PCRE::Extract("no digits here", re, "\\1", &out));
}

// ==================== CheckRewriteString Tests ====================

TEST_F(PCRETest_201, CheckRewriteStringValid_201) {
    PCRE re("(a)(b)");
    std::string error;
    EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
}

TEST_F(PCRETest_201, CheckRewriteStringInvalidBackref_201) {
    PCRE re("(a)");
    std::string error;
    // \2 references a non-existent group
    EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
    EXPECT_FALSE(error.empty());
}

TEST_F(PCRETest_201, CheckRewriteStringNoBackrefs_201) {
    PCRE re("abc");
    std::string error;
    EXPECT_TRUE(re.CheckRewriteString("replacement", &error));
}

// ==================== Consumed parameter in DoMatch ====================

TEST_F(PCRETest_201, DoMatchConsumedBytes_201) {
    PCRE re("\\d+");
    size_t consumed = 0;
    EXPECT_TRUE(re.DoMatch("12345abc", PCRE::ANCHOR_START, &consumed, nullptr, 0));
    EXPECT_EQ(5u, consumed);
}

TEST_F(PCRETest_201, DoMatchConsumedZeroOnNoMatch_201) {
    PCRE re("\\d+");
    size_t consumed = 0;
    EXPECT_FALSE(re.DoMatch("abc", PCRE::ANCHOR_START, &consumed, nullptr, 0));
}

}  // namespace re2
