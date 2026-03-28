#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test_596 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RE2Test_596, ConstructorWithPattern_596) {

    RE2 re("(abc)");

    EXPECT_TRUE(re.ok());

}



TEST_F(RE2Test_596, ConstructorWithInvalidPattern_596) {

    RE2 re("(*");

    EXPECT_FALSE(re.ok());

}



TEST_F(RE2Test_596, FullMatch_Successful_596) {

    RE2 re("(abc)");

    std::string text = "abc";

    EXPECT_TRUE(RE2::FullMatch(text, re));

}



TEST_F(RE2Test_596, FullMatch_Unsuccessful_596) {

    RE2 re("(abc)");

    std::string text = "abcd";

    EXPECT_FALSE(RE2::FullMatch(text, re));

}



TEST_F(RE2Test_596, PartialMatch_Successful_596) {

    RE2 re("(abc)");

    std::string text = "abcd";

    EXPECT_TRUE(RE2::PartialMatch(text, re));

}



TEST_F(RE2Test_596, PartialMatch_Unsuccessful_596) {

    RE2 re("(abc)");

    std::string text = "def";

    EXPECT_FALSE(RE2::PartialMatch(text, re));

}



TEST_F(RE2Test_596, Replace_Successful_596) {

    RE2 re("(abc)");

    std::string str = "abcd";

    std::string rewrite = "xyz";

    EXPECT_TRUE(RE2::Replace(&str, re, rewrite));

    EXPECT_EQ(str, "xyzd");

}



TEST_F(RE2Test_596, Replace_Unsuccessful_596) {

    RE2 re("(abc)");

    std::string str = "def";

    std::string rewrite = "xyz";

    EXPECT_FALSE(RE2::Replace(&str, re, rewrite));

    EXPECT_EQ(str, "def");

}



TEST_F(RE2Test_596, GlobalReplace_Successful_596) {

    RE2 re("(abc)");

    std::string str = "abcdabc";

    std::string rewrite = "xyz";

    EXPECT_EQ(RE2::GlobalReplace(&str, re, rewrite), 2);

    EXPECT_EQ(str, "xyzdxyz");

}



TEST_F(RE2Test_596, GlobalReplace_Unsuccessful_596) {

    RE2 re("(abc)");

    std::string str = "def";

    std::string rewrite = "xyz";

    EXPECT_EQ(RE2::GlobalReplace(&str, re, rewrite), 0);

    EXPECT_EQ(str, "def");

}



TEST_F(RE2Test_596, Extract_Successful_596) {

    RE2 re("(abc)");

    std::string text = "abcd";

    std::string rewrite = "$1";

    std::string out;

    EXPECT_TRUE(RE2::Extract(text, re, rewrite, &out));

    EXPECT_EQ(out, "abc");

}



TEST_F(RE2Test_596, Extract_Unsuccessful_596) {

    RE2 re("(abc)");

    std::string text = "def";

    std::string rewrite = "$1";

    std::string out;

    EXPECT_FALSE(RE2::Extract(text, re, rewrite, &out));

}



TEST_F(RE2Test_596, QuoteMeta_Successful_596) {

    std::string unquoted = "abc.def";

    std::string expected_quoted = "abc\\.def";

    EXPECT_EQ(RE2::QuoteMeta(unquoted), expected_quoted);

}



TEST_F(RE2Test_596, NumberOfCapturingGroups_Boundary_596) {

    RE2 re("(a)(b)(c)");

    EXPECT_EQ(re.NumberOfCapturingGroups(), 3);

}



TEST_F(RE2Test_596, ProgramSize_Normal_596) {

    RE2 re("abc");

    EXPECT_GT(re.ProgramSize(), 0);

}



TEST_F(RE2Test_596, ReverseProgramSize_Normal_596) {

    RE2 re("abc");

    EXPECT_GT(re.ReverseProgramSize(), 0);

}



} // namespace re2
