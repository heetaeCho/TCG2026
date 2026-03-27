#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/parse.cc"

#include "re2/regexp.h"



using namespace re2;



class ParseStateTest_529 : public ::testing::Test {

protected:

    RegexpStatus status;

    absl::string_view whole_class = "test_class";

    Rune rune;

};



TEST_F(ParseStateTest_529, EmptyStringSetsMissingBracketError_529) {

    absl::string_view s = "";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpMissingBracket);

    EXPECT_EQ(status.error_arg(), whole_class);

}



TEST_F(ParseStateTest_529, BackslashAtStartParsesEscape_529) {

    absl::string_view s = "\\a";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_TRUE(result);

    // Assuming \a is parsed as ASCII Bell (7)

    EXPECT_EQ(rune, 7);

}



TEST_F(ParseStateTest_529, SingleCharacterParsesCorrectly_529) {

    absl::string_view s = "a";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(rune, 'a');

}



TEST_F(ParseStateTest_529, InvalidUTF8SetsBadUTF8Error_529) {

    // Assuming invalid UTF-8 sequence

    absl::string_view s = "\xC3\x28";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_FALSE(result);

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(ParseStateTest_529, ValidUTF8ParsesCorrectly_529) {

    // Assuming valid UTF-8 sequence for Unicode character U+00E9 (é)

    absl::string_view s = "\xC3\xA9";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(rune, 0xE9);

}



TEST_F(ParseStateTest_529, SingleCharacterConsumesOneChar_529) {

    absl::string_view s = "ab";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(s, "b");

}



TEST_F(ParseStateTest_529, BackslashConsumesTwoChars_529) {

    absl::string_view s = "\\ab";

    ParseState parse_state(0, "", &status);

    bool result = parse_state.ParseCCCharacter(&s, &rune, whole_class, &status);

    EXPECT_TRUE(result);

    EXPECT_EQ(s, "b");

}
