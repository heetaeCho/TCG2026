#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "absl/strings/string_view.h"



using namespace re2;

using ::testing::_;

using ::testing::Eq;



class ParseStateTest : public ::testing::Test {

protected:

    RegexpStatus status;

    Regexp* out_re = nullptr;

};



TEST_F(ParseStateTest, ParseCharClass_NormalOperation_531) {

    absl::string_view s("[a-z]");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(ParseStateTest, ParseCharClass_Negated_531) {

    absl::string_view s("[^a-z]");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(ParseStateTest, ParseCharClass_Empty_531) {

    absl::string_view s("[]");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(ParseStateTest, ParseCharClass_MissingBracket_531) {

    absl::string_view s("[a-z");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpMissingBracket);

}



TEST_F(ParseStateTest, ParseCharClass_BadRange_531) {

    absl::string_view s("[z-a]");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpBadCharRange);

}



TEST_F(ParseStateTest, ParseCharClass_EmptyString_531) {

    absl::string_view s("");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpInternalError);

}



TEST_F(ParseStateTest, ParseCharClass_NoBrackets_531) {

    absl::string_view s("a-z");

    bool result = Regexp::ParseState(NoParseFlags, "", &status).ParseCharClass(&s, &out_re, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpInternalError);

}
