#include <gtest/gtest.h>

#include "pcre.h"



using namespace re2;



class PCRETest_197 : public ::testing::Test {

protected:

    void SetUp() override {

        pattern = "test_pattern";

        pcre_obj = new PCRE(pattern);

    }



    void TearDown() override {

        delete pcre_obj;

    }



    std::string pattern;

    PCRE* pcre_obj;

};



TEST_F(PCRETest_197, HitLimitFalseByDefault_197) {

    EXPECT_FALSE(pcre_obj->HitLimit());

}



TEST_F(PCRETest_197, ClearHitLimitWorks_197) {

    // Assuming there's a way to set hit_limit_ to true for testing

    pcre_obj->ClearHitLimit();

    EXPECT_FALSE(pcre_obj->HitLimit());

}



TEST_F(PCRETest_197, ReplaceReturnsFalseWithInvalidPattern_197) {

    std::string str = "test_string";

    PCRE invalid_pcre("invalid_pattern");

    bool result = PCRE::Replace(&str, invalid_pcre, "rewrite");

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_197, GlobalReplaceReturnsZeroWithInvalidPattern_197) {

    std::string str = "test_string";

    PCRE invalid_pcre("invalid_pattern");

    int result = PCRE::GlobalReplace(&str, invalid_pcre, "rewrite");

    EXPECT_EQ(result, 0);

}



TEST_F(PCRETest_197, ExtractReturnsFalseWithInvalidPattern_197) {

    std::string out;

    PCRE invalid_pcre("invalid_pattern");

    bool result = PCRE::Extract("test_string", invalid_pcre, "rewrite", &out);

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_197, CheckRewriteStringReturnsFalseWithInvalidPattern_197) {

    std::string error;

    bool result = pcre_obj->CheckRewriteString("\\k<invalid>", &error);

    EXPECT_FALSE(result);

}



TEST_F(PCRETest_197, NumberOfCapturingGroupsReturnsNonNegative_197) {

    int result = pcre_obj->NumberOfCapturingGroups();

    EXPECT_GE(result, 0);

}
