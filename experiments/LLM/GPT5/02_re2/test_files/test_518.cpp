// UnHex_tests_518.cc
#include "gtest/gtest.h"

// Include the actual implementation so we can call the internal (static) function.
// This does NOT re-implement logic; it compiles the production code into the test TU.
#include "re2/parse.cc"

namespace {

// ---- Normal operation: decimal digits ----
TEST(UnHexTest_518, ReturnsCorrectForDigitZero_518) {
  EXPECT_EQ(0, re2::UnHex('0'));
}

TEST(UnHexTest_518, ReturnsCorrectForDigitFive_518) {
  EXPECT_EQ(5, re2::UnHex('5'));
}

TEST(UnHexTest_518, ReturnsCorrectForDigitNine_518) {
  EXPECT_EQ(9, re2::UnHex('9'));
}

// ---- Normal operation: uppercase hex letters ----
TEST(UnHexTest_518, ReturnsCorrectForUppercaseA_518) {
  EXPECT_EQ(10, re2::UnHex('A'));
}

TEST(UnHexTest_518, ReturnsCorrectForUppercaseF_518) {
  EXPECT_EQ(15, re2::UnHex('F'));
}

// ---- Normal operation: lowercase hex letters ----
TEST(UnHexTest_518, ReturnsCorrectForLowercaseA_518) {
  EXPECT_EQ(10, re2::UnHex('a'));
}

TEST(UnHexTest_518, ReturnsCorrectForLowercaseF_518) {
  EXPECT_EQ(15, re2::UnHex('f'));
}

// ---- Boundary conditions around digit range ----
TEST(UnHexTest_518, NonHexBeforeZeroReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('0' - 1));  // '@' (64) is not hex
}

TEST(UnHexTest_518, NonHexAfterNineReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('9' + 1));  // ':' (58) is not hex
}

// ---- Boundary conditions around letter ranges ----
TEST(UnHexTest_518, NonHexBeforeUpperAOnBoundaryReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('A' - 1));  // '@'
}

TEST(UnHexTest_518, NonHexAfterUpperFReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('F' + 1));  // 'G'
}

TEST(UnHexTest_518, NonHexBeforeLoweraOnBoundaryReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('a' - 1));  // '`'
}

TEST(UnHexTest_518, NonHexAfterLowerfReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('f' + 1));  // 'g'
}

// ---- Clearly invalid inputs (error-like via return value) ----
TEST(UnHexTest_518, NonAlnumCharReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex('?'));
}

TEST(UnHexTest_518, NegativeValueReturnsZero_518) {
  EXPECT_EQ(0, re2::UnHex(-1));
}

}  // namespace
