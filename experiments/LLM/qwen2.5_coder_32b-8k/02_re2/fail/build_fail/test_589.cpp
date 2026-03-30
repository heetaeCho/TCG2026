#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"

#include <string>



using namespace re2;

using ::testing::_;

using ::testing::Return;



TEST(PCRETest_589, ConstructorWithPatternAndOption_589) {

    PCRE pcre("test_pattern", Option::kNone);

}



TEST(PCRETest_589, HitLimit_DefaultValue_589) {

    PCRE pcre("test_pattern");

    EXPECT_FALSE(pcre.HitLimit());

}



TEST(PCRETest_589, ClearHitLimit_SetsToFalse_589) {

    PCRE pcre("test_pattern");

    pcre.ClearHitLimit();

    EXPECT_FALSE(pcre.HitLimit());

}



TEST(PCRETest_589, Replace_SuccessfulReplacement_589) {

    std::string str = "abc123";

    PCRE pcre("\\d+");

    bool result = PCRE::Replace(&str, pcre, "XYZ");

    EXPECT_TRUE(result);

    EXPECT_EQ(str, "abcXYZ");

}



TEST(PCRETest_589, Replace_NoMatch_589) {

    std::string str = "abcdef";

    PCRE pcre("\\d+");

    bool result = PCRE::Replace(&str, pcre, "XYZ");

    EXPECT_FALSE(result);

    EXPECT_EQ(str, "abcdef");

}



TEST(PCRETest_589, GlobalReplace_MultipleReplacements_589) {

    std::string str = "abc123def456";

    PCRE pcre("\\d+");

    int count = PCRE::GlobalReplace(&str, pcre, "XYZ");

    EXPECT_EQ(count, 2);

    EXPECT_EQ(str, "abcXYZdefXYZ");

}



TEST(PCRETest_589, GlobalReplace_NoMatch_589) {

    std::string str = "abcdef";

    PCRE pcre("\\d+");

    int count = PCRE::GlobalReplace(&str, pcre, "XYZ");

    EXPECT_EQ(count, 0);

    EXPECT_EQ(str, "abcdef");

}



TEST(PCRETest_589, Extract_SuccessfulExtraction_589) {

    std::string out;

    PCRE pcre("(\\d+)def(\\d+)");

    bool result = PCRE::Extract("abc123def456", pcre, "$1-$2", &out);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "123-456");

}



TEST(PCRETest_589, Extract_NoMatch_589) {

    std::string out;

    PCRE pcre("(\\d+)def(\\d+)");

    bool result = PCRE::Extract("abcdef", pcre, "$1-$2", &out);

    EXPECT_FALSE(result);

    EXPECT_EQ(out, "");

}



TEST(PCRETest_589, CheckRewriteString_ValidRewrite_589) {

    std::string error;

    PCRE pcre("(\\d+)def(\\d+)");

    bool result = pcre.CheckRewriteString("\\1-\\2", &error);

    EXPECT_TRUE(result);

    EXPECT_EQ(error, "");

}



TEST(PCRETest_589, CheckRewriteString_InvalidRewrite_589) {

    std::string error;

    PCRE pcre("(\\d+)def(\\d+)");

    bool result = pcre.CheckRewriteString("\\3", &error);

    EXPECT_FALSE(result);

    EXPECT_NE(error, "");

}



TEST(PCRETest_589, QuoteMeta_EscapesSpecialCharacters_589) {

    std::string quoted = PCRE::QuoteMeta("abc.def(ghi)");

    EXPECT_EQ(quoted, "abc\\.def\\(ghi\\)");

}



TEST(PCRETest_589, NumberOfCapturingGroups_ValidPattern_589) {

    PCRE pcre("(a)(b)(c)");

    int count = pcre.NumberOfCapturingGroups();

    EXPECT_EQ(count, 3);

}



TEST(PCRETest_589, DoMatch_SuccessfulMatch_589) {

    PCRE pcre("abc\\d+");

    size_t consumed = 0;

    bool result = pcre.DoMatch("abc123", Anchor::kUnanchored, &consumed, nullptr, 0);

    EXPECT_TRUE(result);

    EXPECT_EQ(consumed, 6);

}



TEST(PCRETest_589, DoMatch_NoMatch_589) {

    PCRE pcre("abc\\d+");

    size_t consumed = 0;

    bool result = pcre.DoMatch("abcdef", Anchor::kUnanchored, &consumed, nullptr, 0);

    EXPECT_FALSE(result);

}



TEST(PCRETest_589, DoMatch_AnchorStart_SuccessfulMatch_589) {

    PCRE pcre("^abc");

    size_t consumed = 0;

    bool result = pcre.DoMatch("abcdef", Anchor::kAnchorStart, &consumed, nullptr, 0);

    EXPECT_TRUE(result);

    EXPECT_EQ(consumed, 3);

}



TEST(PCRETest_589, DoMatch_AnchorEnd_NoMatch_589) {

    PCRE pcre("def$");

    size_t consumed = 0;

    bool result = pcre.DoMatch("abcdef", Anchor::kAnchorEnd, &consumed, nullptr, 0);

    EXPECT_FALSE(result);

}
