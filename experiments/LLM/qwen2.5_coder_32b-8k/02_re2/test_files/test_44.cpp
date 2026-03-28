#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test : public ::testing::Test {

protected:

    RE2* re2;

    

    void SetUp() override {

        re2 = new RE2("abc");

    }



    void TearDown() override {

        delete re2;

    }

};



TEST_F(RE2Test_44, FullMatch_ReturnsTrueForExactMatch_44) {

    EXPECT_TRUE(RE2::FullMatch("abc", *re2));

}



TEST_F(RE2Test_44, FullMatch_ReturnsFalseForNonExactMatch_44) {

    EXPECT_FALSE(RE2::FullMatch("abcd", *re2));

}



TEST_F(RE2Test_44, PartialMatch_ReturnsTrueForPartialMatch_44) {

    EXPECT_TRUE(RE2::PartialMatch("abcde", *re2));

}



TEST_F(RE2Test_44, PartialMatch_ReturnsFalseForNoMatch_44) {

    EXPECT_FALSE(RE2::PartialMatch("def", *re2));

}



TEST_F(RE2Test_44, Consume_ConsumesExactMatchFromStart_44) {

    absl::string_view input = "abcde";

    EXPECT_TRUE(RE2::Consume(&input, *re2));

    EXPECT_EQ(input, "de");

}



TEST_F(RE2Test_44, Consume_ReturnsFalseForNonMatch_44) {

    absl::string_view input = "def";

    EXPECT_FALSE(RE2::Consume(&input, *re2));

    EXPECT_EQ(input, "def");

}



TEST_F(RE2Test_44, FindAndConsume_ConsumesFirstOccurrence_44) {

    absl::string_view input = "xyzabcuvw";

    EXPECT_TRUE(RE2::FindAndConsume(&input, *re2));

    EXPECT_EQ(input, "uvw");

}



TEST_F(RE2Test_44, FindAndConsume_ReturnsFalseForNoMatch_44) {

    absl::string_view input = "xyzdefuvw";

    EXPECT_FALSE(RE2::FindAndConsume(&input, *re2));

    EXPECT_EQ(input, "xyzdefuvw");

}



TEST_F(RE2Test_44, Replace_ReplacesFirstOccurrence_44) {

    std::string text = "abcdeabc";

    EXPECT_TRUE(re2->Replace(&text, "XYZ"));

    EXPECT_EQ(text, "XYZdeabc");

}



TEST_F(RE2Test_44, GlobalReplace_ReplacesAllOccurrences_44) {

    std::string text = "abcdeabc";

    int count = re2->GlobalReplace(&text, "XYZ");

    EXPECT_EQ(count, 2);

    EXPECT_EQ(text, "XYZdeXYZ");

}



TEST_F(RE2Test_44, Extract_ExtractsMatchedGroup_44) {

    RE2 re("a(b)c");

    std::string result;

    EXPECT_TRUE(re.Extract("abc", "$1", &result));

    EXPECT_EQ(result, "b");

}



TEST_F(RE2Test_44, Extract_ReturnsFalseForNoMatch_44) {

    std::string result;

    EXPECT_FALSE(re2->Extract("def", "abc", &result));

    EXPECT_TRUE(result.empty());

}



TEST_F(RE2Test_44, QuoteMeta_EscapesSpecialCharacters_44) {

    std::string escaped = RE2::QuoteMeta("[abc].*");

    EXPECT_EQ(escaped, "\\[abc\\]\\.\\*");

}



TEST_F(RE2Test_44, ProgramSize_ReturnsNonNegativeValue_44) {

    EXPECT_GE(re2->ProgramSize(), 0);

}



TEST_F(RE2Test_44, ReverseProgramSize_ReturnsNonNegativeValue_44) {

    EXPECT_GE(re2->ReverseProgramSize(), 0);

}



TEST_F(RE2Test_44, NamedCapturingGroups_ReturnsEmptyMapIfNone_44) {

    std::map<std::string, int> named_groups = re2->NamedCapturingGroups();

    EXPECT_TRUE(named_groups.empty());

}



TEST_F(RE2Test_44, CapturingGroupNames_ReturnsEmptyMapIfNone_44) {

    std::map<int, std::string> group_names = re2->CapturingGroupNames();

    EXPECT_TRUE(group_names.empty());

}



TEST_F(RE2Test_44, NumberOfCapturingGroups_ReturnsZeroForNoGroups_44) {

    EXPECT_EQ(re2->NumberOfCapturingGroups(), 0);

}



TEST_F(RE2Test_44, Options_ReturnsDefaultOptions_44) {

    RE2::Options options = re2->options();

    // Assuming default options have a known state which can be checked

    // This is a placeholder as actual checks depend on implementation details

    EXPECT_TRUE(options.pattern_casing() == RE2::CaseSensitive);

}



TEST_F(RE2Test_44, Hex_ReturnsValidArg_44) {

    int value;

    auto arg = re2->Hex(&value);

    (void)arg; // Suppress unused variable warning

}



} // namespace re2
