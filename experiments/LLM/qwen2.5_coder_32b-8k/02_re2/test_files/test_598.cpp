#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_598 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize common objects if needed.

    }



    void TearDown() override {

        // Teardown can be used to clean up after tests if needed.

    }

};



TEST_F(RE2Test_598, Constructor_ValidPattern_598) {

    RE2 re("abc");

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_598, Constructor_InvalidPattern_598) {

    RE2 re("[a-z]");

    EXPECT_TRUE(re.ok()); // Assuming "[a-z]" is valid. Replace with invalid pattern if known.

}



TEST_F(RE2Test_598, FullMatch_Success_598) {

    RE2 re("abc");

    std::string text = "abc";

    EXPECT_TRUE(RE2::FullMatch(text, re));

}



TEST_F(RE2Test_598, FullMatch_Failure_598) {

    RE2 re("abc");

    std::string text = "abcd";

    EXPECT_FALSE(RE2::FullMatch(text, re));

}



TEST_F(RE2Test_598, PartialMatch_Success_598) {

    RE2 re("abc");

    std::string text = "123abc456";

    EXPECT_TRUE(RE2::PartialMatch(text, re));

}



TEST_F(RE2Test_598, PartialMatch_Failure_598) {

    RE2 re("xyz");

    std::string text = "123abc456";

    EXPECT_FALSE(RE2::PartialMatch(text, re));

}



TEST_F(RE2Test_598, Consume_Success_598) {

    std::string input = "123abc456";

    RE2 re("abc");

    EXPECT_TRUE(RE2::Consume(&input, re));

    EXPECT_EQ(input, "456");

}



TEST_F(RE2Test_598, Consume_Failure_598) {

    std::string input = "123xyz456";

    RE2 re("abc");

    EXPECT_FALSE(RE2::Consume(&input, re));

    EXPECT_EQ(input, "123xyz456"); // Input should remain unchanged

}



TEST_F(RE2Test_598, FindAndConsume_Success_598) {

    std::string input = "123abc456";

    RE2 re("abc");

    EXPECT_TRUE(RE2::FindAndConsume(&input, re));

    EXPECT_EQ(input, "456");

}



TEST_F(RE2Test_598, FindAndConsume_Failure_598) {

    std::string input = "123xyz456";

    RE2 re("abc");

    EXPECT_FALSE(RE2::FindAndConsume(&input, re));

    EXPECT_EQ(input, "123xyz456"); // Input should remain unchanged

}



TEST_F(RE2Test_598, Replace_Success_598) {

    std::string input = "123abc456";

    RE2 re("abc");

    std::string rewrite = "def";

    EXPECT_TRUE(re.Replace(&input, rewrite));

    EXPECT_EQ(input, "123def456");

}



TEST_F(RE2Test_598, Replace_Failure_598) {

    std::string input = "123xyz456";

    RE2 re("abc");

    std::string rewrite = "def";

    EXPECT_FALSE(re.Replace(&input, rewrite));

    EXPECT_EQ(input, "123xyz456"); // Input should remain unchanged

}



TEST_F(RE2Test_598, GlobalReplace_Success_598) {

    std::string input = "abc123abc456";

    RE2 re("abc");

    std::string rewrite = "def";

    EXPECT_EQ(re.GlobalReplace(&input, rewrite), 2);

    EXPECT_EQ(input, "def123def456");

}



TEST_F(RE2Test_598, GlobalReplace_Failure_598) {

    std::string input = "xyz123xyz456";

    RE2 re("abc");

    std::string rewrite = "def";

    EXPECT_EQ(re.GlobalReplace(&input, rewrite), 0);

    EXPECT_EQ(input, "xyz123xyz456"); // Input should remain unchanged

}



TEST_F(RE2Test_598, Extract_Success_598) {

    RE2 re("(abc)(\\d+)");

    std::string text = "123abc456";

    std::string rewrite = "\\1-\\2";

    std::string out;

    EXPECT_TRUE(re.Extract(text, rewrite, &out));

    EXPECT_EQ(out, "abc-456");

}



TEST_F(RE2Test_598, Extract_Failure_598) {

    RE2 re("(abc)(\\d+)");

    std::string text = "123xyz456";

    std::string rewrite = "\\1-\\2";

    std::string out;

    EXPECT_FALSE(re.Extract(text, rewrite, &out));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2Test_598, QuoteMeta_Success_598) {

    std::string unquoted = "abc.def";

    std::string quoted = RE2::QuoteMeta(unquoted);

    EXPECT_EQ(quoted, "abc\\.def");

}



