#include <gtest/gtest.h>
#include "./TestProjects/poppler/utils/numberofcharacters.h"

// Test single digit numbers (0-9)
TEST(NumberOfCharactersTest_2651, SingleDigitZero_2651) {
    EXPECT_EQ(1, numberOfCharacters(0));
}

TEST(NumberOfCharactersTest_2651, SingleDigitOne_2651) {
    EXPECT_EQ(1, numberOfCharacters(1));
}

TEST(NumberOfCharactersTest_2651, SingleDigitNine_2651) {
    EXPECT_EQ(1, numberOfCharacters(9));
}

// Test two digit numbers
TEST(NumberOfCharactersTest_2651, TwoDigitTen_2651) {
    EXPECT_EQ(2, numberOfCharacters(10));
}

TEST(NumberOfCharactersTest_2651, TwoDigitNinetyNine_2651) {
    EXPECT_EQ(2, numberOfCharacters(99));
}

TEST(NumberOfCharactersTest_2651, TwoDigitFifty_2651) {
    EXPECT_EQ(2, numberOfCharacters(50));
}

// Test three digit numbers
TEST(NumberOfCharactersTest_2651, ThreeDigitHundred_2651) {
    EXPECT_EQ(3, numberOfCharacters(100));
}

TEST(NumberOfCharactersTest_2651, ThreeDigitNineHundredNinetyNine_2651) {
    EXPECT_EQ(3, numberOfCharacters(999));
}

TEST(NumberOfCharactersTest_2651, ThreeDigitFiveHundred_2651) {
    EXPECT_EQ(3, numberOfCharacters(500));
}

// Test four digit numbers
TEST(NumberOfCharactersTest_2651, FourDigitThousand_2651) {
    EXPECT_EQ(4, numberOfCharacters(1000));
}

TEST(NumberOfCharactersTest_2651, FourDigitMax_2651) {
    EXPECT_EQ(4, numberOfCharacters(9999));
}

// Test five digit numbers
TEST(NumberOfCharactersTest_2651, FiveDigitTenThousand_2651) {
    EXPECT_EQ(5, numberOfCharacters(10000));
}

// Test six digit numbers
TEST(NumberOfCharactersTest_2651, SixDigitHundredThousand_2651) {
    EXPECT_EQ(6, numberOfCharacters(100000));
}

// Test seven digit numbers
TEST(NumberOfCharactersTest_2651, SevenDigitMillion_2651) {
    EXPECT_EQ(7, numberOfCharacters(1000000));
}

// Test large numbers
TEST(NumberOfCharactersTest_2651, TenDigitBillion_2651) {
    EXPECT_EQ(10, numberOfCharacters(1000000000u));
}

// Test boundary at max unsigned int (4294967295 = 10 digits)
TEST(NumberOfCharactersTest_2651, MaxUnsignedInt_2651) {
    EXPECT_EQ(10, numberOfCharacters(4294967295u));
}

// Test boundary between digit counts
TEST(NumberOfCharactersTest_2651, BoundaryOneToTwo_2651) {
    EXPECT_EQ(1, numberOfCharacters(9));
    EXPECT_EQ(2, numberOfCharacters(10));
}

TEST(NumberOfCharactersTest_2651, BoundaryTwoToThree_2651) {
    EXPECT_EQ(2, numberOfCharacters(99));
    EXPECT_EQ(3, numberOfCharacters(100));
}

TEST(NumberOfCharactersTest_2651, BoundaryThreeToFour_2651) {
    EXPECT_EQ(3, numberOfCharacters(999));
    EXPECT_EQ(4, numberOfCharacters(1000));
}

TEST(NumberOfCharactersTest_2651, BoundaryFourToFive_2651) {
    EXPECT_EQ(4, numberOfCharacters(9999));
    EXPECT_EQ(5, numberOfCharacters(10000));
}

TEST(NumberOfCharactersTest_2651, BoundaryFiveToSix_2651) {
    EXPECT_EQ(5, numberOfCharacters(99999));
    EXPECT_EQ(6, numberOfCharacters(100000));
}

TEST(NumberOfCharactersTest_2651, BoundarySixToSeven_2651) {
    EXPECT_EQ(6, numberOfCharacters(999999));
    EXPECT_EQ(7, numberOfCharacters(1000000));
}

TEST(NumberOfCharactersTest_2651, BoundarySevenToEight_2651) {
    EXPECT_EQ(7, numberOfCharacters(9999999));
    EXPECT_EQ(8, numberOfCharacters(10000000));
}

TEST(NumberOfCharactersTest_2651, BoundaryEightToNine_2651) {
    EXPECT_EQ(8, numberOfCharacters(99999999));
    EXPECT_EQ(9, numberOfCharacters(100000000));
}

TEST(NumberOfCharactersTest_2651, BoundaryNineToTen_2651) {
    EXPECT_EQ(9, numberOfCharacters(999999999));
    EXPECT_EQ(10, numberOfCharacters(1000000000u));
}

// Test some arbitrary values
TEST(NumberOfCharactersTest_2651, ArbitraryValue12345_2651) {
    EXPECT_EQ(5, numberOfCharacters(12345));
}

TEST(NumberOfCharactersTest_2651, ArbitraryValue42_2651) {
    EXPECT_EQ(2, numberOfCharacters(42));
}

TEST(NumberOfCharactersTest_2651, ArbitraryValue7777777_2651) {
    EXPECT_EQ(7, numberOfCharacters(7777777));
}
