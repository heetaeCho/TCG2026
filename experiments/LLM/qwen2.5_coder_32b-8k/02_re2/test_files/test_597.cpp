#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test_597 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(RE2Test_597, ConstructorWithPattern_597) {

    RE2 re("abc");

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_597, ConstructorWithOptions_597) {

    RE2::Options options;

    RE2 re("abc", options);

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_597, InvalidPattern_597) {

    RE2 re("*");

    EXPECT_FALSE(re.ok());

}



TEST_F(RE2Test_597, FullMatchSuccess_597) {

    RE2 re("abc");

    EXPECT_TRUE(RE2::FullMatch("abc", re));

}



TEST_F(RE2Test_597, FullMatchFailure_597) {

    RE2 re("abc");

    EXPECT_FALSE(RE2::FullMatch("abcd", re));

}



TEST_F(RE2Test_597, PartialMatchSuccess_597) {

    RE2 re("bc");

    EXPECT_TRUE(RE2::PartialMatch("abc", re));

}



TEST_F(RE2Test_597, PartialMatchFailure_597) {

    RE2 re("bd");

    EXPECT_FALSE(RE2::PartialMatch("abc", re));

}



TEST_F(RE2Test_597, ReplaceSuccess_597) {

    RE2 re("bc");

    std::string input = "abc";

    RE2::Replace(&input, re, "123");

    EXPECT_EQ(input, "a123");

}



TEST_F(RE2Test_597, GlobalReplaceSuccess_597) {

    RE2 re("a");

    std::string input = "aaa";

    int count = RE2::GlobalReplace(&input, re, "b");

    EXPECT_EQ(input, "bbb");

    EXPECT_EQ(count, 3);

}



TEST_F(RE2Test_597, ExtractSuccess_597) {

    RE2 re("(a)(bc)");

    std::string input = "abc";

    std::string out;

    EXPECT_TRUE(RE2::Extract(input, re, "$1", &out));

    EXPECT_EQ(out, "a");

}



TEST_F(RE2Test_597, ExtractFailure_597) {

    RE2 re("(d)(e)");

    std::string input = "abc";

    std::string out;

    EXPECT_FALSE(RE2::Extract(input, re, "$1", &out));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2Test_597, QuoteMetaSuccess_597) {

    std::string quoted = RE2::QuoteMeta("a.b*c+");

    EXPECT_EQ(quoted, "a\\.b\\*c\\+");

}



TEST_F(RE2Test_597, NumberOfCapturingGroups_597) {

    RE2 re("(abc)(def)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 2);

}



TEST_F(RE2Test_597, ProgramSizeBoundary_597) {

    RE2 re("a");

    EXPECT_GE(re.ProgramSize(), 0);

}



TEST_F(RE2Test_597, ReverseProgramSizeBoundary_597) {

    RE2 re("a");

    EXPECT_GE(re.ReverseProgramSize(), 0);

}



} // namespace re2
