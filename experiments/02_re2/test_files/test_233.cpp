#include <gtest/gtest.h>

#include "re2/set.h"

#include "absl/strings/string_view.h"



namespace re2 {



class RE2SetTest : public ::testing::Test {

protected:

    void SetUp() override {

        options = RE2::Options();

        set = std::make_unique<RE2::Set>(options, RE2::Anchor::ANCHOR_BOTH);

    }



    RE2::Options options;

    std::unique_ptr<RE2::Set> set;

};



TEST_F(RE2SetTest_233, CompileReturnsTrueOnFirstCall_233) {

    EXPECT_TRUE(set->Compile());

}



TEST_F(RE2SetTest_233, CompileReturnsFalseOnSecondCall_233) {

    set->Compile();

    EXPECT_FALSE(set->Compile());

}



TEST_F(RE2SetTest_233, CompileDoesNotChangeStateIfCalledTwice_233) {

    set->Compile();

    EXPECT_EQ(set->Compile(), false);

    EXPECT_EQ(set->Compile(), false);

}



TEST_F(RE2SetTest_233, AddPatternBeforeCompileSucceeds_233) {

    std::string error;

    int index = set->Add("a.*", &error);

    EXPECT_GE(index, 0);

    EXPECT_TRUE(error.empty());

}



TEST_F(RE2SetTest_233, AddPatternAfterCompileFails_233) {

    set->Compile();

    std::string error;

    int index = set->Add("a.*", &error);

    EXPECT_EQ(index, -1);

    EXPECT_FALSE(error.empty());

}



}  // namespace re2
