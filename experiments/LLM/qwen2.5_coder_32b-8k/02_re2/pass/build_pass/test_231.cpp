#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/set.h"

#include "absl/strings/string_view.h"



using namespace re2;



class SetTest_231 : public ::testing::Test {

protected:

    RE2::Options options;

    RE2::Anchor anchor = RE2::ANCHOR_BOTH;

    std::unique_ptr<RE2::Set> set;



    void SetUp() override {

        set = std::make_unique<RE2::Set>(options, anchor);

    }

};



TEST_F(SetTest_231, AddPattern_Success_231) {

    std::string error;

    int result = set->Add("abc", &error);

    EXPECT_GE(result, 0);

    EXPECT_TRUE(error.empty());

}



TEST_F(SetTest_231, AddInvalidPattern_Error_231) {

    std::string error;

    int result = set->Add("[z-a]", &error);

    EXPECT_EQ(result, -1);

    EXPECT_FALSE(error.empty());

}



TEST_F(SetTest_231, Compile_Success_231) {

    std::string error;

    set->Add("abc", &error);

    bool compiled = set->Compile();

    EXPECT_TRUE(compiled);

}



TEST_F(SetTest_231, Compile_NoPatterns_Error_231) {

    bool compiled = set->Compile();

    EXPECT_FALSE(compiled);

}



TEST_F(SetTest_231, Match_Success_231) {

    std::string error;

    set->Add("abc", &error);

    set->Compile();

    std::vector<int> matches;

    bool matched = set->Match("abc", &matches);

    EXPECT_TRUE(matched);

    EXPECT_EQ(matches.size(), 1);

}



TEST_F(SetTest_231, Match_NoPatterns_Error_231) {

    std::string error;

    set->Add("abc", &error);

    std::vector<int> matches;

    bool matched = set->Match("abc", &matches);

    EXPECT_FALSE(matched);

    EXPECT_TRUE(matches.empty());

}



TEST_F(SetTest_231, Match_NotCompiled_Error_231) {

    std::string error;

    set->Add("abc", &error);

    std::vector<int> matches;

    bool matched = set->Match("abc", &matches);

    EXPECT_FALSE(matched);

    EXPECT_TRUE(matches.empty());

}



TEST_F(SetTest_231, Match_MultiplePatterns_Success_231) {

    std::string error;

    set->Add("abc", &error);

    set->Add("def", &error);

    set->Compile();

    std::vector<int> matches;

    bool matched = set->Match("abcdef", &matches);

    EXPECT_TRUE(matched);

    EXPECT_EQ(matches.size(), 2);

}



TEST_F(SetTest_231, MoveConstructor_Success_231) {

    std::string error;

    set->Add("abc", &error);

    set->Compile();

    RE2::Set moved_set(std::move(*set));

    std::vector<int> matches;

    bool matched = moved_set.Match("abc", &matches);

    EXPECT_TRUE(matched);

    EXPECT_EQ(matches.size(), 1);

}



TEST_F(SetTest_231, MoveAssignment_Success_231) {

    std::string error;

    set->Add("abc", &error);

    set->Compile();

    RE2::Set new_set(options, anchor);

    new_set = std::move(*set);

    std::vector<int> matches;

    bool matched = new_set.Match("abc", &matches);

    EXPECT_TRUE(matched);

    EXPECT_EQ(matches.size(), 1);

}
