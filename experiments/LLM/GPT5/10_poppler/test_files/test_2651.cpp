// numberofcharacters_test_2651.cpp

#include <gtest/gtest.h>

// Include the header under test.
#include "./TestProjects/poppler/utils/numberofcharacters.h"

namespace {

// NOTE: numberOfCharacters is declared `static` in the header snippet provided.
// Including the header here gives this TU its own internal-linkage copy, which is
// fine for unit testing.

class NumberOfCharactersTest_2651 : public ::testing::Test {};

TEST_F(NumberOfCharactersTest_2651, ZeroHasOneCharacter_2651) {
  EXPECT_EQ(numberOfCharacters(0u), 1);
}

TEST_F(NumberOfCharactersTest_2651, SingleDigitNumbersHaveOneCharacter_2651) {
  EXPECT_EQ(numberOfCharacters(1u), 1);
  EXPECT_EQ(numberOfCharacters(9u), 1);
}

TEST_F(NumberOfCharactersTest_2651, TwoDigitBoundaryAtTen_2651) {
  EXPECT_EQ(numberOfCharacters(10u), 2);
  EXPECT_EQ(numberOfCharacters(11u), 2);
  EXPECT_EQ(numberOfCharacters(99u), 2);
}

TEST_F(NumberOfCharactersTest_2651, ThreeDigitBoundaryAtHundred_2651) {
  EXPECT_EQ(numberOfCharacters(100u), 3);
  EXPECT_EQ(numberOfCharacters(101u), 3);
  EXPECT_EQ(numberOfCharacters(999u), 3);
}

TEST_F(NumberOfCharactersTest_2651, MultipleDigitBoundariesAcrossPowersOfTen_2651) {
  EXPECT_EQ(numberOfCharacters(1000u), 4);
  EXPECT_EQ(numberOfCharacters(9999u), 4);

  EXPECT_EQ(numberOfCharacters(10000u), 5);
  EXPECT_EQ(numberOfCharacters(99999u), 5);

  EXPECT_EQ(numberOfCharacters(100000u), 6);
  EXPECT_EQ(numberOfCharacters(999999u), 6);
}

TEST_F(NumberOfCharactersTest_2651, LargeValuesNearUintMax_2651) {
  // 2^32 - 1 = 4294967295 => 10 digits
  EXPECT_EQ(numberOfCharacters(4294967295u), 10);

  // Around the 1,000,000,000 boundary (10 digits starts at 1,000,000,000)
  EXPECT_EQ(numberOfCharacters(999999999u), 9);
  EXPECT_EQ(numberOfCharacters(1000000000u), 10);
}

}  // namespace