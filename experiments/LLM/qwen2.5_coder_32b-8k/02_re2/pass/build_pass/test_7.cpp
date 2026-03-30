#include <gtest/gtest.h>

#include <re2/re2.h>



class RE2Test_7 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RE2Test_7, FullMatch_SimplePatternMatches_7) {

    re2::RE2 regex("hello");

    EXPECT_TRUE(re2::RE2::FullMatch("hello", regex));

}



TEST_F(RE2Test_7, FullMatch_SimplePatternDoesNotMatch_7) {

    re2::RE2 regex("world");

    EXPECT_FALSE(re2::RE2::FullMatch("hello", regex));

}



TEST_F(RE2Test_7, FullMatch_EmptyStringMatchesEmptyRegex_7) {

    re2::RE2 regex("");

    EXPECT_TRUE(re2::RE2::FullMatch("", regex));

}



TEST_F(RE2Test_7, FullMatch_NonEmptyStringDoesNotMatchEmptyRegex_7) {

    re2::RE2 regex("");

    EXPECT_FALSE(re2::RE2::FullMatch("nonempty", regex));

}



TEST_F(RE2Test_7, FullMatch_InvalidPatternThrowsError_7) {

    re2::RE2 regex("(unmatched_paren");

    EXPECT_FALSE(regex.ok());

}



TEST_F(RE2Test_7, FullMatch_CapturingGroupMatches_7) {

    std::string s;

    re2::RE2::FullMatch("abc123", re2::RE2("(\\w+)"), &s);

    EXPECT_EQ(s, "abc123");

}



TEST_F(RE2Test_7, FullMatch_MultipleCapturingGroupsMatches_7) {

    std::string s1, s2;

    re2::RE2::FullMatch("abc123", re2::RE2("(\\w+)(\\d+)"), &s1, &s2);

    EXPECT_EQ(s1, "abc");

    EXPECT_EQ(s2, "123");

}



TEST_F(RE2Test_7, FullMatch_PatternWithAnchorsMatchesStartAndEnd_7) {

    re2::RE2 regex("^start.*end$");

    EXPECT_TRUE(re2::RE2::FullMatch("startmiddleend", regex));

}



TEST_F(RE2Test_7, FullMatch_PatternWithAnchorsDoesNotMatchStartAndEnd_7) {

    re2::RE2 regex("^start.*end$");

    EXPECT_FALSE(re2::RE2::FullMatch("startmiddle", regex));

}
