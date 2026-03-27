#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"

#include "unicode_casefold.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class AddFoldedRangeTest_488 : public ::testing::Test {

protected:

    void SetUp() override {

        cc = new CharClassBuilder();

    }



    void TearDown() override {

        delete cc;

    }



    CharClassBuilder* cc;

};



TEST_F(AddFoldedRangeTest_488, NormalOperation_488) {

    Rune lo = 'a';

    Rune hi = 'z';

    AddFoldedRange(cc, lo, hi, 0);

    EXPECT_TRUE(cc->Contains('A'));

    EXPECT_TRUE(cc->Contains('Z'));

}



TEST_F(AddFoldedRangeTest_488, BoundaryConditions_LowerBound_488) {

    Rune lo = 0;

    Rune hi = 10;

    AddFoldedRange(cc, lo, hi, 0);

    EXPECT_TRUE(cc->Contains(lo));

}



TEST_F(AddFoldedRangeTest_488, BoundaryConditions_UpperBound_488) {

    Rune lo = 255 - 10;

    Rune hi = 255;

    AddFoldedRange(cc, lo, hi, 0);

    EXPECT_TRUE(cc->Contains(hi));

}



TEST_F(AddFoldedRangeTest_488, RecursiveDepthLimit_488) {

    Rune lo = 'a';

    Rune hi = 'z';

    // Assuming that depth 10 should be the limit

    AddFoldedRange(cc, lo, hi, 9);

    EXPECT_TRUE(cc->Contains('A'));

    EXPECT_TRUE(cc->Contains('Z'));



    cc->RemoveAbove(0);

    AddFoldedRange(cc, lo, hi, 10);

    // No additional ranges should be added due to depth limit

    EXPECT_FALSE(cc->Contains('B'));

}



TEST_F(AddFoldedRangeTest_488, NoCaseFolding_488) {

    Rune lo = 123; // Assuming 123 has no case folding

    Rune hi = 123;

    AddFoldedRange(cc, lo, hi, 0);

    EXPECT_TRUE(cc->Contains(lo));

}



TEST_F(AddFoldedRangeTest_488, CaseFoldingWithEvenOddDelta_488) {

    // Assuming a rune with EvenOdd delta

    Rune lo = '1'; // Hypothetical rune with EvenOdd delta

    Rune hi = '1';

    AddFoldedRange(cc, lo, hi, 0);

    EXPECT_TRUE(cc->Contains('0')); // Depending on how EvenOdd is implemented

}



TEST_F(AddFoldedRangeTest_488, CaseFoldingWithOddEvenDelta_488) {

    // Assuming a rune with OddEven delta

    Rune lo = '2'; // Hypothetical rune with OddEven delta

    Rune hi = '2';

    AddFoldedRange(cc, lo, hi, 0);

    EXPECT_TRUE(cc->Contains('3')); // Depending on how OddEven is implemented

}
