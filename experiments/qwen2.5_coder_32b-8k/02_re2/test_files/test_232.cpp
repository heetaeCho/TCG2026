#include <gtest/gtest.h>

#include "re2/set.h"

#include "absl/strings/string_view.h"



using namespace re2;



class SetTest_232 : public ::testing::Test {

protected:

    RE2::Set set;

    

    SetTest_232() : set(RE2::Options(), RE2::Anchor::UNANCHORED) {}

};



TEST_F(SetTest_232, AddValidPattern_ReturnsIndex_232) {

    std::string error;

    int index = set.Add("abc", &error);

    EXPECT_EQ(index, 0);

}



TEST_F(SetTest_232, AddInvalidPattern_SetsError_ReturnsNegativeOne_232) {

    std::string error;

    int index = set.Add("*(", &error);

    EXPECT_EQ(index, -1);

    EXPECT_FALSE(error.empty());

}



TEST_F(SetTest_232, AddMultiplePatterns_IncreasesIndex_232) {

    std::string error;

    int first_index = set.Add("abc", &error);

    int second_index = set.Add("def", &error);

    EXPECT_EQ(first_index, 0);

    EXPECT_EQ(second_index, 1);

}



TEST_F(SetTest_232, AddAfterCompile_ReturnsNegativeOne_232) {

    std::string error;

    set.Compile();

    int index = set.Add("abc", &error);

    EXPECT_EQ(index, -1);

}



TEST_F(SetTest_232, AddEmptyPattern_ReturnsIndexZero_232) {

    std::string error;

    int index = set.Add("", &error);

    EXPECT_EQ(index, 0);

}



TEST_F(SetTest_232, AddLongestMatchPattern_ReturnsIndex_232) {

    RE2::Options options;

    options.set_longest_match(true);

    RE2::Set longest_set(options, RE2::Anchor::UNANCHORED);



    std::string error;

    int index = longest_set.Add("abc", &error);

    EXPECT_EQ(index, 0);

}



TEST_F(SetTest_232, AddLiteralPattern_ReturnsIndex_232) {

    RE2::Options options;

    options.set_literal(true);

    RE2::Set literal_set(options, RE2::Anchor::UNANCHORED);



    std::string error;

    int index = literal_set.Add("abc", &error);

    EXPECT_EQ(index, 0);

}
