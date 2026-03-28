#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "filtered_re2.h"

#include "absl/strings/string_view.h"



namespace re2 {

using ::testing::Eq;



class FilteredRE2Test_471 : public ::testing::Test {

protected:

    FilteredRE2 filteredRe2;

};



TEST_F(FilteredRE2Test_471, AddPattern_Success_471) {

    int id = -1;

    RE2::ErrorCode errorCode = filteredRe2.Add("test_pattern", RE2::Options(), &id);

    EXPECT_EQ(errorCode, RE2::NoError);

    EXPECT_GE(id, 0);

}



TEST_F(FilteredRE2Test_471, AddPattern_NullIdPointer_471) {

    RE2::ErrorCode errorCode = filteredRe2.Add("test_pattern", RE2::Options(), nullptr);

    EXPECT_EQ(errorCode, RE2::NoError);

}



TEST_F(FilteredRE2Test_471, Compile_EmptyStrings_471) {

    std::vector<std::string> strings_to_match;

    filteredRe2.Compile(&strings_to_match);

    // Assuming compile succeeds without error for an empty list

}



TEST_F(FilteredRE2Test_471, SlowFirstMatch_NoMatches_471) {

    absl::string_view text = "no_matches_here";

    int result = filteredRe2.SlowFirstMatch(text);

    EXPECT_EQ(result, -1); // Assuming -1 indicates no match

}



TEST_F(FilteredRE2Test_471, FirstMatch_EmptyAtoms_471) {

    absl::string_view text = "test_text";

    std::vector<int> atoms;

    int result = filteredRe2.FirstMatch(text, atoms);

    EXPECT_EQ(result, -1); // Assuming -1 indicates no match

}



TEST_F(FilteredRE2Test_471, AllMatches_EmptyAtoms_471) {

    absl::string_view text = "test_text";

    std::vector<int> atoms;

    std::vector<int> matching_regexps;

    bool result = filteredRe2.AllMatches(text, atoms, &matching_regexps);

    EXPECT_FALSE(result); // Assuming false indicates no matches

}



TEST_F(FilteredRE2Test_471, AllPotentials_EmptyAtoms_471) {

    std::vector<int> atoms;

    std::vector<int> potential_regexps;

    filteredRe2.AllPotentials(atoms, &potential_regexps);

    EXPECT_TRUE(potential_regexps.empty());

}



TEST_F(FilteredRE2Test_471, NumRegexps_AfterAdd_471) {

    int id = -1;

    filteredRe2.Add("test_pattern", RE2::Options(), &id);

    EXPECT_EQ(filteredRe2.NumRegexps(), 1);

}



TEST_F(FilteredRE2Test_471, GetRE2_ValidId_471) {

    int id = -1;

    filteredRe2.Add("test_pattern", RE2::Options(), &id);

    const RE2& re2 = filteredRe2.GetRE2(id);

    EXPECT_EQ(re2.pattern(), "test_pattern");

}



TEST_F(FilteredRE2Test_471, GetRE2_InvalidId_471) {

    EXPECT_THROW(filteredRe2.GetRE2(-1), std::out_of_range); // Assuming out_of_range is thrown for invalid id

}

} // namespace re2
