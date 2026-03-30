// File: charclass_negate_test_378.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/util/utf.h"

using namespace re2;

class CharClassNegateTest_378 : public ::testing::Test {
protected:
  // Helper: a small set of representative runes spanning the space.
  static std::vector<Rune> SampleRunes() {
    return {
      0,
      static_cast<Rune>('0'),
      static_cast<Rune>('A'),
      127,        // last ASCII control
      128,        // first non-ASCII
      0x20AC,     // Euro sign
      Runemax     // boundary high
    };
  }
};

// Negating an empty class should produce a class that contains
// (at least) our representative runes, and should report 'full' if supported.
TEST_F(CharClassNegateTest_378, NegateOfEmptyIsFull_378) {
  // Create an empty CharClass via factory and ensure it's empty in observable ways.
  CharClass* empty = CharClass::New(/*maxranges=*/1);
  ASSERT_NE(empty, nullptr);

  for (Rune r : CharClassNegateTest_378::SampleRunes()) {
    EXPECT_FALSE(empty->Contains(r)) << "Expected empty CharClass to not contain rune " << r;
  }
  // If available, empty()/full() are observable predicates.
  // We only assert when they exist per interface.
  EXPECT_TRUE(empty->empty());
  EXPECT_FALSE(empty->full());

  // Negate -> should now be "full" (complement of empty).
  CharClass* full = empty->Negate();
  ASSERT_NE(full, nullptr);

  for (Rune r : CharClassNegateTest_378::SampleRunes()) {
    EXPECT_TRUE(full->Contains(r)) << "Expected Negate(empty) to contain rune " << r;
  }
  EXPECT_TRUE(full->full());
  EXPECT_FALSE(full->empty());

  // Cleanup
  full->Delete();
  empty->Delete();
}

// Double negation should restore the original observable behavior.
TEST_F(CharClassNegateTest_378, DoubleNegateRestores_378) {
  CharClass* orig = CharClass::New(/*maxranges=*/1);
  ASSERT_NE(orig, nullptr);

  // Sanity on original (empty by construction).
  for (Rune r : CharClassNegateTest_378::SampleRunes()) {
    EXPECT_FALSE(orig->Contains(r));
  }
  EXPECT_TRUE(orig->empty());
  EXPECT_FALSE(orig->full());

  // Negate twice
  CharClass* neg1 = orig->Negate();
  ASSERT_NE(neg1, nullptr);
  CharClass* neg2 = neg1->Negate();
  ASSERT_NE(neg2, nullptr);

  // neg2 should behave like orig on observable checks.
  for (Rune r : CharClassNegateTest_378::SampleRunes()) {
    EXPECT_EQ(orig->Contains(r), neg2->Contains(r))
        << "Double negation did not restore membership for rune " << r;
  }
  EXPECT_EQ(orig->empty(), neg2->empty());
  EXPECT_EQ(orig->full(),  neg2->full());
  EXPECT_EQ(orig->FoldsASCII(), neg2->FoldsASCII());

  // Cleanup
  neg2->Delete();
  neg1->Delete();
  orig->Delete();
}

// Negate should be a strict complement on observable membership across sample points.
TEST_F(CharClassNegateTest_378, ComplementarityHoldsOnSamples_378) {
  CharClass* a = CharClass::New(/*maxranges=*/1);  // empty
  ASSERT_NE(a, nullptr);
  CharClass* b = a->Negate();                      // complement
  ASSERT_NE(b, nullptr);

  for (Rune r : CharClassNegateTest_378::SampleRunes()) {
    bool in_a = a->Contains(r);
    bool in_b = b->Contains(r);
    EXPECT_NE(in_a, in_b) << "Expected XOR membership between set and its Negate for rune " << r;
    EXPECT_FALSE(in_a && in_b) << "Element cannot be in both original and its Negate for rune " << r;
  }

  // Cleanup
  b->Delete();
  a->Delete();
}

// Negate must preserve the FoldsASCII observable flag (as seen in the implementation contract).
TEST_F(CharClassNegateTest_378, PreservesFoldsASCIIFlag_378) {
  CharClass* a = CharClass::New(/*maxranges=*/1);
  ASSERT_NE(a, nullptr);

  bool folds_before = a->FoldsASCII();
  CharClass* b = a->Negate();
  ASSERT_NE(b, nullptr);

  EXPECT_EQ(folds_before, b->FoldsASCII()) << "Negate should preserve FoldsASCII flag";

  b->Delete();
  a->Delete();
}
