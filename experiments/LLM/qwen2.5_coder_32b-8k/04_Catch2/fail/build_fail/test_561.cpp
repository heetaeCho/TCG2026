#include <gtest/gtest.h>

#include "catch_wildcard_pattern.hpp"



class WildcardPatternTest_561 : public ::testing::Test {

protected:

    using Catch::WildcardPattern;

    using Catch::CaseSensitive;



    WildcardPattern noWildcardPattern = WildcardPattern("test", CaseSensitive::Yes);

    WildcardPattern wildcardAtStartPattern = WildcardPattern("*test", CaseSensitive::Yes);

    WildcardPattern wildcardAtEndPattern = WildcardPattern("test*", CaseSensitive::Yes);

    WildcardPattern wildcardAtBothEndsPattern = WildcardPattern("*test*", CaseSensitive::Yes);

};



// Normal operation tests

TEST_F(WildcardPatternTest_561, NoWildcardMatch_561) {

    EXPECT_TRUE(noWildcardPattern.matches("test"));

}



TEST_F(WildcardPatternTest_561, NoWildcardNoMatch_561) {

    EXPECT_FALSE(noWildcardPattern.matches("tset"));

}



TEST_F(WildcardPatternTest_561, WildcardAtStartMatch_561) {

    EXPECT_TRUE(wildcardAtStartPattern.matches("prefixtest"));

}



TEST_F(WildcardPatternTest_561, WildcardAtStartNoMatch_561) {

    EXPECT_FALSE(wildcardAtStartPattern.matches("postfixtest"));

}



TEST_F(WildcardPatternTest_561, WildcardAtEndMatch_561) {

    EXPECT_TRUE(wildcardAtEndPattern.matches("testsuffix"));

}



TEST_F(WildcardPatternTest_561, WildcardAtEndNoMatch_561) {

    EXPECT_FALSE(wildcardAtEndPattern.matches("postfixtest"));

}



TEST_F(WildcardPatternTest_561, WildcardAtBothEndsMatch_561) {

    EXPECT_TRUE(wildcardAtBothEndsPattern.matches("prefixtestsuffix"));

}



TEST_F(WildcardPatternTest_561, WildcardAtBothEndsNoMatch_561) {

    EXPECT_FALSE(wildcardAtBothEndsPattern.matches("postfixtest"));

}



// Boundary condition tests

TEST_F(WildcardPatternTest_561, EmptyStringNoWildcard_561) {

    WildcardPattern emptyPattern = WildcardPattern("", CaseSensitive::Yes);

    EXPECT_TRUE(emptyPattern.matches(""));

}



TEST_F(WildcardPatternTest_561, EmptyStringWildcardAtStart_561) {

    WildcardPattern wildcardPattern = WildcardPattern("*", CaseSensitive::Yes);

    EXPECT_TRUE(wildcardPattern.matches("anystring"));

}



TEST_F(WildcardPatternTest_561, EmptyStringWildcardAtEnd_561) {

    WildcardPattern wildcardPattern = WildcardPattern("*", CaseSensitive::Yes);

    EXPECT_TRUE(wildcardPattern.matches("anystring"));

}



TEST_F(WildcardPatternTest_561, EmptyStringWildcardAtBothEnds_561) {

    WildcardPattern wildcardPattern = WildcardPattern("*", CaseSensitive::Yes);

    EXPECT_TRUE(wildcardPattern.matches("anystring"));

}



// Exceptional or error cases

// Note: Since the implementation doesn't throw exceptions and treats unknown enum as an internal error, we cannot test exceptional cases directly.



// Verification of external interactions is not applicable here since there are no external collaborators involved.
