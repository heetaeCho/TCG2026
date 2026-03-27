#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prefilter.cc"

#include "re2/regexp.h"



namespace re2 {



class PrefilterInfoTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common objects or state before each test

    }



    void TearDown() override {

        // Cleanup any common objects or state after each test

    }

};



TEST_F(PrefilterInfoTest_NormalOperation_558, CClassSingleRangeLatin1_558) {

    CharClass *cc = new CharClass();

    cc->ranges_ = new RuneRange[1]{{'a', 'z'}};

    cc->nranges_ = 1;

    Prefilter::Info *info = Prefilter::Info::CClass(cc, true);

    EXPECT_TRUE(info->is_exact_);

    for (char c = 'a'; c <= 'z'; ++c) {

        EXPECT_EQ(info->exact_.find(std::string(1, tolower(c))), info->exact_.end());

        EXPECT_NE(info->exact_.find(std::string(1, tolower(c))), info->exact_.end());

    }

    delete cc;

    delete[] cc->ranges_;

    delete info;

}



TEST_F(PrefilterInfoTest_NormalOperation_558, CClassSingleRangeNonLatin1_558) {

    CharClass *cc = new CharClass();

    cc->ranges_ = new RuneRange[1]{{'A', 'Z'}};

    cc->nranges_ = 1;

    Prefilter::Info *info = Prefilter::Info::CClass(cc, false);

    EXPECT_TRUE(info->is_exact_);

    for (char c = 'A'; c <= 'Z'; ++c) {

        EXPECT_EQ(info->exact_.find(RuneToString(ToLowerRune(c))), info->exact_.end());

        EXPECT_NE(info->exact_.find(RuneToString(ToLowerRune(c))), info->exact_.end());

    }

    delete cc;

    delete[] cc->ranges_;

    delete info;

}



TEST_F(PrefilterInfoTest_BoundaryConditions_558, CClassEmpty_558) {

    CharClass *cc = new CharClass();

    Prefilter::Info *info = Prefilter::Info::CClass(cc, true);

    EXPECT_TRUE(info->is_exact_);

    EXPECT_EQ(info->exact_.size(), 0);

    delete cc;

    delete info;

}



TEST_F(PrefilterInfoTest_BoundaryConditions_558, CClassSizeMoreThan10_558) {

    CharClass *cc = new CharClass();

    cc->ranges_ = new RuneRange[11]{{'a', 'z'}, {'A', 'Z'}, {'0', '9'}, {'!', '@'}, {'#', '$'},

                                   {'%', '^'}, {'&', '*'}, {'(', ')'}, {'-', '+'}, { '=', '['},

                                   {']', '\\'}};

    cc->nranges_ = 11;

    Prefilter::Info *info = Prefilter::Info::CClass(cc, true);

    EXPECT_FALSE(info->is_exact_);

    delete cc;

    delete[] cc->ranges_;

    delete info;

}



TEST_F(PrefilterInfoTest_ExceptionalCases_558, CClassNull_558) {

    CharClass *cc = nullptr;

    Prefilter::Info *info = Prefilter::Info::CClass(cc, true);

    EXPECT_FALSE(info->is_exact_);

    delete info;

}



}  // namespace re2
