// File: compile_emptywidth_test_300.cc
#include <gtest/gtest.h>

#include "re2/compile.h"   // Assumes this declares re2::Compiler, re2::Frag, re2::PatchList, EmptyOp
#include "re2/prog.h"      // For completeness if Frag/PatchList are declared near Prog

using namespace re2;

class CompilerEmptyWidthTest_300 : public ::testing::Test {};

// [Normal] EmptyWidth returns a nullable fragment whose patch list points to (begin << 1).
TEST_F(CompilerEmptyWidthTest_300, ReturnsNullableFragWithPatchPoint_300) {
  Compiler c;

  // Any value is fine; we only observe the returned Frag.
  EmptyOp op = static_cast<EmptyOp>(0);

  Frag f = c.EmptyWidth(op);

  // begin must be a valid instruction index (non-negative).
  EXPECT_GE(f.begin, 0);

  // The function constructs PatchList::Mk(begin << 1), which sets both head and tail.
  EXPECT_EQ(f.out.head, static_cast<uint32_t>(f.begin << 1));
  EXPECT_EQ(f.out.tail, static_cast<uint32_t>(f.begin << 1));

  // The function returns Frag(..., ..., /*nullable=*/true).
  EXPECT_TRUE(f.nullable);
}

// [Boundary/Consistency] Multiple calls produce valid (and typically distinct) frags,
// each having the correct patch list derived from its own begin.
TEST_F(CompilerEmptyWidthTest_300, MultipleCallsYieldSelfConsistentFrags_300) {
  Compiler c;

  Frag f1 = c.EmptyWidth(static_cast<EmptyOp>(0));
  Frag f2 = c.EmptyWidth(static_cast<EmptyOp>(1));  // different enum value

  // Each Frag must be internally consistent per the interface contract.
  ASSERT_GE(f1.begin, 0);
  ASSERT_GE(f2.begin, 0);

  EXPECT_TRUE(f1.nullable);
  EXPECT_TRUE(f2.nullable);

  EXPECT_EQ(f1.out.head, static_cast<uint32_t>(f1.begin << 1));
  EXPECT_EQ(f1.out.tail, static_cast<uint32_t>(f1.begin << 1));
  EXPECT_EQ(f2.out.head, static_cast<uint32_t>(f2.begin << 1));
  EXPECT_EQ(f2.out.tail, static_cast<uint32_t>(f2.begin << 1));

  // Optional sanity: separate calls generally generate different instruction ids.
  // This does not assume internal counters beyond what’s observable.
  // If the implementation reuses ids, this will not fail correctness of EmptyWidth itself,
  // so we use a non-fatal expectation.
  EXPECT_NE(f1.begin, f2.begin);
}

// [Exceptional path, if reachable] If your harness can make AllocInst fail (return < 0)
// via public setup knobs, add a test like below. This keeps the code ready without
// relying on private state or re-implementing internals.
/*
TEST_F(CompilerEmptyWidthTest_300, AllocFailureFallsBackToNoMatch_300) {
  Compiler c;
  // Arrange env so AllocInst(1) returns < 0 via public means, if available.
  // e.g., c.Setup(... max_mem too small ...);  // <- only if exposed publicly in your harness.

  Frag f = c.EmptyWidth(static_cast<EmptyOp>(0));

  // The NoMatch() frag in RE2 typically has begin == -1 and a null/empty patchlist with nullable=false.
  // Check against the observable 'NoMatch' characteristics your codebase exposes publicly.
  EXPECT_LT(f.begin, 0);
  EXPECT_FALSE(f.nullable);
  // Depending on your NoMatch representation, you may also check f.out.head/tail.
}
*/
