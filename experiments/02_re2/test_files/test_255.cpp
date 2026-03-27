#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include "absl/strings/string_view.h"



using namespace re2;



class RE2Test_255 : public ::testing::Test {

protected:

    RE2 regex_pattern_;

    

    RE2Test_255() : regex_pattern_("abc") {}

};



TEST_F(RE2Test_255, FindAndConsumeN_MatchesPattern_255) {

    absl::string_view input("abcdef");

    const Arg* const args[] = {nullptr};

    int n = 0;

    bool result = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_TRUE(result);

    EXPECT_EQ(input, "def");

}



TEST_F(RE2Test_255, FindAndConsumeN_NoMatch_255) {

    absl::string_view input("xyz");

    const Arg* const args[] = {nullptr};

    int n = 0;

    bool result = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_FALSE(result);

    EXPECT_EQ(input, "xyz");

}



TEST_F(RE2Test_255, FindAndConsumeN_EmptyInput_255) {

    absl::string_view input("");

    const Arg* const args[] = {nullptr};

    int n = 0;

    bool result = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_FALSE(result);

    EXPECT_EQ(input, "");

}



TEST_F(RE2Test_255, FindAndConsumeN_PartialMatchAtStart_255) {

    absl::string_view input("abcxyz");

    const Arg* const args[] = {nullptr};

    int n = 0;

    bool result = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_TRUE(result);

    EXPECT_EQ(input, "xyz");

}



TEST_F(RE2Test_255, FindAndConsumeN_MatchAtEnd_255) {

    absl::string_view input("xyzabc");

    const Arg* const args[] = {nullptr};

    int n = 0;

    bool result = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_TRUE(result);

    EXPECT_EQ(input, "");

}



TEST_F(RE2Test_255, FindAndConsumeN_MultipleMatches_255) {

    absl::string_view input("abcabc");

    const Arg* const args[] = {nullptr};

    int n = 0;

    bool result1 = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_TRUE(result1);

    EXPECT_EQ(input, "abc");



    bool result2 = regex_pattern_.FindAndConsumeN(&input, regex_pattern_, args, n);

    EXPECT_TRUE(result2);

    EXPECT_EQ(input, "");

}
