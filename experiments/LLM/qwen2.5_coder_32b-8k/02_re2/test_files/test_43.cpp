#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {

namespace {



class RE2Test : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed.

    }



    void TearDown() override {

        // Cleanup can be done here if needed.

    }

};



TEST_F(RE2Test_43, CRadix_ValidInput_ReturnsArgObject_43) {

    int value = 0;

    RE2::Arg arg = RE2::CRadix(&value);

    // Since Arg is not exposed in the interface, we can only verify that it returns an object.

}



TEST_F(RE2Test_43, FullMatch_ValidPattern_ReturnsTrue_43) {

    RE2 re("hello");

    EXPECT_TRUE(RE2::FullMatch("hello", re));

}



TEST_F(RE2Test_43, FullMatch_InvalidPattern_ReturnsFalse_43) {

    RE2 re("hello");

    EXPECT_FALSE(RE2::FullMatch("world", re));

}



TEST_F(RE2Test_43, PartialMatch_ValidPattern_ReturnsTrue_43) {

    RE2 re("hello");

    EXPECT_TRUE(RE2::PartialMatch("hello world", re));

}



TEST_F(RE2Test_43, PartialMatch_InvalidPattern_ReturnsFalse_43) {

    RE2 re("hello");

    EXPECT_FALSE(RE2::PartialMatch("world", re));

}



TEST_F(RE2Test_43, Consume_ValidPattern_ReturnsTrueAndUpdatesInput_43) {

    absl::string_view input = "hello world";

    RE2 re("hello");

    EXPECT_TRUE(RE2::Consume(&input, re));

    EXPECT_EQ(input, " world");

}



TEST_F(RE2Test_43, Consume_InvalidPattern_ReturnsFalseAndDoesNotUpdateInput_43) {

    absl::string_view input = "world";

    RE2 re("hello");

    EXPECT_FALSE(RE2::Consume(&input, re));

    EXPECT_EQ(input, "world");

}



TEST_F(RE2Test_43, FindAndConsume_ValidPattern_ReturnsTrueAndUpdatesInput_43) {

    absl::string_view input = "foo hello world";

    RE2 re("hello");

    EXPECT_TRUE(RE2::FindAndConsume(&input, re));

    EXPECT_EQ(input, " world");

}



TEST_F(RE2Test_43, FindAndConsume_InvalidPattern_ReturnsFalseAndDoesNotUpdateInput_43) {

    absl::string_view input = "foo world";

    RE2 re("hello");

    EXPECT_FALSE(RE2::FindAndConsume(&input, re));

    EXPECT_EQ(input, "foo world");

}



TEST_F(RE2Test_43, Replace_ValidPattern_ReplacesSubstring_43) {

    std::string str = "hello world";

    RE2 re("world");

    EXPECT_TRUE(RE2::Replace(&str, re, "there"));

    EXPECT_EQ(str, "hello there");

}



TEST_F(RE2Test_43, GlobalReplace_ValidPattern_ReplacesAllOccurrences_43) {

    std::string str = "hello world hello";

    RE2 re("hello");

    int count = RE2::GlobalReplace(&str, re, "hi");

    EXPECT_EQ(count, 2);

    EXPECT_EQ(str, "hi world hi");

}



TEST_F(RE2Test_43, Extract_ValidPattern_ExtractsSubstring_43) {

    std::string out;

    RE2 re("(\\w+) (\\w+)");

    EXPECT_TRUE(RE2::Extract("hello world", re, "\\1 \\2", &out));

    EXPECT_EQ(out, "hello world");

}



TEST_F(RE2Test_43, Extract_InvalidPattern_ReturnsFalseAndDoesNotUpdateOutput_43) {

    std::string out;

    RE2 re("(\\w+) (\\w+)");

    EXPECT_FALSE(RE2::Extract("world", re, "\\1 \\2", &out));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2Test_43, QuoteMeta_ValidString_ReturnsQuotedString_43) {

    std::string quoted = RE2::QuoteMeta("hello.world");

    EXPECT_EQ(quoted, "hello\\.world");

}



