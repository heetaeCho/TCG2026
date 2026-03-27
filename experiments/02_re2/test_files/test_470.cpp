#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "filtered_re2.h"

#include "re2/re2.h"



using namespace re2;

using ::testing::_;

using ::testing::ElementsAre;



class FilteredRE2Test_470 : public ::testing::Test {

protected:

    void SetUp() override {

        filteredRe2 = std::make_unique<FilteredRE2>();

    }



    void TearDown() override {

        filteredRe2.reset();

    }



    std::unique_ptr<FilteredRE2> filteredRe2;

};



TEST_F(FilteredRE2Test_470, AddPatternSuccess_470) {

    int id = -1;

    RE2::ErrorCode errorCode = filteredRe2->Add("abc", RE2::Options(), &id);

    EXPECT_EQ(errorCode, RE2::NoError);

    EXPECT_GE(id, 0);

}



TEST_F(FilteredRE2Test_470, AddInvalidPatternFails_470) {

    int id = -1;

    RE2::ErrorCode errorCode = filteredRe2->Add("abc(", RE2::Options(), &id);

    EXPECT_NE(errorCode, RE2::NoError);

}



TEST_F(FilteredRE2Test_470, NumRegexpsInitiallyZero_470) {

    EXPECT_EQ(filteredRe2->NumRegexps(), 0);

}



TEST_F(FilteredRE2Test_470, NumRegexpsAfterAdd_470) {

    int id = -1;

    filteredRe2->Add("abc", RE2::Options(), &id);

    EXPECT_EQ(filteredRe2->NumRegexps(), 1);

}



TEST_F(FilteredRE2Test_470, GetRE2ReturnsValidObject_470) {

    int id = -1;

    filteredRe2->Add("abc", RE2::Options(), &id);

    const RE2& re2 = filteredRe2->GetRE2(id);

    EXPECT_TRUE(re2.ok());

}



TEST_F(FilteredRE2Test_470, SlowFirstMatchNoMatches_470) {

    int result = filteredRe2->SlowFirstMatch("xyz");

    EXPECT_EQ(result, -1);

}



TEST_F(FilteredRE2Test_470, SlowFirstMatchWithMatch_470) {

    int id = -1;

    filteredRe2->Add("abc", RE2::Options(), &id);

    filteredRe2->Compile(nullptr);

    int result = filteredRe2->SlowFirstMatch("abc");

    EXPECT_EQ(result, 0);

}



TEST_F(FilteredRE2Test_470, FirstMatchNoMatches_470) {

    std::vector<int> atoms;

    int result = filteredRe2->FirstMatch("xyz", atoms);

    EXPECT_EQ(result, -1);

}



TEST_F(FilteredRE2Test_470, FirstMatchWithMatch_470) {

    int id = -1;

    filteredRe2->Add("abc", RE2::Options(), &id);

    std::vector<int> atoms = {0};

    filteredRe2->Compile(&atoms);

    int result = filteredRe2->FirstMatch("abc", atoms);

    EXPECT_EQ(result, 0);

}



TEST_F(FilteredRE2Test_470, AllMatchesNoMatches_470) {

    std::vector<int> atoms;

    std::vector<int> matchingRegexps;

    bool result = filteredRe2->AllMatches("xyz", atoms, &matchingRegexps);

    EXPECT_FALSE(result);

    EXPECT_TRUE(matchingRegexps.empty());

}



TEST_F(FilteredRE2Test_470, AllMatchesWithMatches_470) {

    int id = -1;

    filteredRe2->Add("abc", RE2::Options(), &id);

    std::vector<int> atoms = {0};

    std::vector<int> matchingRegexps;

    filteredRe2->Compile(&atoms);

    bool result = filteredRe2->AllMatches("abc", atoms, &matchingRegexps);

    EXPECT_TRUE(result);

    EXPECT_THAT(matchingRegexps, ElementsAre(0));

}



TEST_F(FilteredRE2Test_470, AllPotentialsNoPotentials_470) {

    std::vector<int> atoms;

    std::vector<int> potentialRegexps;

    filteredRe2->AllPotentials(atoms, &potentialRegexps);

    EXPECT_TRUE(potentialRegexps.empty());

}



TEST_F(FilteredRE2Test_470, AllPotentialsWithPotentials_470) {

    int id = -1;

    filteredRe2->Add("abc", RE2::Options(), &id);

    std::vector<int> atoms = {0};

    std::vector<int> potentialRegexps;

    filteredRe2->Compile(&atoms);

    filteredRe2->AllPotentials(atoms, &potentialRegexps);

    EXPECT_THAT(potentialRegexps, ElementsAre(0));

}
