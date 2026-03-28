#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "filtered_re2.h"

#include "re2.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class FilteredRE2Test : public ::testing::Test {

protected:

    void SetUp() override {

        filtered_re2 = new FilteredRE2();

    }



    void TearDown() override {

        delete filtered_re2;

    }



    FilteredRE2* filtered_re2;

};



TEST_F(FilteredRE2Test_475, FirstMatch_ReturnsMinusOneIfNotCompiled_475) {

    std::vector<int> atoms = {0};

    int result = filtered_re2->FirstMatch("test", atoms);

    EXPECT_EQ(result, -1);

}



TEST_F(FilteredRE2Test_475, FirstMatch_ReturnsCorrectIndexForMatchingPattern_475) {

    RE2* re = new RE2("abc");

    filtered_re2->re2_vec_.push_back(re);

    int id;

    filtered_re2->Add("abc", RE2::Options(), &id);

    std::vector<int> atoms = {0};

    filtered_re2->Compile(&atoms);



    int result = filtered_re2->FirstMatch("abc", atoms);

    EXPECT_EQ(result, 0);

}



TEST_F(FilteredRE2Test_475, FirstMatch_ReturnsMinusOneForNonMatchingPattern_475) {

    RE2* re = new RE2("def");

    filtered_re2->re2_vec_.push_back(re);

    int id;

    filtered_re2->Add("def", RE2::Options(), &id);

    std::vector<int> atoms = {0};

    filtered_re2->Compile(&atoms);



    int result = filtered_re2->FirstMatch("abc", atoms);

    EXPECT_EQ(result, -1);

}



TEST_F(FilteredRE2Test_475, FirstMatch_HandlesEmptyTextCorrectly_475) {

    RE2* re = new RE2("");

    filtered_re2->re2_vec_.push_back(re);

    int id;

    filtered_re2->Add("", RE2::Options(), &id);

    std::vector<int> atoms = {0};

    filtered_re2->Compile(&atoms);



    int result = filtered_re2->FirstMatch("", atoms);

    EXPECT_EQ(result, 0);

}



TEST_F(FilteredRE2Test_475, FirstMatch_HandlesEmptyAtomsCorrectly_475) {

    RE2* re = new RE2("abc");

    filtered_re2->re2_vec_.push_back(re);

    int id;

    filtered_re2->Add("abc", RE2::Options(), &id);



    std::vector<int> atoms = {};

    filtered_re2->Compile(&atoms);



    int result = filtered_re2->FirstMatch("abc", atoms);

    EXPECT_EQ(result, -1);

}