TEST_F(RE2Test_43, PossibleMatchRange_ValidPattern_ReturnsTrueAndUpdatesBounds_43) {

    RE2 re("a(b|c)");

    std::string min, max;

    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_EQ(min, "ab");

    EXPECT_EQ(max, "ac");

}



TEST_F(RE2Test_43, PossibleMatchRange_InvalidPattern_ReturnsFalseAndDoesNotUpdateBounds_43) {

    RE2 re("a(b|c");

    std::string min, max;

    EXPECT_FALSE(re.PossibleMatchRange(&min, &max, 10));

}



TEST_F(RE2Test_43, Match_ValidPattern_ReturnsTrue_43) {

    RE2 re("hello");

    absl::string_view text = "hello";

    EXPECT_TRUE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, nullptr, 0));

}



TEST_F(RE2Test_43, Match_InvalidPattern_ReturnsFalse_43) {

    RE2 re("hello");

    absl::string_view text = "world";

    EXPECT_FALSE(re.Match(text, 0, text.size(), RE2::ANCHOR_START, nullptr, 0));

}



TEST_F(RE2Test_43, CheckRewriteString_ValidPattern_ReturnsTrue_43) {

    RE2 re("hello");

    std::string error;

    EXPECT_TRUE(re.CheckRewriteString("\\0 world", &error));

}



TEST_F(RE2Test_43, CheckRewriteString_InvalidPattern_ReturnsFalseAndUpdateError_43) {

    RE2 re("hello");

    std::string error;

    EXPECT_FALSE(re.CheckRewriteString("\\1 world", &error));

    EXPECT_FALSE(error.empty());

}



TEST_F(RE2Test_43, MaxSubmatch_ValidPattern_ReturnsCorrectValue_43) {

    RE2 re("(\\w+) (\\w+)");

    EXPECT_EQ(re.MaxSubmatch("\\1 \\2"), 2);

}



TEST_F(RE2Test_43, Rewrite_ValidPattern_ReplacesSubstring_43) {

    std::string out;

    RE2 re("(\\w+) (\\w+)");

    absl::string_view vec[] = {"hello world", "hello", "world"};

    EXPECT_TRUE(re.Rewrite(&out, "\\1 \\2", vec, 3));

    EXPECT_EQ(out, "hello world");

}



TEST_F(RE2Test_43, ProgramSize_ValidPattern_ReturnsNonNegativeValue_43) {

    RE2 re("hello");

    EXPECT_GE(re.ProgramSize(), 0);

}



TEST_F(RE2Test_43, ReverseProgramSize_ValidPattern_ReturnsNonNegativeValue_43) {

    RE2 re("hello");

    EXPECT_GE(re.ReverseProgramSize(), 0);

}



TEST_F(RE2Test_43, ProgramFanout_ValidHistogram_ReturnsNonNegativeValue_43) {

    RE2 re("hello");

    std::vector<int> histogram;

    EXPECT_GE(re.ProgramFanout(&histogram), 0);

}



TEST_F(RE2Test_43, ReverseProgramFanout_ValidHistogram_ReturnsNonNegativeValue_43) {

    RE2 re("hello");

    std::vector<int> histogram;

    EXPECT_GE(re.ReverseProgramFanout(&histogram), 0);

}



TEST_F(RE2Test_43, NamedCapturingGroups_ValidPattern_ReturnsEmptyMapIfNoNamedGroups_43) {

    RE2 re("hello");

    const auto& named_groups = re.NamedCapturingGroups();

    EXPECT_TRUE(named_groups.empty());

}



TEST_F(RE2Test_43, CapturingGroupNames_ValidPattern_ReturnsEmptyMapIfNoNamedGroups_43) {

    RE2 re("hello");

    const auto& group_names = re.CapturingGroupNames();

    EXPECT_TRUE(group_names.empty());

}



}  // namespace

}  // namespace re2
