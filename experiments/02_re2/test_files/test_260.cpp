#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test_260 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables or objects here.

    }



    void TearDown() override {

        // Clean up any resources used in the tests.

    }

};



TEST_F(RE2Test_260, PossibleMatchRange_NormalOperation_260) {

    RE2 re("abc");

    std::string min, max;

    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_EQ(min, "abc");

    EXPECT_EQ(max, "abc");

}



TEST_F(RE2Test_260, PossibleMatchRange_MaxLenLessThanPrefix_260) {

    RE2 re("abcdef");

    std::string min, max;

    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 3));

    EXPECT_EQ(min, "abc");

    EXPECT_EQ(max, "abc");

}



TEST_F(RE2Test_260, PossibleMatchRange_EmptyPattern_260) {

    RE2 re("");

    std::string min, max;

    EXPECT_FALSE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_TRUE(min.empty());

    EXPECT_TRUE(max.empty());

}



TEST_F(RE2Test_260, PossibleMatchRange_NullProg_260) {

    RE2 re("abc");

    re.prog_ = nullptr;

    std::string min, max;

    EXPECT_FALSE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_TRUE(min.empty());

    EXPECT_TRUE(max.empty());

}



TEST_F(RE2Test_260, PossibleMatchRange_ProgramReturnsFalse_260) {

    RE2 re("abc");

    std::string min = "prefix", max = "prefix";

    re.prog_->ConfigurePrefixAccel("prefix", false);

    EXPECT_FALSE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_EQ(min, "");

    EXPECT_EQ(max, "");

}



TEST_F(RE2Test_260, PossibleMatchRange_PrefixFoldcase_260) {

    RE2 re("(?i)abc");

    std::string min, max;

    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_EQ(min, "ABC");

    EXPECT_EQ(max, "ABC");

}



TEST_F(RE2Test_260, PossibleMatchRange_ProgramReturnsTrue_260) {

    RE2 re("abc");

    std::string min = "prefix", max = "prefix";

    std::string dmin = "def", dmax = "def";

    re.prog_->ConfigurePrefixAccel("prefix", false);

    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));

    EXPECT_EQ(min, "prefixdef");

    EXPECT_EQ(max, "prefixdef");

}



} // namespace re2
