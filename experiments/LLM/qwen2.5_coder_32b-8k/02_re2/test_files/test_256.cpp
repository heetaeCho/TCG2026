#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test_256 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(RE2Test_256, Replace_SimpleMatch_256) {

    std::string str = "hello world";

    RE2 re("world");

    EXPECT_TRUE(RE2::Replace(&str, re, "planet"));

    EXPECT_EQ(str, "hello planet");

}



TEST_F(RE2Test_256, Replace_NoMatch_256) {

    std::string str = "hello world";

    RE2 re("universe");

    EXPECT_FALSE(RE2::Replace(&str, re, "planet"));

    EXPECT_EQ(str, "hello world");

}



TEST_F(RE2Test_256, Replace_MaxSubmatchExceeded_256) {

    std::string str = "hello 123";

    RE2 re("(\\d)(\\d)(\\d)");

    EXPECT_FALSE(RE2::Replace(&str, re, "\\1\\2\\3\\4")); // \\4 is out of bounds

}



TEST_F(RE2Test_256, Replace_CapturingGroupMismatch_256) {

    std::string str = "hello 12";

    RE2 re("(\\d)(\\d)(\\d)");

    EXPECT_FALSE(RE2::Replace(&str, re, "\\1\\2")); // Pattern has 3 groups but rewrite only uses 2

}



TEST_F(RE2Test_256, Replace_EmptyRewriteString_256) {

    std::string str = "hello world";

    RE2 re("world");

    EXPECT_TRUE(RE2::Replace(&str, re, ""));

    EXPECT_EQ(str, "hello ");

}



TEST_F(RE2Test_256, Replace_MultipleMatches_256) {

    std::string str = "123 456 789";

    RE2 re("\\d+");

    EXPECT_TRUE(RE2::Replace(&str, re, "#"));

    EXPECT_EQ(str, "# # #");

}



TEST_F(RE2Test_256, Replace_AnchorStart_256) {

    std::string str = "hello world";

    RE2 re("^hello");

    EXPECT_TRUE(RE2::Replace(&str, re, "hi"));

    EXPECT_EQ(str, "hi world");

}



TEST_F(RE2Test_256, Replace_AnchorBoth_256) {

    std::string str = "hello";

    RE2 re("^hello$");

    EXPECT_TRUE(RE2::Replace(&str, re, "hi"));

    EXPECT_EQ(str, "hi");

}



} // namespace re2
