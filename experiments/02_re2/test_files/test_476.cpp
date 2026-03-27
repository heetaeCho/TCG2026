#include <gtest/gtest.h>

#include "filtered_re2.h"

#include "re2.h"

#include "prefilter_tree.h"



using namespace re2;



class FilteredRE2Test_476 : public ::testing::Test {

protected:

    void SetUp() override {

        filtered_re2 = std::make_unique<FilteredRE2>();

        int id;

        filtered_re2->Add("hello", RE2::Options(), &id);

        filtered_re2->Add("world", RE2::Options(), &id);

        filtered_re2->Compile(nullptr);

    }



    std::unique_ptr<FilteredRE2> filtered_re2;

};



TEST_F(FilteredRE2Test_476, AllMatches_NormalOperation_476) {

    std::vector<int> atoms = {0, 1}; // Assuming 0 corresponds to "hello" and 1 to "world"

    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("helloworld", atoms, &matching_regexps);

    EXPECT_TRUE(result);

    EXPECT_EQ(matching_regexps.size(), 2);

    EXPECT_EQ(matching_regexps[0], 0);

    EXPECT_EQ(matching_regexps[1], 1);

}



TEST_F(FilteredRE2Test_476, AllMatches_NoMatch_476) {

    std::vector<int> atoms = {0, 1}; // Assuming 0 corresponds to "hello" and 1 to "world"

    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("test", atoms, &matching_regexps);

    EXPECT_FALSE(result);

    EXPECT_TRUE(matching_regexps.empty());

}



TEST_F(FilteredRE2Test_476, AllMatches_EmptyText_476) {

    std::vector<int> atoms = {0, 1}; // Assuming 0 corresponds to "hello" and 1 to "world"

    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("", atoms, &matching_regexps);

    EXPECT_FALSE(result);

    EXPECT_TRUE(matching_regexps.empty());

}



TEST_F(FilteredRE2Test_476, AllMatches_EmptyAtoms_476) {

    std::vector<int> atoms = {}; // No atoms provided

    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("helloworld", atoms, &matching_regexps);

    EXPECT_FALSE(result);

    EXPECT_TRUE(matching_regexps.empty());

}



TEST_F(FilteredRE2Test_476, AllMatches_PartialMatch_476) {

    std::vector<int> atoms = {0}; // Assuming 0 corresponds to "hello"

    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("hello", atoms, &matching_regexps);

    EXPECT_TRUE(result);

    EXPECT_EQ(matching_regexps.size(), 1);

    EXPECT_EQ(matching_regexps[0], 0);

}



TEST_F(FilteredRE2Test_476, AllMatches_MultipleMatchesSamePattern_476) {

    std::vector<int> atoms = {0}; // Assuming 0 corresponds to "hello"

    std::vector<int> matching_regexps;

    bool result = filtered_re2->AllMatches("hellohello", atoms, &matching_regexps);

    EXPECT_TRUE(result);

    EXPECT_EQ(matching_regexps.size(), 1); // Only one unique pattern ID is expected

    EXPECT_EQ(matching_regexps[0], 0);

}
