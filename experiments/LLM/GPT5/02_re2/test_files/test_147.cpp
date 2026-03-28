// File: charclass_full_147_test.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "util/utf.h"   // for Runemax, Runeerror, etc.

using namespace re2;

class CharClassTest_147 : public ::testing::Test {};

// Verifies a freshly created class is not full.
TEST_F(CharClassTest_147, NewIsNotFull_147) {
  // Create with a small number of ranges (exact capacity is an impl detail).
  CharClass* cc = CharClass::New(1);
  ASSERT_NE(cc, nullptr);

  // Observable behavior: a fresh class should not be "full".
  EXPECT_FALSE(cc->full());

  cc->Delete();
}

// Negating an empty class should yield a full class (complement of empty is universal set).
TEST_F(CharClassTest_147, NegateEmptyBecomesFull_ContainsBoundaries_147) {
  CharClass* empty_cc = CharClass::New(1);
  ASSERT_NE(empty_cc, nullptr);
  ASSERT_FALSE(empty_cc->full());  // sanity check

  CharClass* full_cc = empty_cc->Negate();
  ASSERT_NE(full_cc, nullptr);

  EXPECT_TRUE(full_cc->full());

  // Boundary observations: If "full", it should contain representative runes, including extremes.
  // These checks are based on the public Contains(Rune) contract.
  EXPECT_TRUE(full_cc->Contains(0 /* lowest code point */));
  EXPECT_TRUE(full_cc->Contains(Runeself));   // mid-range constant from utf.h
  EXPECT_TRUE(full_cc->Contains(Runemax));    // highest valid code point
  EXPECT_TRUE(full_cc->Contains(Runeerror));  // special replacement rune

  // Clean up safely even if Negate() returned the same pointer.
  if (full_cc != empty_cc) {
    full_cc->Delete();
    empty_cc->Delete();
  } else {
    empty_cc->Delete();
  }
}

// Double negation should restore emptiness; "full" should flip back to "not full".
TEST_F(CharClassTest_147, DoubleNegateRestoresEmpty_NotFull_147) {
  CharClass* cc0 = CharClass::New(1);
  ASSERT_NE(cc0, nullptr);
  ASSERT_FALSE(cc0->full());

  CharClass* cc1 = cc0->Negate();    // expect full
  ASSERT_NE(cc1, nullptr);
  EXPECT_TRUE(cc1->full());

  CharClass* cc2 = cc1->Negate();    // expect empty again
  ASSERT_NE(cc2, nullptr);
  EXPECT_FALSE(cc2->full());

  // Clean up; guard against in-place returns.
  // Delete each distinct pointer exactly once.
  CharClass* ptrs[3] = {cc0, cc1, cc2};
  for (int i = 0; i < 3; ++i) {
    bool first_seen = true;
    for (int j = 0; j < i; ++j) {
      if (ptrs[j] == ptrs[i]) { first_seen = false; break; }
    }
    if (first_seen) ptrs[i]->Delete();
  }
}

// A "full" class should contain a variety of typical runes.
// This test focuses on observable inclusion across a spread of values.
TEST_F(CharClassTest_147, FullClassContainsTypicalRunes_147) {
  CharClass* cc = CharClass::New(1);
  ASSERT_NE(cc, nullptr);

  CharClass* full_cc = cc->Negate();
  ASSERT_NE(full_cc, nullptr);
  ASSERT_TRUE(full_cc->full());

  // Spot-check a few representative runes.
  EXPECT_TRUE(full_cc->Contains('A'));
  EXPECT_TRUE(full_cc->Contains('z'));
  EXPECT_TRUE(full_cc->Contains(0));
  EXPECT_TRUE(full_cc->Contains(0x7F));        // DEL
  EXPECT_TRUE(full_cc->Contains(0x80));        // non-ASCII start
  EXPECT_TRUE(full_cc->Contains(0x20AC));      // Euro sign
  EXPECT_TRUE(full_cc->Contains(Runemax));

  if (full_cc != cc) {
    full_cc->Delete();
    cc->Delete();
  } else {
    cc->Delete();
  }
}
