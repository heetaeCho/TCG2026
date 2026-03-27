#include <gtest/gtest.h>

#include "re2/re2.h"

#include "re2/set.h"

#include "re2/filtered_re2.h"



namespace {



class RE2FuzzerTest : public ::testing::Test {

protected:

    RE2::Options options;

};



TEST_F(RE2FuzzerTest, NormalOperationWithValidPattern_385) {

    absl::string_view pattern = R"(\d+)";

    absl::string_view text = "12345";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, BoundaryConditionEmptyPattern_385) {

    absl::string_view pattern = "";

    absl::string_view text = "abc";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, BoundaryConditionLongPattern_385) {

    std::string long_pattern(100, 'a');

    absl::string_view pattern(long_pattern);

    absl::string_view text = "abc";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, BoundaryConditionComplexPattern_385) {

    absl::string_view pattern = R"((a|b)*c?d+e{1,3}f[gh]\w\W\s\S\d\D[A-Z][a-z])";

    absl::string_view text = "abcdefghi";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, ErrorCaseInvalidPattern_385) {

    absl::string_view pattern = R"((unclosed)";

    absl::string_view text = "abc";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, NormalOperationWithCapturingGroups_385) {

    absl::string_view pattern = R"(a(b)c(d)e)";

    absl::string_view text = "abcde";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, BoundaryConditionManyCharClasses_385) {

    absl::string_view pattern = ".kSsK.s.";

    absl::string_view text = "abcdefghi";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, BoundaryConditionBackslashP_385) {

    absl::string_view pattern = R"(\p\P)";

    absl::string_view text = "abc";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, NormalOperationWithRE2Set_385) {

    re2::RE2::Set set(options, RE2::Anchor::UNANCHORED);

    int index = set.Add(R"(\d+)", nullptr);

    ASSERT_NE(index, -1);

    bool compiled = set.Compile();

    EXPECT_TRUE(compiled);



    std::vector<int> matches;

    set.Match("12345", &matches);

}



TEST_F(RE2FuzzerTest, NormalOperationWithFilteredRE2_385) {

    re2::FilteredRE2 filter;

    int index = -1;

    filter.Add(R"(\d+)", options, &index);

    ASSERT_NE(index, -1);



    std::vector<std::string> atoms;

    filter.Compile(&atoms);



    std::vector<int> matched_atoms(atoms.size());

    for (size_t i = 0; i < atoms.size(); ++i) {

        matched_atoms[i] = static_cast<int>(i);

    }



    std::vector<int> matches;

    filter.AllMatches("12345", matched_atoms, &matches);

}



TEST_F(RE2FuzzerTest, ErrorCaseEmptyText_385) {

    absl::string_view pattern = R"(\d+)";

    absl::string_view text = "";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, ErrorCasePatternWithTooManyCapturingGroups_385) {

    std::string many_groups;

    for (int i = 0; i < 11; ++i) {

        many_groups += "(a)";

    }

    absl::string_view pattern(many_groups);

    absl::string_view text = "aaaaaaaaaaa";

    TestOneInput(pattern, options, RE2::UNANCHORED, text);

}



TEST_F(RE2FuzzerTest, NormalOperationWithAnchors_385) {

    absl::string_view pattern = "^abc$";

    absl::string_view text = "abc";

    TestOneInput(pattern, options, RE2::ANCHOR_BOTH, text);

}



}  // namespace
