#include <gtest/gtest.h>

#include <vector>

#include "prefilter_tree.h"



namespace re2 {



class PrefilterTreeTest_574 : public ::testing::Test {

protected:

    PrefilterTree prefilters;



    PrefilterTreeTest_574() : prefilters(3) {}

};



TEST_F(PrefilterTreeTest_574, RegexpsGivenStrings_NoMatchedAtoms_ReturnsEmpty_574) {

    std::vector<int> matched_atoms;

    std::vector<int> regexps;



    prefilters.RegexpsGivenStrings(matched_atoms, &regexps);



    EXPECT_TRUE(regexps.empty());

}



TEST_F(PrefilterTreeTest_574, RegexpsGivenStrings_NoCompile_ReturnsAllIndices_574) {

    std::vector<int> matched_atoms = {1, 2};

    std::vector<int> regexps;



    prefilters.RegexpsGivenStrings(matched_atoms, &regexps);



    EXPECT_EQ(regexps.size(), prefilters.prefilter_vec_.size());

}



TEST_F(PrefilterTreeTest_574, RegexpsGivenStrings_AfterCompile_ReturnsFilteredIndices_574) {

    std::vector<std::string> atom_vec = {"atom1", "atom2"};

    prefilters.Compile(&atom_vec);

    

    std::vector<int> matched_atoms = {0}; // Assuming 0 is a valid index after compilation

    std::vector<int> regexps;



    prefilters.RegexpsGivenStrings(matched_atoms, &regexps);



    EXPECT_FALSE(regexps.empty());

}



TEST_F(PrefilterTreeTest_574, RegexpsGivenStrings_UnfilteredRegexpsIncluded_574) {

    std::vector<std::string> atom_vec = {"atom1", "atom2"};

    prefilters.Compile(&atom_vec);

    

    std::vector<int> matched_atoms = {0}; // Assuming 0 is a valid index after compilation

    std::vector<int> regexps;



    prefilters.RegexpsGivenStrings(matched_atoms, &regexps);



    for (int unfiltered : prefilters.unfiltered_) {

        EXPECT_TRUE(std::find(regexps.begin(), regexps.end(), unfiltered) != regexps.end());

    }

}



TEST_F(PrefilterTreeTest_574, RegexpsGivenStrings_SortedOutput_574) {

    std::vector<std::string> atom_vec = {"atom1", "atom2"};

    prefilters.Compile(&atom_vec);

    

    std::vector<int> matched_atoms = {0}; // Assuming 0 is a valid index after compilation

    std::vector<int> regexps;



    prefilters.RegexpsGivenStrings(matched_atoms, &regexps);



    EXPECT_TRUE(std::is_sorted(regexps.begin(), regexps.end()));

}



} // namespace re2
