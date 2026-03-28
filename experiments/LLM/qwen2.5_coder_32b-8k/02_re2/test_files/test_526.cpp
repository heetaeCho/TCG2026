#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/parse.h"

#include "absl/strings/string_view.h"



namespace re2 {



class MaybeParsePerlCCEscapeTest : public ::testing::Test {

protected:

    absl::string_view input;

    Regexp::ParseFlags parse_flags;



    void SetUp() override {

        input = "";

        parse_flags = Regexp::NoParseFlags;

    }

};



TEST_F(MaybeParsePerlCCEscapeTest_526, NullIfNotPerlClassesFlag_526) {

    input = "\\pL";

    const UGroup* result = MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MaybeParsePerlCCEscapeTest_526, NullIfInputTooShort_526) {

    input = "\\";

    parse_flags = Regexp::PerlClasses;

    const UGroup* result = MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MaybeParsePerlCCEscapeTest_526, NullIfNotBackslashPrefix_526) {

    input = "pL";

    parse_flags = Regexp::PerlClasses;

    const UGroup* result = MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MaybeParsePerlCCEscapeTest_526, NullIfUnknownGroupName_526) {

    input = "\\pX";

    parse_flags = Regexp::PerlClasses;

    const UGroup* result = MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_EQ(result, nullptr);

}



TEST_F(MaybeParsePerlCCEscapeTest_526, ValidGroupNameReturnsUGroupPtr_526) {

    input = "\\pL";

    parse_flags = Regexp::PerlClasses;

    const UGroup* result = MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_NE(result, nullptr);

}



TEST_F(MaybeParsePerlCCEscapeTest_526, InputIsAdvancedAfterValidGroupName_526) {

    input = "\\pLabc";

    parse_flags = Regexp::PerlClasses;

    MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_EQ(input, "abc");

}



TEST_F(MaybeParsePerlCCEscapeTest_526, ValidGroupNameWithTrailingBackslashHandled_526) {

    input = "\\pL\\";

    parse_flags = Regexp::PerlClasses;

    const UGroup* result = MaybeParsePerlCCEscape(&input, parse_flags);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(input, "\\");

}



}  // namespace re2
