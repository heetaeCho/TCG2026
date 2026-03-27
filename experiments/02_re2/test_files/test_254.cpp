#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_254 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary state before each test.

    }



    void TearDown() override {

        // Clean up after each test, if needed.

    }

};



TEST_F(RE2Test_254, ConsumeN_SuccessfulMatch_254) {

    absl::string_view input = "abc123";

    RE2 re("\\d+");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_TRUE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_254, ConsumeN_NoMatch_254) {

    absl::string_view input = "abc";

    RE2 re("\\d+");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_FALSE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_254, ConsumeN_PartialMatch_254) {

    absl::string_view input = "abc123def";

    RE2 re("\\d+");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_TRUE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abcdef");

}



TEST_F(RE2Test_254, ConsumeN_EmptyInput_254) {

    absl::string_view input = "";

    RE2 re("\\d+");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_FALSE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "");

}



TEST_F(RE2Test_254, ConsumeN_EmptyPattern_254) {

    absl::string_view input = "abc123";

    RE2 re("");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_FALSE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abc123");

}



TEST_F(RE2Test_254, ConsumeN_AnchoredPattern_254) {

    absl::string_view input = "abc123";

    RE2 re("^\\d+");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_FALSE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abc123");

}



TEST_F(RE2Test_254, ConsumeN_MultiDigitMatch_254) {

    absl::string_view input = "123abc";

    RE2 re("\\d+");

    const Arg* const args[] = {};

    int n = 0;

    EXPECT_TRUE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_254, ConsumeN_WithArgs_SuccessfulMatch_254) {

    absl::string_view input = "abc123";

    RE2 re("([a-z]+)(\\d+)");

    int number;

    RE2::Arg args[] = {RE2::CRadix(&number)};

    int n = 1;

    EXPECT_TRUE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "");

    EXPECT_EQ(number, 123);

}



TEST_F(RE2Test_254, ConsumeN_WithArgs_NoMatch_254) {

    absl::string_view input = "abc";

    RE2 re("([a-z]+)(\\d+)");

    int number;

    RE2::Arg args[] = {RE2::CRadix(&number)};

    int n = 1;

    EXPECT_FALSE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "abc");

}



TEST_F(RE2Test_254, ConsumeN_WithArgs_PartialMatch_254) {

    absl::string_view input = "abc123def";

    RE2 re("([a-z]+)(\\d+)");

    int number;

    RE2::Arg args[] = {RE2::CRadix(&number)};

    int n = 1;

    EXPECT_TRUE(re.ConsumeN(&input, re, args, n));

    EXPECT_EQ(input, "def");

    EXPECT_EQ(number, 123);

}
