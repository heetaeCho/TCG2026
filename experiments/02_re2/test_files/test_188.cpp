#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"

#include "absl/strings/string_view.h"



using namespace re2;



TEST(PCRETest_188, ConstructorWithStringPattern_188) {

    PCRE pcre_obj("test_pattern");

}



TEST(PCRETest_188, ConstructorWithCharPtrPattern_188) {

    const char* pattern = "test_pattern";

    PCRE pcre_obj(pattern);

}



TEST(PCRETest_188, HitLimit_DefaultValueFalse_188) {

    PCRE pcre_obj("test_pattern");

    EXPECT_FALSE(pcre_obj.HitLimit());

}



TEST(PCRETest_188, ClearHitLimit_NoEffectOnDefaultValue_188) {

    PCRE pcre_obj("test_pattern");

    pcre_obj.ClearHitLimit();

    EXPECT_FALSE(pcre_obj.HitLimit());

}



TEST(PCRETest_188, NumberOfCapturingGroups_ReturnsCorrectValue_188) {

    PCRE pcre_obj("(a)(b)");

    int num_groups = pcre_obj.NumberOfCapturingGroups();

    EXPECT_EQ(num_groups, 2);

}



TEST(PCRETest_188, QuoteMeta_EscapesSpecialCharacters_188) {

    std::string result = PCRE::QuoteMeta(".[]{}()^$|*+");

    EXPECT_EQ(result, "\\[\\]\\{\\}\\(\\)\\^\\$\\|\\*\\+");

}



TEST(PCRETest_188, Replace_FindsAndReplacesSubstring_188) {

    std::string str = "hello world";

    PCRE pcre_obj("world");

    bool success = PCRE::Replace(&str, pcre_obj, "universe");

    EXPECT_TRUE(success);

    EXPECT_EQ(str, "hello universe");

}



TEST(PCRETest_188, Replace_NoMatchNoChange_188) {

    std::string str = "hello world";

    PCRE pcre_obj("test");

    bool success = PCRE::Replace(&str, pcre_obj, "universe");

    EXPECT_FALSE(success);

    EXPECT_EQ(str, "hello world");

}



TEST(PCRETest_188, GlobalReplace_ReplacesAllOccurrences_188) {

    std::string str = "aa bb aa";

    PCRE pcre_obj("aa");

    int count = PCRE::GlobalReplace(&str, pcre_obj, "cc");

    EXPECT_EQ(count, 2);

    EXPECT_EQ(str, "cc bb cc");

}



TEST(PCRETest_188, Extract_FindsAndExtractsSubstring_188) {

    std::string str;

    PCRE pcre_obj("(\\w+) (\\w+)");

    bool success = PCRE::Extract("hello world", pcre_obj, "\\2 \\1", &str);

    EXPECT_TRUE(success);

    EXPECT_EQ(str, "world hello");

}



TEST(PCRETest_188, Extract_NoMatchNoChange_188) {

    std::string str;

    PCRE pcre_obj("(\\w+) (\\w+)");

    bool success = PCRE::Extract("hello", pcre_obj, "\\2 \\1", &str);

    EXPECT_FALSE(success);

    EXPECT_TRUE(str.empty());

}



TEST(PCRETest_188, CheckRewriteString_ValidRewriteNoError_188) {

    std::string error;

    PCRE pcre_obj("(\\w+) (\\w+)");

    bool success = pcre_obj.CheckRewriteString("\\2 \\1", &error);

    EXPECT_TRUE(success);

    EXPECT_TRUE(error.empty());

}



TEST(PCRETest_188, CheckRewriteString_InvalidRewriteWithError_188) {

    std::string error;

    PCRE pcre_obj("(\\w+) (\\w+)");

    bool success = pcre_obj.CheckRewriteString("\\3 \\1", &error);

    EXPECT_FALSE(success);

    EXPECT_FALSE(error.empty());

}



TEST(PCRETest_188, DoMatch_MatchesPattern_188) {

    PCRE pcre_obj("hello");

    size_t consumed;

    bool match = pcre_obj.DoMatch("hello world", UNANCHORED, &consumed, nullptr, 0);

    EXPECT_TRUE(match);

    EXPECT_EQ(consumed, 5);

}



TEST(PCRETest_188, DoMatch_NoMatch_ReturnsFalse_188) {

    PCRE pcre_obj("test");

    size_t consumed;

    bool match = pcre_obj.DoMatch("hello world", UNANCHORED, &consumed, nullptr, 0);

    EXPECT_FALSE(match);

}
