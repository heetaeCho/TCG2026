#include <gtest/gtest.h>

#include "pcre.h"

#include <string>



using namespace re2;



class PCRETest_587 : public ::testing::Test {

protected:

    void SetUp() override {

        pattern = "test_pattern";

        option = Option();

    }



    std::string pattern;

    Option option;

};



TEST_F(PCRETest_587, ConstructorWithPatternAndOption_587) {

    PCRE pcre(pattern.c_str(), option);

}



TEST_F(PCRETest_587, HitLimitInitiallyFalse_587) {

    PCRE pcre(pattern.c_str(), option);

    EXPECT_FALSE(pcre.HitLimit());

}



TEST_F(PCRETest_587, ClearHitLimitDoesNothingWhenFalse_587) {

    PCRE pcre(pattern.c_str(), option);

    pcre.ClearHitLimit();

    EXPECT_FALSE(pcre.HitLimit());

}



TEST_F(PCRETest_587, NumberOfCapturingGroupsZeroByDefault_587) {

    PCRE pcre(pattern.c_str(), option);

    EXPECT_EQ(0, pcre.NumberOfCapturingGroups());

}



TEST_F(PCRETest_587, ReplaceWithEmptyString_587) {

    std::string str = "test_string";

    PCRE pcre("non_matching_pattern", option);

    bool result = PCRE::Replace(&str, pcre, "");

    EXPECT_TRUE(result);

    EXPECT_EQ("test_string", str);

}



TEST_F(PCRETest_587, GlobalReplaceWithEmptyString_587) {

    std::string str = "test_string";

    PCRE pcre("non_matching_pattern", option);

    int result = PCRE::GlobalReplace(&str, pcre, "");

    EXPECT_EQ(0, result);

    EXPECT_EQ("test_string", str);

}



TEST_F(PCRETest_587, ExtractWithNonMatchingPattern_587) {

    std::string out;

    PCRE pcre("non_matching_pattern", option);

    bool result = PCRE::Extract("test_string", pcre, "", &out);

    EXPECT_FALSE(result);

    EXPECT_TRUE(out.empty());

}



TEST_F(PCRETest_587, QuoteMetaDoesNotModifySimpleString_587) {

    std::string quoted = PCRE::QuoteMeta("simple_string");

    EXPECT_EQ("simple_string", quoted);

}



TEST_F(PCRETest_587, CheckRewriteStringWithValidString_587) {

    std::string error;

    PCRE pcre(pattern.c_str(), option);

    bool result = pcre.CheckRewriteString("\\1\\2", &error);

    EXPECT_TRUE(result);

    EXPECT_TRUE(error.empty());

}



TEST_F(PCRETest_587, CheckRewriteStringWithInvalidString_587) {

    std::string error;

    PCRE pcre(pattern.c_str(), option);

    bool result = pcre.CheckRewriteString("\\g", &error);

    EXPECT_FALSE(result);

    EXPECT_FALSE(error.empty());

}



TEST_F(PCRETest_587, DoMatchWithNonMatchingPattern_587) {

    PCRE pcre("non_matching_pattern", option);

    size_t consumed = 0;

    bool result = pcre.DoMatch("test_string", Anchor::ANCHOR_START, &consumed, nullptr, 0);

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_587, DoMatchWithMatchingPattern_587) {

    PCRE pcre("test_string", option);

    size_t consumed = 0;

    bool result = pcre.DoMatch("test_string", Anchor::ANCHOR_START, &consumed, nullptr, 0);

    EXPECT_TRUE(result);

    EXPECT_EQ(consumed, std::string("test_string").size());

}
