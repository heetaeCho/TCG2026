#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include <string>



using namespace re2;

using ::testing::HasSubstr;



class RE2Test_263 : public ::testing::Test {

protected:

    std::string error_message_;

};



TEST_F(RE2Test_263, CheckRewriteString_ValidRewrite_263) {

    RE2 re("(a)(b)");

    EXPECT_TRUE(re.CheckRewriteString("\\1\\2", &error_message_));

    EXPECT_EQ(error_message_, "");

}



TEST_F(RE2Test_263, CheckRewriteString_BackslashAtEnd_263) {

    RE2 re("abc");

    EXPECT_FALSE(re.CheckRewriteString("abc\\", &error_message_));

    EXPECT_THAT(error_message_, HasSubstr("not allowed at end"));

}



TEST_F(RE2Test_263, CheckRewriteString_NonDigitAfterBackslash_263) {

    RE2 re("abc");

    EXPECT_FALSE(re.CheckRewriteString("a\\b", &error_message_));

    EXPECT_THAT(error_message_, HasSubstr("must be followed by a digit or '\\'"));

}



TEST_F(RE2Test_263, CheckRewriteString_TooManyCapturingGroups_263) {

    RE2 re("(a)(b)");

    EXPECT_FALSE(re.CheckRewriteString("\\1\\3", &error_message_));

    EXPECT_THAT(error_message_, HasSubstr("requests 3 matches, but the regexp only has 2"));

}



TEST_F(RE2Test_263, CheckRewriteString_SingleDigitCapturingGroup_263) {

    RE2 re("(a)");

    EXPECT_TRUE(re.CheckRewriteString("\\1", &error_message_));

    EXPECT_EQ(error_message_, "");

}



TEST_F(RE2Test_263, CheckRewriteString_MultipleDigitsInRewrite_263) {

    RE2 re("(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)");

    EXPECT_TRUE(re.CheckRewriteString("\\1\\2\\3\\4\\5\\6\\7\\8\\9\\10", &error_message_));

    EXPECT_EQ(error_message_, "");

}



TEST_F(RE2Test_263, CheckRewriteString_EscapeBackslash_263) {

    RE2 re("abc");

    EXPECT_TRUE(re.CheckRewriteString("a\\\\b", &error_message_));

    EXPECT_EQ(error_message_, "");

}
