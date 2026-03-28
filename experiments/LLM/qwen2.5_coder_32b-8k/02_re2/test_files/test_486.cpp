#include <gtest/gtest.h>

#include "parse.cc"

#include "unicode_casefold.h"



namespace re2 {



class CycleFoldRuneTest_486 : public ::testing::Test {

protected:

    // No setup needed as there are no member variables to initialize.

};



TEST_F(CycleFoldRuneTest_486, NormalOperation_NoCaseFold_486) {

    Rune r = 'A';  // Example rune that does not have a case fold

    EXPECT_EQ(CycleFoldRune(r), r);

}



TEST_F(CycleFoldRuneTest_486, NormalOperation_CaseFoldExists_486) {

    Rune r = 'a';  // Example rune that has a case fold to 'A'

    EXPECT_EQ(CycleFoldRune(r), 'A');

}



TEST_F(CycleFoldRuneTest_486, BoundaryCondition_LowerBound_486) {

    Rune r = unicode_casefold[0].lo;  // Assuming the first entry is the lower bound

    EXPECT_EQ(CycleFoldRune(r), ApplyFold(&unicode_casefold[0], r));

}



TEST_F(CycleFoldRuneTest_486, BoundaryCondition_UpperBound_486) {

    Rune r = unicode_casefold[num_unicode_casefold - 1].lo;  // Assuming the last entry is the upper bound

    EXPECT_EQ(CycleFoldRune(r), ApplyFold(&unicode_casefold[num_unicode_casefold - 1], r));

}



TEST_F(CycleFoldRuneTest_486, ExceptionalCase_OutOfBounds_Lower_486) {

    Rune r = unicode_casefold[0].lo - 1;  // One less than the lower bound

    EXPECT_EQ(CycleFoldRune(r), r);

}



TEST_F(CycleFoldRuneTest_486, ExceptionalCase_OutOfBounds_Upper_486) {

    Rune r = unicode_casefold[num_unicode_casefold - 1].lo + 1;  // One more than the upper bound

    EXPECT_EQ(CycleFoldRune(r), r);

}



}  // namespace re2
