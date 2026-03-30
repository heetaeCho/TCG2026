#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function ToLowerRune is exposed in a header file for testing purposes.

namespace re2 {

    Rune ToLowerRune(Rune r);

}



using namespace re2;

using ::testing::Eq;



class ToLowerRuneTest_537 : public ::testing::Test {};



TEST_F(ToLowerRuneTest_537, LowercaseLetterRemainsUnchanged_537) {

    EXPECT_EQ(re2::ToLowerRune('a'), 'a');

}



TEST_F(ToLowerRuneTest_537, UppercaseLetterConvertsToLowerCase_537) {

    EXPECT_EQ(re2::ToLowerRune('A'), 'a');

}



TEST_F(ToLowerRuneTest_537, RuneselfBoundaryCaseLowercase_537) {

    EXPECT_EQ(re2::ToLowerRune(Runeself - 1), Runeself - 1);

}



TEST_F(ToLowerRuneTest_537, RuneselfBoundaryCaseUppercase_537) {

    EXPECT_EQ(re2::ToLowerRune(Runeself - ('A' - 'a')), Runeself - 1);

}



TEST_F(ToLowerRuneTest_537, RuneerrorRemainsUnchanged_537) {

    EXPECT_EQ(re2::ToLowerRune(Runeerror), Runeerror);

}



TEST_F(ToLowerRuneTest_537, RunemaxBoundaryCase_537) {

    EXPECT_EQ(re2::ToLowerRune(Runemax), Runemax);

}

```


