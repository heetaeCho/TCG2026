// File: ./TestProjects/re2/tests/compiler_cat_test_292.cc

#include "gtest/gtest.h"

// Assume the project exposes these public headers in the build.
// If your project organizes them differently, adjust includes accordingly.
#include "re2/prog.h"
#include "re2/compile.h"

using namespace re2;

namespace {

// Small helper to compare observable Frag fields (public API).
::testing::AssertionResult FragsEqual(const Frag& a, const Frag& b) {
  if (a.begin != b.begin) {
    return ::testing::AssertionFailure()
           << "begin differs: " << a.begin << " vs " << b.begin;
  }
  if (a.end.head != b.end.head || a.end.tail != b.end.tail) {
    return ::testing::AssertionFailure()
           << "end differs: head(" << a.end.head << " vs " << b.end.head
           << "), tail(" << a.end.tail << " vs " << b.end.tail << ")";
  }
  if (a.nullable != b.nullable) {
    return ::testing::AssertionFailure()
           << "nullable differs: " << a.nullable << " vs " << b.nullable;
  }
  return ::testing::AssertionSuccess();
}

class CompilerCatTest_292 : public ::testing::Test {
 protected:
  Compiler comp_;  // Fresh compiler instance per test
};

}  // namespace

// [Behavior] If either operand is NoMatch, Cat must return NoMatch.
TEST_F(CompilerCatTest_292, ReturnsNoMatchWhenLeftIsNoMatch_292) {
  Frag a = comp_.NoMatch();            // NoMatch (black-box)
  Frag b = comp_.Nop();                // some valid frag (black-box)
  Frag got = comp_.Cat(a, b);
  Frag expect = comp_.NoMatch();       // observable equality check only
  EXPECT_TRUE(FragsEqual(got, expect));
}

TEST_F(CompilerCatTest_292, ReturnsNoMatchWhenRightIsNoMatch_292) {
  Frag a = comp_.Nop();
  Frag b = comp_.NoMatch();
  Frag got = comp_.Cat(a, b);
  Frag expect = comp_.NoMatch();
  EXPECT_TRUE(FragsEqual(got, expect));
}

// [Behavior] NOP optimization path:
// If the left frag is a single NOP with out=0 and its end list matches that instruction,
// Cat(a, b) should return b (observable: b's fields unchanged).
TEST_F(CompilerCatTest_292, NopOptimizationReturnsRightFrag_292) {
  Frag a = comp_.Nop();                        // left is NOP (black-box)
  Frag b = comp_.ByteRange(0, 0, /*foldcase=*/false);  // some non-NOP frag
  Frag got = comp_.Cat(a, b);
  EXPECT_TRUE(FragsEqual(got, b));
}

// [Behavior] Default concatenation path (non-reversed):
// Cat(a, b) returns a frag whose begin == a.begin,
// end == b.end, and nullable == (a.nullable && b.nullable).
TEST_F(CompilerCatTest_292, DefaultConcatenationShapeAndNullability_292) {
  // Use two non-NOP frags so we avoid the NOP fast-path.
  Frag a = comp_.ByteRange('a', 'a', /*foldcase=*/false);
  Frag b = comp_.ByteRange('b', 'b', /*foldcase=*/false);

  Frag got = comp_.Cat(a, b);

  // Expected, per interface of returned Frag (public fields)
  // (We do NOT attempt to assert about internal patching.)
  EXPECT_EQ(got.begin, a.begin);
  EXPECT_EQ(got.end.head, b.end.head);
  EXPECT_EQ(got.end.tail, b.end.tail);
  EXPECT_EQ(got.nullable, (a.nullable && b.nullable));
}

// [Behavior] Chaining: Cat is stable when the left is NOP then default path.
// This ensures NOP optimization doesn’t corrupt a subsequent Cat’s shape.
TEST_F(CompilerCatTest_292, NopThenDefaultConcatenationStability_292) {
  Frag a = comp_.Nop();                                   // triggers NOP fast-path with next Cat
  Frag mid = comp_.ByteRange('x', 'x', /*foldcase=*/false);
  Frag b = comp_.ByteRange('y', 'y', /*foldcase=*/false);

  Frag ab = comp_.Cat(a, mid);                            // should be exactly 'mid'
  EXPECT_TRUE(FragsEqual(ab, mid));

  Frag got = comp_.Cat(ab, b);                            // default path on two non-NOPs
  EXPECT_EQ(got.begin, ab.begin);
  EXPECT_EQ(got.end.head, b.end.head);
  EXPECT_EQ(got.end.tail, b.end.tail);
  EXPECT_EQ(got.nullable, (ab.nullable && b.nullable));
}

// NOTE:
// - We intentionally do not attempt to verify calls to PatchList::Patch via mocking,
//   since PatchList is a static, internal collaborator and there is no public seam
//   to replace it without violating the “black box” constraint.
// - The branch guarded by an internal `reversed_` flag is not covered here because
//   that flag is not exposed or configurable via the public interface in this setup.
//   If a public constructor or factory allowing a `reversed=true` Compiler is available
//   in your test environment, you can mirror the “DefaultConcatenationShape…” test and
//   assert that Cat(b, a) shape/nullable conforms to the reversed branch contract.
