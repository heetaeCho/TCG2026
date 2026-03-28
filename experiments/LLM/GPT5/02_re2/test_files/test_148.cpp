// File: charclass_foldsascii_test_148.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

using re2::CharClass;

class CharClassTest_148 : public ::testing::Test {
protected:
  // Helper to safely build and tear down a CharClass via the public API we see.
  static CharClass* NewWithRanges(size_t maxranges) {
    // Treat implementation as black box; just use the factory visible in headers.
    return CharClass::New(maxranges);
  }
  static void DeleteSafely(CharClass* cc) {
    if (cc) cc->Delete();
  }
};

// -- Normal operation: FoldsASCII() is callable and stable on a fresh object.
TEST_F(CharClassTest_148, FoldsASCII_IsStableAcrossRepeatedCalls_148) {
  CharClass* cc = NewWithRanges(0);
  ASSERT_NE(cc, nullptr);

  bool v1 = cc->FoldsASCII();
  bool v2 = cc->FoldsASCII();
  EXPECT_EQ(v1, v2) << "FoldsASCII() should be stable across repeated calls.";

  DeleteSafely(cc);
}

// -- Boundary: constructing with zero and larger maxranges should still allow calling FoldsASCII().
TEST_F(CharClassTest_148, FoldsASCII_CallableWithZeroAndLargeMaxRanges_148) {
  // Zero ranges.
  CharClass* cc0 = NewWithRanges(0);
  ASSERT_NE(cc0, nullptr);
  (void)cc0->FoldsASCII();  // Just ensure it’s callable without crashing.
  DeleteSafely(cc0);

  // Larger number of ranges (arbitrary boundary-ish value).
  CharClass* ccBig = NewWithRanges(128);
  ASSERT_NE(ccBig, nullptr);
  (void)ccBig->FoldsASCII();
  DeleteSafely(ccBig);
}

// -- Interaction: FoldsASCII() remains stable even after invoking other visible operations.
// We don't assert *what* it is, only that it doesn't spontaneously change after Negate().
TEST_F(CharClassTest_148, FoldsASCII_RemainsStableAfterNegate_148) {
  CharClass* cc = NewWithRanges(4);
  ASSERT_NE(cc, nullptr);

  const bool before = cc->FoldsASCII();

  // Negate produces another CharClass via the public API; verify both are internally stable.
  CharClass* neg = cc->Negate();
  ASSERT_NE(neg, nullptr);

  const bool before_again = cc->FoldsASCII();
  EXPECT_EQ(before, before_again) << "Original instance should remain stable.";

  const bool neg_first = neg->FoldsASCII();
  const bool neg_second = neg->FoldsASCII();
  EXPECT_EQ(neg_first, neg_second) << "Negated instance should be stable.";

  DeleteSafely(neg);
  DeleteSafely(cc);
}

// -- Multiple instances: each instance’s FoldsASCII() is self-consistent, independent of the other.
TEST_F(CharClassTest_148, FoldsASCII_SelfConsistentPerInstance_148) {
  CharClass* a = NewWithRanges(1);
  CharClass* b = NewWithRanges(2);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  bool a1 = a->FoldsASCII();
  bool a2 = a->FoldsASCII();
  EXPECT_EQ(a1, a2);

  bool b1 = b->FoldsASCII();
  bool b2 = b->FoldsASCII();
  EXPECT_EQ(b1, b2);

  DeleteSafely(b);
  DeleteSafely(a);
}
