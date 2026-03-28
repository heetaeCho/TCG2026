#include <gtest/gtest.h>

#include "catch_amalgamated.cpp"

#include "catch_case_insensitive_comparisons.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;



class TagComparisonTest_992 : public ::testing::Test {

protected:

    StringRef lhsStr;

    StringRef rhsStr;

    Tag lhsTag;

    Tag rhsTag;

    Detail::CaseInsensitiveLess comparator;



    void SetUp() override {

        lhsStr = "example";

        rhsStr = "EXAMPLE";

        lhsTag = Tag(lhsStr);

        rhsTag = Tag(rhsStr);

    }

};



TEST_F(TagComparisonTest_992, CaseInsensitiveLessOperator_ReturnsTrue_WhenLeftIsLowercaseAndRightIsUppercase_992) {

    EXPECT_TRUE(comparator(lhsStr, rhsStr));

}



TEST_F(TagComparisonTest_992, CaseInsensitiveLessOperator_ReturnsFalse_WhenLeftIsUppercaseAndRightIsLowercase_992) {

    EXPECT_FALSE(comparator(rhsStr, lhsStr));

}



TEST_F(TagComparisonTest_992, TagLessOperator_ReturnsTrue_WhenLeftIsLowercaseAndRightIsUppercase_992) {

    EXPECT_TRUE(lhsTag < rhsTag);

}



TEST_F(TagComparisonTest_992, TagLessOperator_ReturnsFalse_WhenLeftIsUppercaseAndRightIsLowercase_992) {

    EXPECT_FALSE(rhsTag < lhsTag);

}



TEST_F(TagComparisonTest_992, TagEqualityOperator_ReturnsTrue_WhenBothTagsAreSameCase_992) {

    EXPECT_TRUE(lhsTag == Tag("example"));

}



TEST_F(TagComparisonTest_992, TagEqualityOperator_ReturnsTrue_WhenBothTagsAreDifferentCase_992) {

    EXPECT_TRUE(lhsTag == rhsTag);

}



TEST_F(TagComparisonTest_992, TagEqualityOperator_ReturnsFalse_WhenTagsAreDifferentStrings_992) {

    EXPECT_FALSE(lhsTag == Tag("different"));

}
