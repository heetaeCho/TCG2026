#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



// Test Fixture for RE2 class

class RE2Test_4 : public ::testing::Test {

protected:

    virtual void SetUp() {}

    virtual void TearDown() {}

};



// Test normal operation of error_code() when pattern is valid

TEST_F(RE2Test_4, ValidPatternErrorCode_4) {

    RE2 re("abc");

    EXPECT_EQ(re.error_code(), ErrorCode::kNoError);

}



// Test boundary condition with empty string pattern

TEST_F(RE2Test_4, EmptyPatternErrorCode_4) {

    RE2 re("");

    EXPECT_NE(re.error_code(), ErrorCode::kNoError);

}



// Test exceptional case with invalid regex pattern

TEST_F(RE2Test_4, InvalidPatternErrorCode_4) {

    RE2 re("[");

    EXPECT_NE(re.error_code(), ErrorCode::kNoError);

}



// Test normal operation of ok() when pattern is valid

TEST_F(RE2Test_4, ValidPatternOk_4) {

    RE2 re("abc");

    EXPECT_TRUE(re.ok());

}



// Test boundary condition with empty string pattern for ok()

TEST_F(RE2Test_4, EmptyPatternOk_4) {

    RE2 re("");

    EXPECT_FALSE(re.ok());

}



// Test exceptional case with invalid regex pattern for ok()

TEST_F(RE2Test_4, InvalidPatternOk_4) {

    RE2 re("[");

    EXPECT_FALSE(re.ok());

}



// Test normal operation of FullMatch

TEST_F(RE2Test_4, FullMatchSuccess_4) {

    RE2 re("abc");

    EXPECT_TRUE(FullMatch("abc", re));

}



// Test boundary condition with empty string pattern for FullMatch

TEST_F(RE2Test_4, EmptyPatternFullMatchFailure_4) {

    RE2 re("");

    EXPECT_FALSE(FullMatch("abc", re));

}



// Test exceptional case with invalid regex pattern for FullMatch

TEST_F(RE2Test_4, InvalidPatternFullMatchFailure_4) {

    RE2 re("[");

    EXPECT_FALSE(FullMatch("abc", re));

}



// Test normal operation of PartialMatch

TEST_F(RE2Test_4, PartialMatchSuccess_4) {

    RE2 re("bc");

    EXPECT_TRUE(PartialMatch("abc", re));

}



// Test boundary condition with empty string pattern for PartialMatch

TEST_F(RE2Test_4, EmptyPatternPartialMatchFailure_4) {

    RE2 re("");

    EXPECT_FALSE(PartialMatch("abc", re));

}



// Test exceptional case with invalid regex pattern for PartialMatch

TEST_F(RE2Test_4, InvalidPatternPartialMatchFailure_4) {

    RE2 re("[");

    EXPECT_FALSE(PartialMatch("abc", re));

}



// Test normal operation of Replace

TEST_F(RE2Test_4, ReplaceSuccess_4) {

    RE2 re("(a)(b)(c)");

    std::string str = "abc";

    EXPECT_TRUE(Replace(&str, re, "\\3\\2\\1"));

    EXPECT_EQ(str, "cba");

}



// Test boundary condition with empty string pattern for Replace

TEST_F(RE2Test_4, EmptyPatternReplaceFailure_4) {

    RE2 re("");

    std::string str = "abc";

    EXPECT_FALSE(Replace(&str, re, "\\3\\2\\1"));

}



// Test exceptional case with invalid regex pattern for Replace

TEST_F(RE2Test_4, InvalidPatternReplaceFailure_4) {

    RE2 re("[");

    std::string str = "abc";

    EXPECT_FALSE(Replace(&str, re, "\\3\\2\\1"));

}



// Test normal operation of GlobalReplace

TEST_F(RE2Test_4, GlobalReplaceSuccess_4) {

    RE2 re("a");

    std::string str = "aaaa";

    EXPECT_EQ(GlobalReplace(&str, re, ""), 0);

    EXPECT_EQ(str, "");

}



// Test boundary condition with empty string pattern for GlobalReplace

TEST_F(RE2Test_4, EmptyPatternGlobalReplaceFailure_4) {

    RE2 re("");

    std::string str = "abc";

    EXPECT_EQ(GlobalReplace(&str, re, "\\3\\2\\1"), 0);

}



// Test exceptional case with invalid regex pattern for GlobalReplace

TEST_F(RE2Test_4, InvalidPatternGlobalReplaceFailure_4) {

    RE2 re("[");

    std::string str = "abc";

    EXPECT_EQ(GlobalReplace(&str, re, "\\3\\2\\1"), 0);

}



// Test normal operation of Extract

TEST_F(RE2Test_4, ExtractSuccess_4) {

    RE2 re("(a)(b)(c)");

    std::string result;

    EXPECT_TRUE(Extract("abc", re, "\\3\\2\\1", &result));

    EXPECT_EQ(result, "cba");

}



// Test boundary condition with empty string pattern for Extract

TEST_F(RE2Test_4, EmptyPatternExtractFailure_4) {

    RE2 re("");

    std::string result;

    EXPECT_FALSE(Extract("abc", re, "\\3\\2\\1", &result));

}



// Test exceptional case with invalid regex pattern for Extract

TEST_F(RE2Test_4, InvalidPatternExtractFailure_4) {

    RE2 re("[");

    std::string result;

    EXPECT_FALSE(Extract("abc", re, "\\3\\2\\1", &result));

}
