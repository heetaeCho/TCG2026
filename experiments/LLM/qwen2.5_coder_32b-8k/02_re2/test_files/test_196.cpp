#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"

#include "absl/strings/string_view.h"



using namespace re2;

using ::testing::Eq;



class PCRETest_196 : public ::testing::Test {

protected:

    // No setup or teardown needed for this test as the class is stateless for QuoteMeta

};



TEST_F(PCRETest_196, QuoteMeta_NormalOperation_196) {

    EXPECT_EQ(PCRE::QuoteMeta("abc"), "abc");

    EXPECT_EQ(PCRE::QuoteMeta("a.c"), "a\\.c");

    EXPECT_EQ(PCRE::QuoteMeta("a*c"), "a\\*c");

}



TEST_F(PCRETest_196, QuoteMeta_BoundaryConditions_196) {

    EXPECT_EQ(PCRE::QuoteMeta(""), "");

    EXPECT_EQ(PCRE::QuoteMeta("."), "\\.");

    EXPECT_EQ(PCRE::QuoteMeta("*"), "\\*");

}



TEST_F(PCRETest_196, QuoteMeta_SpecialCharacters_196) {

    EXPECT_EQ(PCRE::QuoteMeta("()[]{}|\\^-=$!<>:?"), "\\(\\)\\[\\]\\{\\}\\|\\\\\\^\\-=\\$\\!\\<\\>\\:\\?");

}



TEST_F(PCRETest_196, QuoteMeta_AlphanumericAndUnderscore_196) {

    EXPECT_EQ(PCRE::QuoteMeta("abcXYZ0123_"), "abcXYZ0123_");

}



TEST_F(PCRETest_196, QuoteMeta_NullCharacter_196) {

    EXPECT_EQ(PCRE::QuoteMeta("\x00"), "\\x00");

    EXPECT_EQ(PCRE::QuoteMeta("a\x00b"), "a\\x00b");

}