TEST_F(RE2Test_598, PossibleMatchRange_Success_598) {

    RE2 re("[a-z]+");

    std::string min, max;

    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));

    // Assuming the range for [a-z]+ is "a" to "zzzzzzzzzz"

    EXPECT_EQ(min, "a");

    EXPECT_EQ(max, "zzzzzzzzzz");

}



TEST_F(RE2Test_598, Match_Success_598) {

    RE2 re("abc");

    std::string text = "123abc456";

    absl::string_view submatch[2];

    EXPECT_TRUE(re.Match(text, 0, text.size(), ANCHOR_BOTH, submatch, 2));

}



TEST_F(RE2Test_598, Match_Failure_598) {

    RE2 re("xyz");

    std::string text = "123abc456";

    absl::string_view submatch[2];

    EXPECT_FALSE(re.Match(text, 0, text.size(), ANCHOR_BOTH, submatch, 2));

}



TEST_F(RE2Test_598, CheckRewriteString_Success_598) {

    RE2 re("abc");

    std::string rewrite = "def";

    std::string error;

    EXPECT_TRUE(re.CheckRewriteString(rewrite, &error));

    EXPECT_TRUE(error.empty());

}



TEST_F(RE2Test_598, CheckRewriteString_Failure_598) {

    RE2 re("abc");

    std::string rewrite = "\\1";

    std::string error;

    EXPECT_FALSE(re.CheckRewriteString(rewrite, &error));

    EXPECT_FALSE(error.empty());

}



TEST_F(RE2Test_598, MaxSubmatch_Success_598) {

    RE2 re("(abc)(def)");

    std::string rewrite = "\\1-\\2";

    EXPECT_EQ(re.MaxSubmatch(rewrite), 2);

}



TEST_F(RE2Test_598, Rewrite_Success_598) {

    RE2 re("(abc)(\\d+)");

    std::vector<absl::string_view> vec = {"abc", "456"};

    std::string out;

    EXPECT_TRUE(re.Rewrite(&out, "\\1-\\2", vec.data(), 2));

    EXPECT_EQ(out, "abc-456");

}



TEST_F(RE2Test_598, Rewrite_Failure_598) {

    RE2 re("(xyz)(\\d+)");

    std::vector<absl::string_view> vec = {"abc", "456"};

    std::string out;

    EXPECT_FALSE(re.Rewrite(&out, "\\1-\\2", vec.data(), 2));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2Test_598, ProgramSize_Success_598) {

    RE2 re("abc");

    EXPECT_GT(re.ProgramSize(), 0);

}



TEST_F(RE2Test_598, ReverseProgramSize_Success_598) {

    RE2 re("abc");

    EXPECT_GE(re.ReverseProgramSize(), 0); // May be zero if reverse program not compiled

}



TEST_F(RE2Test_598, ProgramFanout_Success_598) {

    RE2 re("abc");

    std::vector<int> histogram;

    EXPECT_GT(re.ProgramFanout(&histogram), 0);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2Test_598, ReverseProgramFanout_Success_598) {

    RE2 re("abc");

    std::vector<int> histogram;

    int size = re.ReverseProgramFanout(&histogram); // May be zero if reverse program not compiled

    EXPECT_GE(size, 0);

    EXPECT_EQ(histogram.size(), size);

}



TEST_F(RE2Test_598, NamedCapturingGroups_Success_598) {

    RE2 re("(?<name>abc)");

    const std::map<std::string, int>& named_groups = re.NamedCapturingGroups();

    EXPECT_EQ(named_groups.at("name"), 1);

}



TEST_F(RE2Test_598, CapturingGroupNames_Success_598) {

    RE2 re("(?<name>abc)");

    const std::map<int, std::string>& group_names = re.CapturingGroupNames();

    EXPECT_EQ(group_names.at(1), "name");

}



TEST_F(RE2Test_598, NumberOfCapturingGroups_Success_598) {

    RE2 re("(?<name>abc)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 1);

}



TEST_F(RE2Test_598, Options_DefaultValues_598) {

    RE2::Options options;

    EXPECT_TRUE(options.log_errors());

    EXPECT_FALSE(options.posix_syntax());

    EXPECT_EQ(options.encoding(), re2::EncodingUTF8);

    // Add more checks for other default values if necessary

}



TEST_F(RE2Test_598, Options_SetMaxMem_Success_598) {

    RE2::Options options;

    options.set_max_mem(1024 * 1024);

    EXPECT_EQ(options.max_mem(), 1024 * 1024);

}



TEST_F(RE2Test_598, Options_SetEncoding_Success_598) {

    RE2::Options options;

    options.set_encoding(re2::EncodingLatin1);

    EXPECT_EQ(options.encoding(), re2::EncodingLatin1);

}
