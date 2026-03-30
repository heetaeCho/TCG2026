#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_spec.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using namespace testing;



class TagPatternTest_1004 : public ::testing::Test {

protected:

    TagPattern tagPattern_;



    void SetUp() override {

        // Initialize the TagPattern with a specific tag and filter string

        tagPattern_ = TagPattern("testTag", "filter");

    }

};



TEST_F(TagPatternTest_1004, Matches_ReturnsTrueForMatchingTag_1004) {

    TestCaseInfo testCase;

    testCase.tags.push_back(Tag("testTag"));

    EXPECT_TRUE(tagPattern_.matches(testCase));

}



TEST_F(TagPatternTest_1004, Matches_ReturnsFalseForNonMatchingTag_1004) {

    TestCaseInfo testCase;

    testCase.tags.push_back(Tag("otherTag"));

    EXPECT_FALSE(tagPattern_.matches(testCase));

}



TEST_F(TagPatternTest_1004, Matches_ReturnsTrueForMultipleTagsIncludingMatch_1004) {

    TestCaseInfo testCase;

    testCase.tags.push_back(Tag("tag1"));

    testCase.tags.push_back(Tag("testTag"));

    testCase.tags.push_back(Tag("tag3"));

    EXPECT_TRUE(tagPattern_.matches(testCase));

}



TEST_F(TagPatternTest_1004, Matches_ReturnsFalseForNoTags_1004) {

    TestCaseInfo testCase;

    EXPECT_FALSE(tagPattern_.matches(testCase));

}
