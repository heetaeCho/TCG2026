#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/filtered_re2.h"

#include "./TestProjects/re2/re2/prefilter_tree.h"



using namespace re2;

using ::testing::_;

using ::testing::NiceMock;



class MockPrefilterTree : public PrefilterTree {

public:

    MOCK_CONST_METHOD2(RegexpsGivenStrings, void(const std::vector<int>& matched_atoms, std::vector<int>* regexps));

};



class FilteredRE2Test_477 : public ::testing::Test {

protected:

    NiceMock<MockPrefilterTree> mock_prefilter_tree;

    FilteredRE2 filtered_re2;



    FilteredRE2Test_477() {

        // Replace the internal prefilter_tree_ with our mock

        const_cast<PrefilterTree*&>(filtered_re2.prefilter_tree_) = &mock_prefilter_tree;

    }

};



TEST_F(FilteredRE2Test_477, AllPotentials_CallsRegexpsGivenStrings_477) {

    std::vector<int> atoms = {1, 2, 3};

    std::vector<int> potential_regexps;



    EXPECT_CALL(mock_prefilter_tree, RegexpsGivenStrings(atoms, _))

        .WillOnce([](const std::vector<int>& matched_atoms, std::vector<int>* regexps) {

            *regexps = {4, 5}; // Simulate some return values

        });



    filtered_re2.AllPotentials(atoms, &potential_regexps);



    EXPECT_EQ(potential_regexps, std::vector<int>({4, 5}));

}



TEST_F(FilteredRE2Test_477, AllPotentials_EmptyAtoms_ReturnsEmpty_477) {

    std::vector<int> atoms = {};

    std::vector<int> potential_regexps;



    EXPECT_CALL(mock_prefilter_tree, RegexpsGivenStrings(atoms, _))

        .WillOnce([](const std::vector<int>& matched_atoms, std::vector<int>* regexps) {

            *regexps = {}; // Simulate empty return values

        });



    filtered_re2.AllPotentials(atoms, &potential_regexps);



    EXPECT_EQ(potential_regexps, std::vector<int>({}));

}



TEST_F(FilteredRE2Test_477, AllPotentials_NoMatchingAtoms_ReturnsEmpty_477) {

    std::vector<int> atoms = {10, 20, 30};

    std::vector<int> potential_regexps;



    EXPECT_CALL(mock_prefilter_tree, RegexpsGivenStrings(atoms, _))

        .WillOnce([](const std::vector<int>& matched_atoms, std::vector<int>* regexps) {

            *regexps = {}; // Simulate no matches

        });



    filtered_re2.AllPotentials(atoms, &potential_regexps);



    EXPECT_EQ(potential_regexps, std::vector<int>({}));

}



TEST_F(FilteredRE2Test_477, AllPotentials_AllAtomsMatch_ReturnsAllRegexps_477) {

    std::vector<int> atoms = {1, 2, 3};

    std::vector<int> potential_regexps;



    EXPECT_CALL(mock_prefilter_tree, RegexpsGivenStrings(atoms, _))

        .WillOnce([](const std::vector<int>& matched_atoms, std::vector<int>* regexps) {

            *regexps = {0, 1, 2}; // Simulate all matches

        });



    filtered_re2.AllPotentials(atoms, &potential_regexps);



    EXPECT_EQ(potential_regexps, std::vector<int>({0, 1, 2}));

}
