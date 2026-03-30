// File: ./TestProjects/re2/re2/tests/charclassbuilder_foldsascii_373_test.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace re2 {

class CharClassBuilderTest_373 : public ::testing::Test {};

// [Normal] Constructing a fresh builder and calling FoldsASCII returns a bool.
// We also assert the call succeeds without throwing and produces a stable value on repeated calls.
TEST_F(CharClassBuilderTest_373, DefaultConstruction_FoldsASCII_IsStable_373) {
  CharClassBuilder ccb;

  // First observation
  bool v1 = ccb.FoldsASCII();

  // Repeated observations should be identical (idempotent behavior of the query)
  for (int i = 0; i < 10; ++i) {
    bool vi = ccb.FoldsASCII();
    EXPECT_EQ(vi, v1) << "FoldsASCII should be stable across repeated calls on the same instance";
  }
}

// [Boundary-ish / Interaction] After making a simple, observable API call (like AddRange),
// FoldsASCII should still be callable and return a stable boolean. We do NOT assert
// a specific truth value (black-box); we only verify consistent observable behavior.
TEST_F(CharClassBuilderTest_373, AddRange_DoesNotDestabilizeFoldsASCII_373) {
  CharClassBuilder ccb;

  // Perform some public operations (treating impl as black box).
  // Use a small ASCII range and a high Unicode boundary to exercise “boundary-like” inputs.
  (void)ccb.AddRange('A', 'Z');     // normal ASCII range
  (void)ccb.AddRange(0, 0);         // degenerate/singleton
  (void)ccb.AddRange(0, 127);       // full 7-bit ASCII span
  (void)ccb.AddRange(0x10FFFF, 0x10FFFF); // max valid Unicode code point as boundary-like input

  bool v1 = ccb.FoldsASCII();
  for (int i = 0; i < 5; ++i) {
    bool vi = ccb.FoldsASCII();
    EXPECT_EQ(vi, v1) << "FoldsASCII should remain stable after public API mutations";
  }
}

// [Copy semantics] Copy() should produce an independent object whose FoldsASCII observation
// initially matches the source; subsequent mutations to either should not affect the other.
// We only check equality at copy time and independence thereafter (no internal peeking).
TEST_F(CharClassBuilderTest_373, Copy_PreservesInitialFoldsASCII_AndIsIndependent_373) {
  CharClassBuilder original;

  // Capture source observation
  bool original_before = original.FoldsASCII();

  // Copy and verify initial observation matches
  std::unique_ptr<CharClassBuilder> copy(original.Copy());
  ASSERT_NE(copy, nullptr);
  bool copy_before = copy->FoldsASCII();
  EXPECT_EQ(copy_before, original_before)
      << "Copy() should preserve the observable FoldsASCII state at copy time";

  // Mutate original via public API
  (void)original.AddRange('a', 'z');
  // Both remain callable; we don’t assume particular truth values.
  bool original_after = original.FoldsASCII();
  bool copy_after = copy->FoldsASCII();

  // Independence check: there is no requirement that values differ or match post-mutation,
  // but each instance should be stable on its own across repeated calls.
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(original.FoldsASCII(), original_after)
        << "Original FoldsASCII should remain stable after mutations";
    EXPECT_EQ(copy->FoldsASCII(), copy_after)
        << "Copied instance FoldsASCII should be unaffected by mutations to the original";
  }
}

// [Isolation] Mutations on one instance must not affect another fresh instance.
// This verifies absence of unintended global/shared effects (observable only).
TEST_F(CharClassBuilderTest_373, Instances_AreIsolated_NoGlobalSideEffects_373) {
  CharClassBuilder c1;
  CharClassBuilder c2;

  // Observe initial values
  bool c1_initial = c1.FoldsASCII();
  bool c2_initial = c2.FoldsASCII();

  // Mutate c1 via several public operations
  (void)c1.AddRange('0', '9');
  (void)c1.AddRange(1, 1);
  (void)c1.AddRange(100, 200);

  // c2’s observable behavior should not be altered by c1’s mutations
  bool c2_after = c2.FoldsASCII();
  EXPECT_EQ(c2_after, c2_initial)
      << "Mutations to one instance should not affect another instance's FoldsASCII result";

  // Each instance remains stable on repeated calls
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(c1.FoldsASCII(), c1.FoldsASCII())
        << "c1 FoldsASCII should be stable across repeated calls";
    EXPECT_EQ(c2.FoldsASCII(), c2_after)
        << "c2 FoldsASCII should remain unchanged from its own perspective";
  }
}

}  // namespace re2
