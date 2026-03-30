#include <gtest/gtest.h>

#include "filtered_re2.h"

#include "absl/strings/string_view.h"



using namespace re2;



class FilteredRE2Test_606 : public ::testing::Test {

protected:

    FilteredRE2Test_606() {}

    virtual ~FilteredRE2Test_606() {}

};



TEST_F(FilteredRE2Test_606, DefaultConstructorInitialization_606) {

    FilteredRE2 filtered_re2;

    EXPECT_FALSE(filtered_re2.compiled_);

}



TEST_F(FilteredRE2Test_606, ParameterizedConstructorInitialization_606) {

    int min_atom_len = 5;

    FilteredRE2 filtered_re2(min_atom_len);

    EXPECT_FALSE(filtered_re2.compiled_);

}



TEST_F(FilteredRE2Test_606, MoveConstructorPreservesState_606) {

    FilteredRE2 original(10);

    original.Add("test_pattern", RE2::Options(), nullptr);



    FilteredRE2 moved(std::move(original));

    EXPECT_EQ(moved.NumRegexps(), 1);

}



TEST_F(FilteredRE2Test_606, AddPatternReturnsNoError_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    RE2::ErrorCode error_code = filtered_re2.Add("test_pattern", RE2::Options(), &id);

    EXPECT_EQ(error_code, RE2::NoError);

}



TEST_F(FilteredRE2Test_606, AddPatternSetsIdCorrectly_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    filtered_re2.Add("test_pattern", RE2::Options(), &id);

    EXPECT_EQ(id, 0);

}



TEST_F(FilteredRE2Test_606, CompileSetsCompiledFlagToTrue_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    filtered_re2.Add("test_pattern", RE2::Options(), &id);



    std::vector<std::string> strings_to_match = {"match_this"};

    filtered_re2.Compile(&strings_to_match);

    EXPECT_TRUE(filtered_re2.compiled_);

}



TEST_F(FilteredRE2Test_606, NumRegexpsReturnsCorrectCount_606) {

    FilteredRE2 filtered_re2;

    int id1 = -1, id2 = -1;

    filtered_re2.Add("pattern1", RE2::Options(), &id1);

    filtered_re2.Add("pattern2", RE2::Options(), &id2);



    EXPECT_EQ(filtered_re2.NumRegexps(), 2);

}



TEST_F(FilteredRE2Test_606, GetRE2ReturnsCorrectPattern_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    filtered_re2.Add("test_pattern", RE2::Options(), &id);



    const RE2& re2 = filtered_re2.GetRE2(id);

    EXPECT_EQ(re2.pattern(), "test_pattern");

}



TEST_F(FilteredRE2Test_606, SlowFirstMatchFindsPattern_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    filtered_re2.Add("test_pattern", RE2::Options(), &id);



    std::vector<std::string> strings_to_match = {"match_this"};

    filtered_re2.Compile(&strings_to_match);

    int match_id = filtered_re2.SlowFirstMatch("test_pattern");

    EXPECT_EQ(match_id, id);

}



TEST_F(FilteredRE2Test_606, FirstMatchFindsPatternWithAtoms_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    filtered_re2.Add("test_pattern", RE2::Options(), &id);



    std::vector<std::string> strings_to_match = {"match_this"};

    filtered_re2.Compile(&strings_to_match);

    std::vector<int> atoms = {0}; // Assuming atom 0 matches "test_pattern"

    int match_id = filtered_re2.FirstMatch("test_pattern", atoms);

    EXPECT_EQ(match_id, id);

}



TEST_F(FilteredRE2Test_606, AllMatchesFindsAllPatterns_606) {

    FilteredRE2 filtered_re2;

    int id1 = -1, id2 = -1;

    filtered_re2.Add("test_pattern1", RE2::Options(), &id1);

    filtered_re2.Add("test_pattern2", RE2::Options(), &id2);



    std::vector<std::string> strings_to_match = {"match_this"};

    filtered_re2.Compile(&strings_to_match);

    std::vector<int> atoms = {0}; // Assuming atom 0 matches both patterns

    std::vector<int> matching_regexps;

    bool result = filtered_re2.AllMatches("test_pattern1", atoms, &matching_regexps);

    EXPECT_TRUE(result);

    EXPECT_EQ(matching_regexps.size(), 2);

}



TEST_F(FilteredRE2Test_606, AllPotentialsFindsPotentialPatterns_606) {

    FilteredRE2 filtered_re2;

    int id = -1;

    filtered_re2.Add("test_pattern", RE2::Options(), &id);



    std::vector<std::string> strings_to_match = {"match_this"};

    filtered_re2.Compile(&strings_to_match);

    std::vector<int> atoms = {0}; // Assuming atom 0 matches "test_pattern"

    std::vector<int> potential_regexps;

    filtered_re2.AllPotentials(atoms, &potential_regexps);

    EXPECT_EQ(potential_regexps.size(), 1);

}
