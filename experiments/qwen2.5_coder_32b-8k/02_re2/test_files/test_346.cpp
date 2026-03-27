#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_346 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    // Helper function to create a literal regexp

    static Regexp* CreateLiteralRegexp(Rune rune, ParseFlags flags) {

        return Regexp::NewLiteral(rune, flags);

    }

};



TEST_F(RegexpTest_346, NewLiteral_ReturnsNonNullPointer_346) {

    Regexp* re = CreateLiteralRegexp('a', 0);

    ASSERT_NE(re, nullptr);

    delete re;

}



TEST_F(RegexpTest_346, NewLiteral_CorrectOpCode_346) {

    Regexp* re = CreateLiteralRegexp('b', 0);

    EXPECT_EQ(re->op(), kRegexpLiteral);

    delete re;

}



TEST_F(RegexpTest_346, NewLiteral_CorrectRuneValue_346) {

    Rune rune = 'c';

    Regexp* re = CreateLiteralRegexp(rune, 0);

    EXPECT_EQ(re->rune(), rune);

    delete re;

}



TEST_F(RegexpTest_346, NewLiteral_ParseFlagsSetCorrectly_346) {

    ParseFlags flags = 1; // Example flag

    Regexp* re = CreateLiteralRegexp('d', flags);

    EXPECT_EQ(re->parse_flags(), flags);

    delete re;

}



TEST_F(RegexpTest_346, NewLiteral_MultipleInstancesHaveUniqueAddresses_346) {

    Regexp* re1 = CreateLiteralRegexp('e', 0);

    Regexp* re2 = CreateLiteralRegexp('f', 0);

    EXPECT_NE(re1, re2);

    delete re1;

    delete re2;

}



TEST_F(RegexpTest_346, NewLiteral_DestructorDoesNotCrash_346) {

    Regexp* re = CreateLiteralRegexp('g', 0);

    delete re;

}
