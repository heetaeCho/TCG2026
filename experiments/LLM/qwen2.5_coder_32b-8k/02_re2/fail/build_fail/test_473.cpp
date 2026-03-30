#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/filtered_re2.h"



using namespace re2;



class FilteredRE2Test_473 : public ::testing::Test {

protected:

    void SetUp() override {

        filtered_re2 = std::make_unique<FilteredRE2>();

    }



    std::unique_ptr<FilteredRE2> filtered_re2;

};



TEST_F(FilteredRE2Test_473, CompileOnce_473) {

    std::vector<std::string> atoms = {"atom1", "atom2"};

    EXPECT_CALL(*filtered_re2->prefilter_tree_, Compile(::testing::_)).Times(1);

    filtered_re2->Compile(&atoms);

}



TEST_F(FilteredRE2Test_473, CompileTwiceLogsError_473) {

    std::vector<std::string> atoms = {"atom1", "atom2"};

    EXPECT_CALL(*filtered_re2->prefilter_tree_, Compile(::testing::_)).Times(1);

    filtered_re2->Compile(&atoms);



    testing::internal::CaptureStderr();

    filtered_re2->Compile(&atoms);

    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_THAT(output, ::testing::HasSubstr("Compile called already."));

}



TEST_F(FilteredRE2Test_473, CompileWithEmptyRe2Vec_473) {

    std::vector<std::string> atoms = {"atom1", "atom2"};

    EXPECT_CALL(*filtered_re2->prefilter_tree_, Compile(::testing::_)).Times(0);

    filtered_re2->Compile(&atoms);

}



TEST_F(FilteredRE2Test_473, CompileClearsAtoms_473) {

    std::vector<std::string> atoms = {"atom1", "atom2"};

    EXPECT_CALL(*filtered_re2->prefilter_tree_, Compile(::testing::_)).Times(1);

    filtered_re2->Compile(&atoms);

    EXPECT_TRUE(atoms.empty());

}



TEST_F(FilteredRE2Test_473, AddPatternSuccessfully_473) {

    int id = 0;

    RE2::ErrorCode error_code = filtered_re2->Add("test_pattern", RE2::Options(), &id);

    EXPECT_EQ(error_code, RE2::NoError);

}



TEST_F(FilteredRE2Test_473, AddPatternInvalidRegex_473) {

    int id = 0;

    RE2::ErrorCode error_code = filtered_re2->Add("(unmatched_paren", RE2::Options(), &id);

    EXPECT_EQ(error_code, RE2::ErrorParse);

}



TEST_F(FilteredRE2Test_473, SlowFirstMatchReturnsValidIndex_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    int match_index = filtered_re2->SlowFirstMatch("test_string");

    EXPECT_EQ(match_index, 0); // Assuming it matches the first pattern

}



TEST_F(FilteredRE2Test_473, SlowFirstMatchNoMatches_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    int match_index = filtered_re2->SlowFirstMatch("no_match_string");

    EXPECT_EQ(match_index, -1); // Assuming no match

}



TEST_F(FilteredRE2Test_473, FirstMatchWithAtomsReturnsValidIndex_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    int match_index = filtered_re2->FirstMatch("test_string", {0});

    EXPECT_EQ(match_index, 0); // Assuming it matches the first pattern

}



TEST_F(FilteredRE2Test_473, FirstMatchWithAtomsNoMatches_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    int match_index = filtered_re2->FirstMatch("no_match_string", {0});

    EXPECT_EQ(match_index, -1); // Assuming no match

}



TEST_F(FilteredRE2Test_473, AllMatchesReturnsTrueWithMatches_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("test_string", {0}, &matching_regexps);

    EXPECT_TRUE(result);

    EXPECT_EQ(matching_regexps.size(), 1); // Assuming it matches the first pattern

}



TEST_F(FilteredRE2Test_473, AllMatchesReturnsFalseWithNoMatches_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("no_match_string", {0}, &matching_regexps);

    EXPECT_FALSE(result);

    EXPECT_TRUE(matching_regexps.empty());

}



TEST_F(FilteredRE2Test_473, AllPotentialsFillsPotentialRegexps_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    std::vector<int> potential_regexps;

    filtered_re2->AllPotentials({0}, &potential_regexps);

    EXPECT_EQ(potential_regexps.size(), 1); // Assuming it matches the first pattern

}



TEST_F(FilteredRE2Test_473, AllPotentialsWithNoAtomsFillsEmptyPotentialRegexps_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);

    std::vector<std::string> atoms = {"test"};

    filtered_re2->Compile(&atoms);



    std::vector<int> potential_regexps;

    filtered_re2->AllPotentials({}, &potential_regexps);

    EXPECT_TRUE(potential_regexps.empty());

}



TEST_F(FilteredRE2Test_473, NumRegexpsReturnsCorrectCount_473) {

    int id1, id2;

    filtered_re2->Add("pattern1", RE2::Options(), &id1);

    filtered_re2->Add("pattern2", RE2::Options(), &id2);



    EXPECT_EQ(filtered_re2->NumRegexps(), 2);

}



TEST_F(FilteredRE2Test_473, GetRE2ReturnsValidReference_473) {

    int id;

    filtered_re2->Add("test_pattern", RE2::Options(), &id);



    const RE2& re2 = filtered_re2->GetRE2(id);

    EXPECT_EQ(re2.pattern(), "test_pattern");

}
