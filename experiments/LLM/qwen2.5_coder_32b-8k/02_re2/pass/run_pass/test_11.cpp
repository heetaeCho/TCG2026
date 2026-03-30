#include <gtest/gtest.h>

#include "re2/re2.h"

#include "absl/strings/string_view.h"



using namespace re2;



class RE2Test_11 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RE2Test_11, NumberOfCapturingGroups_ZeroCaptures_11) {

    RE2 re("(a)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 0);

}



TEST_F(RE2Test_11, NumberOfCapturingGroups_OneCapture_11) {

    RE2 re("(.*)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 1);

}



TEST_F(RE2Test_11, NumberOfCapturingGroups_MultipleCaptures_11) {

    RE2 re("(a)(b)(c)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 3);

}



TEST_F(RE2Test_11, Match_NoMatch_11) {

    RE2 re("abc");

    bool match = RE2::FullMatch("def", re);

    EXPECT_FALSE(match);

}



TEST_F(RE2Test_11, Match_ExactMatch_11) {

    RE2 re("abc");

    bool match = RE2::FullMatch("abc", re);

    EXPECT_TRUE(match);

}



TEST_F(RE2Test_11, Match_PartialMatch_11) {

    RE2 re("abc");

    bool match = RE2::PartialMatch("defabcghi", re);

    EXPECT_TRUE(match);

}



TEST_F(RE2Test_11, Match_EmptyString_11) {

    RE2 re("");

    bool match = RE2::FullMatch("", re);

    EXPECT_TRUE(match);

}



TEST_F(RE2Test_11, Replace_NoReplacement_11) {

    std::string input = "abc";

    RE2 re("def");

    RE2::Replace(&input, re, "xyz");

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_11, Replace_SimpleReplacement_11) {

    std::string input = "abc";

    RE2 re("b");

    RE2::Replace(&input, re, "x");

    EXPECT_EQ(input, "axc");

}



TEST_F(RE2Test_11, Replace_GlobalReplacement_11) {

    std::string input = "abacaba";

    RE2 re("a");

    int count = RE2::GlobalReplace(&input, re, "");

    EXPECT_EQ(count, 3);

    EXPECT_EQ(input, "bcb");

}



TEST_F(RE2Test_11, Extract_NoMatch_11) {

    std::string input = "def";

    std::string result;

    RE2 re("abc");

    bool match = RE2::Extract(input, re, "\\0", &result);

    EXPECT_FALSE(match);

    EXPECT_TRUE(result.empty());

}



TEST_F(RE2Test_11, Extract_MatchWithGroup_11) {

    std::string input = "abc";

    std::string result;

    RE2 re("(a)(bc)");

    bool match = RE2::Extract(input, re, "\\1", &result);

    EXPECT_TRUE(match);

    EXPECT_EQ(result, "a");

}



TEST_F(RE2Test_11, QuoteMeta_SimpleString_11) {

    std::string input = "abc";

    std::string quoted = RE2::QuoteMeta(input);

    EXPECT_EQ(quoted, "abc");

}



TEST_F(RE2Test_11, QuoteMeta_StringWithSpecialChars_11) {

    std::string input = "a.b+c?d*e[f]g{h}i|j(l)m\\n";

    std::string quoted = RE2::QuoteMeta(input);

    EXPECT_EQ(quoted, "a\\.b\\+c\\?d\\*e\\[f\\]g\\{h\\}i\\|j\\(l\\)m\\\\n");

}



TEST_F(RE2Test_11, CheckRewriteString_Valid_11) {

    std::string rewrite = "abc";

    std::string error;

    RE2 re("a(b)c");

    bool valid = re.CheckRewriteString(rewrite, &error);

    EXPECT_TRUE(valid);

    EXPECT_TRUE(error.empty());

}



TEST_F(RE2Test_11, CheckRewriteString_InvalidBackslash_11) {

    std::string rewrite = "abc\\";

    std::string error;

    RE2 re("a(b)c");

    bool valid = re.CheckRewriteString(rewrite, &error);

    EXPECT_FALSE(valid);

    EXPECT_EQ(error, "invalid backreference syntax: \\ at end of string");

}
