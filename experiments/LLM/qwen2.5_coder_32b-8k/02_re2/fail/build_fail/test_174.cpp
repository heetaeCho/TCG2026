#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/re2/util/pcre.h"

#include <string>



using namespace re2;



// Test fixture for PCRE class

class PCRETest_174 : public ::testing::Test {

protected:

    std::string test_pattern = "test_pattern";

};



TEST_F(PCRETest_174, ConstructorWithCString_174) {

    PCRE pcre(test_pattern.c_str());

    EXPECT_EQ(pcre.pattern(), test_pattern);

}



TEST_F(PCRETest_174, ConstructorWithString_174) {

    PCRE pcre(test_pattern);

    EXPECT_EQ(pcre.pattern(), test_pattern);

}



TEST_F(PCRETest_174, HitLimitInitiallyFalse_174) {

    PCRE pcre(test_pattern);

    EXPECT_FALSE(pcre.HitLimit());

}



TEST_F(PCRETest_174, ClearHitLimitDoesNotCrash_174) {

    PCRE pcre(test_pattern);

    pcre.ClearHitLimit();

}



TEST_F(PCRETest_174, QuoteMetaEscapesSpecialCharacters_174) {

    std::string special_chars = ".*+?^${}()|[]\\";

    std::string expected_result = "\\Q.*+?^${}()|[\\]\\E";

    EXPECT_EQ(PCRE::QuoteMeta(special_chars), expected_result);

}



TEST_F(PCRETest_174, NumberOfCapturingGroupsBoundary_174) {

    PCRE pcre("(a)(b)(c)");

    EXPECT_EQ(pcre.NumberOfCapturingGroups(), 3);

}



TEST_F(PCRETest_174, CheckRewriteStringValidRewrite_174) {

    PCRE pcre(test_pattern);

    std::string rewrite = "valid_rewrite";

    std::string error;

    EXPECT_TRUE(pcre.CheckRewriteString(rewrite, &error));

    EXPECT_EQ(error, "");

}



TEST_F(PCRETest_174, CheckRewriteStringInvalidRewrite_174) {

    PCRE pcre(test_pattern);

    std::string rewrite = "\\g<invalid>";

    std::string error;

    EXPECT_FALSE(pcre.CheckRewriteString(rewrite, &error));

    EXPECT_NE(error, "");

}



TEST_F(PCRETest_174, ExtractBoundaryConditions_174) {

    PCRE pcre("(\\d+)-(\\w+)");

    std::string text = "123-abc";

    std::string rewrite = "\\1:\\2";

    std::string out;

    EXPECT_TRUE(pcre.Extract(text, pcre, rewrite, &out));

    EXPECT_EQ(out, "123:abc");

}



TEST_F(PCRETest_174, ReplaceBoundaryConditions_174) {

    PCRE pcre("(\\d+)-(\\w+)");

    std::string text = "123-abc";

    std::string rewrite = "\\1:\\2";

    EXPECT_TRUE(pcre.Replace(&text, pcre, rewrite));

    EXPECT_EQ(text, "123:abc");

}



TEST_F(PCRETest_174, GlobalReplaceBoundaryConditions_174) {

    PCRE pcre("(\\d+)-(\\w+)");

    std::string text = "123-abc 456-def";

    std::string rewrite = "\\1:\\2";

    EXPECT_EQ(pcre.GlobalReplace(&text, pcre, rewrite), 2);

    EXPECT_EQ(text, "123:abc 456:def");

}



TEST_F(PCRETest_174, DoMatchBoundaryConditions_174) {

    PCRE pcre("\\d+");

    std::string text = "123";

    size_t consumed = 0;

    EXPECT_TRUE(pcre.DoMatch(text, Anchor::UNANCHORED, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 3);

}



TEST_F(PCRETest_174, ErrorInitiallyEmpty_174) {

    PCRE pcre(test_pattern);

    EXPECT_EQ(pcre.error(), "");

}
