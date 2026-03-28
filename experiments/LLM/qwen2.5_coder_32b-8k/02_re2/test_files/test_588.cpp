#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"



using namespace re2;



class PCRETest_588 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PCRETest_588, ConstructorWithStringPattern_588) {

    PCRE pcre("test_pattern");

}



TEST_F(PCRETest_588, ConstructorWithCharArrayPattern_588) {

    PCRE pcre("test_pattern");

}



TEST_F(PCRETest_588, HitLimitInitiallyFalse_588) {

    PCRE pcre("test_pattern");

    EXPECT_FALSE(pcre.HitLimit());

}



TEST_F(PCRETest_588, ClearHitLimitDoesNotThrow_588) {

    PCRE pcre("test_pattern");

    pcre.ClearHitLimit();

}



TEST_F(PCRETest_588, ReplaceWithValidPatternAndRewrite_588) {

    std::string str = "hello world";

    PCRE pcre("world");

    bool result = PCRE::Replace(&str, pcre, "universe");

    EXPECT_TRUE(result);

    EXPECT_EQ(str, "hello universe");

}



TEST_F(PCRETest_588, GlobalReplaceWithValidPatternAndRewrite_588) {

    std::string str = "hello world, hello everyone";

    PCRE pcre("hello");

    int result = PCRE::GlobalReplace(&str, pcre, "hi");

    EXPECT_EQ(result, 2);

    EXPECT_EQ(str, "hi world, hi everyone");

}



TEST_F(PCRETest_588, ExtractWithValidPatternAndRewrite_588) {

    std::string str = "hello world";

    PCRE pcre("world");

    std::string out;

    bool result = PCRE::Extract(str, pcre, "$0", &out);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "world");

}



TEST_F(PCRETest_588, CheckRewriteStringValid_588) {

    PCRE pcre("test_pattern");

    std::string error;

    bool result = pcre.CheckRewriteString("\\1", &error);

    EXPECT_TRUE(result);

    EXPECT_TRUE(error.empty());

}



TEST_F(PCRETest_588, QuoteMetaEscapesSpecialChars_588) {

    std::string quoted = PCRE::QuoteMeta(".$|()[]{}^?*+\\");

    EXPECT_EQ(quoted, "\\Q.$|()[]{}^?*+\\\\E");

}



TEST_F(PCRETest_588, NumberOfCapturingGroupsReturnsNonNegative_588) {

    PCRE pcre("(a)(b)");

    int groups = pcre.NumberOfCapturingGroups();

    EXPECT_GE(groups, 0);

}
