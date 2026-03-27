#include <gtest/gtest.h>

#include "re2/re2.h"

#include <string>



using namespace re2;



TEST_F(RE2Test_39, DefaultConstructorWithPattern_39) {

    RE2 regex("test");

    EXPECT_EQ(regex.pattern(), "test");

}



TEST_F(RE2Test_39, OptionsConstructor_39) {

    RE2::Options options;

    RE2 regex("test", options);

    EXPECT_EQ(regex.pattern(), "test");

}



TEST_F(RE2Test_39, OkMethod_ReturnsTrueForValidPattern_39) {

    RE2 regex("valid_pattern");

    EXPECT_TRUE(regex.ok());

}



TEST_F(RE2Test_39, OkMethod_ReturnsFalseForInvalidPattern_39) {

    RE2 regex("*invalid*pattern*");

    EXPECT_FALSE(regex.ok());

}



TEST_F(RE2Test_39, ErrorMethod_ReturnsErrorMessageForInvalidPattern_39) {

    RE2 regex("*invalid*pattern*");

    EXPECT_FALSE(regex.error().empty());

}



TEST_F(RE2Test_39, FullMatch_NonMatchingPattern_39) {

    RE2 regex("test_pattern");

    std::string text = "non_matching_text";

    EXPECT_FALSE(RE2::FullMatch(text, regex));

}



TEST_F(RE2Test_39, FullMatch_MatchingPattern_39) {

    RE2 regex("test_pattern");

    std::string text = "test_pattern";

    EXPECT_TRUE(RE2::FullMatch(text, regex));

}



TEST_F(RE2Test_39, PartialMatch_NonMatchingPattern_39) {

    RE2 regex("test_pattern");

    std::string text = "non_matching_text";

    EXPECT_FALSE(RE2::PartialMatch(text, regex));

}



TEST_F(RE2Test_39, PartialMatch_MatchingPattern_39) {

    RE2 regex("test");

    std::string text = "this_is_a_test_string";

    EXPECT_TRUE(RE2::PartialMatch(text, regex));

}



TEST_F(RE2Test_39, Replace_Method_39) {

    RE2 regex("cat");

    std::string target = "one cat two cats in the hat";

    std::string replacement = "dog";

    RE2::Replace(&target, regex, replacement);

    EXPECT_EQ(target, "one dog two dogs in the hat");

}



TEST_F(RE2Test_39, GlobalReplace_Method_39) {

    RE2 regex("cat");

    std::string target = "one cat two cats in the hat";

    std::string replacement = "dog";

    int replacements = RE2::GlobalReplace(&target, regex, replacement);

    EXPECT_EQ(target, "one dog two dogs in the hat");

    EXPECT_EQ(replacements, 2);

}



TEST_F(RE2Test_39, NumberOfCapturingGroups_ReturnsCorrectCount_39) {

    RE2 regex("(a)(b)(c)");

    EXPECT_EQ(regex.NumberOfCapturingGroups(), 3);

}



TEST_F(RE2Test_39, QuoteMeta_EscapesSpecialCharacters_39) {

    std::string unquoted = "abc.def*ghi+jkl";

    std::string quoted = RE2::QuoteMeta(unquoted);

    EXPECT_EQ(quoted, "abc\\.def\\*ghi\\+jkl");

}



TEST_F(RE2Test_39, ProgramSize_ReturnsNonNegativeValue_39) {

    RE2 regex("test_pattern");

    EXPECT_GE(regex.ProgramSize(), 0);

}



TEST_F(RE2Test_39, ReverseProgramSize_ReturnsNonNegativeValue_39) {

    RE2 regex("test_pattern");

    EXPECT_GE(regex.ReverseProgramSize(), 0);

}
