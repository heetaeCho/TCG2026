#include <gtest/gtest.h>

#include "re2/re2.h"

#include "absl/strings/string_view.h"



using namespace re2;



class RE2ExtractTest_258 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed, but for this example it's not necessary.

    }

};



TEST_F(RE2ExtractTest_258, ExtractBasicMatch_258) {

    RE2 re("\\d+");

    std::string text = "abc123def";

    std::string rewrite = "\\0";

    std::string out;



    EXPECT_TRUE(re.Extract(text, re, rewrite, &out));

    EXPECT_EQ(out, "123");

}



TEST_F(RE2ExtractTest_258, ExtractNoMatch_258) {

    RE2 re("\\d+");

    std::string text = "abcdef";

    std::string rewrite = "\\0";

    std::string out;



    EXPECT_FALSE(re.Extract(text, re, rewrite, &out));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2ExtractTest_258, ExtractWithRewrite_258) {

    RE2 re("(\\d+)-(\\d+)");

    std::string text = "range-100-200";

    std::string rewrite = "\\1 to \\2";

    std::string out;



    EXPECT_TRUE(re.Extract(text, re, rewrite, &out));

    EXPECT_EQ(out, "100 to 200");

}



TEST_F(RE2ExtractTest_258, ExtractWithEmptyRewrite_258) {

    RE2 re("\\d+");

    std::string text = "abc123def";

    std::string rewrite = "";

    std::string out;



    EXPECT_TRUE(re.Extract(text, re, rewrite, &out));

    EXPECT_TRUE(out.empty());

}



TEST_F(RE2ExtractTest_258, ExtractWithTooManyCapturingGroups_258) {

    RE2 re("(\\d+)-(\\d+)");

    std::string text = "range-100-200";

    std::string rewrite = "\\1-\\2-\\3"; // More groups than in pattern

    std::string out;



    EXPECT_FALSE(re.Extract(text, re, rewrite, &out));

}



TEST_F(RE2ExtractTest_258, ExtractWithInvalidRewriteString_258) {

    RE2 re("(\\d+)-(\\d+)");

    std::string text = "range-100-200";

    std::string rewrite = "\\g"; // Invalid escape sequence

    std::string out;



    EXPECT_FALSE(re.Extract(text, re, rewrite, &out));

}



TEST_F(RE2ExtractTest_258, ExtractWithLongRewriteString_258) {

    RE2 re("(\\d+)-(\\d+)");

    std::string text = "range-100-200";

    std::string rewrite(kVecSize * 3 + 1, 'a'); // Longer than kVecSize * 3

    std::string out;



    EXPECT_FALSE(re.Extract(text, re, rewrite, &out));

}



TEST_F(RE2ExtractTest_258, ExtractWithEmptyText_258) {

    RE2 re("\\d+");

    std::string text = "";

    std::string rewrite = "\\0";

    std::string out;



    EXPECT_FALSE(re.Extract(text, re, rewrite, &out));

}



TEST_F(RE2ExtractTest_258, ExtractWithInvalidPattern_258) {

    RE2 re("(");

    std::string text = "abc123def";

    std::string rewrite = "\\0";

    std::string out;



    EXPECT_FALSE(re.Extract(text, re, rewrite, &out));

}
