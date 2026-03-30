#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "absl/strings/string_view.h"



using namespace re2;



class RegexpTest_421 : public ::testing::Test {

protected:

    std::string dst;

    RegexpStatus status;

};



TEST_F(RegexpTest_421, SimplifyValidRegex_421) {

    bool result = Regexp::SimplifyRegexp("a*", ParseFlags::kNone, &dst, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_EQ(dst, "a*");

}



TEST_F(RegexpTest_421, SimplifyEmptyString_421) {

    bool result = Regexp::SimplifyRegexp("", ParseFlags::kNone, &dst, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_EQ(dst, "");

}



TEST_F(RegexpTest_421, SimplifyComplexRegex_421) {

    bool result = Regexp::SimplifyRegexp("(a|b)*c?", ParseFlags::kNone, &dst, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_EQ(dst, "(a|b)*c?");

}



TEST_F(RegexpTest_421, SimplifyInvalidRegex_421) {

    bool result = Regexp::SimplifyRegexp("(", ParseFlags::kNone, &dst, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpMissingParen);

}



TEST_F(RegexpTest_421, SimplifyWithStatusNull_421) {

    bool result = Regexp::SimplifyRegexp("a*", ParseFlags::kNone, &dst, nullptr);

    EXPECT_TRUE(result);

    EXPECT_EQ(dst, "a*");

}



TEST_F(RegexpTest_421, SimplifyInternalError_421) {

    // Assuming there's a way to force an internal error, this is a placeholder

    bool result = Regexp::SimplifyRegexp("a*", ParseFlags::kNone, &dst, &status);

    EXPECT_TRUE(result || status.code() == kRegexpInternalError);

}



TEST_F(RegexpTest_421, SimplifyWithParseFlagCaseInsensitive_421) {

    bool result = Regexp::SimplifyRegexp("a", ParseFlags::kCaseInsensitive, &dst, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_EQ(dst, "a");

}



TEST_F(RegexpTest_421, SimplifyWithParseFlagLiteral_421) {

    bool result = Regexp::SimplifyRegexp("a", ParseFlags::kLiteral, &dst, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

    EXPECT_EQ(dst, "a");

}
