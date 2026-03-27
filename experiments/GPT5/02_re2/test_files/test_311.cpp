// File: re2_compile_findbyterange_test.cc

#include <gtest/gtest.h>
#include "re2/prog.h"
#include "re2/compile.h"

using namespace re2;

// Helper to compare two Frag values without relying on internal implementation.
// We only check observable fields that are exposed through the Frag interface.
// (In RE2's compiler, Frag typically exposes begin id, a PatchList, and nullability.)
static void ExpectFragEq(const Frag& a, const Frag& b) {
  // These accessors/fields are part of the public/observable contract for Frag
  // in the compiler layer. If your local Frag wrapper has different names,
  // adjust to the accessible ones (e.g., .begin, .out, .nullable).
  EXPECT_EQ(a.begin, b.begin);
  EXPECT_EQ(a.out.head, b.out.head);
  EXPECT_EQ(a.out.tail, b.out.tail);
  EXPECT_EQ(a.nullable, b.nullable);
}

// Fixture: nothing fancy; we’ll build tiny instruction graphs via public APIs.
class CompilerFindByteRangeTest_311 : public ::testing::Test {
 protected:
  Compiler c_;  // Default-constructed; we’ll only use public methods.
};

// --- Normal operation: direct root is a ByteRange and equals the target ID.
TEST_F(CompilerFindByteRangeTest_311, RootIsEqualByteRange_311) {
  // Build two byte-range instructions with identical [lo,hi] so they are equal.
  // Use the public Compiler::ByteRange(lo, hi, foldcase) to create them.
  Frag r1 = c_.ByteRange('a', 'a', /*foldcase=*/false);
  Frag r2 = c_.ByteRange('a', 'a', /*foldcase=*/false);

  // When root is a kInstByteRange equal to id, FindByteRange should return
  // Frag(root, kNullPatchList, false). We'll compare to that expected Frag.
  Frag got = c_.FindByteRange(/*root=*/r1.begin, /*id=*/r2.begin);

  Frag want(r1.begin, kNullPatchList, /*nullable=*/false);
  ExpectFragEq(got, want);
}

// --- Boundary/negative: root is a ByteRange but NOT equal to target ID => NoMatch.
TEST_F(CompilerFindByteRangeTest_311, RootIsDifferentByteRange_NoMatch_311) {
  // Different ranges ensure ByteRangeEqual(...) is false through the public API.
  Frag r1 = c_.ByteRange('a', 'a', /*foldcase=*/false);
  Frag r2 = c_.ByteRange('b', 'b', /*foldcase=*/false);

  Frag got = c_.FindByteRange(/*root=*/r1.begin, /*id=*/r2.begin);

  // Compare to the public NoMatch() sentinel fragment.
  Frag nomatch = c_.NoMatch();
  ExpectFragEq(got, nomatch);
}

// --- Alt-chain: match on out1 branch when equal -> PatchList::Mk((root<<1)|1).
TEST_F(CompilerFindByteRangeTest_311, Alt_Out1Matches_YieldsPatchOnOut1_311) {
  // Left branch (a) is non-matching; right branch (b) is matching target.
  Frag a = c_.ByteRange('x', 'x', /*foldcase=*/false);  // won't equal target
  Frag b = c_.ByteRange('y', 'y', /*foldcase=*/false);  // will equal target
  Frag alt = c_.Alt(a, b);                              // root is an Alt

  // Find y from alt. The function checks out1 first and if equal, returns
  // Frag(root, PatchList::Mk((root<<1)|1), false).
  Frag got = c_.FindByteRange(/*root=*/alt.begin, /*id=*/b.begin);

  PatchList expected_out = PatchList::Mk((alt.begin << 1) | 1);
  Frag want(alt.begin, expected_out, /*nullable=*/false);
  ExpectFragEq(got, want);
}

// --- Alt-chain negative (non-reversed): neither out1 nor the subsequent path matches.
TEST_F(CompilerFindByteRangeTest_311, Alt_NoMatchWhenNotReversed_311) {
  // Both branches intentionally do not equal the target.
  Frag a = c_.ByteRange('a', 'a', /*foldcase=*/false);
  Frag b = c_.ByteRange('b', 'b', /*foldcase=*/false);
  Frag alt = c_.Alt(a, b);

  // Target is a third, unrelated byte range so equality fails.
  Frag target = c_.ByteRange('c', 'c', /*foldcase=*/false);

  // In the provided logic, if out1 is not equal and !reversed_, it returns NoMatch().
  // We don't toggle reversed_ here (default compiler orientation), so expect NoMatch.
  Frag got = c_.FindByteRange(/*root=*/alt.begin, /*id=*/target.begin);

  Frag nomatch = c_.NoMatch();
  ExpectFragEq(got, nomatch);
}

// NOTE: There is a reversed_-only path in FindByteRange that walks alt->out chains.
// If your test harness exposes a public way to construct a reversed compiler
// (e.g., via a public Setup/Compile that sets reversed = true), you can add:
//
// TEST_F(CompilerFindByteRangeTest_311, Alt_FollowOutWhenReversed_311) { ... }
//
// to validate the “reversed_” branch by building an Alt chain and asserting that
// a match found via the out edge yields PatchList::Mk(root<<1). We deliberately
// avoid private-state access and only use public API in the above tests.
