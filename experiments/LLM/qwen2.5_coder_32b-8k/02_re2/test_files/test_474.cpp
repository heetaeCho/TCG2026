#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/filtered_re2.h"

#include "re2/re2.h"



using namespace re2;

using ::testing::ElementsAre;



class FilteredRE2Test_474 : public ::testing::Test {

protected:

    void SetUp() override {

        filtered_re2 = std::make_unique<FilteredRE2>();

    }



    void AddPattern(const std::string& pattern, int* id) {

        RE2::Options options;

        auto result = filtered_re2->Add(pattern, options, id);

        EXPECT_EQ(result, RE2::NoError) << "Failed to add pattern: " << pattern;

    }



    std::unique_ptr<FilteredRE2> filtered_re2;

};



TEST_F(FilteredRE2Test_474, SlowFirstMatch_NoPatternsAdded_474) {

    EXPECT_EQ(filtered_re2->SlowFirstMatch("test"), -1);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_PatternNotMatching_474) {

    int id;

    AddPattern("hello", &id);

    EXPECT_EQ(filtered_re2->SlowFirstMatch("world"), -1);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_SinglePatternMatching_474) {

    int id;

    AddPattern("hello", &id);

    EXPECT_EQ(filtered_re2->SlowFirstMatch("hello world"), 0);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_MultiplePatternsMatchingFirstOne_474) {

    int id1, id2;

    AddPattern("hello", &id1);

    AddPattern("world", &id2);

    EXPECT_EQ(filtered_re2->SlowFirstMatch("hello world"), 0);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_MultiplePatternsMatchingSecondOne_474) {

    int id1, id2;

    AddPattern("foo", &id1);

    AddPattern("bar", &id2);

    EXPECT_EQ(filtered_re2->SlowFirstMatch("bar foo"), 1);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_PatternWithSpecialCharsMatching_474) {

    int id;

    AddPattern("hello\\d+", &id);

    EXPECT_EQ(filtered_re2->SlowFirstMatch("hello123 world"), 0);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_EmptyStringPatternMatching_474) {

    int id;

    AddPattern("", &id);

    EXPECT_EQ(filtered_re2->SlowFirstMatch(""), 0);

}



TEST_F(FilteredRE2Test_474, SlowFirstMatch_EmptyInputString_474) {

    int id;

    AddPattern("hello", &id);

    EXPECT_EQ(filtered_re2->SlowFirstMatch(""), -1);

}
