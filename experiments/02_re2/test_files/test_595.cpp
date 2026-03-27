#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_595 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RE2Test_595, Constructor_DefaultOptions_595) {

    RE2 re("abc");

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_595, Constructor_PosixOptions_595) {

    RE2::Options options;

    options.set_posix_syntax(true);

    RE2 re("abc", options);

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_595, FullMatch_Success_595) {

    RE2 re("abc");

    EXPECT_TRUE(RE2::FullMatch("abc", re));

}



TEST_F(RE2Test_595, FullMatch_Failure_595) {

    RE2 re("abc");

    EXPECT_FALSE(RE2::FullMatch("abcd", re));

}



TEST_F(RE2Test_595, PartialMatch_Success_595) {

    RE2 re("abc");

    EXPECT_TRUE(RE2::PartialMatch("abcde", re));

}



TEST_F(RE2Test_595, PartialMatch_Failure_595) {

    RE2 re("abc");

    EXPECT_FALSE(RE2::PartialMatch("def", re));

}



TEST_F(RE2Test_595, Replace_Success_595) {

    RE2 re("abc");

    std::string result = "abcdef";

    EXPECT_TRUE(re.Replace(&result, "xyz"));

    EXPECT_EQ(result, "xyzdef");

}



TEST_F(RE2Test_595, GlobalReplace_Success_595) {

    RE2 re("a");

    std::string result = "aaabaaa";

    int count = re.GlobalReplace(&result, "x");

    EXPECT_EQ(count, 3);

    EXPECT_EQ(result, "xxxbxxx");

}



TEST_F(RE2Test_595, Extract_Success_595) {

    RE2 re("(\\d+)-(\\d+)");

    std::string result;

    EXPECT_TRUE(re.Extract("123-456", "$1-$2=$0", &result));

    EXPECT_EQ(result, "123-456=123-456");

}



TEST_F(RE2Test_595, Extract_Failure_595) {

    RE2 re("(\\d+)-(\\d+)");

    std::string result;

    EXPECT_FALSE(re.Extract("abc-def", "$1-$2=$0", &result));

}



TEST_F(RE2Test_595, QuoteMeta_Success_595) {

    std::string quoted = RE2::QuoteMeta("[abc].*");

    EXPECT_EQ(quoted, "\\[abc\\]\\.");

}



TEST_F(RE2Test_595, Match_Success_595) {

    RE2 re("(\\d+)-(\\d+)");

    absl::string_view submatch[3];

    EXPECT_TRUE(re.Match("123-456", 0, 7, RE2::ANCHOR_BOTH, submatch, 3));

    EXPECT_EQ(submatch[1], "123");

    EXPECT_EQ(submatch[2], "456");

}



TEST_F(RE2Test_595, Match_Failure_595) {

    RE2 re("(\\d+)-(\\d+)");

    absl::string_view submatch[3];

    EXPECT_FALSE(re.Match("abc-def", 0, 7, RE2::ANCHOR_BOTH, submatch, 3));

}



TEST_F(RE2Test_595, CheckRewriteString_Success_595) {

    RE2 re("(\\d+)-(\\d+)");

    std::string error;

    EXPECT_TRUE(re.CheckRewriteString("$1-$2=$0", &error));

    EXPECT_EQ(error, "");

}



TEST_F(RE2Test_595, CheckRewriteString_Failure_595) {

    RE2 re("(\\d+)-(\\d+)");

    std::string error;

    EXPECT_FALSE(re.CheckRewriteString("$1-$2=$", &error));

    EXPECT_NE(error, "");

}



TEST_F(RE2Test_595, MaxSubmatch_Success_595) {

    RE2 re("abc");

    EXPECT_EQ(re.MaxSubmatch(""), 0);

    EXPECT_EQ(re.MaxSubmatch("$0"), 0);

    EXPECT_EQ(re.MaxSubmatch("${1}"), 1);

}



TEST_F(RE2Test_595, Rewrite_Success_595) {

    RE2 re("(\\d+)-(\\d+)");

    std::string out;

    absl::string_view vec[] = {"123-456", "123", "456"};

    EXPECT_TRUE(re.Rewrite(&out, "$1-$2=$0", vec, 3));

    EXPECT_EQ(out, "123-456=123-456");

}



TEST_F(RE2Test_595, NumberOfCapturingGroups_Success_595) {

    RE2 re("(\\d+)-(\\d+)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 2);

}



TEST_F(RE2Test_595, ProgramSize_Success_595) {

    RE2 re("abc");

    EXPECT_GT(re.ProgramSize(), 0);

}



TEST_F(RE2Test_595, ReverseProgramSize_Success_595) {

    RE2 re("abc");

    EXPECT_GT(re.ReverseProgramSize(), 0);

}



TEST_F(RE2Test_595, ProgramFanout_Success_595) {

    RE2 re("abc");

    std::vector<int> histogram;

    int fanout = re.ProgramFanout(&histogram);

    EXPECT_GE(fanout, 0);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2Test_595, ReverseProgramFanout_Success_595) {

    RE2 re("abc");

    std::vector<int> histogram;

    int fanout = re.ReverseProgramFanout(&histogram);

    EXPECT_GE(fanout, 0);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2Test_595, NamedCapturingGroups_Success_595) {

    RE2 re("(?P<first>\\d+)-(?P<second>\\d+)");

    const auto& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.size(), 2);

    EXPECT_NE(named_groups.find("first"), named_groups.end());

    EXPECT_NE(named_groups.find("second"), named_groups.end());

}



TEST_F(RE2Test_595, CapturingGroupNames_Success_595) {

    RE2 re("(?P<first>\\d+)-(?P<second>\\d+)");

    const auto& group_names = re.CapturingGroupNames();

    EXPECT_EQ(group_names.size(), 2);

    EXPECT_NE(group_names.find(1), group_names.end());

    EXPECT_NE(group_names.find(2), group_names.end());

}



TEST_F(RE2Test_595, Pattern_Success_595) {

    RE2 re("abc");

    EXPECT_EQ(re.pattern(), "abc");

}
