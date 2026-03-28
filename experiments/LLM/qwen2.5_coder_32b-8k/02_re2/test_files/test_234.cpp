#include <gtest/gtest.h>

#include "re2/set.h"

#include <absl/strings/string_view.h>



using namespace re2;



class RE2SetTest_234 : public ::testing::Test {

protected:

    void SetUp() override {

        RE2::Options options;

        RE2::Anchor anchor = RE2::ANCHOR_BOTH;

        set = std::make_unique<RE2::Set>(options, anchor);

    }



    void TearDown() override {

        set.reset();

    }



    std::unique_ptr<RE2::Set> set;

};



TEST_F(RE2SetTest_234, AddPattern_234) {

    std::string error;

    int index = set->Add("abc", &error);

    EXPECT_GE(index, 0) << "Failed to add pattern: " << error;

}



TEST_F(RE2SetTest_234, CompilePatterns_234) {

    std::string error;

    set->Add("abc", &error);

    bool success = set->Compile();

    EXPECT_TRUE(success) << "Failed to compile patterns";

}



TEST_F(RE2SetTest_234, MatchExistingPattern_234) {

    std::string error;

    set->Add("abc", &error);

    set->Compile();



    std::vector<int> matches;

    bool result = set->Match("abc", &matches);

    EXPECT_TRUE(result);

    EXPECT_EQ(matches.size(), 1);

}



TEST_F(RE2SetTest_234, MatchNonExistingPattern_234) {

    std::string error;

    set->Add("abc", &error);

    set->Compile();



    std::vector<int> matches;

    bool result = set->Match("xyz", &matches);

    EXPECT_FALSE(result);

    EXPECT_EQ(matches.size(), 0);

}



TEST_F(RE2SetTest_234, MatchAfterClearingPatterns_234) {

    std::string error;

    int index1 = set->Add("abc", &error);

    int index2 = set->Add("def", &error);

    set->Compile();



    set.reset();

    RE2::Options options;

    RE2::Anchor anchor = RE2::ANCHOR_BOTH;

    set = std::make_unique<RE2::Set>(options, anchor);



    std::vector<int> matches;

    bool result = set->Match("abc", &matches);

    EXPECT_FALSE(result);

    EXPECT_EQ(matches.size(), 0);

}



TEST_F(RE2SetTest_234, MatchEmptyString_234) {

    std::string error;

    set->Add("", &error);

    set->Compile();



    std::vector<int> matches;

    bool result = set->Match("", &matches);

    EXPECT_TRUE(result);

    EXPECT_EQ(matches.size(), 1);

}



TEST_F(RE2SetTest_234, MatchMultiplePatterns_234) {

    std::string error;

    set->Add("abc", &error);

    set->Add("def", &error);

    set->Compile();



    std::vector<int> matches;

    bool result = set->Match("abc def", &matches);

    EXPECT_TRUE(result);

    EXPECT_EQ(matches.size(), 2);

}



TEST_F(RE2SetTest_234, MatchWithNoPatterns_234) {

    std::vector<int> matches;

    bool result = set->Match("anything", &matches);

    EXPECT_FALSE(result);

    EXPECT_EQ(matches.size(), 0);

}
