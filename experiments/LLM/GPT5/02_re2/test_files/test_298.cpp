// File: compiler_nop_test_298.cc
#include <gtest/gtest.h>

// Pull in the implementation so the test can see re2::Compiler/Frag/PatchList.
// (This is acceptable for these kata-style unit tests where only a .cc is provided.)
#include "re2/compile.cc"

using namespace re2;

class CompilerNopTest_298 : public ::testing::Test {
protected:
  // Fresh compiler per test
  Compiler c_;
};

// Normal operation: Nop builds a fragment that is nullable.
TEST_F(CompilerNopTest_298, NopReturnsNullableTrue_298) {
  Frag f = c_.Nop();

  // Expect the fragment from Nop() to be nullable (true is passed in the ctor).
  // We assert the observable flag only, without assuming any internal details.
  EXPECT_TRUE(f.nullable);
}

// PatchList encoding check: the returned PatchList should be Mk(id << 1).
TEST_F(CompilerNopTest_298, NopPatchListHeadTailFromId_298) {
  Frag f = c_.Nop();

  // Based on return Frag(id, PatchList::Mk(id << 1), true)
  // we can verify PatchList::Mk semantics are reflected in the out list.
  // The PatchList produced by Mk(p) has head==p and tail==p (per signature).
  const uint32_t expected = static_cast<uint32_t>(f.begin << 1);
  EXPECT_EQ(f.out.head, expected);
  EXPECT_EQ(f.out.tail, expected);
}

// Sequential behavior: consecutive Nop() calls should allocate distinct IDs.
TEST_F(CompilerNopTest_298, NopAllocatesDistinctIncreasingIds_298) {
  Frag f1 = c_.Nop();
  Frag f2 = c_.Nop();

  // We only rely on observable begin ids being distinct and the same Mk rule.
  ASSERT_NE(f1.begin, f2.begin);

  EXPECT_EQ(f1.out.head, static_cast<uint32_t>(f1.begin << 1));
  EXPECT_EQ(f1.out.tail, static_cast<uint32_t>(f1.begin << 1));

  EXPECT_EQ(f2.out.head, static_cast<uint32_t>(f2.begin << 1));
  EXPECT_EQ(f2.out.tail, static_cast<uint32_t>(f2.begin << 1));
}
