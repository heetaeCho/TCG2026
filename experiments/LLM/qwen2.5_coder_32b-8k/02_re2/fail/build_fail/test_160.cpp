#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_160 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RegexpTest_160, LiteralStringReturnsRunes_160) {

    Rune runes[] = { 't', 'e', 's', 't' };

    Regexp* regexp = Regexp::LiteralString(runes, 4, 0);

    ASSERT_EQ(regexp->op(), kRegexpLiteralString);

    EXPECT_EQ(regexp->runes()[0], 't');

    EXPECT_EQ(regexp->runes()[1], 'e');

    EXPECT_EQ(regexp->runes()[2], 's');

    EXPECT_EQ(regexp->runes()[3], 't');

    regexp->Decref();

}



TEST_F(RegexpTest_160, LiteralStringBoundaryConditionEmpty_160) {

    Rune runes[] = {};

    Regexp* regexp = Regexp::LiteralString(runes, 0, 0);

    ASSERT_EQ(regexp->op(), kRegexpLiteralString);

    EXPECT_EQ(regexp->runes(), nullptr); // Assuming runes should be nullptr for empty literal

    regexp->Decref();

}



TEST_F(RegexpTest_160, LiteralStringBoundaryConditionSingleRune_160) {

    Rune runes[] = { 'a' };

    Regexp* regexp = Regexp::LiteralString(runes, 1, 0);

    ASSERT_EQ(regexp->op(), kRegexpLiteralString);

    EXPECT_EQ(regexp->runes()[0], 'a');

    regexp->Decref();

}



TEST_F(RegexpTest_160, LiteralStringExceptionalCaseInvalidOp_160) {

    // Assuming there's no direct way to test invalid op as it's set internally

    // This case might be more relevant if we had a method to set op externally for testing.

    // Since we can't, this test remains speculative based on assumptions.

}



TEST_F(RegexpTest_160, ParseValidLiteralString_160) {

    RegexpStatus status;

    Regexp* regexp = Regexp::Parse("test", 0, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->op(), kRegexpLiteralString);

    regexp->Decref();

}



TEST_F(RegexpTest_160, ParseInvalidPattern_160) {

    RegexpStatus status;

    Regexp* regexp = Regexp::Parse("[", 0, &status);

    EXPECT_FALSE(status.ok());

    EXPECT_EQ(regexp, nullptr);

}
