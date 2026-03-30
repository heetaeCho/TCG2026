#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/tostring.cc"



using namespace re2;



class RegexpTest_225 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_225, ToStringNormalOperation_225) {

    Regexp* regexp = Regexp::Parse("abc", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "abc");



    regexp->Decref();

}



TEST_F(RegexpTest_225, ToStringComplexPattern_225) {

    Regexp* regexp = Regexp::Parse("(a|b)*c+", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "(a|b)*c+");



    regexp->Decref();

}



TEST_F(RegexpTest_225, ToStringTruncatedPattern_225) {

    Regexp* regexp = Regexp::Parse("a{1000}", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "a{1000} [truncated]");



    regexp->Decref();

}



TEST_F(RegexpTest_225, ToStringEmptyPattern_225) {

    Regexp* regexp = Regexp::Parse("", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "");



    regexp->Decref();

}



TEST_F(RegexpTest_225, ToStringInvalidPattern_225) {

    Regexp* regexp = Regexp::Parse("[", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "");



    regexp->Decref();

}



TEST_F(RegexpTest_225, ToStringCapturingGroup_225) {

    Regexp* regexp = Regexp::Parse("(a)", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "(a)");



    regexp->Decref();

}



TEST_F(RegexpTest_225, ToStringNestedCapturingGroups_225) {

    Regexp* regexp = Regexp::Parse("((ab)c)", Regexp::NoParseFlags(), nullptr);

    ASSERT_NE(regexp, nullptr);



    std::string result = regexp->ToString();

    EXPECT_EQ(result, "((ab)c)");



    regexp->Decref();

}
