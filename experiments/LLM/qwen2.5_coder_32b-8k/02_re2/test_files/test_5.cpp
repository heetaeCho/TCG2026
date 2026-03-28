#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_5 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RE2Test_5, ConstructorValidPattern_5) {

    RE2 re("valid_pattern");

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_5, ConstructorInvalidPattern_5) {

    RE2 re("invalid[");

    EXPECT_FALSE(re.ok());

}



TEST_F(RE2Test_5, ErrorMethodOnValidPattern_5) {

    RE2 re("valid_pattern");

    EXPECT_EQ("", re.error());

}



TEST_F(RE2Test_5, ErrorMethodOnInvalidPattern_5) {

    RE2 re("invalid[");

    EXPECT_FALSE(re.error().empty());

}



TEST_F(RE2Test_5, ErrorArgMethodOnValidPattern_5) {

    RE2 re("valid_pattern");

    EXPECT_EQ("", re.error_arg());

}



TEST_F(RE2Test_5, ErrorArgMethodOnInvalidPattern_5) {

    RE2 re("invalid[");

    EXPECT_FALSE(re.error_arg().empty());

}



TEST_F(RE2Test_5, FullMatchValidPattern_5) {

    RE2 re("abc");

    std::string text = "abc";

    EXPECT_TRUE(FullMatch(text, re));

}



TEST_F(RE2Test_5, FullMatchInvalidPattern_5) {

    RE2 re("abc");

    std::string text = "abcd";

    EXPECT_FALSE(FullMatch(text, re));

}



TEST_F(RE2Test_5, PartialMatchValidPattern_5) {

    RE2 re("abc");

    std::string text = "xabcx";

    EXPECT_TRUE(PartialMatch(text, re));

}



TEST_F(RE2Test_5, PartialMatchInvalidPattern_5) {

    RE2 re("abc");

    std::string text = "xyz";

    EXPECT_FALSE(PartialMatch(text, re));

}



TEST_F(RE2Test_5, ConsumeValidPattern_5) {

    absl::string_view input = "abcde";

    RE2 re("abc");

    EXPECT_TRUE(Consume(&input, re));

    EXPECT_EQ(input, "de");

}



TEST_F(RE2Test_5, ConsumeInvalidPattern_5) {

    absl::string_view input = "xyz";

    RE2 re("abc");

    EXPECT_FALSE(Consume(&input, re));

    EXPECT_EQ(input, "xyz");

}



TEST_F(RE2Test_5, FindAndConsumeValidPattern_5) {

    absl::string_view input = "xabcde";

    RE2 re("abc");

    EXPECT_TRUE(FindAndConsume(&input, re));

    EXPECT_EQ(input, "de");

}



TEST_F(RE2Test_5, FindAndConsumeInvalidPattern_5) {

    absl::string_view input = "xyzabc";

    RE2 re("^abc");

    EXPECT_FALSE(FindAndConsume(&input, re));

    EXPECT_EQ(input, "xyzabc");

}



TEST_F(RE2Test_5, ReplaceValidPattern_5) {

    std::string str = "abcde";

    RE2 re("abc");

    bool result = Replace(&str, re, "123");

    EXPECT_TRUE(result);

    EXPECT_EQ(str, "123de");

}



TEST_F(RE2Test_5, GlobalReplaceValidPattern_5) {

    std::string str = "ab cab ab";

    RE2 re("ab");

    int count = GlobalReplace(&str, re, "xy");

    EXPECT_EQ(count, 2);

    EXPECT_EQ(str, "xy cxy xy");

}



TEST_F(RE2Test_5, ExtractValidPattern_5) {

    std::string text = "abcde";

    RE2 re("ab(c)d(e)");

    std::string out;

    bool result = Extract(text, re, "\\1\\2", &out);

    EXPECT_TRUE(result);

    EXPECT_EQ(out, "ce");

}



TEST_F(RE2Test_5, QuoteMetaValidPattern_5) {

    std::string unquoted = "abc.def";

    std::string quoted = RE2::QuoteMeta(unquoted);

    EXPECT_EQ(quoted, "abc\\.def");

}



TEST_F(RE2Test_5, ProgramSizeOnValidPattern_5) {

    RE2 re("abc");

    int size = re.ProgramSize();

    EXPECT_GE(size, 0); // Size should be non-negative

}



TEST_F(RE2Test_5, ReverseProgramSizeOnValidPattern_5) {

    RE2 re("abc");

    int size = re.ReverseProgramSize();

    EXPECT_GE(size, 0); // Size should be non-negative

}
