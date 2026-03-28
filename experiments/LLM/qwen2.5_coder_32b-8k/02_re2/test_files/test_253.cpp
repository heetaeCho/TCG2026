#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_253 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(RE2Test_253, PartialMatchN_NormalOperation_253) {

    RE2 re("a+b+");

    const Arg* const args[] = {nullptr};

    EXPECT_TRUE(re.PartialMatchN("aaabbb", re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_EmptyString_253) {

    RE2 re("a+b+");

    const Arg* const args[] = {nullptr};

    EXPECT_FALSE(re.PartialMatchN("", re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_NoMatch_253) {

    RE2 re("a+b+");

    const Arg* const args[] = {nullptr};

    EXPECT_FALSE(re.PartialMatchN("abc", re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_BoundaryCondition_253) {

    RE2 re("ab");

    const Arg* const args[] = {nullptr};

    EXPECT_TRUE(re.PartialMatchN("ab", re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_WithArgs_253) {

    int n;

    RE2::Arg arg(&n);

    RE2 re("(\\d+)");

    const Arg* const args[] = {&arg};

    EXPECT_TRUE(re.PartialMatchN("123abc", re, args, 1));

    EXPECT_EQ(n, 123);

}



TEST_F(RE2Test_253, PartialMatchN_InvalidPattern_253) {

    RE2 re("(a+");

    const Arg* const args[] = {nullptr};

    EXPECT_FALSE(re.ok());

    EXPECT_FALSE(re.PartialMatchN("aaa", re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_LargeInput_253) {

    std::string large_input(1000000, 'a');

    RE2 re("a+");

    const Arg* const args[] = {nullptr};

    EXPECT_TRUE(re.PartialMatchN(large_input, re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_AnchoredStart_253) {

    RE2 re("^abc");

    const Arg* const args[] = {nullptr};

    EXPECT_TRUE(re.PartialMatchN("abcd", re, args, 0));

    EXPECT_FALSE(re.PartialMatchN("1abc", re, args, 0));

}



TEST_F(RE2Test_253, PartialMatchN_AnchoredBoth_253) {

    RE2 re("^abc$");

    const Arg* const args[] = {nullptr};

    EXPECT_TRUE(re.PartialMatchN("abc", re, args, 0));

    EXPECT_FALSE(re.PartialMatchN("abcd", re, args, 0));

    EXPECT_FALSE(re.PartialMatchN("1abc", re, args, 0));

}
