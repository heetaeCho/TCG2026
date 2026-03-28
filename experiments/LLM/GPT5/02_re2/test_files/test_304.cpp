// File: uncached_rune_byte_suffix_304_test.cc

#include <gtest/gtest.h>
#include <cstdint>

//
// Minimal link-time test doubles to observe external interactions.
// We only define what is necessary to compile and to verify calls.
// No internal behavior is re-implemented.
//

namespace re2 {

// Forward decls to match signatures from the provided headers.
class Prog {
 public:
  struct Inst {};  // Incomplete type is sufficient for pointer passing.
};

struct PatchList {
 public:
  uint32_t head;
  uint32_t tail;

  // Decls as per Known Dependencies. We provide definitions below for testing.
  static PatchList Mk(uint32_t p);
  static void Patch(Prog::Inst* inst0, PatchList l, uint32_t p);
  static PatchList Append(Prog::Inst* inst0, PatchList l1, PatchList l2);
};

// Needed by Frag default constructor in the provided code.
extern const PatchList kNullPatchList;

// Track calls for verification.
namespace testing_hooks_304 {
  inline bool patch_called = false;
  inline bool append_called = false;

  inline uint32_t last_patch_p = 0;
  inline Prog::Inst* last_patch_inst = nullptr;

  inline Prog::Inst* last_append_inst = nullptr;
  inline PatchList last_append_l1{};
  inline PatchList last_append_l2{};

  inline void Reset() {
    patch_called = false;
    append_called = false;
    last_patch_p = 0;
    last_patch_inst = nullptr;
    last_append_inst = nullptr;
    last_append_l1 = PatchList{0, 0};
    last_append_l2 = PatchList{0, 0};
  }
}  // namespace testing_hooks_304

// Minimal, observable-only implementations.
PatchList PatchList::Mk(uint32_t p) { return PatchList{p, p}; }

void PatchList::Patch(Prog::Inst* inst0, PatchList /*l*/, uint32_t p) {
  testing_hooks_304::patch_called = true;
  testing_hooks_304::last_patch_p = p;
  testing_hooks_304::last_patch_inst = inst0;
}

PatchList PatchList::Append(Prog::Inst* inst0, PatchList l1, PatchList l2) {
  testing_hooks_304::append_called = true;
  testing_hooks_304::last_append_inst = inst0;
  testing_hooks_304::last_append_l1 = l1;
  testing_hooks_304::last_append_l2 = l2;
  // Return value is irrelevant to UncachedRuneByteSuffix' branching;
  // we return one of the inputs to keep behavior opaque.
  return l1.head ? l1 : l2;
}

// Provide a definition for kNullPatchList used by Frag's default ctor.
const PatchList kNullPatchList = PatchList{0, 0};

}  // namespace re2

// Bring in the production header(s) that declare re2::Compiler, Frag, etc.
// If your project organizes headers differently, include accordingly.
#include "re2/compile.h"  // Adjust include path to your project if needed.

namespace {

using namespace re2;

class UncachedRuneByteSuffixTest_304 : public ::testing::Test {
 protected:
  void SetUp() override { testing_hooks_304::Reset(); }
  void TearDown() override { testing_hooks_304::Reset(); }
};

//
// Tests
//

// Normal operation with non-zero `next`: must invoke Patch (not Append)
// and forward the exact `next` value to Patch.
TEST_F(UncachedRuneByteSuffixTest_304, NextNonZero_CallsPatchOnly_304) {
  Compiler c;

  const uint8_t lo = 0x20;
  const uint8_t hi = 0x7E;
  const bool foldcase = false;
  const int next = 123;  // non-zero triggers Patch branch

  (void)c.UncachedRuneByteSuffix(lo, hi, foldcase, next);

  EXPECT_TRUE(testing_hooks_304::patch_called);
  EXPECT_FALSE(testing_hooks_304::append_called);

  // Observable parameter: `next` must be forwarded to Patch.
  EXPECT_EQ(static_cast<uint32_t>(next), testing_hooks_304::last_patch_p);

  // We can't assume specifics about inst_.data(); just verify it's a pointer.
  // (It may be null depending on the underlying state; both are valid pointers.)
  // The key observable here is that a Patch attempt occurred, with a pointer passed.
  SUCCEED();
}

// Boundary condition: `next == 0` must invoke Append (not Patch).
TEST_F(UncachedRuneByteSuffixTest_304, NextZero_CallsAppendOnly_304) {
  Compiler c;

  const uint8_t lo = 0x00;
  const uint8_t hi = 0xFF;
  const bool foldcase = true;
  const int next = 0;  // zero triggers Append branch

  (void)c.UncachedRuneByteSuffix(lo, hi, foldcase, next);

  EXPECT_FALSE(testing_hooks_304::patch_called);
  EXPECT_TRUE(testing_hooks_304::append_called);

  // We only assert that Append was invoked; parameters are opaque.
  SUCCEED();
}

// Cross-check that the foldcase flag does not affect the branching decision:
// when next != 0 => Patch; when next == 0 => Append.
TEST_F(UncachedRuneByteSuffixTest_304, FoldcaseDoesNotAffectBranching_304) {
  Compiler c;

  // Case A: foldcase=true, next != 0 => Patch
  {
    testing_hooks_304::Reset();
    (void)c.UncachedRuneByteSuffix(0x61, 0x7A, /*foldcase=*/true, /*next=*/1);
    EXPECT_TRUE(testing_hooks_304::patch_called);
    EXPECT_FALSE(testing_hooks_304::append_called);
  }

  // Case B: foldcase=false, next == 0 => Append
  {
    testing_hooks_304::Reset();
    (void)c.UncachedRuneByteSuffix(0x41, 0x5A, /*foldcase=*/false, /*next=*/0);
    EXPECT_FALSE(testing_hooks_304::patch_called);
    EXPECT_TRUE(testing_hooks_304::append_called);
  }
}

}  // namespace
