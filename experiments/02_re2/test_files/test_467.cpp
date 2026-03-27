#include <gtest/gtest.h>

#include "re2/prefilter.h"



using namespace re2;



class PrefilterLengthThenLexTest : public ::testing::Test {

protected:

    LengthThenLex comparator;

};



TEST_F(PrefilterLengthThenLexTest_467, CompareDifferentLengthStrings_ShorterFirst_467) {

    EXPECT_TRUE(comparator("short", "longer"));

}



TEST_F(PrefilterLengthThenLexTest_467, CompareDifferentLengthStrings_LongerSecond_467) {

    EXPECT_FALSE(comparator("longer", "short"));

}



TEST_F(PrefilterLengthThenLexTest_467, CompareSameLengthStrings_LexicographicallySmallerFirst_467) {

    EXPECT_TRUE(comparator("apple", "banana"));

}



TEST_F(PrefilterLengthThenLexTest_467, CompareSameLengthStrings_LexicographicallyLargerSecond_467) {

    EXPECT_FALSE(comparator("banana", "apple"));

}



TEST_F(PrefilterLengthThenLexTest_467, CompareIdenticalStrings_ReturnFalse_467) {

    EXPECT_FALSE(comparator("same", "same"));

}
