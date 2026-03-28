// File: prog_inst_matches_test_111.cc
#include "re2/prog.h"
#include <gtest/gtest.h>

using re2::Prog;

class ProgInstMatchesTest_111 : public ::testing::Test {};

// Normal operation: within-range matches without foldcase.
TEST_F(ProgInstMatchesTest_111, WithinRange_NoFold_111) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', /*foldcase=*/0, /*out=*/0);

  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('m'));
  EXPECT_TRUE(inst.Matches('z'));

  EXPECT_FALSE(inst.Matches('A'));   // uppercase should not match without fold
  EXPECT_FALSE(inst.Matches('`'));   // just below 'a'
  EXPECT_FALSE(inst.Matches('{'));   // just above 'z'
}

// Boundary conditions: exactly lo and hi should match.
TEST_F(ProgInstMatchesTest_111, Boundary_Inclusive_111) {
  Prog::Inst inst;
  inst.InitByteRange('c', 'f', /*foldcase=*/0, /*out=*/0);

  EXPECT_TRUE(inst.Matches('c'));    // lo
  EXPECT_TRUE(inst.Matches('f'));    // hi
  EXPECT_FALSE(inst.Matches('b'));   // below lo
  EXPECT_FALSE(inst.Matches('g'));   // above hi
}

// Foldcase behavior: A–Z should be folded to lowercase before range check.
TEST_F(ProgInstMatchesTest_111, UppercaseFolded_WhenFoldcaseEnabled_111) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', /*foldcase=*/1, /*out=*/0);

  EXPECT_TRUE(inst.Matches('A'));
  EXPECT_TRUE(inst.Matches('M'));
  EXPECT_TRUE(inst.Matches('Z'));

  EXPECT_FALSE(inst.Matches('@'));   // not a letter; remains '@' (out of range)
  EXPECT_FALSE(inst.Matches('['));   // not a letter; remains '[' (out of range)
}

// Foldcase does not force unrelated ranges to match.
TEST_F(ProgInstMatchesTest_111, NonLetterUnaffected_WithFoldcase_111) {
  Prog::Inst inst;
  inst.InitByteRange('0', '9', /*foldcase=*/1, /*out=*/0);

  EXPECT_TRUE(inst.Matches('0'));
  EXPECT_TRUE(inst.Matches('5'));
  EXPECT_TRUE(inst.Matches('9'));

  // 'A' folds to 'a', which is not in '0'..'9' => still false
  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('a'));
}

// Values outside typical byte range: negative and >255 should not match.
TEST_F(ProgInstMatchesTest_111, OutOfRange_IntegerValues_111) {
  Prog::Inst inst;
  inst.InitByteRange(0, 127, /*foldcase=*/1, /*out=*/0); // ASCII range

  EXPECT_FALSE(inst.Matches(-1));
  EXPECT_FALSE(inst.Matches(256));
  EXPECT_FALSE(inst.Matches(1000));
}

// Regression-style: foldcase disabled should not match uppercase if only lowercase in range.
TEST_F(ProgInstMatchesTest_111, UppercaseDoesNotMatch_WhenFoldcaseDisabled_111) {
  Prog::Inst inst;
  inst.InitByteRange('a', 'z', /*foldcase=*/0, /*out=*/0);

  EXPECT_FALSE(inst.Matches('A'));
  EXPECT_FALSE(inst.Matches('Z'));
  EXPECT_TRUE(inst.Matches('a'));
  EXPECT_TRUE(inst.Matches('z'));
}
