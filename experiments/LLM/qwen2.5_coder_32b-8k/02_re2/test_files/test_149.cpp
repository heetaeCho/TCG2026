#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class RegexpTest_149 : public ::testing::Test {

protected:

    // Helper function to create a simple literal Regexp

    static Regexp* CreateLiteralRegexp(const std::string& pattern, ParseFlags flags) {

        RegexpStatus status;

        return Regexp::Parse(pattern, flags, &status);

    }

};



TEST_F(RegexpTest_149, OpReturnsCorrectValue_149) {

    auto regexp = CreateLiteralRegexp("a", kFlagNone);

    ASSERT_NE(regexp, nullptr);

    EXPECT_EQ(regexp->op(), kRegexpLiteral);

    delete regexp;

}



TEST_F(RegexpTest_149, RefCountingWorks_149) {

    auto regexp = CreateLiteralRegexp("a", kFlagNone);

    ASSERT_NE(regexp, nullptr);



    int initial_ref_count = regexp->Ref();

    EXPECT_EQ(initial_ref_count, 1);



    auto incremented_regexp = regexp->Incref();

    EXPECT_EQ(incremented_regexp->Ref(), 2);



    regexp->Decref(); // Decrease to 1

    regexp->Decref(); // Decrease to 0 and delete



    // Ensure the object is deleted

    EXPECT_DEATH(regexp->Ref(), ".*");

}



TEST_F(RegexpTest_149, SimplifyDoesNotChangeOpForSimpleLiteral_149) {

    auto regexp = CreateLiteralRegexp("a", kFlagNone);

    ASSERT_NE(regexp, nullptr);



    Regexp* simplified_regexp = regexp->Simplify();

    EXPECT_EQ(simplified_regexp->op(), kRegexpLiteral);



    delete regexp;

}



TEST_F(RegexpTest_149, NumCapturesReturnsZeroForSimpleLiteral_149) {

    auto regexp = CreateLiteralRegexp("a", kFlagNone);

    ASSERT_NE(regexp, nullptr);



    EXPECT_EQ(regexp->NumCaptures(), 0);



    delete regexp;

}



TEST_F(RegexpTest_149, ToStringMatchesPattern_149) {

    std::string pattern = "abc";

    auto regexp = CreateLiteralRegexp(pattern, kFlagNone);

    ASSERT_NE(regexp, nullptr);



    EXPECT_EQ(regexp->ToString(), pattern);



    delete regexp;

}



TEST_F(RegexpTest_149, ParseInvalidPatternReturnsNull_149) {

    RegexpStatus status;

    auto invalid_regexp = Regexp::Parse("(*)", kFlagNone, &status);

    EXPECT_EQ(invalid_regexp, nullptr);

}



TEST_F(RegexpTest_149, RequiredPrefixForSimpleLiteralWorks_149) {

    std::string pattern = "abc";

    auto regexp = CreateLiteralRegexp(pattern, kFlagNone);

    ASSERT_NE(regexp, nullptr);



    std::string prefix;

    bool foldcase;

    Regexp* suffix;



    EXPECT_TRUE(regexp->RequiredPrefix(&prefix, &foldcase, &suffix));

    EXPECT_EQ(prefix, pattern);

    EXPECT_FALSE(foldcase);

    EXPECT_EQ(suffix, regexp); // For a simple literal, the suffix should be itself



    delete regexp;

}



} // namespace re2
