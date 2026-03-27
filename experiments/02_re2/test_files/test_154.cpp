#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/regexp_status.h"



using namespace re2;



class RegexpTest_154 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary state before each test.

    }



    void TearDown() override {

        // Clean up any resources after each test.

    }

};



TEST_F(RegexpTest_154, MinValueForRepeatOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("(abc){2,3}", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 2);

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForSingleCharacterLiteral_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Single character literal does not have a repeat operation.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForEmptyMatch_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Empty match has no minimum length.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForStarOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a*", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Star operation can match zero occurrences.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForPlusOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a+", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 1); // Plus operation must match at least one occurrence.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForQuestOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a?", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Quest operation can match zero occurrences.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForConcatOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("ab", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Concat operation has no repeat operation.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForAlternateOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("a|b", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Alternate operation has no repeat operation.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForCaptureOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("(a)", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Capture operation has no repeat operation.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForCharClassOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("[a-z]", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Char class operation has no repeat operation.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForLiteralStringOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("abc", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Literal string operation has no repeat operation.

    regexp->Decref();

}



TEST_F(RegexpTest_154, MinValueForHaveMatchOp_154) {

    RegexpStatus status;

    auto* regexp = Regexp::Parse("\\A", kParseDefault, &status);

    ASSERT_TRUE(status.ok());

    EXPECT_EQ(regexp->min(), 0); // Have match operation has no repeat operation.

    regexp->Decref();

}
