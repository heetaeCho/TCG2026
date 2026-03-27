#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"



using namespace re2;



class PCRETest_200 : public ::testing::Test {

protected:

    PCRE* pcre_instance;

    

    void SetUp() override {

        pcre_instance = new PCRE("");

    }



    void TearDown() override {

        delete pcre_instance;

    }

};



TEST_F(PCRETest_200, CheckRewriteString_ValidRewrite_200) {

    std::string error;

    EXPECT_TRUE(pcre_instance->CheckRewriteString("abc\\1def", &error));

    EXPECT_EQ(error, "");

}



TEST_F(PCRETest_200, CheckRewriteString_EscapedBackslashAtEnd_200) {

    std::string error;

    EXPECT_FALSE(pcre_instance->CheckRewriteString("abc\\", &error));

    EXPECT_EQ(error, "Rewrite schema error: '\\' not allowed at end.");

}



TEST_F(PCRETest_200, CheckRewriteString_NonDigitAfterBackslash_200) {

    std::string error;

    EXPECT_FALSE(pcre_instance->CheckRewriteString("abc\\xdef", &error));

    EXPECT_EQ(error, "Rewrite schema error: '\\' must be followed by a digit or '\\'.");

}



TEST_F(PCRETest_200, CheckRewriteString_MaxTokenGreaterThanCapturingGroups_200) {

    std::string error;

    // Assuming NumberOfCapturingGroups returns 1 for this test case

    ON_CALL(*pcre_instance, NumberOfCapturingGroups()).WillByDefault(::testing::Return(1));

    EXPECT_FALSE(pcre_instance->CheckRewriteString("abc\\2def", &error));

    EXPECT_EQ(error, "Rewrite schema requests 2 matches, but the regexp only has 1 parenthesized subexpressions.");

}



TEST_F(PCRETest_200, CheckRewriteString_NoBackslash_200) {

    std::string error;

    EXPECT_TRUE(pcre_instance->CheckRewriteString("abcdef", &error));

    EXPECT_EQ(error, "");

}



TEST_F(PCRETest_200, CheckRewriteString_MultipleValidBackslashes_200) {

    std::string error;

    EXPECT_TRUE(pcre_instance->CheckRewriteString("\\1\\2\\3", &error));

    EXPECT_EQ(error, "");

}
