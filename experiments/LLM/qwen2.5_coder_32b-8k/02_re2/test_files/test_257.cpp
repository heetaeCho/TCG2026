#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



class RE2GlobalReplaceTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset maximum_global_replace_count to default value for each test

        RE2::FUZZING_ONLY_set_maximum_global_replace_count(-1);

    }

};



TEST_F(RE2GlobalReplaceTest_257, NormalReplacement_257) {

    std::string input = "hello world";

    RE2 re("world");

    int result = RE2::GlobalReplace(&input, re, "universe");

    EXPECT_EQ(result, 1);

    EXPECT_EQ(input, "hello universe");

}



TEST_F(RE2GlobalReplaceTest_257, NoMatch_257) {

    std::string input = "hello world";

    RE2 re("test");

    int result = RE2::GlobalReplace(&input, re, "universe");

    EXPECT_EQ(result, 0);

    EXPECT_EQ(input, "hello world");

}



TEST_F(RE2GlobalReplaceTest_257, MultipleMatches_257) {

    std::string input = "banana";

    RE2 re("a");

    int result = RE2::GlobalReplace(&input, re, "o");

    EXPECT_EQ(result, 3);

    EXPECT_EQ(input, "bonono");

}



TEST_F(RE2GlobalReplaceTest_257, EmptyReplacementString_257) {

    std::string input = "banana";

    RE2 re("a");

    int result = RE2::GlobalReplace(&input, re, "");

    EXPECT_EQ(result, 3);

    EXPECT_EQ(input, "bnn");

}



TEST_F(RE2GlobalReplaceTest_257, MultipleCapturingGroupsExceedLimit_257) {

    std::string input = "banana";

    RE2 re("(a)(n)");

    absl::string_view rewrite = "\\1\\2o"; // This would require 4 submatches (1 + max_submatch)

    int result = RE2::GlobalReplace(&input, re, rewrite);

    EXPECT_EQ(result, false);

}



TEST_F(RE2GlobalReplaceTest_257, RewriteStringTooLarge_257) {

    std::string input = "banana";

    RE2 re("a");

    absl::string_view rewrite = "\\1\\2o"; // This would require 4 submatches (1 + max_submatch)

    int result = RE2::GlobalReplace(&input, re, rewrite);

    EXPECT_EQ(result, false);

}



TEST_F(RE2GlobalReplaceTest_257, MaximumReplacementCountReached_257) {

    std::string input = "banana";

    RE2 re("a");

    RE2::FUZZING_ONLY_set_maximum_global_replace_count(1);

    int result = RE2::GlobalReplace(&input, re, "o");

    EXPECT_EQ(result, 1);

    EXPECT_EQ(input, "bonana");

}



TEST_F(RE2GlobalReplaceTest_257, RewriteWithCapturingGroup_257) {

    std::string input = "hello world";

    RE2 re("(\\w+) (\\w+)");

    int result = RE2::GlobalReplace(&input, re, "\\2 \\1");

    EXPECT_EQ(result, 1);

    EXPECT_EQ(input, "world hello");

}



TEST_F(RE2GlobalReplaceTest_257, EmptyStringInput_257) {

    std::string input = "";

    RE2 re("a");

    int result = RE2::GlobalReplace(&input, re, "o");

    EXPECT_EQ(result, 0);

    EXPECT_EQ(input, "");

}



TEST_F(RE2GlobalReplaceTest_257, EmptyPattern_257) {

    std::string input = "banana";

    RE2 re("");

    int result = RE2::GlobalReplace(&input, re, "o");

    EXPECT_EQ(result, false);

}
