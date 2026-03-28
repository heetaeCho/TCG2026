#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2QuoteMetaTest : public ::testing::Test {

protected:

    // No setup or teardown required for this simple function.

};



TEST_F(RE2QuoteMetaTest_259, NormalOperation_259) {

    std::string input = "Hello, World!";

    std::string expected_output = "Hello\\, World\\!";

    EXPECT_EQ(expected_output, RE2::QuoteMeta(input));

}



TEST_F(RE2QuoteMetaTest_259, EmptyString_259) {

    std::string input = "";

    std::string expected_output = "";

    EXPECT_EQ(expected_output, RE2::QuoteMeta(input));

}



TEST_F(RE2QuoteMetaTest_259, SpecialCharacters_259) {

    std::string input = ".^$|()[]*+?";

    std::string expected_output = "\\.\\^\\$\\|\\(\\)\\[\\]\\*\\+\\?";

    EXPECT_EQ(expected_output, RE2::QuoteMeta(input));

}



TEST_F(RE2QuoteMetaTest_259, AlphanumericAndUnderscore_259) {

    std::string input = "abc123_ABC";

    std::string expected_output = "abc123_ABC";

    EXPECT_EQ(expected_output, RE2::QuoteMeta(input));

}



TEST_F(RE2QuoteMetaTest_259, NullCharacter_259) {

    std::string input(1, '\0');

    std::string expected_output = "\\x00";

    EXPECT_EQ(expected_output, RE2::QuoteMeta(input));

}



TEST_F(RE2QuoteMetaTest_259, MixedWithNullCharacters_259) {

    std::string input = "Hello\0World!";

    std::string expected_output = "Hello\\x00World\\!";

    EXPECT_EQ(expected_output, RE2::QuoteMeta(input));

}
