#include <gtest/gtest.h>

#include "catch_wildcard_pattern.hpp"



using namespace Catch;



class WildcardPatternTest_1082 : public ::testing::Test {

protected:

    WildcardPattern pattern_no_wildcard;

    WildcardPattern pattern_start_wildcard;

    WildcardPattern pattern_end_wildcard;

    WildcardPattern pattern_both_ends_wildcard;



    WildcardPatternTest_1082()

        : pattern_no_wildcard("test", CaseSensitive::Yes),

          pattern_start_wildcard("*test", CaseSensitive::Yes),

          pattern_end_wildcard("test*", CaseSensitive::Yes),

          pattern_both_ends_wildcard("*test*", CaseSensitive::Yes) {}

};



TEST_F(WildcardPatternTest_1082, MatchesExactCaseSensitive_1082) {

    EXPECT_TRUE(pattern_no_wildcard.matches("test"));

    EXPECT_FALSE(pattern_no_wildcard.matches("Test"));

}



TEST_F(WildcardPatternTest_1082, MatchesStartWildcardCaseSensitive_1082) {

    EXPECT_TRUE(pattern_start_wildcard.matches("mytest"));

    EXPECT_FALSE(pattern_start_wildcard.matches("testmy"));

    EXPECT_FALSE(pattern_start_wildcard.matches("Test"));

}



TEST_F(WildcardPatternTest_1082, MatchesEndWildcardCaseSensitive_1082) {

    EXPECT_TRUE(pattern_end_wildcard.matches("mytest"));

    EXPECT_FALSE(pattern_end_wildcard.matches("testmy"));

    EXPECT_FALSE(pattern_end_wildcard.matches("Test"));

}



TEST_F(WildcardPatternTest_1082, MatchesBothEndsWildcardCaseSensitive_1082) {

    EXPECT_TRUE(pattern_both_ends_wildcard.matches("mytestmore"));

    EXPECT_TRUE(pattern_both_ends_wildcard.matches("test"));

    EXPECT_FALSE(pattern_both_ends_wildcard.matches("MytestMore"));

}



TEST_F(WildcardPatternTest_1082, MatchesExactCaseInsensitive_1082) {

    WildcardPattern pattern_case_insensitive("test", CaseSensitive::No);

    EXPECT_TRUE(pattern_case_insensitive.matches("test"));

    EXPECT_TRUE(pattern_case_insensitive.matches("Test"));

    EXPECT_TRUE(pattern_case_insensitive.matches("TEST"));

}



TEST_F(WildcardPatternTest_1082, MatchesStartWildcardCaseInsensitive_1082) {

    WildcardPattern pattern_start_wildcard_case_insensitive("*test", CaseSensitive::No);

    EXPECT_TRUE(pattern_start_wildcard_case_insensitive.matches("myTest"));

    EXPECT_FALSE(pattern_start_wildcard_case_insensitive.matches("testmy"));

}



TEST_F(WildcardPatternTest_1082, MatchesEndWildcardCaseInsensitive_1082) {

    WildcardPattern pattern_end_wildcard_case_insensitive("test*", CaseSensitive::No);

    EXPECT_TRUE(pattern_end_wildcard_case_insensitive.matches("myTEST"));

    EXPECT_FALSE(pattern_end_wildcard_case_insensitive.matches("testmy"));

}



TEST_F(WildcardPatternTest_1082, MatchesBothEndsWildcardCaseInsensitive_1082) {

    WildcardPattern pattern_both_ends_wildcard_case_insensitive("*test*", CaseSensitive::No);

    EXPECT_TRUE(pattern_both_ends_wildcard_case_insensitive.matches("myTeStMoRe"));

    EXPECT_TRUE(pattern_both_ends_wildcard_case_insensitive.matches("TEST"));

}



TEST_F(WildcardPatternTest_1082, MatchesEmptyString_1082) {

    WildcardPattern pattern_empty("", CaseSensitive::Yes);

    EXPECT_TRUE(pattern_empty.matches(""));

    EXPECT_FALSE(pattern_empty.matches("test"));

}



TEST_F(WildcardPatternTest_1082, MatchesOnlyWildcard_1082) {

    WildcardPattern pattern_only_wildcard("*", CaseSensitive::Yes);

    EXPECT_TRUE(pattern_only_wildcard.matches(""));

    EXPECT_TRUE(pattern_only_wildcard.matches("test"));

}
